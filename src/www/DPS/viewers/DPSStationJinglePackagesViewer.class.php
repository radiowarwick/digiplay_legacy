<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSStationJinglePackagesViewer extends Viewer {

	const module = 'DPS';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();

		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$loc = 1;
		$sql = "SELECT * from jinglepkgs";

		$jinglepkgs = $db->getAll($sql);

		$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,33), $userID));
		$this->assign('access_sue',AuthUtil::getDetailedUserrealmAccess(
			array(3,20,24), $userID));
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		$this->assign('jinglepkgs', $jinglepkgs);
	}
}
?>
