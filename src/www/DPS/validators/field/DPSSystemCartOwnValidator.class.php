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
class DPSSystemCartOwnValidator extends ValidatorRule {
	
  public function isValid(&$data) {
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
    if(!is_numeric($data)) {
      return false;
    }
    $cartID = $data;
    $flag = false;

    $sql = "select count(*) from cartsetsusers, cartwalls, cartsaudio where cartsetsusers.userid = " . $cfg['DPS']['systemUserID'] . " 
            AND cartsetsusers.cartsetid = cartwalls.cartsetid AND cartwalls.id = cartsaudio.cartwallid and cartsaudio.id = $cartID 
	    AND (cartsetsusers.permissions = 'o')";
    $check = $db->getOne($sql);
    if($check > 0) {
      $flag = true;
    } else {
      $sql = "select count(*) from cartsetsgroups, cartwalls, cartsaudio, usersgroups where cartsetsgroups.groupid = usersgroups.groupid
	      AND usersgroups.userid = " . $cfg['DPS']['systemUserID'] . " AND cartsetsgroups.cartsetid = cartwalls.cartsetid AND cartwalls.id = cartsaudio.cartwallid and cartsaudio.id = $cartID 
	      AND (cartsetsgroups.permissions = 'o')";
      $check = $db->getOne($sql);
      if($check > 0) {
	$flag = true;
      }
    }

    if(!$flag) {
      $flag = "You do not own that cartset";
    }

    return $flag;
  }
	
}

?>
