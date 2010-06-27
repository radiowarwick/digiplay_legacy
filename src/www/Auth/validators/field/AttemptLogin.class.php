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
		
		BasicLogger::logMessage("checking login for '$user'", self::module, 'debug');
		if($auth->attemptLogin($user, $password)){
			BasicLogger::logMessage("successful login for '$user'", self::module, 'debug');
			return true;
		}else{
			BasicLogger::logMessage("failed login for '$user'", self::module, 'debug');
			return "Invalid username or password";
		}
	}
	
}

?>