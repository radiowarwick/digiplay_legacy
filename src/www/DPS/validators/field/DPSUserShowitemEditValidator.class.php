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
class DPSUserShowitemEditValidator extends ValidatorRule {
	
  public function isValid(&$data) {
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
    if(!is_numeric($data)) {
      return false;
    }
    $itemID = $data;
    $flag = false;
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();

    $sql = "select count(*) from showplanusers, showitems 
						where showplanusers.userid = $userID AND 
						showplanusers.showplanid = showitems.showplanid AND 
						showitems.id = $itemID AND 
						showplanusers.permissions & B'" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
    $check = $db->getOne($sql);
    if($check > 0) {
      $flag = true;
    } else {
      $sql = "select count(*) from showplangroups, usersgroups, showitems 
							where showplangroups.groupid = usersgroups.groupid AND 
							usersgroups.userid = $userID AND 
							showplangroups.showplanid = showitems.showplanid 
							AND showitems.id = $itemID AND 
							showplangroups.permissions & B'" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
      $check = $db->getOne($sql);
      if($check > 0) {
	$flag = true;
      }
    }

    if(!$flag) {
      $flag = "You can not edit that showplan";
    }

    return $flag;
  }
	
}

?>
