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
 * Check that a realm does not contain any templates. This should be used before deletions
 * 
 * 
 */
class NoTemplatesInRealm extends ValidatorRule {
	
	public function isValid(&$data){
		global $cfg;
		$out = true;
		
		$sqldata = addslashes($data);
		$sql = "SELECT COUNT(*) FROM templates WHERE realmid = '$sqldata'";
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$count = $db->getOne($sql);
		
		if($count == 0){
			return true;
		}else{
			return "This realm contains $count template(s). All templates within this realm must be moved or deleted first.";
		}
	}
	
}

?>