<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that the system owns a cartset
 *
 */
class DPSSystemCartsetOwnValidator extends ValidatorRule {
	
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(!is_numeric($data)) {
			return false;
		}
		$cartID = $data;
	
		$sql = "SELECT COUNT(*) FROM v_tree_cartset
			WHERE userid = " . $cfg['DPS']['systemUserID'] . "
			AND id = $cartID
			AND permissions & B '" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		} else {
			return "You do not own that cartset";
		}
	}
}

?>
