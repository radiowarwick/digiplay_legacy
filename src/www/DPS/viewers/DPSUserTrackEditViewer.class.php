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

		//As there is no general audio view
		$sql = "SELECT count(*) FROM v_tree_jingle 
			WHERE id = " . pg_escape_string($trackID) . " 
				AND userid = " . $userID . " 
				AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '" .
					$cfg['DPS']['fileW'] . "'";
		$check = $db->getOne($sql);
		$sql = "SELECT count(*) FROM v_tree_advert 
			WHERE id = " . pg_escape_string($trackID) . " 
				AND userid = " . $userID . " 
				AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '" .
					$cfg['DPS']['fileW'] . "'";
		$check = $check + $db->getOne($sql);
		$sql = "SELECT count(*) FROM v_tree_prerec 
			WHERE id = " . pg_escape_string($trackID) . " 
				AND userid = " . $userID . " 
				AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '" .
					$cfg['DPS']['fileW'] . "'";
		$check = $check + $db->getOne($sql);
		if($check < 1) {
			$this->assign('authError','t');
		} else {
			$sql = "SELECT audio.* FROM audio 
				WHERE audio.id = " . pg_escape_string($trackID);
			$trackDetails = $db->getRow($sql);
			$sql = "SELECT DISTINCT artists.name AS name, artists.id AS id 
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
		
			$sql = "SELECT DISTINCT keywords.name AS name, keywords.id AS id 
				FROM keywords, audiokeywords 
				WHERE audiokeywords.track = " . pg_escape_string($trackID) . " 
					AND audiokeywords.keyword = keywords.id"; 
			$trackDetails['keywords'] = $db->getAll($sql);
			$i = 0;
			foreach($trackDetails['keywords'] as &$keyword) {
				$keyword['number'] = $i;
				$i++;
			}
			$keywordNum = $i;
		
			$samples = $trackDetails['length_smpl'];
			$trackDetails['length'] = $tracksLen = floor((($samples/44100)/60)) .
				"mins " . (($samples/44100)%60) . "secs.";
		
			$sql = "SELECT * from audiocomments 
				WHERE audioid = " . pg_escape_string($trackID) . "
				ORDER BY creationdate ASC";
			$trackDetails['comments'] = $db->getAll($sql);
			foreach($trackDetails['comments'] as &$comment) {
				$comment['username'] = AuthUtil::getUsername($comment['userid']);
				$comment['comment'] = str_replace("\n","<br>",$comment['comment']);
				$comment['ctime'] = substr($comment['creationdate'],0,10);
			}
			$this->assign('trackDetails', $trackDetails);
			$this->assign('keywordNum', $keywordNum);
			$this->assign('artistNum', $artistNum);
			$this->assign('trackID', $trackID);
		}
		$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,33), $userID));
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(
			array(1), $userID));
		$this->assign('studioAccess',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,34), $userID));
	}
}
?>