<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSSueStatsViewer extends Viewer {

  const module = 'DPS';

  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();

    $db = Database::getInstance($cfg['DPS']['dsn']);
//    $db_web = Database::getInstance($cfg['DPS']['dsn_web']);

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
    $query = "SELECT audio.title AS title, audio.id AS id FROM sustschedule, audio WHERE sustschedule.audio = audio.id order by
sustschedule.id asc";
    $suePlaylist = $db->getAll($query);
    foreach($suePlaylist as $key => &$track) {
      $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND
audioartists.artist = artists.id";
      $artists = $db->getAll($sql);
      foreach($artists as $artist) {
        $track['artist'] = $track['artist'] . $artist['name'] . " & ";
      }
      $track['artist'] = rtrim($track['artist']," & ");
    }
    
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
    $this->assign('Access_EditSue',AuthUtil::getDetailedUserrealmAccess(array(58,59,66), $userID));
	$this->assign('Access_ViewSue',AuthUtil::getDetailedUserrealmAccess(array(58,60,3), $userID));
    $this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
    
    $this->assign('storedTracks', $systemTracks);
    $this->assign('lengthOfTracks', $systemLength);
    $this->assign('suePlaylistTracks', $sueTracks);
    $this->assign('suePlaylistLength', $sueLength);
    $this->assign('sueLastTrack', $suePlaylist[0]);
    $this->assign('sueNextTrack', $suePlaylist[1]);
    $this->assign('suePlaylist', $suePlaylist);
   }
}

?>
		    
