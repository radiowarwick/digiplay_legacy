<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that a given audio ID is either a jingle or an advert.
 *
 */
class DPSJAAudioIDValidator extends ValidatorRule {
	public function isValid(&$data) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if($data == '' || !is_numeric($data)) {
		return "Please select a Jingle or and Advert";
		}
		$audioID = pg_escape_string($data);
		
		$sql = "SELECT COUNT(*) FROM v_audio_adverts, v_audio_jingles
			WHERE v_audio_adverts.id = $audioID
			OR v_audio_jingles.id = $audioID";
		
		$check = $db->getOne($sql);
		if($check > 0) {
			return true
		}
		return "Please select a Jingle or and Advert";
	}
}
?>
