<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserFileViewer extends Viewer {

	const module = 'DPS';
	protected $activeNode = 'foldersTree';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$this->assign('treeType','jacspm');
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(
			array(1), $userID));
	}
}
?>
