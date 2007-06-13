<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserTrackEditViewer extends Viewer {
	
	const module = 'DPS';
	
	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$trackID = $this->fieldData['trackID'];
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();

		$sql = "SELECT count(*) from audiousers where audio = " . pg_escape_string($trackID) . " and userid = " . $userID . " and 
						(permissions = 'o' or permissions = 'rw' or permissions = 'w')";
		$check = $db->getOne($sql);
		$sql = "SELECT count(*) from audiogroups, groupmembers where audiogroups.audio = " . pg_escape_string($trackID) . " and 
						audiogroups.groupid = groupmembers.groupid and groupmembers.userid = " . $userID . " and 
						(audiogroups.permissions = 'o' or audiogroups.permissions = 'rw' or audiogroups.permissions = 'w')";
		$check = $check + $db->getOne($sql);
		if($check < 1) {
			$this->assign('authError','t');
			$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(array(58,69,4), $userID));
			$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
			$this->assign('studioAccess',AuthUtil::getDetailedUserrealmAccess(array(58,69,70), $userID));
		} else {
			$sql = "SELECT audio.* FROM audio where audio.id = " . pg_escape_string($trackID);
			$trackDetails = $db->getRow($sql);
			$sql = "SELECT DISTINCT artists.name as name, artists.id as id FROM artists, audioartists WHERE audioartists.audio = " . pg_escape_string($trackID) . " AND audioartists.artist = artists.id";
			$trackDetails['artist'] = $db->getAll($sql);
			$i = 0;
			foreach($trackDetails['artist'] as &$artist) {
				$artist['number'] = $i;
				$i++;
			}
			$artistNum = $i;
		
			$sql = "SELECT DISTINCT keywords.name as name, keywords.id as id FROM keywords, audiokeywords WHERE audiokeywords.track = " . pg_escape_string($trackID) . " AND audiokeywords.keyword = keywords.id"; 
			$trackDetails['keywords'] = $db->getAll($sql);
			$i = 0;
			foreach($trackDetails['keywords'] as &$keyword) {
				$keyword['number'] = $i;
				$i++;
			}
			$keywordNum = $i;
		
			$samples = $trackDetails['length_smpl'];
			$trackDetails['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
		
			$sql = "SELECT * from audiocomments WHERE audio = " . pg_escape_string($trackID) . " ORDER BY creationdate ASC";
			$trackDetails['comments'] = $db->getAll($sql);
			foreach($trackDetails['comments'] as &$comment) {
				$comment['username'] = AuthUtil::getUsername($comment['userid']);
				$comment['comment'] = str_replace("\n","<br>",$comment['comment']);
				$comment['ctime'] = substr($comment['creationdate'],0,10);
			}

			$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(array(58,69,4), $userID));
			$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
			$this->assign('studioAccess',AuthUtil::getDetailedUserrealmAccess(array(58,69,70), $userID));
			$this->assign('trackDetails', $trackDetails);
			$this->assign('keywordNum', $keywordNum);
			$this->assign('artistNum', $artistNum);
			$this->assign('trackID', $trackID);
		}
	}
}

?>
