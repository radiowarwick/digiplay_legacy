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
class DPSUserScriptDelValidator extends ValidatorRule {
	
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

    $sql = "select bit_or(permissions) from (select permissions from scriptsusers 
													where userid = $userID 
													AND scriptid = $scriptID 
													UNION (select scriptsgroups.permissions from scriptsgroups, usersgroups 
													where scriptsgroups.groupid = usersgroups.groupid AND 
													usersgroups.userid = $userID AND 
													scriptsgroups.scriptid = $scriptID)) AS Q1";
    $check = $db->getOne($sql);
    if(substr($check,1,1) == "1") {
      $flag = true;
    } 

    if(!$flag) {
     return "You do not have write permission to that script";
    }

    return $flag;
  }
	
}

?>
