<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSStationAwWallViewer extends Viewer {

	const module = 'DPS';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();

		$db = Database::getInstance($cfg['DPS']['dsn']);
		$awset = pg_escape_string($this->fieldData['awset']);
		$flag = false;
		if($awset != '' && is_numeric($awset)) {
			$sql = "SELECT count(*) from v_tree_aw_sets 
				WHERE v_tree_aw_sets.userid = " . $cfg['DPS']['systemUserID'] . " 
					AND v_tree_aw_sets.id = $awset 
					AND v_tree_aw_sets.permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
			$check = $db->getOne($sql);
			if($check > 0) {
				$flag = true;
			}
		}

		if($flag) {
			$page = pg_escape_string($this->fieldData['page']);
			if($page == "" || !is_numeric($page)){
				$page = 0;
			}

			$sql = "SELECT * FROM aw_walls 
			WHERE set_id = $awset AND page = $page";
			$awwall = $db->getRow($sql);

			$sql = "SELECT count(*) FROM aw_walls WHERE set_id = " . $awset;
			$pages = $db->getOne($sql);
			$pageArray = array();
			for($i=0; $i < $pages; $i++) {
				$pageArray[$i]['num'] = $i+1;
				$pageArray[$i]['id'] = $i;
				if($i == $page) {
					$pageArray[$i]['active'] = 't';
				}
			}
			for($i=0; $i<12; $i++) {
				$awitem = array();
				$sql = "SELECT aw_items.id AS id, aw_items.audio_id AS audio, 
					aw_items.text AS name, aw_items.item AS item, 
					audio.length_smpl AS len 
				FROM aw_walls, aw_items, audio 
				WHERE aw_walls.set_id = " . $awset . " 
					AND aw_walls.id = aw_items.wall_id 
					AND aw_items.audio_id = audio.id 
					AND aw_walls.page = " . $page . " 
					AND aw_items.item = " . $i;
				$awitem = $db->getRow($sql);
				$awitem['name'] = str_replace("\n","<br>",$awitem['name']);
				if(isset($awitem['id'])) {
					$mins = floor($awitem['len']/44100/60);
					$secs = round(($awitem['len'] - $mins*44100*60)/44100);
					if($mins != 0) {
						$awitem['length'] = $mins . "m " . $secs . "s";
					} else {
						$awitem['length'] = $secs . "s";
					}
					$sql = "SELECT aw_styles_props.value AS value, 
						aw_item_props.name AS name
					FROM aw_items, aw_styles, aw_styles_props, aw_props
					WHERE aw_items.id = " . $awitem['id'] . " 
						AND aw_items.style_id = aw_styles.id 
						AND aw_styles.id = aw_styles_props.style_id 
						AND aw_styles_props.prop_id = aw_props.id";
					$awitemprop = $db->getAll($sql);
					foreach($awitemprop as $prop) {
						if($prop['name'] == 'ForeColourRGB') {
							$awitem['ForeColour']['r'] = (int)((int)$prop['value'] / (256*256));
							$awitem['ForeColour']['g'] = (int)(($prop['value']
								-$awitem['ForeColour']['r']*256*256) / 256);
							$awitem['ForeColour']['b'] = (int)(($prop['value']
								-$awitem['ForeColour']['r']*256*256
								-$awitem['ForeColour']['g']*256));
						} elseif($prop['name'] == 'BackColourRGB') {
							$awitem['BackColour']['r'] = (int)((int)$prop['value'] / (256*256));
							$awitem['BackColour']['g'] = (int)(($prop['value']
								-$awitem['BackColour']['r']*256*256) / 256);
							$awitem['BackColour']['b'] = ($prop['value']
								-$awitem['BackColour']['r']*256*256
								-$awitem['BackColour']['g']*256);
						}
					}
				} else {
					$tawitem['name'] = '<b>[BLANK]</b>';
					$tawitem['ForeColour']['r'] = 100;
					$tawitem['ForeColour']['g'] = 100;
					$tawitem['ForeColour']['b'] = 100;
					$tawitem['BackColour']['r'] = 220;
					$tawitem['BackColour']['g'] = 220;
					$tawitem['BackColour']['b'] = 220;
				}
				$this->assign('awitem' . ($i+1), $tawitem);
			}
			$auth = Auth::getInstance();
			$userID = $auth->getUserID();

			if($awset != '' && is_numeric($awset)) {
				$sql = "SELECT count(*) FROM v_tree_aw_set 
					WHERE v_tree_aw_set.userid = " . $cfg['DPS']['systemUserID'] . " 
						AND v_tree_aw_set.id = $awset 
						AND v_tree_aw_set.permissions & B'" . $cfg['DPS']['fileW'] .
							"' = '" . $cfg['DPS']['fileW'] . "'";
				$check = $db->getOne($sql);
				if($check > 0) {
					$this->assign('editperm','t');
				}
			}

			$this->assign('audiowall',$awwall);
			$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
			$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(
				array(3,21,33), $userID));
			$this->assign('pagelink',$pageArray);
			$this->assign('awsetID',$awset);
		} else {
			$this->assign('permError','t');
		}
	}
}
?>
