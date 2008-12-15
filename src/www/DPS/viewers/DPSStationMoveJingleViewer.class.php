<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSStationMoveJingleViewer extends Viewer {

	const module = 'DPS';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();

		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();

		$audioID = pg_escape_string($this->fieldData['audioID']);

		$sql = "SELECT jinglepkgid FROM audiojinglepkgs WHERE audioid = $audioID";
		$jinglepkgID = $db->getOne($sql);

		$sql = "SELECT name FROM jinglepkgs WHERE id = $jinglepkgID";
		$currentpkg = $db->getOne($sql);
		if($currentpkg == '') {
			$currentpkg = 'Default';
		}

		$sql = "SELECT title FROM audio WHERE id = $audioID";
		$jinglename = $db->getOne($sql);

		$sql = "SELECT name, id FROM jinglepkgs";
		$jinglepkgs = $db->getAll($sql);

		$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,33), $userID));
		$this->assign('access_sue',AuthUtil::getDetailedUserrealmAccess(
			array(24,20,3), $userID));
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		$this->assign('jinglepkgs', $jinglepkgs);
		$this->assign('currentpkg', $currentpkg);
		$this->assign('currentpkgid', $jinglepkgID);
		$this->assign('jinglename', $jinglename);
		$this->assign('jingleID', $audioID);
	}
}
?>
