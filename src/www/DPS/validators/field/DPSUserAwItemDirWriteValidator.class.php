<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that a user owns an awitem
 *
 */
class DPSUserAwItemDirWriteValidator extends ValidatorRule {
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(!is_numeric($data)) {
			return false;
		}
		
		$awitemID = $data;
		$flag = false;
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		
		$sql = "SELECT v_tree_aw_sets.parent FROM v_tree_aw_sets, aw_walls, aw_items
			WHERE v_tree_aw_sets.id = aw_walls.set_id
			AND aw_walls.id = aw_items.wall_id
			AND aw_items.id = $awitemID";
		$parentID = $db->getOne($sql);
		$sql = "SELECT COUNT(*) FROM v_tree_dir
			WHERE v_tree_dir.userid = $userID
			AND v_tree_dir.id = $parentID
			AND v_tree_dir.permissions & B'" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		}
		return "You can not perform that action";
}

?>
