<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that aa user owns a cartset
 *
 */
class DPSUserCartsetOwnValidator extends ValidatorRule {
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
				AND v_tree_cartset.permissions & B '" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		}
	
		return "You do not own that cartset";
	}
}

?>
