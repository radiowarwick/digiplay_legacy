<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeViewer('MVCViewer', 'MVC');

class AddTemplateViewer extends MVCViewer {
	
	const module = 'MVCFrontEnd';
	
	protected function setupTemplate(){
		parent::setupTemplate();
		$this->assignTemplateNames();
		$this->assignModelNames();
		$this->assignViewerNames();
	}
	
	protected function assignTemplateNames(){
		
		global $cfg;
		
		$db = Database::getInstance($cfg['MVC']['dsn']);
		
		$physicalTemplates = MVCUtils::listPresent('template');
		
		$sql = "SELECT filename FROM templates";
		$dbTemplates = $db->getColumn($sql);
		
		$unusedTemplates = array_diff($physicalTemplates, $dbTemplates);
		
		if(count($unusedTemplates) > 0){
			$this->assign("unusedTemplates", $unusedTemplates);
		}
	}
	
	protected function assignModelNames(){
		
		global $cfg;
		
		$db = Database::getInstance($cfg['MVC']['dsn']);
		
		$physicalModels = MVCUtils::listPresent('model');
		
		for ($i=0; $i<count($physicalModels); $i++){
			$tmp = preg_split('/\./', $physicalModels[$i]);
			$physicalModels[$i] = $tmp[0];
		}
		
		if(count($physicalModels) > 0){
			$this->assign("models", $physicalModels);
		}
	}
	
	protected function assignViewerNames(){
		
		global $cfg;
		
		$db = Database::getInstance($cfg['MVC']['dsn']);
		
		$physicalViewers = MVCUtils::listPresent('viewer');
		
		for ($i=0; $i<count($physicalViewers); $i++){
			$tmp = preg_split('/\./', $physicalViewers[$i]);
			$physicalViewers[$i] = $tmp[0];
		}
		
		if(count($physicalViewers) > 0){
			$this->assign("viewers", $physicalViewers);
		}
	}
	
}

?>