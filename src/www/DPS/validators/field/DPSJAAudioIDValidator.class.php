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
class DPSJAAudioIDValidator extends ValidatorRule {
	
  public function isValid(&$data) {
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
    if($data == '' || !is_numeric($data)) {
      return "Please select a Jingle or and Advert";
    }
    $audioID = pg_escape_string($data);
    $flag = false;

    $sql = "select count(*) from audio, audiotypes where audio.id = $audioID and audio.type = audiotypes.id AND (audiotypes.name = 'jingle' OR audiotypes.name = 'advert')";
    $check = $db->getOne($sql);
    if($check > 0) {
      $flag = true;
    }

    if(!$flag) {
      $flag = "Please select a Jingle or and Advert";
    }

    return $flag;
  }
	
}

?>
