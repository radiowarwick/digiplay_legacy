<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check if a user owns a track.
 *
 */
class DPSUserAudioDirWriteValidator extends ValidatorRule {
	
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(!is_numeric($data)) {
			return false;
		}
		$audioID = $data;
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		
		// Check for if this audio is an advert
		$sql = "SELECT parent FROM v_tree_audio
			WHERE id = $audioID";
		$parentID = $db->getOne($sql);

		$sql = "SELECT COUNT(*) FROM v_tree_dir
			WHERE v_tree_dir.userid = $userID
			AND v_tree_dir.id = $parentID
			AND v_tree_dir.permissions & B'" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		} else {
			return "You can not perform that action";
		}
	}
}

?>
