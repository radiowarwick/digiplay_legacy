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
class ValidModelName extends ValidatorRule {
	
	public function isValid($data){
		global $cfg;
		
		$db = Database::getInstance($cfg['MVC']['dsn']);
		$data = $db->quoteSmart($data);
		$exists = $db->getOne("SELECT COUNT(*) FROM templates WHERE modelclassname = $data");
		if($exists == 0){
			return 'The specified model does not exist';
		}else{
			return true;
		}
	}
	
}

?>