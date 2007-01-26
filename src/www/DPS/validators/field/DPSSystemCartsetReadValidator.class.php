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
class DPSSystemCartsetReadValidator extends ValidatorRule {
	
  public function isValid(&$data) {
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
    if(!is_numeric($data)) {
      return false;
    }
    $cartID = $data;
    $flag = false;

    $sql = "select count(*) from cartsetsusers where cartsetsusers.userid = " . $cfg['DPS']['systemUserID'] . " 
            AND cartsetsusers.cartsetid = $cartID 
	    AND (cartsetsusers.permissions = 'o' or cartsetsusers.permissions = 'r' or cartsetsusers.permissions = 'rw')";
    $check = $db->getOne($sql);
    if($check > 0) {
      $flag = true;
    } else {
      $sql = "select count(*) from cartsetsgroups, groupmembers where cartsetsgroups.groupid = groupmembers.groupid
	      AND groupmembers.userid = " . $cfg['DPS']['systemUserID'] . " AND cartsetsgroups.cartsetid = $cartID 
	      AND (cartsetsgroups.permissions = 'o' or cartsetsgroups.permissions = 'r' or cartsetsgroups.permissions = 'rw')";
      $check = $db->getOne($sql);
      if($check > 0) {
	$flag = true;
      }
    }

    if(!$flag) {
      $flag = "You do not have access to read that cartset";
    }

    return $flag;
  }
	
}

?>
