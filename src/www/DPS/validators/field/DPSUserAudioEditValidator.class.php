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
class DPSUserAudioEditValidator extends ValidatorRule {
	
  public function isValid(&$data) {
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
    if(!is_numeric($data)) {
      return false;
    }
    $audioID = $data;
    $flag = false;
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();

    $sql = "select count(*) from audiousers where userid = $userID AND audioid = $audioID AND (permissions = 'o' or permissions = 'w' or permissions = 'rw')";
    $check = $db->getOne($sql);
    if($check > 0) {
      $flag = true;
    } else {
      $sql = "select count(*) from audiogroups, usersgroups where audiogroups.groupid = usersgroups.groupid
	      AND usersgroups.userid = $userID AND audiogroups.audioid = $audioID 
	      AND (audiogroups.permissions = 'o' or audiogroups.permissions = 'w' or audiogroups.permissions = 'rw')";
      $check = $db->getOne($sql);
      if($check > 0) {
	$flag = true;
      }
    }

    if(!$flag) {
      $flag = "You do not have write permission on that track";
    }

    return $flag;
  }
	
}

?>
