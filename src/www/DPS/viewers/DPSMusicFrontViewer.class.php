<?php
/**
 * @package DPS
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSMusicFrontViewer extends Viewer {
	
	const module = 'DPS';
	
	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$this->assign('RequestTrack',
			AuthUtil::getDetailedUserrealmAccess(array(3,21,29), $userID));
		$this->assign('Admin',
			AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		
	}
}
?>
