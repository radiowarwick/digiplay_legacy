<?php
/**
*
* @package DPS
*/

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
* Check that a user can edit a show item.
*
*/
class DPSUserShowitemEditValidator extends ValidatorRule {
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(!is_numeric($data)) {
		return false;
		}
		$itemID = $data;
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
	
		$sql = "SELECT COUNT(*) FROM v_tree_showplan, showitems
			WHERE v_tree_showplan.userid = $userID
			AND v_tree_showplan.id = showitems.showplanid
			AND showitems.id = $itemID
			AND v_tree_showplan.permissions & B '" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		}
		return "You can not edit that showitem";
	}
}
?>
