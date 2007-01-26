<?php
/**
 * 
 * @package MVC
 * @subpackage Validators
 */

MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Validate an email address
 * 
 * Note: Will not accept IP based email addresses (e.g. user@123.45.67.89)
 */
class EmailValidator extends ValidatorRule {
	
	public function isValid(&$data){
		$pattern = "/^(([A-Za-z0-9]+_+)|([A-Za-z0-9]+\-+)|([A-Za-z0-9]+\.+)|([A-Za-z0-9]+\++))*[A-Za-z0-9]+@((\w+\-+)|(\w+\.))*\w{1,63}\.[a-zA-Z]{2,6}$/";
		if(preg_match($pattern, $data)){
			return true;
		}else{
			return "The email address you entered was invalid";
		}
	}
	
}

?>