<?php
/**
*
* @package DPS
*/

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
* Check that a user can edit an audiowall set.
*
*/
class DPSUserAwSetEditValidator extends ValidatorRule {
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
		$sql = "SELECT COUNT(*) FROM v_tree_aw_sets
			WHERE v_tree_aw_sets.userid = $userID
			AND v_tree_aw_sets.id = $awitemID
			AND v_tree_aw_sets.permissions & B'" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";

		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		}
	
		return "You do not have access to edit that audiowall set";
	}
}

?>
