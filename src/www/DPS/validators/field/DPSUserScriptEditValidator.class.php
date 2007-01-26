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
class DPSUserScriptEditValidator extends ValidatorRule {
	
  public function isValid(&$data) {
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
    if(!is_numeric($data)) {
      return "Invalid script ID";
    }
    $scriptID = $data;
    $flag = false;
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();

    $sql = "select count(*) from scriptusers where userid = $userID AND scriptid = $scriptID AND  (permissions = 'o' or permissions = 'rw' or permissions = 'w')";
    $check = $db->getOne($sql);
    if($check > 0) {
      $flag = true;
    } else {
      $sql = "select count(*) from scriptgroups, groupmembers where scriptgroups.groupid = groupmembers.groupid
	      AND groupmembers.userid = $userID AND scriptgroups.scriptid = $scriptID 
	      AND (scriptgroups.permissions = 'o' or scriptgroups.permissions = 'rw' or scriptgroups.permissions = 'w')";
      $check = $db->getOne($sql);
      if($check > 0) {
				$flag = true;
      }
    }

    if(!$flag) {
     return "You do not have write permission to that script";
    }

    return $flag;
  }
	
}

?>
