<?php
/**
 * 
 * @package FrontEnds
 * @subpackage Auth
 */
 
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Validate a users login information
 * 
 * This validator will validate a users login/password. If the validation 
 * succeeds the user will be logged in.
 * 
 * @todo Add some more checks
 */
class AttemptLogin extends ValidatorRule {
	/**
	 * 
	 * The username to be logged in is taken from the $fieldData class 
	 * variable
	 */
	public function isValid(&$password){
		$user = $this->fieldData['authUser'];
		$auth = Auth::getInstance();
		$flag = false;
		BasicLogger::logMessage("checking login for '$user'", self::module, 'debug');
		if($auth->attemptLogin($user, $password)){
			BasicLogger::logMessage("successful login for '$user'", self::module, 'debug');
			$flag = true;
		}else{
			BasicLogger::logMessage("failed login for '$user'", self::module, 'debug');
			$flag = "Invalid username or password";
		}
		if(is_null($auth->getUserID())) {
		  $Nuser = array();
		  $Nuser['username'] = $auth->getUser();
		  $Nuser['enabled'] = 't';
		  $Nuser['id'] = "#id#";
		  $db = Database::getInstance($cfg['Auth']['dsn']);
		  $userID = $db->insert('users',$Nuser, true);
		  if(isset($cfg['Auth']['defaultNewUserGroup'])) {
		    $group = array();
		    $group['groupid'] = $cfg['Auth']['defaultNewUserGroup'];
		    $group['userid'] = $userID;
		    $db->insert('groupmembers',$group, true);
		  }
		  $auth->attemptLogin();
		    BasicLogger::logMessage("new user created for for '$user'", self::module, 'debug');
		}
		return $flag;
	}
	
}

?>
