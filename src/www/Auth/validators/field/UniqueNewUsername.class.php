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
 * Check that a new username is unique
 * 
 * 
 */
class UniqueNewUsername extends ValidatorRule {
	
	public function isValid(&$data){
		global $cfg;
		$out = true;
		
		$sql = 'SELECT COUNT(*) FROM users WHERE username = ?';
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$count = $db->getOne($sql, array($data));
		
		if($count == 0){
			return true;
		}else{
			return "The username use chose is taken";
		}
	}
	
}

?>