<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check if a user can delete a script
 *
 */
class DPSUserScriptDirWriteValidator extends ValidatorRule {
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(!is_numeric($data)) {
			return "Invalid script ID";
		}
		$scriptID = $data;
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		
		$sql = "SELECT v_tree_script.parent FROM v_tree_script
			WHERE v_tree_script.id = $scriptID";
		$parentID = $db->getOne($sql);
		$sql = "SELECT COUNT(*) FROM v_tree_dir
			WHERE v_tree_dir.userid = $userID
			AND v_tree_dir.id = $parentID
			AND v_tree_dir.permissions & B'" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
		$check = $db->getOne($sql);
		if ($check > 0) {
			return true;
		}
		return "You can not perform that action";
	}
}
?>
