<?php
/**
 *
 * @package DPS
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Confirms that the number is a valid 24-hour clock hour.
 *
 */
class DPS24HourValidator extends ValidatorRule {
	
	public function isValid(&$data){
		global $cfg;
		if(is_numeric($data) && $data >= 0 && $data <= 23) {
			return true;
		}
		return "Please enter a value between 0-23";
	}
	
}

?>
