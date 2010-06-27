<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that the system can edit a audiowall.
 *
 */
class DPSSystemAwWallEditValidator extends ValidatorRule {
	
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(!is_numeric($data)) {
			return false;
		}
		$awwallID = $data;
		
		$sql = "SELECT COUNT(*) FROM v_tree_aw_sets, aw_walls
			WHERE v_tree_aw_sets.userid = " . $cfg['DPS']['systemUserID'] . "
			AND v_tree_aw_sets.id = aw_walls.set_id
			AND aw_walls.id = $awwallID
			AND v_tree_aw_sets.permissions & B'" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		} else {
			return "You do not have access to edit that audiowall";
		}
	}
	
}

?>
