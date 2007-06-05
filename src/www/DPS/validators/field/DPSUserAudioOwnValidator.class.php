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
class DPSUserAudioOwnValidator extends ValidatorRule {
	
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
			AND permissions & B '" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			return true;
		}
		
		// Check for if this audio is a jingle
		$sql = "SELECT COUNT(*) FROM v_tree_jingle
			WHERE userid = $userID
			AND id = $audioID
			AND permissions & B '" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
		$check = $db->getOne($sql);
		if ($check > 0) {
			return true;
		}
		
		// Check for if this is a piece of music
		$sql = "SELECT COUNT(*) FROM v_tree_music
			WHERE userid = $userID
			AND id = $audioID
			AND permissions & B '" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
		$check = $db->getOne($sql);
		if ($check > 0) {
			return true;
		}
		
		return "You do not own this track";
	}
}

?>
