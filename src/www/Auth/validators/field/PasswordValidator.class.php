<?php
/**
 * 
 * @package FrontEnds
 * @subpackage Auth
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Validate a password
 * 
 * This will check to ensure a password contains valid characters.
 * This will <strong>not</strong> authenticate a user.
 * 
 * @todo Add some more checks
 */
class PasswordValidator extends ValidatorRule {
	
	public function isValid(&$data){
		$out = true;
		if(!isset($this->fieldData['changePassword'])){
			return true;
		}
		
		if(strlen($data) < 8){
			$out = "The password you entered was too short";
		}
		
		if(strlen($data) > 25){
			$out = "The password you entered was too long";
		}
		
		return $out;
	}
	
}

?>