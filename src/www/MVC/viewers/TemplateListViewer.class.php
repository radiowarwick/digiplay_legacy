<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeViewer('MVCViewer', 'MVC');

class TemplateListViewer extends MVCViewer {
	
	const module = 'MVCFrontEnd';
	
	protected function setupTemplate(){
		parent::setupTemplate();
		
		$this->assign('templateList', $this->makeList());
	}
	
	protected function makeList(){
		global $cfg;
		$db = Database::getInstance($cfg['MVC']['dsn']);
		
		$niceNames = array('ID');
		$customFields = "";
		if($cfg['MVC']['templatefields'] > 0){
			//Flip array as we want field names, not nice names
			//$fieldNames = array_flip($cfg['MVC']['templatefields']);
			$fieldNames = $cfg['MVC']['templatefields'];
			foreach($fieldNames as $field => $niceName){
				$modFieldNames[] = 'templates.' . $field;
				$niceNames[] = $niceName;
			}
			$customFields = join(',', $modFieldNames);
			$customFields = ',' . $customFields;
		}
		$niceNames[] = 'Realm Name';
		$sql = "SELECT templates.templateid $customFields, realms.name FROM templates, realms WHERE templates.realmid = realms.realmid";
		$result = $db->getAll($sql);
		array_unshift($result, $niceNames);
		return $result;
	}
	
}

?>