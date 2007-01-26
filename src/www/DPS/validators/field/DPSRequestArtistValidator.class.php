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
class DPSRequestArtistValidator extends ValidatorRule {
	
  public function isValid(&$data){
    global $cfg;
    $out = true;
    if($data == "Artist" || $data == "") {
      $out = "Please enter an Artists name";
    }
    return $out;
  }
	
}

?>
