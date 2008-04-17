<?php
/**
 * 
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that a user can read a cartset
 *
 */
class DPSUserCartsetReadValidator extends ValidatorRule {
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(!is_numeric($data)) {
			return false;
		}
		$cartID = $data;
		$flag = false;
	
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$sql = "SELECT COUNT(*) FROM v_tree_cartset
				WHERE v_tree_cartset.userid = $userID
				AND v_tree_cartset.id = $cartID
				AND v_tree_cartset.permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		}
	
		return "You do not have permission to read that cartset";
	}
}


?>
