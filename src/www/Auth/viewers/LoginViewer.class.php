<?php
/**
 * @package FrontEnds
 * @subpackage Auth
 */
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');

MVCUtils::includeViewer('AuthViewer', 'Auth');

class LoginViewer extends AuthViewer {
	protected function setupTemplate(){
		global $cfg;
		parent::setupTemplate();
		
		$loginTplID = MVCUtils::getTemplateID('login.tpl');
		
		$this->assign('loginTplID', $loginTplID);
	}
}

?>