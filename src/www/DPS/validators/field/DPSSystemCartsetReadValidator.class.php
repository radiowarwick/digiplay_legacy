<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that the system can read a cartset.
 *
 */
class DPSSystemCartsetReadValidator extends ValidatorRule {
	
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
				AND permissions & B '" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		} else {
			return "You do not have access to read that cartset";
		}
	}
}

?>
