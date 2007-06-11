<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check if a user can edit a script
 *
 */
class DPSUserScriptEditValidator extends ValidatorRule {
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(!is_numeric($data)) {
			return "Invalid script ID";
		}
		$scriptID = $data;
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		
		$sql = "SELECT COUNT(*) FROM v_tree_script
				WHERE userid = $userID
				AND id = $scriptID
				AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
		$check = $db->getOne($sql);
		if ($check > 0) {
			return true;
		}
		return "You do not have write permission to that script";
	}
}
?>
