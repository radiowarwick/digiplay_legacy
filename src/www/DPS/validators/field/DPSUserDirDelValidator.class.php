<?php
/**
* 
* @package DPS
*/

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
* Check that the user can remove a directory
*
*/
class DPSUserDirDelValidator extends ValidatorRule {
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$dirID = pg_escape_string($data);
		if(!is_numeric($dirID)) {
			return "Not a valid directory ID";
		}
		$auth = Auth::getInstance();
		$userID = pg_escape_string($auth->getUserID());
		$sql = "SELECT COUNT(*) FROM v_tree_dir
			WHERE id = $dirID
			AND userid = $userID
			AND permissions & B '" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
		} else {
			return "You do not have permission to delete that directory";
		}
	
		$sql = "SELECT COUNT(*) FROM v_tree_dir WHERE parent = $dirID";
		$count = $db->getOne($sql);
		if($count > 0) {
			return "The directory can not be deleted as it is not empty";
		}
		return true;
	}
}
?>
