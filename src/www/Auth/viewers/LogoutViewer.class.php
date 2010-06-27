<?php
/**
 * @package FrontEnds
 * @subpackage Auth
 */
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');

MVCUtils::includeViewer('AuthViewer', 'Auth');

class LogoutViewer extends AuthViewer {
	protected function setupTemplate(){
		$auth = Auth::getInstance();
		$auth->logout();
		
		parent::setupTemplate();
	}
}

?>