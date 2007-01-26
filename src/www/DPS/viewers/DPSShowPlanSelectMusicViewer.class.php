<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['Auth']['dir']['root'] . '/AuthUtil.class.php');
class DPSShowPlanSelectMusicViewer extends Viewer {
	
  const module = 'DPS';
	
  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();
    
    $db = Database::getInstance($cfg['DPS']['dsn']);
   
	 	$itemID = pg_escape_string($this->fieldData['itemID']);
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
    $date = time();
		if(is_numeric($itemID) && isset($itemID)) {	
			$show_query = "SELECT count(*) FROM showplanusers, showitems where 
										showitems.showplanid = showplanusers.showplanid AND 
										showplanusers.userid = " . $userID . " AND
										showitems.id = " . $itemID . " AND 
										(showplanusers.permissions = 'o' OR showplanusers.permissions = 'rw')";
    	$checkShows = $db->getOne($show_query);
			if($checkShows == 0) {
				$show_query = "SELECT count(*) FROM showplangroups, groupmembers, showitems where 
										showplangroups.groupid = groupmembers.groupid and 
										showplangroups.showplanid = showitems.showplanid and 
										showitems.id = $itemID and 
										groupmembers.userid = $userID and 
										(showplangroups.permissions = 'o' OR showplangroups.permissions = 'rw')";
				$checkShows = $db->getOne($show_query);
			}
			if($checkShows > 0) {
				$show_sql = "SELECT showplans.* FROM showplans, showitems where showitems.showplanid = showplans.id AND showitems.id = " . $itemID;
				$show = $db->getRow($show_sql);
      	$show['niceAirDate'] = date("d/m/y",$show['showdate']);
      	$show['niceAirTime'] = date("g a",$show['showdate']);
      	$show['niceCreateDate'] = date("d/m/y",$show['creationdate']);
      	$show['niceCreateTime'] = date("g a",$show['creationdate']);
				$items_sql = "SELECT * from showitems where showplanid = " . $show['id'] . " order by position asc";
				$items = $db->getAll($items_sql);
				$time = $show['showdate'];
				$i = 0;
				foreach($items as &$item) {
					if($item['id'] == $itemID) {
						$item['time'] = $time;
						$item['niceTime'] = date("H:i:s",$item['time']);
						$item['niceLength'] = ((int)($item['length'] / 60)) . ":" . ($item['length'] - (((int)($item['length'] / 60))*60));
						if($item['audio'] != '') {
							$sql = "select audio.title as title, audiotypes.name as type, audio.length_smpl as len from audio, audiotypes  where 
										audio.type = audiotypes.id and audio.id = " . $item['audio'];
							$stuff = $db->getRow($sql);
							$item['audioTitle'] = $stuff['title'];
							$item['nature'] = $stuff['type'];
							$item['niceAudioLength'] = round((($stuff['len']/44100)/60)) .  ":" . (($stuff['len']/44100)%60);
						} else {
							$item['nature'] = 'unknown';
						}
						if($item['script'] != '') {
							$sql = "select name, length from scripts where id = " . $item['script'];
							$stuff = $db->getRow($sql);
							$item['scriptName'] = $stuff['name'];
							$item['niceScriptLength'] = ((int)($stuff['length'] / 60)) . ":" . ($stuff['length'] - (((int)($stuff['length'] / 60))*60));
						}
						break;
					}
					$time = $time + $item['length'];
					$i++;
				}
				$this->musicSearch();
				$this->assign('show', $show);
				$this->assign('item', $items[$i]);
			} else {
				$this->assign('error', 'You do not have permission to edit that item.');
			}
		} else {
			$this->assign('error', 'Invalid Item ID supplied');
		}

    $this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
  }

	function treeSetup($dirID,$userid) {
  	global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
    $sql = "SELECT DISTINCT dir.id, dir.parent, dir.name, dir.notes 
						FROM dir, users, dirusers 
						WHERE 
    					dir.id = dirusers.directory AND 
							(dirusers.permissions = 'r' OR 
								dirusers.permissions = 'w' OR 
								dirusers.permissions = 'rw' OR 
								dirusers.permissions = 'o') AND 
							dirusers.userid = $userid AND 
							dir.parent = " . pg_escape_string($dirID) . " 
							ORDER BY dir.name asc";
    $users = $db->getAll($sql);
    $sql = "SELECT DISTINCT dir.id, dir.parent, dir.name, dir.notes 
						FROM dir, dirgroups, groups, groupmembers, users 
						WHERE
            	dir.id = dirgroups.directory AND 
							(dirgroups.permissions= 'r' OR 
								dirgroups.permissions = 'w' OR 
								dirgroups.permissions = 'rw' OR 
								dirgroups.permissions = 'o') AND 
							dirgroups.groupid = groups.id AND
            	groups.id = groupmembers.groupid AND 
							groupmembers.userid = $userid AND 
							dir.parent = " . pg_escape_string($dirID) . " 
							ORDER BY dir.name asc";
    $groups = $db->getAll($sql);
  	$total = 0;
  	$done[0] = -1;
   	foreach($users as $user) {
     	if($user != false) {
       	$total++;
				$list = $list . '<item text="' . htmlspecialchars($user['name']) . '" id="dir' . $user['id'] . '" im0="folderClosed.gif">';
      	$list = $list . $this->treeSetup($user['id'],$userid);
				$list = $list . '</item>';
			}
			$done[$total] = $user['id'];
    }
  	foreach($groups as $group) {
    	if(!array_search($group['id'],$done)) {
    		$total++;
				$list = $list . '<item text="' . htmlspecialchars($group['name']) . '" id="dir' . $group['id'] . '" im0="folderClosed.gif">';
      	$list = $list . $this->treeSetup($group['id'],$userid);
				$list = $list . '</item>';
   		}
  	}
		  //#######
			//JINGLES
			//Add groups
			//#######
			$sql = "SELECT audiodir.id, audio.title, audio.id FROM audiodir, audio, audiotypes WHERE
			        audio.id = audiodir.audio AND directory = " . pg_escape_string($dirID) . " AND
					    audio.type = audiotypes.id AND (audiotypes.name = 'music')
					    order by audio.title asc";
			$files = pg_query($sql);
			$total=0;
			while($file = pg_fetch_array($files)) {
				$total++;
			  $list = $list . '<item text="' . htmlspecialchars($file[1]) . '" id="jgl' . $file[2] . '"/>';
			}
  	return $list;
	}

  function musicSearch() {
    global $cfg;
    
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
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name) 
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
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name) 
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
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name) 
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
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name) 
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
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name) 
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
			min(audio.flagged) as flagged, min(audio.censor) as censor, min(artists.name) 
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
