<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that a user owns a cart
 *
 */
class DPSUserCartOwnValidator extends ValidatorRule {
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
		
		$sql = "SELECT COUNT(*) FROM v_tree_cartset, cartwalls, cartsaudio
				WHERE v_tree_cartset.userid = $userID
				AND v_tree_cartset.id = cartwalls.cartsetid
				AND cartwalls.id = cartsaudio.cartwallid
				AND cartsaudio.id = $cartID
				AND v_tree_cartset.permissions & B '" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		}
		return "You do not own that cartset";
}

?>
