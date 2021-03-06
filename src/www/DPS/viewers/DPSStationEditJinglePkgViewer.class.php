<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSStationEditJinglePkgViewer extends Viewer {

	const module = 'DPS';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();

		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();

		$jinglepkgID = pg_escape_string($this->fieldData['jinglepkgID']);

		$sql = "SELECT * FROM jinglepkgs WHERE id = $jinglepkgID";
		$jinglepkg = $db->getRow($sql);

		if ( count( $jinglepkg ) == 0) {
                	$sql = "SELECT id FROM jinglepkgs WHERE name = ''";
                	$jinglepkgID = $db->getOne($sql);
		}

		$sql = "SELECT audio.title, audio.id FROM audio INNER JOIN audiojinglepkgs ON audio.id = audiojinglepkgs.audioid WHERE audiojinglepkgs.jinglepkgid = $jinglepkgID ORDER BY audio.title";
		$jingles = $db->getAll($sql);

		$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,33), $userID));
		$this->assign('access_sue',AuthUtil::getDetailedUserrealmAccess(
			array(24,20,3), $userID));
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		$this->assign('jinglepkg', $jinglepkg);
		$this->assign('jingles', $jingles);
	}
}
?>
