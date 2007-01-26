<?php
/**
 * @package FrontEnds
 * @subpackage Auth
 */
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');

class AuthViewer extends Viewer {
	
	
	const module = 'AuthFrontEnd';
	
	protected function setupTemplate(){
		parent::setupTemplate();
	}
	
	public function SMARTY_getTemplateID($params){
		if(isset($params['name'])){
			return MVCUtils::getTemplateID($params['name']);
		}else{
			return '';
		}
	}
	
	protected function assignCustomFields($table, $rguid){
		
		global $cfg;
		
		if($table == "users"){
			$fields = $cfg['Auth']['userfields'];
			$idFieldName = 'userid';
		}elseif($table == "groups"){
			$fields = $cfg['Auth']['groupfields'];
			$idFieldName = 'id';
		}elseif($table == "realms"){
			$fields = $cfg['Auth']['realmfields'];
			$idFieldName = 'realmid';
		}else{
			throw new LoggedException("An invalid table ($table) was specified", 0, self::module, 'warning');
		}
		
		if(isset($fields) && count($fields) > 0 && isset($rguid)){
			
			$db = Database::getInstance($cfg['Auth']['dsn']);
			
			$sqlFields = join(',', array_flip($fields));
			
			$customFieldData = $db->getRow("SELECT $sqlFields FROM $table WHERE $idFieldName = '$rguid'");
			foreach ($fields as $fieldName => $niceName){
				$tmp = array();
				$tmp['fieldName'] = $fieldName;
				$tmp['niceName'] = $niceName;
				$tmp['value'] = $customFieldData[$fieldName];
				$customFields[] = $tmp;
			}
			
			$this->assign('customFields', $customFields);
		} else {
			$blankFields = array();
			foreach($fields as $fieldName => $niceName) {
				$tmp['fieldName'] = $fieldName;
				$tmp['niceName'] = $niceName;
				$tmp['value'] = '';
				$blankFields[] = $tmp;
			}
			$this->assign('customFields', $blankFields);
		}
	}
}

?>
