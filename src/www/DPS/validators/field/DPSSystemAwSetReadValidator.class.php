<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that the system can read a audiowall set.
 *
 */
class DPSSystemAwSetReadValidator extends ValidatorRule {
	
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(!is_numeric($data)) {
			return false;
		}
		$awitemID = $data;
	
		$sql = "SELECT COUNT(*) FROM v_tree_aw_sets
				WHERE userid = " . $cfg['DPS']['systemUserID'] . "
				AND id = $awitemID
				AND permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		} else {
			return "You do not have access to read that audiowall set";
		}
	}
}

?>
