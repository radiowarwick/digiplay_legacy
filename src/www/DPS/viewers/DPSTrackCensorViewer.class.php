<?php
/**
* @package FrontEnds
* @subpackage MVC
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSTrackCensorViewer extends Viewer {
	
	const module = 'DPS';
	
	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		
		$db = Database::getInstance($cfg['DPS']['dsn']);
	
		$count_query = "SELECT count(audio.id) 
		FROM audio 
		WHERE audio.flagged='t'";
		$flaggedNum = $db->getOne($count_query);
		
		$query = "SELECT DISTINCT audio.title as title, audio.id as id 
		FROM audio 
		WHERE audio.flagged='t'";
		$flaggedResult = $db->getAll($query);
		$i=0;
		foreach($flaggedResult as $key => &$track) { 
			$sql = "SELECT DISTINCT artists.name as name 
			FROM artists, audioartists 
			WHERE audioartists.audioid = " . $track['id'] . " 
				AND audioartists.artistid = artists.id";
			$artists = $db->getAll($sql);
			foreach($artists as $artist) {
				$track['artist'] = $track['artist'] . $artist['name'] . " & "; 
			}
			$track['artist'] = rtrim($track['artist']," & ");
			$track['searchNumber'] = $i;
			$i++;
		}
		
		$count_query = "SELECT count(audio.id) 
		FROM audio 
		WHERE audio.censor='t'";
		$censoredNum = $db->getOne($count_query);
		
		$query = "SELECT DISTINCT audio.title as title, audio.id as id 
		FROM audio 
		WHERE audio.censor='t'";
		$censoredResult = $db->getAll($query);
		$i = 0;
		foreach($censoredResult as $key => &$track) { 
			$sql = "SELECT DISTINCT artists.name as name 
			FROM artists, audioartists 
			WHERE audioartists.audioid = " . $track['id'] . " 
				AND audioartists.artistid = artists.id";
			$artists = $db->getAll($sql);
			foreach($artists as $artist) {
				$track['artist'] = $track['artist'] . $artist['name'] . " & "; 
			}
			$track['artist'] = rtrim($track['artist']," & ");
			$track['searchNumber'] = $i;
			$i++;
		}
		
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$this->assign('RequestTrack',AuthUtil::getDetailedUserrealmAccess(array(3,21,29), $userID));
		$this->assign('CensorTrack',AuthUtil::getDetailedUserrealmAccess(array(3,21,30), $userID));
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		$this->assign('flaggedTracks', $flaggedResult);
		$this->assign('censoredTracks', $censoredResult);
		$this->assign('flagNum', $flaggedNum);
		$this->assign('censorNum', $censoredNum);
	}
}

?>
