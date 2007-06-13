<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSSueFrontViewer extends Viewer {

	const module = 'DPS';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();

		$db = Database::getInstance($cfg['DPS']['dsn']);

		//Sue playing now/next
		$query = "SELECT audio.title AS title, audio.id AS id 
			FROM sustschedule, audio 
			WHERE sustschedule.audioid = audio.id 
			ORDER BY sustschedule.id asc";
		$suePlaylist = $db->getAll($query);
		foreach($suePlaylist as $key => &$track) {
			$sql = "SELECT DISTINCT artists.name AS name 
				FROM artists, audioartists 
				WHERE audioartists.audioid = " . $track['id'] . " 
					AND audioartists.artist = artists.id";
			$artists = $db->getAll($sql);
			foreach($artists as $artist) {
				$track['artist'] = $track['artist'] . $artist['name'] . " & ";
			}
			$track['artist'] = rtrim($track['artist']," & ");
		}
		
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$this->assign('Access_ViewSue',AuthUtil::getDetailedUserrealmAccess(
			array(58,60,3), $userID));
		$this->assign('Access_EditSue',AuthUtil::getDetailedUserrealmAccess(
			array(58,60,66), $userID));
		$this->assign('Access_SueStats',AuthUtil::getDetailedUserrealmAccess(
			array(58,60,2), $userID));
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(
			array(1), $userID));
		
		$this->assign('storedTracks', $systemTracks);
		$this->assign('sueLastTrack', $suePlaylist[0]);
		$this->assign('sueNextTrack', $suePlaylist[1]);
	}
}
?>
