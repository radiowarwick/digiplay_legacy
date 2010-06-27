<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserEditAwItemViewer extends Viewer {

	const module = 'DPS';
	protected $activeNode = 'foldersTree';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();

		$db = Database::getInstance($cfg['DPS']['dsn']);
		$awitemID = pg_escape_string($this->fieldData['awitemID']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();

		if($awitemID == "New" || !is_numeric($awitemID)) {
			$awwallID = pg_escape_string($this->fieldData['awwallID']);
			$flag = false;
			if($awwallID != '' && is_numeric($awwallID)) {
				$sql = "SELECT count(*) from v_tree_aw_sets, aw_walls 
				WHERE v_tree_aw_sets.userid = $userID 
					AND v_tree_aw_sets.id = aw_walls.set_id 
					AND aw_walls.id = $awwallID 
					AND v_tree_aw_sets.permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
				$check = $db->getOne($sql);
				if($check > 0) {
					$flag = true;
				} else {
					$flag = false;
				}
			}
			if($flag) {
				$this->assign('new', 't');
				$this->assign('awwallID', $this->fieldData['awwallID']);
				$this->assign('awitemPos', $this->fieldData['awitemPos']);
			} else {
				$this->assign('permError', 't');
			}
		} else {
			$flag = false;
			if($awitemID != '' && is_numeric($awitemID)) {
				$sql = "SELECT count(*) from v_tree_aw_sets, aw_walls, aw_items 
				WHERE v_tree_aw_sets.userid = $userID 
					AND aw_items.wall_id = aw_walls.id 
					AND v_tree_aw_sets.id = aw_walls.set_id 
					AND aw_items.id = $awitemID 
					AND v_tree_aw_sets.permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
				$check = $db->getOne($sql);
				if($check > 0) {
					$flag = true;
				} else {
					$flag = false;
				}
			}
			if($flag) {
				// aw_walls
				$sql = "SELECT aw_items.id AS id, aw_items.text AS text,
        				aw_items.audio_id AS audioID, aw_walls.set_id AS awset,
						aw_items.style_id AS styleID,aw_items.item AS item 
						FROM aw_items, aw_walls 
						WHERE aw_items.wall_id = aw_walls.id AND 
						aw_items.id = " . $awitemID;
				$awitem = $db->getRow($sql);
				$this->assign('awitemInfo', $awitem);
			} else {
				$this->assign('permError', 't');
			}
		}
		
		//CHECK IF ANYONE ELSE CAN READ PERMS (IE NEED TO USE ALL USERS TREE)
		if($flag) {
			$sql= "SELECT * FROM aw_styles ORDER BY name asc";
			$styles = $db->getAll($sql);

			$auth = Auth::getInstance();
			$userID = $auth->getUserID();
			
			//CHECK IF ANYONE ELSE CAN READ PERMS (IE NEED TO USE ALL USERS TREE)
			if($awitemID == "New") {
				$sql = "SELECT count(*) from v_tree_aw_sets_explicit, aw_walls 
				WHERE v_tree_aw_sets_explicit.cause = {$cfg['DPS']['allusersgroupid']}
					AND v_tree_aw_sets_explicit.id = aw_walls.set_id
					AND aw_walls.id = $awwallID
					AND v_tree_aw_sets_explicit.causetype = 'group'
					AND v_tree_aw_sets_explicit.permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
				$user_count = $db->getOne($sql);
				$sql = "SELECT count(*) from v_tree_aw_sets_inherited, aw_walls 
				WHERE v_tree_aw_sets_inherited.cause = {$cfg['DPS']['allusersgroupid']}
					AND v_tree_aw_sets_inherited.id = aw_walls.set_id
					AND aw_walls.id = $awwallID
					AND v_tree_aw_sets_inherited.causetype = 'group'
					AND v_tree_aw_sets_inherited.permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
				$user_count = $user_count + $db->getOne($sql);
			} else {
				$sql = "SELECT count(*) from v_tree_aw_sets_explicit, aw_walls, aw_items 
				WHERE v_tree_aw_sets_explicit.cause = {$cfg['DPS']['allusersgroupid']}
					AND v_tree_aw_sets_explicit.id = aw_walls.set_id
					AND aw_walls.id = aw_items.wall_id
					AND aw_items.id = $awitemID
					AND v_tree_aw_sets_explicit.causetype = 'group'
					AND v_tree_aw_sets_explicit.permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
				$user_count = $db->getOne($sql);
				$sql = "SELECT count(*) from v_tree_aw_sets_inherited, aw_walls, aw_items 
				WHERE v_tree_aw_sets_inherited.cause = {$cfg['DPS']['allusersgroupid']}
					AND v_tree_aw_sets_inherited.id = aw_walls.set_id
					AND aw_walls.id = aw_items.wall_id
					AND aw_items.id = $awitemID
					AND v_tree_aw_sets_inherited.causetype = 'group'
					AND v_tree_aw_sets_inherited.permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
				$user_count = $user_count + $db->getOne($sql);
			}

			if($user_count == 0) {
				$this->assign('treeUser', 'system');
			} else {
				$this->assign('treeUser', 'group');
			}

			$this->assign('activeNode', $this->activeNode);
			$this->assign('treeType', 'aj');
			$this->assign('styles', $styles);
		}
	}
}
?>
