<?php
/**
 * @package DPS
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSHomeViewer extends Viewer {
	
	const module = 'DPS';
		
	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$db_web = Database::getInstance($cfg['DPS']['dsn_web']);
		
		//System Track count
		$query = "SELECT count(audio.id) FROM audio";
		$systemTracks = $db->getOne($query);
		
		//System Track length
		$query = "SELECT sum(audio.length_smpl) FROM audio";
		$systemSamps = $db->getOne($query);
		$days = floor($systemSamps/44100/60/60/24);
		$hours = floor($systemSamps/44100/60/60 - $days*24);
		$mins = round($systemSamps/44100/60 - $hours*60 - $days*24*60);
		$systemLength = $days . "days " . $hours . "h " . $mins . "m";
		//Sue Track count
		$query = "SELECT count(audio.id) FROM audio WHERE sustainer = 't'";
		$sueTracks = $db->getOne($query);
		
		//Sue Track length
		$query = "SELECT sum(audio.length_smpl) FROM audio WHERE sustainer = 't'";
		$sueSamps = $db->getOne($query);
		$days = floor($sueSamps/44100/60/60/24);
		$hours = floor($sueSamps/44100/60/60 - $days*24);
		$mins = round($sueSamps/44100/60 - $hours*60 - $days*24*60);
		$sueLength = $days . "days " . $hours . "h " . $mins . "m";
		
		//Sue playing now/next
		$query = "SELECT audio.title AS title, audio.id AS id 
			FROM sustschedule, audio 
			WHERE sustschedule.audioid = audio.id 
			ORDER BY sustschedule.id ASC LIMIT 2";
		$suePlaying = $db->getAll($query);
		foreach($suePlaying as $key => &$track) {
			$sql = "SELECT DISTINCT artists.name as name 
				FROM artists, audioartists 
				WHERE audioartists.audioid = " . $track['id'] . " 
				AND audioartists.artistid = artists.id";
			$artists = $db->getAll($sql);
			foreach($artists as $artist) {
				$track['artist'] = $track['artist'] . $artist['name'] . " & ";
			}
			$track['artist'] = rtrim($track['artist']," & ");
		}
		
		//Show on now
		putenv("TZ=GB");
		$current_time = date("Y-m-d H:i:s", time());
		$sql = "SELECT shows.* FROM shows , schedule 
			WHERE(shows.id = schedule.showid 
			AND '$current_time' > schedule.start 
			AND '$current_time' <= schedule.finish);";
		$showC = $db_web->getRow($sql);
		if(!$showC) {
			$sql = "SELECT * FROM shows 
				WHERE id = " . pg_escape_string($cfg['DPS']['defaultShowID']);
			$showC = $db_web->getRow($sql);
		}
		
		//Show on next
		$sql = "SELECT shows.* FROM shows, schedule 
			WHERE (shows.id = schedule.showid 
			AND '$current_time' < schedule.start) 
			ORDER BY schedule.start ASC LIMIT 1;";
		$showN = $db_web->getRow($sql);
		if(!$showN) {
			$sql = "SELECT * FROM shows 
				WHERE id = " . pg_escape_string($cfg['DPS']['defaultShowID']);
			$showN = $db_web->getRow($sql);
		}
		
		//Show just on
		$sql = "SELECT shows.* FROM shows, schedule 
			WHERE(shows.id = schedule.showid 
			AND '$current_time' > schedule.finish) 
			ORDER BY schedule.finish DESC LIMIT 1;";
		$showL = $db_web->getRow($sql);
		if(!$showL) {
			$sql = "SELECT * FROM shows 
				WHERE id = " . pg_escape_string($cfg['DPS']['defaultShowID']);
			$showL = $db_web->getRow($sql);
		}
		
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$sql = "SELECT usersconfigs.val FROM configs, usersconfigs 
			WHERE configs.id = usersconfigs.configid 
			AND configs.name = 'user_lastlogin'
			AND usersconfigs.userid = " . $userID;
		$userlogin = $db->getOne($sql);
		if(is_null($userlogin)) {
			$userLastLog = "Not available";
		} else {
			$userLastLog = date("d/m/y G:i:s",intval($userlogin));
		}
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		$this->assign('userLastLogin', $userLastLog);
		$this->assign('storedTracks', $systemTracks);
		$this->assign('lengthOfTracks', $systemLength);
		$this->assign('suePlaylistTracks', $sueTracks);
		$this->assign('suePlaylistLength', $sueLength);
		$this->assign('sueLastTrack', $suePlaying[0]);
		$this->assign('sueNextTrack', $suePlaying[1]);
		$this->assign('scheduleCurrent', $showC);
		$this->assign('scheduleNext', $showN);
		$this->assign('scheduleLast', $showL);
	}
}
?>
