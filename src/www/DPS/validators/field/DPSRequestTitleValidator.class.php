<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that a string is a title
 *
 */
class DPSRequestTitleValidator extends ValidatorRule {
	
	public function isValid(&$data){
		global $cfg;
		if($data == "Title" || $data == "") {
			return "Please enter a Title";
		}
		return true;
	}
	
}

?>
