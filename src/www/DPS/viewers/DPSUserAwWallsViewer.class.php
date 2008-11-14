<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserAwWallsViewer extends Viewer {

	const module = 'DPS';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();

		$db = Database::getInstance($cfg['DPS']['dsn']);
		$awset = pg_escape_string($this->fieldData['awset']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$flag = false;
		
		if($awset != '' && is_numeric($awset)) {
			$sql = "SELECT count(*) from v_tree_aw_sets 
				WHERE v_tree_aw_sets.userid = $userID 
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
				$tawitem = array();
				$sql = "SELECT aw_items.id AS id, aw_items.audio_id AS audio, 
					aw_items.text AS name, aw_items.item AS item, 
					audio.length_smpl AS len 
				FROM aw_walls, aw_items, audio 
				WHERE aw_walls.set_id = " . $awset . " 
					AND aw_walls.id = aw_items.wall_id 
					AND aw_items.audio_id = audio.id 
					AND aw_walls.page = " . $page . " 
					AND aw_items.item = " . $i;
				$tawitem = $db->getRow($sql);
				$tawitem['name'] = str_replace("\n","<br>",$tawitem['name']);
				if(isset($tawitem['audio'])) {
					$mins = floor($tawitem['len']/44100/60);
					$secs = round(($tawitem['len'] - $mins*44100*60)/44100);
					if($mins != 0) {
						$tawitem['length'] = $mins . "m " . $secs . "s";
					} else {
						$tawitem['length'] = $secs . "s";
					}
					$sql = "SELECT aw_styles_props.value AS value,
							aw_props.name AS name
						FROM aw_items, aw_styles, aw_styles_props, aw_props
						WHERE aw_items.id = " . $tawitem['id'] . " 
							AND aw_items.style_id = aw_styles.id 
							AND aw_styles.id = aw_styles_props.style_id 
							AND aw_styles_props.prop_id = aw_props.id";
					$aw_prop = $db->getAll($sql);
					foreach($aw_prop as $prop) {
						if($prop['name'] == 'ForeColourRGB') {
							$tawitem['ForeColour']['r'] = (int)((int)$prop['value'] / (256*256));
							$tawitem['ForeColour']['g'] = (int)(($prop['value']
								-$tawitem['ForeColour']['r']*256*256) / 256);
							$tawitem['ForeColour']['b'] = (int)(($prop['value']
								-$tawitem['ForeColour']['r']*256*256
								-$tawitem['ForeColour']['g']*256));
						} elseif($prop['name'] == 'BackColourRGB') {
							$tawitem['BackColour']['r'] = (int)((int)$prop['value'] / (256*256));
							$tawitem['BackColour']['g'] = (int)(($prop['value']
								-$tawitem['BackColour']['r']*256*256) / 256);
							$tawitem['BackColour']['b'] = ($prop['value']
								-$tawitem['BackColour']['r']*256*256
								-$tawitem['BackColour']['g']*256);
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

			$sql = "SELECT count(*) from v_tree_aw_sets 
				WHERE v_tree_aw_sets.userid = $userID 
					AND v_tree_aw_sets.id = $awset 
					AND v_tree_aw_sets.permissions & B'" . $cfg['DPS']['fileW'] .
						"' = '" . $cfg['DPS']['fileW'] . "'";
			$check = $db->getOne($sql);
			if($check > 0) {
				$this->assign('editperm','t');
			}
			$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(
				array(3,21,33), $userID));
			$this->assign('awwall',$awwall);
			$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(
				array(1), $userID));
			$this->assign('studioAccess',AuthUtil::getDetailedUserrealmAccess(
				array(3,21,34), $userID));
			$this->assign('pagelink',$pageArray);
			$this->assign('awsetID',$awset);
		} else {
			$this->assign('permError','t');
		}
	}
}
?>
