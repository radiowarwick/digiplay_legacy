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
class IntValidator extends ValidatorRule {
	
	public function isValid(&$data){
		global $cfg;
		$out = true;
        if(!preg_match("/^[0-9]*$/i",$data)) {
          $out = false;
        }
        return $out;
	}
	
}

?>
