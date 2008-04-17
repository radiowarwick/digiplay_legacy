<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that a user can edit a cartwall
 *
 */
class DPSUserCartwallEditValidator extends ValidatorRule {
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(!is_numeric($data)) {
			return false;
		}
		$cartwallID = $data;
		$flag = false;
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		
		$sql = "SELECT COUNT(*) FROM v_tree_cartset, cartwalls
				WHERE v_tree_cartset.userid = $userID
				AND v_tree_cartset.id = cartwalls.cartsetid
				AND cartwalls.id = $cartwallID
				AND v_tree_cartset.permissions & B'" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		}
		return "You do not have permission to edit that cartwall";
	}
}

?>
