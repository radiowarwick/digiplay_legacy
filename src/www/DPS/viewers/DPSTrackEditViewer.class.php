<?php
/**
* @package FrontEnds
* @subpackage MVC
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSTrackEditViewer extends Viewer {
	
	const module = 'DPS';
	
	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$trackID = $this->fieldData['trackID'];

		$sql = "SELECT audio.*, albums.name as album 
		FROM audio, albums 
		WHERE audio.music_album = albums.id 
			AND audio.id = " . pg_escape_string($trackID);
		$trackDetails = $db->getRow($sql);

		$sql = "SELECT DISTINCT artists.name as name, artists.id as id 
		FROM artists, audioartists 
		WHERE audioartists.audioid = " . pg_escape_string($trackID) . " 
			AND audioartists.artistid = artists.id";
		$trackDetails['artist'] = $db->getAll($sql);
		$i = 0;
		foreach($trackDetails['artist'] as &$artist) {
			$artist['number'] = $i;
			$i++;
		}
		$artistNum = $i;
		
		$sql = "SELECT DISTINCT keywords.name as name, keywords.id as id 
		FROM keywords, audiokeywords 
		WHERE audiokeywords.audioid = " . pg_escape_string($trackID) . " 
			AND audiokeywords.keywordid = keywords.id"; 
		$trackDetails['keywords'] = $db->getAll($sql);
		$i = 0;
		foreach($trackDetails['keywords'] as &$keyword) {
			$keyword['number'] = $i;
			$i++;
		}
		$keywordNum = $i;
		
		$samples = $trackDetails['length_smpl'];
		$trackDetails['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
		
		$sql = "SELECT * from audiocomments 
		WHERE audioid = " . pg_escape_string($trackID) . " 
		ORDER BY creationdate ASC";
		$trackDetails['comments'] = $db->getAll($sql);
		foreach($trackDetails['comments'] as &$comment) {
			$comment['username'] = AuthUtil::getUsername($comment['userid']);
			$comment['comment'] = str_replace("\n","<br>",$comment['comment']);
			$comment['ctime'] = substr($comment['creationdate'],0,10);
		}

		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$this->assign('RequestTrack',AuthUtil::getDetailedUserrealmAccess(array(3,21,29), $userID));
		$this->assign('CensorTrack',AuthUtil::getDetailedUserrealmAccess(array(3,21,30), $userID));
		$this->assign('ReportTrack',AuthUtil::getDetailedUserrealmAccess(array(3,21,43), $userID));
		$this->assign('SueEdit',AuthUtil::getDetailedUserrealmAccess(array(3,20,24), $userID));
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		
		$this->assign('trackDetails', $trackDetails);
		$this->assign('keywordNum', $keywordNum);
		$this->assign('artistNum', $artistNum);
		$this->assign('trackID', $trackID);
	}
}

?>
