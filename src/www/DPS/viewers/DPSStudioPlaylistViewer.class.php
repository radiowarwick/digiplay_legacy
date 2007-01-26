<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSStudioPlaylistViewer extends Viewer {
	
  const module = 'DPS';
	
  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();
    
    $db = Database::getInstance($cfg['DPS']['dsn']);
	$playlistID = pg_escape_string($this->fieldData['dpsPlaylistID']);
	if($playlistID == '' || !is_numeric($playlistID)) {
	  $playlistID = 1;
	}
	$offset = $this->fieldData['dpsSearchPage'];
    if($offset == "") {
      $offset = 0;
    } else {
      $offset--;
    }

    $searchValue = $this->fieldData['dpsSearchVal'];
    $searchType = $this->fieldData['dpsSearchType'];
    $letter = pg_escape_string($this->fieldData['dpsSearchLetter']);
    if($searchType == '' && $letter != '') {
      if($letter == "*") {
	$searchType = 'Number';
      } else {
	$searchType = 'Letter';
      }
    }
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
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name), min(audio.length_smpl) as length_smpl 
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
	  $samples = $track['length_smpl'];
	  $track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
	  $artists = $db->getAll($sql);
	  foreach($artists as $artist) {
	    $track['artist'] = $track['artist'] . $artist['name'] . " & "; 
	  }
	  $track['artist'] = rtrim($track['artist']," & ");
	  $sql = "select count(*) from audioplaylists where audio = " . $track['id'] . " AND playlist = " . $playlistID;
	  if($db->getOne($sql)) {
		$track['playlist'] = 't';
	  } else {
		$track['playlist'] = 'f';
	  }
	  $track['searchNumber'] = $number;
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
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name), min(audio.length_smpl) as length_smpl 
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
	  $samples = $track['length_smpl'];
	  $track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
	  $artists = $db->getAll($sql);
	  foreach($artists as $artist) {
	    $track['artist'] = $track['artist'] . $artist['name'] . " & "; 
	  }
	  $track['artist'] = rtrim($track['artist']," & ");
	  $sql = "select count(*) from audioplaylists where audio = " . $track['id'] . " AND playlist = " . $playlistID;
	  if($db->getOne($sql)) {
		$track['playlist'] = 't';
	  } else {
		$track['playlist'] = 'f';
	  }
	  $track['searchNumber'] = $number;
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
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name), min(audio.length_smpl) as length_smpl 
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
	  $samples = $track['length_smpl'];
	  $track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
	  $artists = $db->getAll($sql);
	  foreach($artists as $artist) {
	    $track['artist'] = $track['artist'] . $artist['name'] . " & "; 
	  }
	  $track['artist'] = rtrim($track['artist']," & ");
	  $sql = "select count(*) from audioplaylists where audio = " . $track['id'] . " AND playlist = " . $playlistID;
	  if($db->getOne($sql)) {
		$track['playlist'] = 't';
	  } else {
		$track['playlist'] = 'f';
	  }
	  $track['searchNumber'] = $number;
	  $number++;
	}
      } else if($searchType == "Letter") {
	$count_query = "SELECT count(*) FROM (
			  SELECT min(audio.id) 
			  FROM audio, artists, audioartists, audiodir, audiotypes 
			  WHERE audio.type = audiotypes.id 
				AND audiotypes.name = 'music' 
				AND audio.id = audiodir.audio 
				AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
				AND audioartists.artist = artists.id 
				AND audioartists.audio = audio.id 
				AND audio.title ILIKE '" . $letter . "%' 
			  GROUP BY audio.id
			)as a1";
	$rNum = $db->getOne($count_query);
	$searchInfo = $rNum . ' Results for "' . $letter . '"';
	$query = "SELECT min(audio.title) AS title, min(audio.id) AS id, min(audio.sustainer) as sust, 
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name), min(audio.length_smpl) as length_smpl 
		  FROM audio, artists, audioartists, audiodir, audiotypes 
		  WHERE audio.type = audiotypes.id 
			AND audiotypes.name = 'music' 
			AND audio.id = audiodir.audio 
			AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
			AND audioartists.artist = artists.id 
			AND audioartists.audio = audio.id 
			AND audio.title ILIKE '" . $letter . "%' 
		  GROUP BY audio.id 
		  ORDER BY min(artists.name) asc 
		  LIMIT " . pg_escape_string($cfg['DPS']['resultLimit']) . " 
		  OFFSET " . ($offset*$cfg['DPS']['resultLimit']);
	$searchResult = $db->getAll($query);
	$number=0;
	foreach($searchResult as $key => &$track) {
	  $samples = $track['length_smpl'];
	  $track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
	  $artists = $db->getAll($sql);
	  foreach($artists as $artist) {
	    $track['artist'] = $track['artist'] . $artist['name'] . " & "; 
	  }
	  $track['artist'] = rtrim($track['artist']," & ");
	  $sql = "select count(*) from audioplaylists where audio = " . $track['id'] . " AND playlist = " . $playlistID;
	  if($db->getOne($sql)) {
		$track['playlist'] = 't';
	  } else {
		$track['playlist'] = 'f';
	  }
	  $track['searchNumber'] = $number;
	  $number++;
	}
      } else if($searchType == "Number") {
	$count_query = "SELECT count(*) FROM (
			  SELECT min(audio.id) 
			  FROM audio, artists, audioartists, audiodir, audiotypes 
			  WHERE audio.type = audiotypes.id 
				AND audiotypes.name = 'music' 
				AND audio.id = audiodir.audio 
				AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
				AND audioartists.artist = artists.id 
				AND audioartists.audio = audio.id 
				AND (audio.title ILIKE '0%' OR
				    audio.title ILIKE '1%' OR
				    audio.title ILIKE '2%' OR
				    audio.title ILIKE '3%' OR
				    audio.title ILIKE '4%' OR
				    audio.title ILIKE '5%' OR
				    audio.title ILIKE '6%' OR
				    audio.title ILIKE '7%' OR
				    audio.title ILIKE '8%' OR
				    audio.title ILIKE '9%' 
				)
			  GROUP BY audio.id
			)as a1";
	$rNum = $db->getOne($count_query);
	$searchInfo = $rNum . ' Results for "#"';
	$query = "SELECT min(audio.title) AS title, min(audio.id) AS id, min(audio.sustainer) as sust, 
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name), min(audio.length_smpl) as length_smpl 
		  FROM audio, artists, audioartists, audiodir, audiotypes 
		  WHERE audio.type = audiotypes.id 
			AND audiotypes.name = 'music' 
			AND audio.id = audiodir.audio 
			AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
			AND audioartists.artist = artists.id 
			AND audioartists.audio = audio.id 
			AND (audio.title ILIKE '0%' OR
			    audio.title ILIKE '1%' OR
			    audio.title ILIKE '2%' OR
			    audio.title ILIKE '3%' OR
			    audio.title ILIKE '4%' OR
			    audio.title ILIKE '5%' OR
			    audio.title ILIKE '6%' OR
			    audio.title ILIKE '7%' OR
			    audio.title ILIKE '8%' OR
			    audio.title ILIKE '9%' 
			)
		  GROUP BY audio.id 
		  ORDER BY min(artists.name) asc 
		  LIMIT " . pg_escape_string($cfg['DPS']['resultLimit']) . " 
		  OFFSET " . ($offset*$cfg['DPS']['resultLimit']);
	$searchResult = $db->getAll($query);
	$number=0;
	foreach($searchResult as $key => &$track) {
	  $samples = $track['length_smpl'];
	  $track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
	  $artists = $db->getAll($sql);
	  foreach($artists as $artist) {
	    $track['artist'] = $track['artist'] . $artist['name'] . " & "; 
	  }
	  $track['artist'] = rtrim($track['artist']," & ");
	  $sql = "select count(*) from audioplaylists where audio = " . $track['id'] . " AND playlist = " . $playlistID;
	  if($db->getOne($sql)) {
		$track['playlist'] = 't';
	  } else {
		$track['playlist'] = 'f';
	  }
	  $track['searchNumber'] = $number;
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
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name), min(audio.length_smpl) as length_smpl 
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
	  $samples = $track['length_smpl'];
	  $track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
	  $artists = $db->getAll($sql);
	  foreach($artists as $artist) {
	    $track['artist'] = $track['artist'] . $artist['name'] . " & "; 
	  }
	  $track['artist'] = rtrim($track['artist']," & ");
	  $sql = "select count(*) from audioplaylists where audio = " . $track['id'] . " AND playlist = " . $playlistID;
	  if($db->getOne($sql)) {
		$track['playlist'] = 't';
	  } else {
		$track['playlist'] = 'f';
	  }
	  $track['searchNumber'] = $number;
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
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name), min(audio.length_smpl) as length_smpl 
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
	  $samples = $track['length_smpl'];
	  $track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
	  $artists = $db->getAll($sql);
	  foreach($artists as $artist) {
	    $track['artist'] = $track['artist'] . $artist['name'] . " & "; 
	  }
	  $track['artist'] = rtrim($track['artist']," & ");
	  $sql = "select count(*) from audioplaylists where audio = " . $track['id'] . " AND playlist = " . $playlistID;
	  if($db->getOne($sql)) {
		$track['playlist'] = 't';
	  } else {
		$track['playlist'] = 'f';
	  }
	  $track['searchNumber'] = $number;
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
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name), min(audio.length_smpl) as length_smpl 
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
	  $samples = $track['length_smpl'];
	  $track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
	  $artists = $db->getAll($sql);
	  foreach($artists as $artist) {
	    $track['artist'] = $track['artist'] . $artist['name'] . " & "; 
	  }
	  $track['artist'] = rtrim($track['artist']," & ");
	  $sql = "select count(*) from audioplaylists where audio = " . $track['id'] . " AND playlist = " . $playlistID;
	  if($db->getOne($sql)) {
		$track['playlist'] = 't';
	  } else {
		$track['playlist'] = 'f';
	  }
	  $track['searchNumber'] = $number;
	  $number++;
	}
      } else if($searchType == "Letter") {
	$count_query = "SELECT count(*) FROM (
			  SELECT min(audio.id) 
			  FROM audio, artists, audioartists, audiodir, audiotypes 
			  WHERE audio.type = audiotypes.id 
				AND audiotypes.name = 'music' 
				AND audio.id = audiodir.audio 
				AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
				AND audioartists.artist = artists.id 
				AND audioartists.audio = audio.id 
				AND audio.title ILIKE '" . $letter . "%' 
			  GROUP BY audio.id
			)as a1";
	$rNum = $db->getOne($count_query);
	$searchInfo = $rNum . ' Results for "' . $letter . '"';
	$query = "SELECT min(audio.title) AS title, min(audio.id) AS id, min(audio.sustainer) as sust, 
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name), min(audio.length_smpl) as length_smpl 
		  FROM audio, artists, audioartists, audiodir, audiotypes 
		  WHERE audio.type = audiotypes.id 
			AND audiotypes.name = 'music' 
			AND audio.id = audiodir.audio 
			AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
			AND audioartists.artist = artists.id 
			AND audioartists.audio = audio.id 
			AND audio.title ILIKE '" . $letter . "%' 
		  GROUP BY audio.id 
		  ORDER BY min(audio.title) asc 
		  LIMIT " . pg_escape_string($cfg['DPS']['resultLimit']) . " 
		  OFFSET " . ($offset*$cfg['DPS']['resultLimit']);
	$searchResult = $db->getAll($query);
	$number=0;
	foreach($searchResult as $key => &$track) {
	  $samples = $track['length_smpl'];
	  $track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
	  $artists = $db->getAll($sql);
	  foreach($artists as $artist) {
	    $track['artist'] = $track['artist'] . $artist['name'] . " & "; 
	  }
	  $track['artist'] = rtrim($track['artist']," & ");
	  $sql = "select count(*) from audioplaylists where audio = " . $track['id'] . " AND playlist = " . $playlistID;
	  if($db->getOne($sql)) {
		$track['playlist'] = 't';
	  } else {
		$track['playlist'] = 'f';
	  }
	  $track['searchNumber'] = $number;
	  $number++;
	}
      } else if($searchType == "Number") {
	$count_query = "SELECT count(*) FROM (
			  SELECT min(audio.id) 
			  FROM audio, artists, audioartists, audiodir, audiotypes 
			  WHERE audio.type = audiotypes.id 
				AND audiotypes.name = 'music' 
				AND audio.id = audiodir.audio 
				AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
				AND audioartists.artist = artists.id 
				AND audioartists.audio = audio.id 
				AND (audio.title ILIKE '0%' OR
				    audio.title ILIKE '1%' OR
				    audio.title ILIKE '2%' OR
				    audio.title ILIKE '3%' OR
				    audio.title ILIKE '4%' OR
				    audio.title ILIKE '5%' OR
				    audio.title ILIKE '6%' OR
				    audio.title ILIKE '7%' OR
				    audio.title ILIKE '8%' OR
				    audio.title ILIKE '9%' 
				)
			  GROUP BY audio.id
			)as a1";
	$rNum = $db->getOne($count_query);
	$searchInfo = $rNum . ' Results for "#"';
	$query = "SELECT min(audio.title) AS title, min(audio.id) AS id, min(audio.sustainer) as sust, 
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name), min(audio.length_smpl) as length_smpl 
		  FROM audio, artists, audioartists, audiodir, audiotypes 
		  WHERE audio.type = audiotypes.id 
			AND audiotypes.name = 'music' 
			AND audio.id = audiodir.audio 
			AND audiodir.directory != " . $cfg['DPS']['binDirectoryID'] . " 
			AND audioartists.artist = artists.id 
			AND audioartists.audio = audio.id 
			AND (audio.title ILIKE '0%' OR
			    audio.title ILIKE '1%' OR
			    audio.title ILIKE '2%' OR
			    audio.title ILIKE '3%' OR
			    audio.title ILIKE '4%' OR
			    audio.title ILIKE '5%' OR
			    audio.title ILIKE '6%' OR
			    audio.title ILIKE '7%' OR
			    audio.title ILIKE '8%' OR
			    audio.title ILIKE '9%' 
			)
		  GROUP BY audio.id 
		  ORDER BY min(audio.title) asc 
		  LIMIT " . pg_escape_string($cfg['DPS']['resultLimit']) . " 
		  OFFSET " . ($offset*$cfg['DPS']['resultLimit']);
	$searchResult = $db->getAll($query);
	$number=0;
	foreach($searchResult as $key => &$track) {
	  $samples = $track['length_smpl'];
	  $track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
	  $sql = "SELECT DISTINCT artists.name as name FROM artists, audioartists WHERE audioartists.audio = " . $track['id'] . " AND audioartists.artist = artists.id order by artists.name asc";
	  $artists = $db->getAll($sql);
	  foreach($artists as $artist) {
	    $track['artist'] = $track['artist'] . $artist['name'] . " & "; 
	  }
	  $track['artist'] = rtrim($track['artist']," & ");
	  $sql = "select count(*) from audioplaylists where audio = " . $track['id'] . " AND playlist = " . $playlistID;
	  if($db->getOne($sql)) {
		$track['playlist'] = 't';
	  } else {
		$track['playlist'] = 'f';
	  }
	  $track['searchNumber'] = $number;
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
		$sql = "select * from playlists";
		$playlists = $db->getAll($sql);
		$sql = "select * from playlists where id = " . pg_escape_string($playlistID);
		$playlist = $db->getRow($sql);
		$auth = Auth::getInstance();
    $userID = $auth->getUserID();
    $this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		$this->assign('studioAccess',AuthUtil::getDetailedUserrealmAccess(array(58,69,70), $userID));
		$this->assign('playlists',$playlists);
		$this->assign('playlist',$playlist);
    $this->assign('page', $offset);
    $this->assign('searchResult', $searchResult);
    $this->assign('searchInfo', $searchInfo);
    $this->assign('pages', $pageArray);
    $this->assign('searchType', $searchType);
    $this->assign('searchValue', $searchValue);
    $this->assign('searchLetter', $letter);
    $this->assign('sortType',$sortType);
  }
}

?>
