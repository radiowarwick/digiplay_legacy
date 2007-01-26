<?php
/**
 * @package FrontEnds
 * @subpackage Common
 */
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');

class LoginViewer extends Viewer {
	protected function setupTemplate(){
		global $cfg;
		parent::setupTemplate();
		
		$loginTplID = MVCUtils::getTemplateID('login.tpl');
		
		$this->assign('fwdtid', end($this->templateIDStack));
		$this->assign('loginTplID', $loginTplID);
		
	}
}

?>
