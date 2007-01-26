<?php
/**
 * @package FrontEnds
 * @subpackage Auth
 */
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');

MVCUtils::includeViewer('AuthViewer', 'Auth');

class DPSLogoutViewer extends AuthViewer {
	protected function setupTemplate(){
		parent::setupTemplate();
		$auth = Auth::getInstance();
		$auth->logout();
	}
}

?>
