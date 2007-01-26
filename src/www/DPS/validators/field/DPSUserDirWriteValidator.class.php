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
class DPSUserDirWriteValidator extends ValidatorRule {
	
  public function isValid(&$data) {
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
    $dirID = pg_escape_string($data);
		if(!is_numeric($dirID)) {
			return "Not a valid directory ID " . $dirID;
		}
    $flag = false;
    $auth = Auth::getInstance();
    $userID = pg_escape_string($auth->getUserID());

		$sql = "select count(*) from dirusers where userid = " . $userID . " and directory = " . pg_escape_string($dirID) . " 
						and (permissions = 'o' or permissions = 'rw' or permissions = 'w')";
    $check = $db->getOne($sql);
    if($check > 0) {
      $flag = true;
    } else {
			$sql = "select count(*) from dirgroups, groupmembers where groupmembers.userid = " . $userID . " and  
						groupmembers.groupid = dirgroups.groupid and directory = " . pg_escape_string($dirID) . " 
						and (dirgroups.permissions = 'o' or dirgroups.permissions = 'rw' or dirgroups.permissions = 'w')";
      $check = $db->getOne($sql);
      if($check > 0) {
				$flag = true;
      }
    }

    if(!$flag) {
      $flag = "You do not have access to modify that directory";
    }
    return $flag;
  }
	
}

?>
