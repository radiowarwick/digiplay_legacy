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
class DPSSystemCartDirWriteValidator extends ValidatorRule {
	
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(!is_numeric($data)) {
			return false;
		}
		$cartID = $data;
		$sql = "SELECT v_tree_cartset.parent FROM v_tree_cartset, cartwalls, cartsaudio
			WHERE v_tree_cartset.id = cartwalls.cartsetid
			AND cartwalls.id = cartsaudio.cartwallid
			AND cartsaudio.id = $cartID";
		$parentID = $db->getOne($sql);
		$sql = "SELECT COUNT(*) FROM v_tree_dir
			WHERE v_tree_dir.userid = " . $cfg['DPS']['systemUserID'] . "
			AND v_tree_dir.id = $parentID
			AND v_tree_dir.permissions & B'" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		} else {
			return "You can not perform that action";
		}
	}
	
}

?>
