<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSSueAddPlaylistViewer extends Viewer {

  const module = 'DPS';

  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();

    $db = Database::getInstance($cfg['DPS']['dsn']);
    //$auth = Auth::getInstance();

    $offset = $this->fieldData['dpsSearchPage'];
    if($offset == "") {
      $offset = 0;
    } else {
      $offset--;
    }
    $rNum = 0;
    $searchValue = $this->fieldData['dpsSearchVal'];
    $searchType = $this->fieldData['dpsSearchType'];
    $letter = pg_escape_string($this->fieldData['dpsSearchLetter']);
    if($searchValue != "") {
      if($searchType == "Both") {
	$count_query = "SELECT DISTINCT count(audio.id) FROM audio, artists, audioartists, audiodir, audiotypes WHERE audio.type = audiotypes.id AND audiotypes.name = 'music' AND audio.id = audiodir.audio AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " AND audioartists.artist = artists.id AND audioartists.audio = audio.id AND (artists.name ILIKE '%" . pg_escape_string($searchValue) . "%' OR audio.title ILIKE '%" . pg_escape_string($searchValue) . "%')";
	$rNum = $db->getOne($count_query);
	$searchInfo = $rNum . ' Results for "' . $searchValue . '"';
	$query = "SELECT DISTINCT audio.title AS title, audio.length_smpl as length_smpl, audio.id AS id, audio.sustainer as sust, audio.flagged as flagged, audio.censor as censor FROM audio, artists, audioartists, audiodir, audiotypes WHERE audio.type = audiotypes.id AND audiotypes.name = 'music' AND audio.id = audiodir.audio AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " AND audioartists.artist = artists.id AND audioartists.audio = audio.id AND (artists.name ILIKE '%" . pg_escape_string($searchValue) . "%' OR audio.title ILIKE '%" . pg_escape_string($searchValue) . "%') ORDER BY audio.title LIMIT " . pg_escape_string($cfg['DPS']['resultLimit']) . " OFFSET " . ($offset*$cfg['DPS']['resultLimit']);
	$searchResult = $db->getAll($query);
	$number=0;
	foreach($searchResult as $key => &$track) { 
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id";
	  $artists = $db->getAll($sql);
	  foreach($artists as $artist) {
	    $track['artist'] = $track['artist'] . $artist['name'] . " & "; 
	  }
	  $track['artist'] = rtrim($track['artist']," & ");
	  $track['searchNumber'] = $number;
	  $samples = $track['length_smpl'];
	  $track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
	  $number++;
	}

      } else if($searchType == "Artist") {
	$count_query = "SELECT DISTINCT count(audio.id) FROM audio, artists, audioartists, audiodir, audiotypes WHERE audio.type = audiotypes.id AND audiotypes.name = 'music' AND audio.id = audiodir.audio AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " AND audioartists.artist = artists.id AND audioartists.audio = audio.id AND artists.name ILIKE '%" . pg_escape_string($searchValue) . "%'";
	$rNum = $db->getOne($count_query);
	$searchInfo = $rNum . ' Results for "' . $searchValue . '"';
	$query = "SELECT DISTINCT audio.title AS title, audio.length_smpl as length_smpl, audio.id AS id, audio.sustainer as sust, audio.flagged as flagged, audio.censor as censor FROM audio, artists, audioartists, audiodir, audiotypes WHERE audio.type = audiotypes.id AND audiotypes.name = 'music' AND audio.id = audiodir.audio AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " AND audioartists.artist = artists.id AND audioartists.audio = audio.id AND artists.name ILIKE '%" . pg_escape_string($searchValue) . "%' ORDER BY audio.title LIMIT " . pg_escape_string($cfg['DPS']['resultLimit']) . " OFFSET " . ($offset*$cfg['DPS']['resultLimit']);
	$searchResult = $db->getAll($query);
	$number = 0;
	foreach($searchResult as &$track) { 
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id";
	  $artists = $db->getAll($sql);
	  foreach($artists as $artist) {
	    $track['artist'] = $track['artist'] . $artist['name'] . " & ";
	  }
	  $track['artist'] = rtrim($track['artist']," & ");
	  $track['searchNumber']=$number;
	  $samples = $track['length_smpl'];
	  $track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
	  $number++;
	}
      } else if($searchType == "Title") {
	$count_query = "SELECT DISTINCT count(audio.id) FROM audio, audiodir, audiotypes WHERE audio.type = audiotypes.id AND audiotypes.name = 'music' AND audio.id = audiodir.audio AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " AND audio.title ILIKE '%" . pg_escape_string($searchValue) . "%'";
	$rNum = $db->getOne($count_query);
	$searchInfo = $rNum . ' Results for "' . $searchValue . '"';
	$query = "SELECT DISTINCT audio.title AS title, audio.length_smpl as length_smpl, audio.id AS id, audio.sustainer as sust, audio.flagged as flagged, audio.censor as censor FROM audio, audiodir, audiotypes WHERE audio.type = audiotypes.id AND audiotypes.name = 'music' AND audio.id = audiodir.audio AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " AND audio.title ILIKE '%" . pg_escape_string($searchValue) . "%' ORDER BY audio.title LIMIT " . pg_escape_string($cfg['DPS']['resultLimit']) . " OFFSET " . ($offset*$cfg['DPS']['resultLimit']);
	$searchResult = $db->getAll($query);
	$number = 0;
	foreach($searchResult as &$track) {
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id";
	  $artists = $db->getAll($sql);
	  foreach($artists as $artist) {
	    $track['artist'] = $track['artist'] . $artist['name'] . " & ";
	  }
	  $track['artist'] = rtrim($track['artist']," & ");
	  $track['searchNumber'] = $number;
	  $samples = $track['length_smpl'];
	  $track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
	  $number++;
	}	
      } 
    } elseif($this->fieldData['dpsSearchLetter'] == "*") {
      $count_query = "SELECT DISTINCT count(audio.id) FROM audio, audiodir, audiotypes WHERE audio.type = audiotypes.id AND audiotypes.name = 'music' AND audio.id = audiodir.audio AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " AND  
	(audio.title ILIKE '0%' OR 
	audio.title ILIKE '1%' OR 
	audio.title ILIKE '2%' OR 
	audio.title ILIKE '3%' OR 
	audio.title ILIKE '4%' OR 
	audio.title ILIKE '5%' OR 
	audio.title ILIKE '6%' OR 
	audio.title ILIKE '7%' OR 
	audio.title ILIKE '8%' OR 
	audio.title ILIKE '9%')";
      $rNum = $db->getOne($count_query);
      $searchInfo = $rNum . ' Results for "#"';
      $query = "SELECT DISTINCT audio.title AS title, audio.length_smpl as length_smpl, audio.id AS id, audio.sustainer as sust, audio.flagged as flagged, audio.censor as censor FROM audio, audiodir, audiotypes WHERE audio.type = audiotypes.id AND audiotypes.name = 'music' AND audio.id = audiodir.audio AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " AND 
	(audio.title ILIKE '0%' OR 
	audio.title ILIKE '1%' OR 
	audio.title ILIKE '2%' OR 
	audio.title ILIKE '3%' OR 
	audio.title ILIKE '4%' OR 
	audio.title ILIKE '5%' OR 
	audio.title ILIKE '6%' OR 
	audio.title ILIKE '7%' OR 
	audio.title ILIKE '8%' OR 
	audio.title ILIKE '9%') 
	ORDER BY audio.title LIMIT " . pg_escape_string($cfg['DPS']['resultLimit']) . " OFFSET " . ($offset*$cfg['DPS']['resultLimit']);
      $searchResult = $db->getAll($query);
      $number = 0;
      foreach($searchResult as &$track) {
	$sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id";
	$artists = $db->getAll($sql);
	foreach($artists as $artist) {
	  $track['artist'] = $track['artist'] . $artist['name'] . " & ";
	}
	$track['artist'] = rtrim($track['artist']," & ");
	$track['searchNumber'] = $number;
	$samples = $track['length_smpl'];
	$track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
	$number++;
      }
    } elseif(preg_match("/^[a-z0-9]$/i",$letter)) {
      $count_query = "SELECT DISTINCT count(audio.id) FROM audio, audiodir, audiotypes WHERE audio.type = audiotypes.id AND audiotypes.name = 'music' AND audio.id = audiodir.audio AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " AND  audio.title ILIKE '" . $letter . "%'";
      $rNum = $db->getOne($count_query);
      $searchInfo = $rNum . ' Results for "' . $letter . '"';
      $query = "SELECT DISTINCT audio.title AS title, audio.length_smpl as length_smpl, audio.id AS id, audio.sustainer as sust, audio.flagged as flagged, audio.censor as censor FROM audio, audiodir, audiotypes WHERE audio.type = audiotypes.id AND audiotypes.name = 'music' AND audio.id = audiodir.audio AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " AND  audio.title ILIKE '" . $letter . "%' ORDER BY audio.title LIMIT " . pg_escape_string($cfg['DPS']['resultLimit']) . " OFFSET " . ($offset*$cfg['DPS']['resultLimit']);
      $searchResult = $db->getAll($query);
      $number = 0;
      foreach($searchResult as &$track) {
	$sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id";
	$artists = $db->getAll($sql);
	foreach($artists as $artist) {
	  $track['artist'] = $track['artist'] . $artist['name'] . " & ";
	}
	$track['artist'] = rtrim($track['artist']," & ");
	$track['searchNumber'] = $number;
	$samples = $track['length_smpl'];
	$track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
	$number++;
      }
    }
    
    //search page string
    $pages = 1; 
    $pageArray[] = $pages;
    $rNum = $rNum-$cfg['DPS']['resultLimit'];
    while($rNum > $cfg['DPS']['resultLimit']) {
      $pages++;
      $pageArray[] = $pages;
      $rNum = $rNum-$cfg['DPS']['resultLimit'];
    }
    
    //Sue playing now/next
    $query = "SELECT audio.title AS title, audio.id AS id FROM sustschedule, audio WHERE sustschedule.audio = audio.id order by
sustschedule.id asc offset 1 limit 1";
    $sueNextTrack = $db->getRow($query);
    $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $sueNextTrack['id'] . " AND
audioartists.artist = artists.id";
    $artists = $db->getAll($sql);
    foreach($artists as $artist) {
      $sueNextTrack['artist'] = $sueNextTrack['artist'] . $artist['name'] . " & ";
    }
    $sueNextTrack['artist'] = rtrim($sueNextTrack['artist']," & ");
    
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
    $this->assign('Access_EditSue',AuthUtil::getDetailedUserrealmAccess(array(58,59,66), $userID));
    $this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));

    $this->assign('sueNextTrack', $sueNextTrack);
    $this->assign('page', ($offset+1));
    $this->assign('searchResult', $searchResult);
    $this->assign('searchInfo', $searchInfo);
    $this->assign('searchValue', $searchValue);
    $this->assign('searchType', $searchType);
    $this->assign('searchLetter', $letter);
    $this->assign('pages', $pageArray);
    
   }
}

?>
