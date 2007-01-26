<?php
/**
 * 
 * @package FrontEnds
 * @subpackage Auth
 */

include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that a username is unique
 * 
 * 
 */
class UniqueUsername extends ValidatorRule {
	
	public function isValid(&$data){
		global $cfg;
		$out = true;
		
		if(!isset($this->fieldData['userToEdit']) 
		  || $this->fieldData['userToEdit'] == ''){
		 	return 'No user ID was specified';	
		 }
		
		$sql = 'SELECT COUNT(*) FROM users WHERE username = ? AND userid != ?';
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$count = $db->getOne($sql, array($data, $this->fieldData['userToEdit']));
		
		if($count == 0){
			return true;
		}else{
			return "The username use chose is taken";
		}
	}
	
}

?>