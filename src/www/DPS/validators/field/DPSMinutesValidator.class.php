<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that data is between 0 and 59
 *
 */
class DPSMinutesValidator extends ValidatorRule {
	
	public function isValid(&$data){
		global $cfg;
		if(is_numeric($data) && $data >= 0 && $data <= 59) {
			return true;
		}
		return "Please enter a value between 0-59";
	}
	
}

?>
