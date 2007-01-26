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
		
		$tid = $this->fieldData['editid'];
		
		$this->assign('templateID', $tid);
		$this->assign('templateFileName', MVCUtils::getTemplateFileName($tid));
		$this->assign('templateModel', MVCUtils::getModelClassNameFromDB($tid));
		$this->assign('templateViewer', MVCUtils::getViewerClassNameFromDB($tid));
		$this->assign('templateRealm', MVCUtils::getRealmIDFromDB($tid));
	}
	
	protected function detectModels(){
		
	}
	
	protected function detectViewers(){
		
	}
	
	protected function detectTemplates(){
		
	}
	
}

?>