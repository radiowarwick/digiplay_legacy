<?php
/**
*
* @package DPS
*/

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
* Check if a user owns a audiowall
*
*/
class DPSUserAwWallOwnValidator extends ValidatorRule {
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(!is_numeric($data)) {
			return false;
		}
		$awwallID = $data;
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		
		$sql = "SELECT COUNT(*) FROM v_tree_aw_sets, aw_walls
			WHERE v_tree_aw_sets.userid = $userID
			AND v_tree_aw_sets.id = aw_walls.set_id
			AND aw_walls.id = $awwallID
			AND v_tree_aw_sets.permissions & B'" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		}
		return "You do not own that audiowall";
	}
}
?>
