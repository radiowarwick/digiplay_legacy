<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that a user owns a show.
 *
 */
class DPSUserShowOwnValidator extends ValidatorRule {
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(!is_numeric($data)) {
			return false;
		}
		$showID = $data;
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		
		$sql = "SELECT COUNT(*) FROM v_tree_showplan
			WHERE userid = $userID
			AND id = $showID
			AND permissions & B '" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		}
		return "You do not own that showplan.";
	}
}
?>
