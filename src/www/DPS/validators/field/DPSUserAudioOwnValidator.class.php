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
class DPSUserAudioOwnValidator extends ValidatorRule {
	
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

    $sql = "select count(*) from audiousers where userid = $userID AND audio = $audioID AND  permissions = 'o'";
    $check = $db->getOne($sql);
    if($check > 0) {
      $flag = true;
    } else {
      $sql = "select count(*) from audiogroups, groupmembers where audiogroups.groupid = groupmembers.groupid
	      AND groupmembers.userid = $userID AND audiogroups.audio = $audioID 
	      AND (audiogroups.permissions = 'o')";
      $check = $db->getOne($sql);
      if($check > 0) {
	$flag = true;
      }
    }

    if(!$flag) {
      $flag = "You do not own that track";
    }

    return $flag;
  }
	
}

?>
