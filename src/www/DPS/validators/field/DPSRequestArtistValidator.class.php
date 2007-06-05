<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that data is an artist name.
 *
 */
class DPSRequestArtistValidator extends ValidatorRule {
	
	public function isValid(&$data){
		global $cfg;
		if($data == "Artist" || $data == "") {
			return "Please enter an Artists name";
		}
		return true;
	}
	
}

?>
