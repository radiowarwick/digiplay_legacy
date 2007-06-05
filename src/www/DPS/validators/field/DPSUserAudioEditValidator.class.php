<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that the user can edit some audio.
 *
 */
class DPSUserAudioEditValidator extends ValidatorRule {
	
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
		$sql = "SELECT COUNT(*) FROM v_tree_advert
			WHERE userid = $userID
			AND id = $audioID
			AND permissions & B '" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		}
		
		// Check for if this audio is a jingle
		$sql = "SELECT COUNT(*) FROM v_tree_jingle
			WHERE userid = $userID
			AND id = $audioID
			AND permissions & B '" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
		$check = $db->getOne($sql);
		if ($check > 0) {
			return true;
		}
		
		// Check for if this is a piece of music
		$sql = "SELECT COUNT(*) FROM v_tree_music
			WHERE userid = $userID
			AND id = $audioID
			AND permissions & B '" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
		$check = $db->getOne($sql);
		if ($check > 0) {
			return true;
		}
		
		// If it reaches here then no permissions are present
		return "You do not have write permission on that track";
	}
}

?>
