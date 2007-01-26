<?php
/**
 * 
 * @package FrontEnds
 * @subpackage Auth
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that a string is a valid name
 * 
 * 
 */
class StringValidator extends ValidatorRule {
	
	public function isValid(&$data){
		global $cfg;
		$out = true;
        if(!preg_match("/^[a-z0-9]([ _a-z0-9]*[a-z0-9])|([a-z0-9]*)$/i",$data)) {
          $out = 'You have not entered a valid string';
        }
        return $out;
	}
	
}

?>
