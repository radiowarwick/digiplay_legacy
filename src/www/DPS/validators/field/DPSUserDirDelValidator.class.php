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

		$sql = "select sum(num) from (select count(*) as num from dirusers where userid = " . $userID . " and dirid = " . $dirID . " 
						and permissions & B'00100000' = '00100000') UNION (select count(*) as num from dirgroups, usersgroups where usersgroups.userid = " . $userID . " and  
						usersgroups.groupid = dirgroups.groupid and dirid = " . $dirID . " 
						and dirgroups.permissions & B'00100000' = '00100000') as Q1";
    $check = $db->getOne($sql);
    if($check > 0) {
      $flag = true;
    } else {
			$flag = "You do not have permission to delete that directory";
			return $flag;
		}

		$sql = "select count(*) from dir where parent = " . $dirID;
		$count = $db->getOne($sql);
		if($count > 0) {
			$flag = false;
		}
		
		$sql = "select count(*) from audiodir where dirid = " . $dirID;
		$count = $db->getOne($sql);
		if($count > 0) {
			$flag = false;
		}
		$sql = "select count(*) from scriptsdir where dirid = " . $dirID;
		$count = $db->getOne($sql);
		if($count > 0) {
			$flag = false;
		}
		$sql = "select count(*) from cartsetsdir where dirid = " . $dirID;
		$count = $db->getOne($sql);
		if($count > 0) {
			$flag = false;
		}
		$sql = "select count(*) from showplandir where dirid = " . $dirID;
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
