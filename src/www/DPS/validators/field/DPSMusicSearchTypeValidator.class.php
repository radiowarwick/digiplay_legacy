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
class DPSMusicSearchTypeValidator extends ValidatorRule {
	
  public function isValid(&$data){
    global $cfg;
    $out = "Please select a valid search type";
    if($data == "Both" || $data == "Title" || $data == "Artist") {
      $out = true;
    }
    return $out;
  }
	
}

?>
