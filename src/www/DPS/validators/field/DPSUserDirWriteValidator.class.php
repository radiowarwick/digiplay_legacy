<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that the user can write to the directory.
 *
 */
class DPSUserDirWriteValidator extends ValidatorRule {
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$dirID = pg_escape_string($data);
		if(!is_numeric($dirID)) {
			return "Not a valid directory ID";
		}
		$flag = false;
		$auth = Auth::getInstance();
		$userID = pg_escape_string($auth->getUserID());
		
		$sql = "SELECT COUNT(*) FROM v_tree_dir
			WHERE id = $dirID
			AND userid = $userID
			AND permissions & B '" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		} else {
			return "You do not have permission to write to that directory";
		}
	}
?>
