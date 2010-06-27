<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that system has edit permissions on a audiowall item.
 *
 */
class DPSSystemAwItemEditValidator extends ValidatorRule {
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(!is_numeric($data)) {
			return false;
		}
		$awitemID = $data;
		
		$sql = "SELECT COUNT(*) FROM v_tree_aw_sets, aw_walls, aw_items 
			WHERE v_tree_aw_sets.userid = " . $cfg['DPS']['systemUserID'] . "
			AND v_tree_aw_sets.id = aw_walls.set_id
			AND aw_walls.id = aw_items.wall_id
			AND aw_items.id = $awitemID
			AND v_tree_aw_sets.permissions & B'" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		} else {
			return "You do not have access to edit that audiowall set";
		}
	}
}
?>
