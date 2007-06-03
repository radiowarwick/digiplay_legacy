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
class DPSUserCartsetOwnValidator extends ValidatorRule {
	
  public function isValid(&$data) {
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
    if(!is_numeric($data)) {
      return false;
    }
    $cartID = $data;
    $flag = false;
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();

    $sql = "select count(*) from cartsetsusers, cartwalls where cartsetsusers.userid = $userID 
            AND cartsetsusers.cartsetid = $cartID 
	    AND (cartsetsusers.permissions = 'o')";
    $check = $db->getOne($sql);
    if($check > 0) {
      $flag = true;
    } else {
      $sql = "select count(*) from cartsetsgroups, cartwalls, usersgroups where cartsetsgroups.groupid = usersgroups.groupid
	      AND usersgroups.userid = $userID AND cartsetsgroups.cartsetid = $cartID 
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
