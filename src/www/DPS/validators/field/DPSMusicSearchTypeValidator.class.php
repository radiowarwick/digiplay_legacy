<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that a string is a valid search type
 *
 */
class DPSMusicSearchTypeValidator extends ValidatorRule {
	
	public function isValid(&$data){
		global $cfg;
		if($data == "Both" || $data == "Title" || $data == "Artist" || $data == "Album" ) {
			return true;
		}
		return "Please select a valid search type";
	}
	
}

?>
