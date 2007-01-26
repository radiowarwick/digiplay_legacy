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
class Logout extends ValidatorRule {
	/**
	 * 
	 * The username to be logged in is taken from the $fieldData class 
	 * variable
	 */
	public function isValid(){
		$auth = Auth::getInstance();

		BasicLogger::logMessage("loging out '$auth->getUsername()'", self::module, 'debug');
		$auth->logout();
		return true
	}
	
}

?>
