<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that the system owns a audiowall set
 *
 */
class DPSSystemAwSetOwnValidator extends ValidatorRule {
	
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
			AND permissions & B'" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		} else {
			return "You do not own that audiowall set";
		}
	}
}

?>
