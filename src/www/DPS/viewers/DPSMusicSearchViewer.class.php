<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSMusicSearchViewer extends Viewer {
	
  const module = 'DPS';
	
  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();
    
    $db = Database::getInstance($cfg['DPS']['dsn']);
    
    $offset = $this->fieldData['dpsSearchPage'];
    if($offset == "") {
      $offset = 0;
    } else {
      $offset--;
    }
    $searchValue = $this->fieldData['dpsSearchVal'];
    $searchType = $this->fieldData['dpsSearchType'];
    if($this->fieldData['dpsSortType'] != '') {
      $sesh = Session::getInstance();
      $sortType = $this->fieldData['dpsSortType'];
      $sesh->setValue("dpsSortType",$sortType);
    } else {
      $sesh = Session::getInstance();
      if($sesh->keyExists("dpsSortType")) {
				$sortType=$sesh->getValue("dpsSortType");
      } else {
				$sortType="title";
      }
    }
    if($sortType == "artist") {
      if($searchType == "Title") {
	$count_query = "SELECT count(*) FROM (
			  SELECT min(audio.id) 
			  FROM audio, artists, audioartists, audiodir, audiotypes 
			  WHERE audio.type = audiotypes.id 
				AND audiotypes.name = 'music' 
				AND audio.id = audiodir.audio 
				AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
				AND audioartists.artist = artists.id 
				AND audioartists.audio = audio.id 
				AND audio.title ILIKE '%" . pg_escape_string($searchValue) . "%' 
			  GROUP BY audio.id
			)as a1";
	$rNum = $db->getOne($count_query);
	$searchInfo = $rNum . ' Results for "' . $searchValue . '"';
	$query = "SELECT min(audio.title) AS title, min(audio.id) AS id, min(audio.sustainer) as sust, 
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name), 
			min(audio.reclibid) as reclibid, min(audio.length_smpl) as length_smpl, min(audio.origin) as origin 
		  FROM audio, artists, audioartists, audiodir, audiotypes 
		  WHERE audio.type = audiotypes.id 
			AND audiotypes.name = 'music' 
			AND audio.id = audiodir.audio 
			AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
			AND audioartists.artist = artists.id 
			AND audioartists.audio = audio.id 
			AND audio.title ILIKE '%" . pg_escape_string($searchValue) . "%' 
		  GROUP BY audio.id 
		  ORDER BY min(artists.name) asc 
		  LIMIT " . pg_escape_string($cfg['DPS']['resultLimit']) . " 
		  OFFSET " . ($offset*$cfg['DPS']['resultLimit']);
	$searchResult = $db->getAll($query);
	$number=0;
	foreach($searchResult as $key => &$track) { 
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
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
      } else if($searchType == "Both") {
	$count_query = "SELECT count(*) FROM (
			  SELECT min(audio.id) 
			  FROM audio, artists, audioartists, audiodir, audiotypes 
			  WHERE audio.type = audiotypes.id 
				AND audiotypes.name = 'music' 
				AND audio.id = audiodir.audio 
				AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
				AND audioartists.artist = artists.id 
				AND audioartists.audio = audio.id 
				AND (audio.title ILIKE '%" . pg_escape_string($searchValue) . "%' 
				  OR artists.name ILIKE '%" . pg_escape_string($searchValue) . "%') 
			  GROUP BY audio.id
			)as a1";
	$rNum = $db->getOne($count_query);
	$searchInfo = $rNum . ' Results for "' . $searchValue . '"';
	$query = "SELECT min(audio.title) AS title, min(audio.id) AS id, min(audio.sustainer) as sust, 
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name),  
			min(audio.reclibid) as reclibid, min(audio.length_smpl) as length_smpl, min(audio.origin) as origin 
		  FROM audio, artists, audioartists, audiodir, audiotypes 
		  WHERE audio.type = audiotypes.id 
			AND audiotypes.name = 'music' 
			AND audio.id = audiodir.audio 
			AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
			AND audioartists.artist = artists.id 
			AND audioartists.audio = audio.id 
			AND (audio.title ILIKE '%" . pg_escape_string($searchValue) . "%' 
			  OR artists.name ILIKE '%" . pg_escape_string($searchValue) . "%') 
		  GROUP BY audio.id 
		  ORDER BY min(artists.name) asc 
		  LIMIT " . pg_escape_string($cfg['DPS']['resultLimit']) . " 
		  OFFSET " . ($offset*$cfg['DPS']['resultLimit']);
	$searchResult = $db->getAll($query);
	$number=0;
	foreach($searchResult as $key => &$track) { 
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
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
	$count_query = "SELECT count(*) 
			FROM (
			  SELECT min(audio.id) 
			  FROM audio, artists, audioartists, audiodir, audiotypes 
			  WHERE audio.type = audiotypes.id 
				AND audiotypes.name = 'music' 
				AND audio.id = audiodir.audio 
				AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
				AND audioartists.artist = artists.id 
				AND audioartists.audio = audio.id 
				AND artists.name ILIKE '%" . pg_escape_string($searchValue) . "%' 
			  GROUP BY audio.id
			)as a1";
	$rNum = $db->getOne($count_query);
	$searchInfo = $rNum . ' Results for "' . $searchValue . '"';
	$query = "SELECT min(audio.title) AS title, min(audio.id) AS id, min(audio.sustainer) as sust,
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name),
			min(audio.reclibid) as reclibid, min(audio.length_smpl) as length_smpl, min(audio.origin) as origin 
		  FROM audio, artists, audioartists, audiodir, audiotypes 
		  WHERE audio.type = audiotypes.id 
			AND audiotypes.name = 'music' 
			AND audio.id = audiodir.audio 
			AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
			AND audioartists.artist = artists.id 
			AND audioartists.audio = audio.id 
			AND artists.name ILIKE '%" . pg_escape_string($searchValue) . "%' 
		  GROUP BY audio.id 
		  ORDER BY min(artists.name) asc 
		  LIMIT " . pg_escape_string($cfg['DPS']['resultLimit']) . " 
		  OFFSET " . ($offset*$cfg['DPS']['resultLimit']);
	$searchResult = $db->getAll($query);
	$number=0;
	foreach($searchResult as $key => &$track) { 
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
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
    } else {
      if($searchType == "Title") {
	$count_query = "SELECT count(*) FROM (
			  SELECT min(audio.id) 
			  FROM audio, artists, audioartists, audiodir, audiotypes 
			  WHERE audio.type = audiotypes.id 
				AND audiotypes.name = 'music' 
				AND audio.id = audiodir.audio 
				AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
				AND audioartists.artist = artists.id 
				AND audioartists.audio = audio.id 
				AND audio.title ILIKE '%" . pg_escape_string($searchValue) . "%' 
			  GROUP BY audio.id
			)as a1";
	$rNum = $db->getOne($count_query);
	$searchInfo = $rNum . ' Results for "' . $searchValue . '"';
	$query = "SELECT min(audio.title) AS title, min(audio.id) AS id, min(audio.sustainer) as sust, 
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name),  
			min(audio.reclibid) as reclibid, min(audio.length_smpl) as length_smpl, min(audio.origin) as origin 
		  FROM audio, artists, audioartists, audiodir, audiotypes 
		  WHERE audio.type = audiotypes.id 
			AND audiotypes.name = 'music' 
			AND audio.id = audiodir.audio 
			AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
			AND audioartists.artist = artists.id 
			AND audioartists.audio = audio.id 
			AND audio.title ILIKE '%" . pg_escape_string($searchValue) . "%' 
		  GROUP BY audio.id 
		  ORDER BY min(audio.title) asc 
		  LIMIT " . pg_escape_string($cfg['DPS']['resultLimit']) . " 
		  OFFSET " . ($offset*$cfg['DPS']['resultLimit']);
	$searchResult = $db->getAll($query);
	$number=0;
	foreach($searchResult as $key => &$track) { 
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
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
      } else if($searchType == "Both") {
	$count_query = "SELECT count(*) FROM (
			  SELECT min(audio.id) 
			  FROM audio, artists, audioartists, audiodir, audiotypes 
			  WHERE audio.type = audiotypes.id 
				AND audiotypes.name = 'music' 
				AND audio.id = audiodir.audio 
				AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
				AND audioartists.artist = artists.id 
				AND audioartists.audio = audio.id 
				AND (audio.title ILIKE '%" . pg_escape_string($searchValue) . "%' 
				  OR artists.name ILIKE '%" . pg_escape_string($searchValue) . "%') 
			  GROUP BY audio.id
			)as a1";
	$rNum = $db->getOne($count_query);
	$searchInfo = $rNum . ' Results for "' . $searchValue . '"';
	$query = "SELECT min(audio.title) AS title, min(audio.id) AS id, min(audio.sustainer) as sust, 
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name),  
			min(audio.reclibid) as reclibid, min(audio.length_smpl) as length_smpl, min(audio.origin) as origin 
		  FROM audio, artists, audioartists, audiodir, audiotypes 
		  WHERE audio.type = audiotypes.id 
			AND audiotypes.name = 'music' 
			AND audio.id = audiodir.audio 
			AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
			AND audioartists.artist = artists.id 
			AND audioartists.audio = audio.id 
			AND (audio.title ILIKE '%" . pg_escape_string($searchValue) . "%' 
			  OR artists.name ILIKE '%" . pg_escape_string($searchValue) . "%') 
		  GROUP BY audio.id 
		  ORDER BY min(audio.title) asc 
		  LIMIT " . pg_escape_string($cfg['DPS']['resultLimit']) . " 
		  OFFSET " . ($offset*$cfg['DPS']['resultLimit']);
	$searchResult = $db->getAll($query);
	$number=0;
	foreach($searchResult as $key => &$track) { 
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
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
	$count_query = "SELECT count(*) 
			FROM (
			  SELECT min(audio.id) 
			  FROM audio, artists, audioartists, audiodir, audiotypes 
			  WHERE audio.type = audiotypes.id 
				AND audiotypes.name = 'music' 
				AND audio.id = audiodir.audio 
				AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
				AND audioartists.artist = artists.id 
				AND audioartists.audio = audio.id 
				AND artists.name ILIKE '%" . pg_escape_string($searchValue) . "%' 
			  GROUP BY audio.id
			)as a1";
	$rNum = $db->getOne($count_query);
	$searchInfo = $rNum . ' Results for "' . $searchValue . '"';
	$query = "SELECT min(audio.title) AS title, min(audio.id) AS id, min(audio.sustainer) as sust,
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name),  
			min(audio.reclibid) as reclibid, min(audio.length_smpl) as length_smpl, min(audio.origin) as origin 
		  FROM audio, artists, audioartists, audiodir, audiotypes 
		  WHERE audio.type = audiotypes.id 
			AND audiotypes.name = 'music' 
			AND audio.id = audiodir.audio 
			AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
			AND audioartists.artist = artists.id 
			AND audioartists.audio = audio.id 
			AND artists.name ILIKE '%" . pg_escape_string($searchValue) . "%' 
		  GROUP BY audio.id 
		  ORDER BY min(audio.title) asc 
		  LIMIT " . pg_escape_string($cfg['DPS']['resultLimit']) . " 
		  OFFSET " . ($offset*$cfg['DPS']['resultLimit']);
	$searchResult = $db->getAll($query);
	$number=0;
	foreach($searchResult as $key => &$track) { 
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
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
    }

    $pages = 1; 
    $pageArray[] = $pages;
    $rNum = $rNum-$cfg['DPS']['resultLimit'];
    while($rNum > $cfg['DPS']['resultLimit']) {
      $pages++;
      $pageArray[] = $pages;
      $rNum = $rNum-$cfg['DPS']['resultLimit'];
    }

    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
    $this->assign('RequestTrack',AuthUtil::getDetailedUserrealmAccess(array(58,59,63), $userID));
    $this->assign('CensorTrack',AuthUtil::getDetailedUserrealmAccess(array(58,59,65), $userID));
    $this->assign('ReportTrack',AuthUtil::getDetailedUserrealmAccess(array(58,59,64), $userID));
    $this->assign('EditTrack',AuthUtil::getDetailedUserrealmAccess(array(58,59,61), $userID));
    $this->assign('DeleteTrack',AuthUtil::getDetailedUserrealmAccess(array(58,59,68), $userID));
    $this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
    
    $this->assign('page', $offset);
    $this->assign('searchResult', $searchResult);
    $this->assign('searchInfo', $searchInfo);
    $this->assign('pages', $pageArray);
    $this->assign('searchType', $searchType);
    $this->assign('searchValue', $searchValue);
    $this->assign('sortType',$sortType);
  }
}

?>
