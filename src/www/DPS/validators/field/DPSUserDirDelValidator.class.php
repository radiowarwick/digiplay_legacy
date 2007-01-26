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
class DPSUserDirDelValidator extends ValidatorRule {
	
  public function isValid(&$data) {
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
    $dirID = pg_escape_string($data);
    if(!is_numeric($dirID)) {
			return "Not a valid directory ID";
    }
    $flag = false;
    $auth = Auth::getInstance();
    $userID = pg_escape_string($auth->getUserID());

		$sql = "select count(*) from dirusers where userid = " . $userID . " and directory = " . $dirID . " 
						and (permissions = 'o' or permissions = 'rw' or permissions = 'w')";
    $check = $db->getOne($sql);
    if($check > 0) {
      $flag = true;
    } else {
			$sql = "select count(*) from dirgroups, groupmembers where groupmembers.userid = " . $userID . " and  
						groupmembers.groupid = dirgroups.groupid and directory = " . $dirID . " 
						and (dirgroups.permissions = 'o' or dirgroups.permissions = 'rw' or dirgroups.permissions = 'w')";
      $check = $db->getOne($sql);
      if($check > 0) {
				$flag = true;
      }
    }

		$sql = "select count(*) from dir where parent = " . $dirID;
		$count = $db->getOne($sql);
		if($count > 0) {
			$flag = false;
		}
		
		$sql = "select count(*) from audiodir where directory = " . $dirID;
		$count = $db->getOne($sql);
		if($count > 0) {
			$flag = false;
		}
		$sql = "select count(*) from scriptsdir where dir = " . $dirID;
		$count = $db->getOne($sql);
		if($count > 0) {
			$flag = false;
		}
		$sql = "select count(*) from cartsetsdir where dir = " . $dirID;
		$count = $db->getOne($sql);
		if($count > 0) {
			$flag = false;
		}
		$sql = "select count(*) from showplandir where dir = " . $dirID;
		$count = $db->getOne($sql);
		if($count > 0) {
			$flag = false;
		}

    if(!$flag) {
      $flag = "That directory can not be deleted";
    }
    return $flag;
  }
	
}

?>
