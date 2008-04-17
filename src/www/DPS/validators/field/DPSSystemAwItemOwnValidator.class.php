<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that a cart is owned by the system.
 *
 */
class DPSSystemCartOwnValidator extends ValidatorRule {
	
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(!is_numeric($data)) {
		return false;
		}
		$cartID = $data;
		
		$sql = "SELECT COUNT(*) FROM v_tree_cartset, cartwalls, cartsaudio
			WHERE v_tree_cartset.userid = " . $cfg['DPS']['systemUserID'] . "
			AND v_tree_cartset.id = cartwalls.cartsetid
			AND cartwalls.id = cartsaudio.cartwallid
			AND cartsaudio.id = $cartID
			AND v_tree_cartset.permissions & B'" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		} else {
			return "You do not own that cartset";
		}
	}
	
}

?>
