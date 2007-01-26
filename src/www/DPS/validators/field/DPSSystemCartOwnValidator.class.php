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
            AND cartsetsusers.cartsetid = cartwalls.cartset AND cartwalls.id = cartsaudio.cartwall and cartsaudio.id = $cartID 
	    AND (cartsetsusers.permissions = 'o')";
    $check = $db->getOne($sql);
    if($check > 0) {
      $flag = true;
    } else {
      $sql = "select count(*) from cartsetsgroups, cartwalls, cartsaudio, groupmembers where cartsetsgroups.groupid = groupmembers.groupid
	      AND groupmembers.userid = " . $cfg['DPS']['systemUserID'] . " AND cartsetsgroups.cartsetid = cartwalls.cartset AND cartwalls.id = cartsaudio.cartwall and cartsaudio.id = $cartID 
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
