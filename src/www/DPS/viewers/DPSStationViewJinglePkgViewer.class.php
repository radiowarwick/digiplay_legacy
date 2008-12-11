<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSStationViewJinglePkgViewer extends Viewer {

	const module = 'DPS';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();

		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();

		$jinglepkgid = pg_escape_string($this->fieldData['jinglepkg']);

		$sql = "SELECT * FROM jinglepkgs WHERE id = $jinglepkgid";
		$jinglepkg = $db->getRow($sql);

		$sql = "SELECT audio.title, audio.id FROM audio INNER JOIN audiojinglepkgs ON audio.id = audiojinglepkgs.audioid WHERE audiojinglepkgs.jinglepkgid = $jinglepkgid";
		$jingles = $db->getAll($sql);

		$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,33), $userID));
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		$this->assign('jinglepkg', $jinglepkg);
		$this->assign('jingles', $jingles);
	}
}
?>
