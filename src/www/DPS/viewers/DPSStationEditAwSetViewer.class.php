<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSStationEditAwSetViewer extends Viewer {

	const module = 'DPS';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();

		$db = Database::getInstance($cfg['DPS']['dsn']);
	
		$awset = pg_escape_string($this->fieldData['awset']);
		$page = pg_escape_string($this->fieldData['page']);

		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$flag = false;
		if($awset != '' && is_numeric($awset)) {
			$sql = "SELECT count(*) from v_tree_aw_sets 
				WHERE v_tree_aw_sets.userid = " . $cfg['DPS']['systemUserID'] . " 
					AND v_tree_aw_sets.id =  $awset 
					AND v_tree_aw_sets.permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
			$check = $db->getOne($sql);
			if($check > 0) {
				$flag = true;
			}
		}
		if($flag) {
			if($page == "" || !is_numeric($page)){
				$page = 0;
			}

			$sql = "SELECT * FROM aw_walls 
				WHERE set_id = $awset AND page = $page";
			$awwall = $db->getRow($sql);
			if($awwall == null) {
				$page = 0;
				$sql = "SELECT * FROM aw_walls 
					WHERE set_id = $awset AND page = $page";
				$awwall = $db->getRow($sql);
			}

			$sql = "SELECT count(*) FROM aw_walls WHERE set_id = " . $awset;
			$pages = $db->getOne($sql);
			$pageArray = array();
			for($i=0; $i < $pages; $i++) {
				$pageArray[$i]['num'] = $i+1;
				$pageArray[$i]['id'] = $i;
			}

			for($i=0; $i<12; $i++) {
				$tawitem = array();
				$sql = "SELECT aw_items.id AS id, aw_items.audioid AS audio,
								aw_items.text AS name, aw_items.item AS item,
								audio.length_smpl AS len, audio.title AS title 
							FROM aw_walls, aw_items, audio 
							WHERE aw_walls.set_id = $awset
							AND aw_walls.id = aw_items.wall_id 
							AND aw_items.audioid = audio.id 
							AND aw_walls.page = $page 
							AND aw_items.item = $i";
				$tawitem = $db->getRow($sql);
				$tawitem['name'] = str_replace("\n","<br>",$tawitem['name']);
				if(isset($tawitem['id'])) {
					$mins = floor($tawitem['len']/44100/60);
					$secs = round(($tawitem['len'] - $mins*44100*60)/44100);
					if($mins != 0) {
						$tawitem['length'] = $mins . "m " . $secs . "s";
					} else {
						$tawitem['length'] = $secs . "s";
					}
					$sql = "SELECT aw_styles_props.value as value,
							aw_props.name as name
						FROM aw_items, aw_styles, aw_styles_props, 
								aw_props
						WHERE aw_items.id = " . $tawitem['id'] . "
						AND aw_items.style_id = aw_styles.id  
						AND aw_styles.id = aw_styles_props.style_id 
						AND aw_styles_props.prop_id = aw_props.id"; 
					$awprop = $db->getAll($sql);
					foreach($awprop as $prop) {
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
					$tawitem['name'] = '';
					$tawitem['audioid'] = 'none';
					$tawitem['ForeColour']['r'] = 0;
					$tawitem['ForeColour']['g'] = 0;
					$tawitem['ForeColour']['b'] = 0;
					$tawitem['BackColour']['r'] = 255;
					$tawitem['BackColour']['g'] = 255;
					$tawitem['BackColour']['b'] = 255;
				}
				$this->assign('awitem' . ($i+1), $tawitem);
			}

			//IF SYSTEM OWNS THIS, CHECK TO SEE IF OTHER PEOPLE HAVE READ/WRITE
			$sql = "SELECT parent FROM v_tree_aw_sets WHERE id = $awset";
			$dirID = $db->getOne($sql);
			$sql = "SELECT count(*) 
				FROM v_tree_dir 
				WHERE v_tree_dir.id = $dirID
					AND v_tree_dir.userid = {$cfg['DPS']['systemUserID']}
					AND v_tree_dir.permissions & B'" . $cfg['DPS']['fileW'] .
						"' = '" . $cfg['DPS']['fileW'] . "'";
			$check = $db->getOne($sql);
			if($check > 0) {
				$this->assign('owner','t');
				$sql = "SELECT count(*) from v_tree_aw_sets_explicit 
				WHERE cause = {$cfg['DPS']['allusersgroupid']}
					AND id = $awset 
					AND causetype = 'group'
					AND permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
				$check = $db->getOne($sql);
				$sql = "SELECT count(*) from v_tree_aw_sets_inherited 
				WHERE cause = {$cfg['DPS']['allusersgroupid']}
					AND id = $awset 
					AND causetype = 'group'
					AND permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
				$check = $check + $db->getOne($sql);
				if($check > 0) {
					$this->assign('groupread','t');
				}
				$sql = "SELECT count(*) from v_tree_aw_sets_explicit 
				WHERE cause = {$cfg['DPS']['allusersgroupid']}
					AND id = $awset 
					AND causetype = 'group'
					AND permissions & B'" . $cfg['DPS']['fileW'] .
						"' = '" . $cfg['DPS']['fileW'] . "'";
				$check = $db->getOne($sql);
				$sql = "SELECT count(*) from v_tree_aw_sets_inherited 
				WHERE cause = {$cfg['DPS']['allusersgroupid']}
					AND id = $awset 
					AND causetype = 'group'
					AND permissions & B'" . $cfg['DPS']['fileW'] .
						"' = '" . $cfg['DPS']['fileW'] . "'";
				$check = $check + $db->getOne($sql);
				if($check > 0) {
					$this->assign('groupwrite','t');
				}
			}

			$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(
				array(3,21,33), $userID));
			$this->assign('StationAwSet','t', $userID);
			$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
			$this->assign('pagelink',$pageArray);
			$this->assign('awwall',$awwall);
			$this->assign('awsetID',$awset);
		} else {
			$this->assign('permError','t');
		}
	}
}
?>
