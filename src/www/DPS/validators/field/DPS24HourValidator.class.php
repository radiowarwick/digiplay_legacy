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
class DPS24HourValidator extends ValidatorRule {
	
  public function isValid(&$data){
    global $cfg;
    $out = "Please enter a value between 0-23";
    if(is_numeric($data) && $data >= 0 && $data <= 23) {
      $out = true;
    }
    return $out;
  }
	
}

?>
