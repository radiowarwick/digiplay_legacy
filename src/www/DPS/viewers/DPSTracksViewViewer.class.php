<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSTracksViewViewer extends Viewer {
	
	const module = 'DPS';
	
	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$trackIDs = explode(";",$this->fieldData['trackID']);
		$tracksDetails = array();
		foreach($trackIDs as $trackID) {
			$sql = "SELECT audio.*, albums.name AS album 
			FROM audio, albums 
			WHERE audio.music_album = albums.id 
				AND audio.id = " . pg_escape_string($trackID);
			$trackDetails = $db->getRow($sql);

			$sql = "SELECT DISTINCT artists.name AS name 
			FROM artists, audioartists 
			WHERE audioartists.audioid = " . pg_escape_string($trackID) . " 
				AND audioartists.artistid = artists.id";
			$trackDetails['artist'] = $db->getColumn($sql);
		
			$sql = "SELECT DISTINCT keywords.name AS name 
			FROM keywords, audiokeywords 
			WHERE audiokeywords.audioid = " . pg_escape_string($trackID) . " 
				AND audiokeywords.keywordid = keywords.id";
			$trackDetails['keywords'] = $db->getColumn($sql);
			$samples = $trackDetails['length_smpl'];
			$trackDetails['length'] = $tracksLen = round((($samples/44100)/60)) .
				"mins " . (($samples/44100)%60) . "secs.";

			$sql = "SELECT * FROM audiocomments 
			WHERE audioid = " . pg_escape_string($trackID) . " 
			ORDER BY creationdate ASC";
			$trackDetails['comments'] = $db->getAll($sql);
			foreach($trackDetails['comments'] as &$comment) {
				$comment['username'] = AuthUtil::getUsername($comment['userid']);
				$comment['comment'] = str_replace("\n","<br>",$comment['comment']);
				$comment['ctime'] = substr($comment['creationdate'],0,10);
			}
			$tracksDetails[] = $trackDetails;
		}
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$this->assign('RequestTrack',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,29), $userID));
		$this->assign('Access_CommentTrack',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,34), $userID));
		$this->assign('Access_EditTrack',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,27), $userID));
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(
			array(1), $userID));
		$this->assign('tracksDetails', $tracksDetails);
	}
}
?>
