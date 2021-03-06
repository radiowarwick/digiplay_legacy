<?php
/**
* 
* @package DPS
*/

class DPS extends Module  {

	const module = 'DPS';

	/**
	* Initialise the object
	*
	*/
	function __construct($fieldData, $templateID){
		parent::__construct(NULL, $fieldData, $templateID);
	}

	/*$type [j][a][c][s]
	* j - show jingles
	* a - show adverts
	* r - show prerecs
	* c - show awsets
	* s - show scripts
	* p - show show plan
	* m - show music
	*/
	public static function singleTreeSetup($dirID,$userID,$type) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$dirID = pg_escape_string($dirID);
		$userID = pg_escape_string($userID);
		$readPerm = $cfg['DPS']['fileR'];

		//#######
		//DIRS
		//#######
		$sql = "SELECT * from v_tree_dir 
		WHERE
			parent = $dirID AND 
			permissions & B'$readPerm' = '$readPerm' AND 
			userid = $userID 
		ORDER BY name asc";
		$dirs = $db->getAll($sql);
        
		foreach($dirs as $dir) {
			if($dir != false) {
                /*
				$sql = "SELECT count(*) from v_tree 
				WHERE
					parent = " . $dir['id'] . " AND 
					permissions & B'$readPerm' = '$readPerm' AND 
					userid = $userID AND (
					itemtype = 'dir' ";
				if(strpos($type,'c') !== false) {
					$sql = $sql . " OR itemtype = 'aw_set' ";
				}
				if(strpos($type,'s') !== false) {
					$sql = $sql . " OR itemtype = 'script' ";
				}
				if(strpos($type,'m') !== false) {
					$sql = $sql . " OR itemtype = 'music' ";
				}
				if(strpos($type,'j') !== false) {
					$sql = $sql . " OR itemtype = 'jingle' ";
				}
				if(strpos($type,'a') !== false) {
					$sql = $sql . " OR itemtype = 'advert' ";
				}
				if(strpos($type,'p') !== false) {
					$sql = $sql . " OR itemtype = 'showplan' ";
				}
				if(strpos($type,'r') !== false) {
					$sql = $sql . " OR itemtype = 'prerec' ";
				}
				$sql = $sql . ")";
				$childCount = $db->getOne($sql);
				if($childCount > 0) {
                */
					$list = $list . '<item text="' . htmlspecialchars($dir['name']) . 
						'" id="dir' . $dir['id'] . '" im0="folderClosed.gif" child="1" >';
                /*
				} else {
					$list = $list . '<item text="' . htmlspecialchars($dir['name']) . 
						'" id="dir' . $dir['id'] . '" im0="folderClosed.gif" child="0" >';
				}
                */
				$list = $list . '<userdata name="perm">' . $dir['permissions'] . '</userdata>';
				$list = $list . '</item>';
			}
		}

		//#######
		//JINGLES
		//#######
		if(strpos($type,'j') !== false) {
			$sql = "SELECT v_tree_jingle.* from v_tree_jingle 
			WHERE
				v_tree_jingle.parent = $dirID AND 
				v_tree_jingle.permissions & B'$readPerm' = '$readPerm' AND 
				v_tree_jingle.userid = $userID 
			ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . 
					'" id="jgl' . $file['id'] . '" im0="jingle16.png">';
				$list = $list . '<userdata name="perm">' . $file['permissions'] . '</userdata>';
				$list = $list . '</item>';
			}
		}

		//#######
		//ADVERTS
		//#######
		if(strpos($type,'a') !== false) {
			$sql = "SELECT v_tree_advert.* from v_tree_advert 
			WHERE
				v_tree_advert.parent = $dirID AND 
				v_tree_advert.permissions & B'$readPerm' = '$readPerm' AND 
				v_tree_advert.userid = $userID 
			ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . 
					'" id="adv' . $file['id'] . '" im0="jingle16.png">';
				$list = $list . '<userdata name="perm">' . $file['permissions'] . '</userdata>';
				$list = $list . '</item>';
			}
		}

		//#######
		//PRE-RECS
		//#######
		if(strpos($type,'r') !== false) {
			$sql = "SELECT v_tree_prerec.* from v_tree_prerec 
			WHERE
				v_tree_prerec.parent = $dirID AND 
				v_tree_prerec.permissions & B'$readPerm' = '$readPerm' AND 
				v_tree_prerec.userid = $userID 
			ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . 
					'" id="jgl' . $file['id'] . '" im0="jingle16.png">';
				$list = $list . '<userdata name="perm">' . $file['permissions'] . '</userdata>';
				$list = $list . '</item>';
			}
		}

		//#######
		//AUDIOWALL SETS
		//#######
		if(strpos($type,'c') !== false) {
			$sql = "SELECT * from v_tree_aw_sets 
			WHERE
				parent = $dirID AND 
				permissions & B'$readPerm' = '$readPerm' AND 
				userid = $userID 
			ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . 
					'" id="crt' . $file['id'] . '" im0="awset16.png">';
				$list = $list . '<userdata name="perm">' . $file['permissions'] . '</userdata>';
				$list = $list . '</item>';
			}
		}

		//#######
		//SCRIPTS
		//#######
		if(strpos($type,'s') !== false) {
			$sql = "SELECT * from v_tree_script
			WHERE
				parent = $dirID AND 
				permissions & B'$readPerm' = '$readPerm' AND 
				userid = $userID 
			ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . '" 
					id="scr' . $file['id'] . '" im0="script16.png">';
				$list = $list . '<userdata name="perm">' . $file['permissions'] . '</userdata>';
				$list = $list . '</item>';
			}
		}

		//#######
		//SHOWPLANS
		//#######
		if(strpos($type,'p') !== false) {
			$sql = "SELECT * from v_tree_showplan
			WHERE
				parent = $dirID AND 
				permissions & B'$readPerm' = '$readPerm' AND 
				userid = $userID 
			ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . '" 
					id="shp' . $file['id'] . '" im0="showplan16.png">';
				$list = $list . '<userdata name="perm">' . $file['permissions'] . '</userdata>';
				$list = $list . '</item>';
			}
		}

		//#######
		//MUSIC
		//#######
		if(strpos($type,'m') !== false) {
			$sql = "SELECT * from v_tree_music
			WHERE
				parent = $dirID AND 
				permissions & B'$readPerm' = '$readPerm' AND 
				userid = $userID 
			ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . '"  
					id="mus' . $file['id'] . '" im0="music16.png">';
				$list = $list . '<userdata name="perm">' . $file['permissions'] . '</userdata>';
				$list = $list . '</item>';
			}
		}
		return $list;
	}

	/*$type [j][a][c][s]
	* j - show jingles
	* a - show adverts
	* c - show awsets
	* s - show scripts
	* p - show show plan
	* m - show music
	*/
	public static function singleGroupTreeSetup($dirID,$groupID,$type) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$dirID = pg_escape_string($dirID);
		$groupID = pg_escape_string($groupID);
		$readPerm = $cfg['DPS']['fileR'];

		//#######
		//DIRS
		//#######
		$sql = "SELECT * from dir, dirgroups 
		WHERE
			dir.parent = $dirID AND 
			dir.id = dirgroups.dirid AND 
			dirgroups.permissions & B'$readPerm' = '$readPerm' AND 
			dirgroups.groupid = $groupID 
		ORDER BY dir.name asc";
		$dirs = $db->getAll($sql);
		foreach($dirs as $dir) {
			if($dir != false) {
                /*
				$sql = "SELECT count(*) from dir, dirgroups 
				WHERE
					dir.parent = " . $dir['id'] . " AND 
					dir.id = dirgroups.dirid AND 
					dirgroups.permissions & B'$readPerm' = '$readPerm' AND 
					dirgroups.groupid = $groupID";
				if(strpos($type,'c') !== false) {
					$sql = $sql . " OR itemtype = 'aw_set' ";
				}
				if(strpos($type,'s') !== false) {
					$sql = $sql . " OR itemtype = 'script' ";
				}
				if(strpos($type,'m') !== false) {
					$sql = $sql . " OR itemtype = 'music' ";
				}
				if(strpos($type,'j') !== false) {
					$sql = $sql . " OR itemtype = 'jingle' ";
				}
				if(strpos($type,'a') !== false) {
					$sql = $sql . " OR itemtype = 'advert' ";
				}
				$sql = $sql . ")";
				$childCount = $db->getOne($sql);
				if($childCount > 0) {
                */
					$list = $list . '<item text="' . htmlspecialchars($dir['name']) . '" id="dir' . $dir['id'] . '" im0="folderClosed.gif" child="1" >';
                /*
				} else {
					$list = $list . '<item text="' . htmlspecialchars($dir['name']) . '" id="dir' . $dir['id'] . '" im0="folderClosed.gif" child="0" >';
				}
                */
				$list = $list . '<userdata name="perm">' . $dir['permissions'] . '</userdata>';
				$list = $list . '</item>';
			}
		}

		//#######
		//JINGLES
		//#######
		if(strpos($type,'j') !== false) {
			$sql = "SELECT audio.title AS name, audio.id AS id 
			FROM audio, audiodir, audiogroups, audiotypes 
			WHERE
				audiodir.dirid = $dirID AND 
				audiodir.audioid = audio.id AND 
				audiogroups.audioid = audio.id AND 
				audiogroups.permissions & B'$readPerm' = '$readPerm' AND 
				audiogroups.groupid = $groupID AND
				audio.type = audiotypes.id AND 
				audiotypes.name = " . $cfg['DPS']['JingleType'] . " 
			ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . '" id="jgl' . $file['id'] . '" im0="jingle16.png">';
				$list = $list . '<userdata name="perm">' . $file['permissions'] . '</userdata>';
				$list = $list . '</item>';
			}
		}

		//#######
		//ADVERTS
		//#######
		if(strpos($type,'a') !== false) {
			$sql = "SELECT audio.title AS name, audio.id AS id 
			FROM audio, audiodir, audiogroups, audiotypes 
			WHERE
				audiodir.dirid = $dirID AND 
				audiodir.audioid = audio.id AND 
				audiogroups.audioid = audio.id AND 
				audiogroups.permissions & B'$readPerm' = '$readPerm' AND 
				audiogroups.groupid = $groupID AND
				audio.type = audiotypes.id AND 
				audiotypes.name = " . $cfg['DPS']['AdvertType'] . " 
			ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . '" id="adv' . $file['id'] . '" im0="jingle16.png">';
				$list = $list . '<userdata name="perm">' . $file['permissions'] . '</userdata>';
				$list = $list . '</item>';
			}
		}

		//#######
		//AUDIOWALL SETS
		//#######
		if(strpos($type,'c') !== false) {
			$sql = "SELECT aw_sets.name AS name, aw_sets.id AS id 
			FROM aw_sets, aw_sets_dir, aw_sets_groups 
			WHERE
				aw_sets_dir.dir_id = $dirID AND 
				aw_sets_dir.set_id = aw_sets.id AND 
				aw_sets_groups.set_id = aw_sets.id AND 
				aw_sets_groups.permissions & B'$readPerm' = '$readPerm' AND 
				aw_sets_groups.group_id = $groupID 
			ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . '" id="crt' . $file['id'] . '" im0="awset16.png">';
				$list = $list . '<userdata name="perm">' . $file['permissions'] . '</userdata>';
				$list = $list . '</item>';
			}
		}

		//#######
		//SCRIPTS
		//#######
		if(strpos($type,'s') !== false) {
			$sql = "SELECT script.name AS name, scripts.id AS id 
			FROM scripts, scriptsdir, scriptsgroups 
			WHERE
				scriptsdir.dirid = $dirID AND 
				scriptsdir.scriptid = scripts.id AND 
				scriptsgroups.scriptid = scripts.id AND 
				scriptsgroups.permissions & B'$readPerm' = '$readPerm' AND 
				scriptsgroups.groupid = $groupID 
			ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . '" 
				id="scr' . $file['id'] . '" im0="script16.png">';
				$list = $list . '<userdata name="perm">' . $file['permissions'] . '</userdata>';
				$list = $list . '</item>';
			}
		}

		//#######
		//MUSIC
		//#######
		if(strpos($type,'m') !== false) {
			$sql = "SELECT audio.title AS name, audio.id AS id 
			FROM audio, audiodir, audiogroups, audiotypes 
			WHERE
				audiodir.dirid = $dirID AND 
				audiodir.audioid = audio.id AND 
				audiogroups.audioid = audio.id AND 
				audiogroups.permissions & B'$readPerm' = '$readPerm' AND 
				audiogroups.groupid = $groupID AND
				audio.type = audiotypes.id AND 
				audiotypes.name = " . $cfg['DPS']['MusicType'] . " 
			ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . '"  
				id="mus' . $file['id'] . '" im0="music16.png">';
				$list = $list . '<userdata name="perm">' . $file['permissions'] . '</userdata>';
				$list = $list . '</item>';
			}
		}
		return $list;
	}

	public static function searchAudio($searchValue,$searchType,$sortType,$offset,$sust) {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$offsetCount = $offset*$cfg['DPS']['resultLimit'];
		$resultLimit = pg_escape_string($cfg['DPS']['resultLimit']);
		$binID = pg_escape_string($cfg['DPS']['binDirectoryID']);
		if(strtolower(substr($searchValue,0,4)) == 'the ') {
			$searchValue = substr($searchValue,4);
		}
		$searchValue = pg_escape_string($searchValue);
		if($sortType == "artist") {
			$sortstr = "artists.name";
		} else {
			$sortstr = "audio.title";
		}

		if($searchType == "Title") {
			$query = "SELECT min(audio.title) AS title, min(audio.id) AS id,
				min(audio.sustainer) as sust, min(audio.flagged) as flagged,
				min(audio.censor) as censor, min(artists.name), 
				min(audio.reclibid) as reclibid, min(audio.end_smpl) as end_smpl,
				min(audio.origin) as origin, min(albums.name) as album, 
				min(audio.start_smpl) as start_smpl  
			FROM audio, artists, audioartists, audiodir, audiotypes, albums 
			WHERE audio.type = audiotypes.id 
				AND audio.music_album = albums.id 
				AND audiotypes.name = 'Music' 
				AND audio.id = audiodir.audioid 
				AND audiodir.dirid != $binID 
				AND audioartists.artistid = artists.id 
				AND audioartists.audioid = audio.id 
				AND audio.title ILIKE '%$searchValue%' "; 
			if($sust != '') {
				$query = $query . " AND audio.sustainer = '$sust' ";
			}
			$query = $query . "GROUP BY audio.id 
			ORDER BY min($sortstr) asc 
			LIMIT $resultLimit 
			OFFSET $offsetCount";
			$searchResult = $db->getAll($query);
		} else if($searchType == "Both") {
			$query = "SELECT min(audio.title) AS title, min(audio.id) AS id,
				min(audio.sustainer) as sust, min(audio.flagged) as flagged,
				min(audio.censor) as censor, min(artists.name), 
				min(audio.reclibid) as reclibid, min(audio.end_smpl) as end_smpl,
				min(audio.origin) as origin, min(albums.name) as album, 
				min(audio.start_smpl) as start_smpl  
				FROM audio, artists, audioartists, audiodir, audiotypes, albums 
				WHERE audio.type = audiotypes.id 
				AND audio.music_album = albums.id 
				AND audiotypes.name = 'Music' 
				AND audio.id = audiodir.audioid 
				AND audiodir.dirid != $binID 
				AND audioartists.artistid = artists.id 
				AND audioartists.audioid = audio.id 
				AND (audio.title ILIKE '%$searchValue%' 
					OR artists.name ILIKE '%$searchValue%') ";
			if($sust != '') {
				$query = $query . " AND audio.sustainer = '$sust' ";
			}
			$query = $query . "GROUP BY audio.id 
				ORDER BY min($sortstr) asc 
				LIMIT $resultLimit 
				OFFSET $offsetCount";
			$searchResult = $db->getAll($query);
		} else if($searchType == "Artist") {
			$query = "SELECT min(audio.title) AS title, min(audio.id) AS id,
				min(audio.sustainer) as sust, min(audio.flagged) as flagged,
				min(audio.censor) as censor, min(artists.name), 
				min(audio.reclibid) as reclibid, min(audio.end_smpl) as end_smpl,
				min(audio.origin) as origin, min(albums.name) as album, 
				min(audio.start_smpl) as start_smpl  
				FROM audio, artists, audioartists, audiodir, audiotypes, albums 
				WHERE audio.type = audiotypes.id 
				AND audio.music_album = albums.id 
				AND audiotypes.name = 'Music' 
				AND audio.id = audiodir.audioid 
				AND audiodir.dirid != $binID 
				AND audioartists.artistid = artists.id 
				AND audioartists.audioid = audio.id 
				AND artists.name ILIKE '%$searchValue%' "; 
			if($sust != '') {
				$query = $query . " AND audio.sustainer = '$sust' ";
			}
			$query = $query . "GROUP BY audio.id 
				ORDER BY min($sortstr) asc 
				LIMIT $resultLimit 
				OFFSET $offsetCount";
			$searchResult = $db->getAll($query);
		} else if($searchType == "Album") {
			$query = "SELECT min(audio.title) AS title, min(audio.id) AS id,
									min(audio.sustainer) as sust, min(audio.flagged) as flagged,
									min(audio.censor) as censor, min(artists.name), 
									min(audio.reclibid) as reclibid, min(audio.end_smpl) as end_smpl,
									min(audio.origin) as origin, min(albums.name) as album, 
									min(audio.start_smpl) as start_smpl  
									FROM audio, artists, audioartists, audiodir, audiotypes, albums 
									WHERE audio.type = audiotypes.id 
									AND audio.music_album = albums.id 
									AND audiotypes.name = 'Music' 
									AND audio.id = audiodir.audioid 
									AND audiodir.dirid != $binID 
									AND audioartists.artistid = artists.id 
									AND audioartists.audioid = audio.id 
									AND albums.name ILIKE '%$searchValue%' "; 
			if($sust != '') {
				$query = $query . " AND audio.sustainer = '$sust' ";
			}
			$query = $query . "GROUP BY audio.id 
									ORDER BY min($sortstr) asc 
									LIMIT $resultLimit 
									OFFSET $offsetCount";
			$searchResult = $db->getAll($query);
		} else if($searchType == "Letter") {
			$query = "SELECT min(audio.title) AS title, min(audio.id) AS id,
								min(audio.sustainer) as sust, min(audio.flagged) as flagged,
								min(audio.censor) as censor, min(artists.name), 
								min(audio.reclibid) as reclibid, min(audio.end_smpl) as end_smpl,
								min(audio.origin) as origin, min(albums.name) as album, 
								min(audio.start_smpl) as start_smpl  
								FROM audio, artists, audioartists, audiodir, audiotypes, albums 
								WHERE audio.type = audiotypes.id 
								AND audio.music_album = albums.id 
								AND audiotypes.name = 'Music' 
								AND audio.id = audiodir.audioid 
								AND audiodir.dirid != $binID 
								AND audioartists.artistid = artists.id 
								AND audioartists.audioid = audio.id 
								AND artists.name ILIKE '$searchValue%' "; 
			if($sust != '') {
				$query = $query . " AND audio.sustainer = '$sust' ";
			}
			$query = $query . "GROUP BY audio.id 
								ORDER BY min($sortstr) asc 
								LIMIT $resultLimit 
								OFFSET $offsetCount";
			$searchResult = $db->getAll($query);
		} else if($searchType == "Number") {
			$query = "SELECT min(audio.title) AS title, min(audio.id) AS id,
									min(audio.sustainer) as sust, min(audio.flagged) as flagged,
									min(audio.censor) as censor, min(artists.name), 
									min(audio.reclibid) as reclibid, min(audio.end_smpl) as end_smpl,
									min(audio.origin) as origin, min(albums.name) as album, 
									min(audio.start_smpl) as start_smpl  
									FROM audio, artists, audioartists, audiodir, audiotypes, albums 
									WHERE audio.type = audiotypes.id 
									AND audio.music_album = albums.id 
									AND audiotypes.name = 'Music' 
									AND audio.id = audiodir.audioid 
									AND audiodir.dirid != $binID 
									AND audioartists.artistid = artists.id 
									AND audioartists.audioid = audio.id 
									AND( artists.name ILIKE '0%' OR 
											artists.name ILIKE '1%' OR 
											artists.name ILIKE '2%' OR 
											artists.name ILIKE '3%' OR 
											artists.name ILIKE '4%' OR 
											artists.name ILIKE '5%' OR 
											artists.name ILIKE '6%' OR 
											artists.name ILIKE '7%' OR 
											artists.name ILIKE '8%' OR 
											artists.name ILIKE '9%') "; 
			if($sust != '') {
				$query = $query . " AND audio.sustainer = '$sust' ";
			}
			$query = $query . "GROUP BY audio.id 
									ORDER BY min($sortstr) asc 
									LIMIT $resultLimit 
									OFFSET $offsetCount";
			$searchResult = $db->getAll($query);
		}
		$number=0;
		foreach($searchResult as $key => &$track) { 
			$sql = "SELECT DISTINCT artists.name as name 
			FROM artists, audioartists 
			WHERE audioartists.audioid = " . $track['id'] . " 
			AND audioartists.artistid = artists.id 
			ORDER BY artists.name ASC";
			$artists = $db->getAll($sql);
			foreach($artists as $artist) {
				$track['artist'] = $track['artist'] . $artist['name'] . " & "; 
			}
			$track['artist'] = rtrim($track['artist']," & ");
			$track['searchNumber'] = $number;
			$samples = $track['end_smpl'] - $track['start_smpl'];
			$track['length'] = $tracksLen = floor((($samples/44100)/60)) . "mins " . ceil((($samples/44100)%60)) . "secs.";
			$number++;
		}
		return $searchResult;
	}

	public static function searchPageAudio($searchValue,$searchType,$sust) {
		global $cfg;
		
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$binID = pg_escape_string($cfg['DPS']['binDirectoryID']);
		$searchValue = pg_escape_string($searchValue);
		if($searchType == "Title") {
			$count_query = "SELECT count(*) FROM (
												SELECT min(audio.id) 
												FROM audio, artists, audioartists, audiodir, audiotypes, albums 
												WHERE audio.type = audiotypes.id 
												AND audio.music_album = albums.id 
												AND audiotypes.name = 'Music' 
												AND audio.id = audiodir.audioid 
												AND audiodir.dirid != $binID 
												AND audioartists.artistid = artists.id 
												AND audioartists.audioid = audio.id 
												AND audio.title ILIKE '%$searchValue%' ";
			if($sust != '') {
				$count_query = $count_query . " AND audio.sustainer = '$sust' ";
			}
			$count_query = $count_query . "GROUP BY audio.id)as a1";
			
			$rNum = $db->getOne($count_query);
		} else if($searchType == "Both") {
			$count_query = "SELECT count(*) FROM (
												SELECT min(audio.id) 
												FROM audio, artists, audioartists, audiodir, audiotypes, albums 
												WHERE audio.type = audiotypes.id 
													AND audio.music_album = albums.id 
													AND audiotypes.name = 'Music' 
													AND audio.id = audiodir.audioid 
													AND audiodir.dirid != $binID 
													AND audioartists.artistid = artists.id 
													AND audioartists.audioid = audio.id
													AND (audio.title ILIKE '%$searchValue%' 
														OR artists.name ILIKE '%$searchValue%')";
			if($sust != '') {
				$count_query = $count_query . " AND audio.sustainer = '$sust' ";
			}
			$count_query = $count_query . "GROUP BY audio.id)as a1";
			
			$rNum = $db->getOne($count_query);
		} else if($searchType == "Artist") {
			$count_query = "SELECT count(*) FROM (
												SELECT min(audio.id) 
												FROM audio, artists, audioartists, audiodir, audiotypes, albums 
												WHERE audio.type = audiotypes.id 
												AND audio.music_album = albums.id 
												AND audiotypes.name = 'Music' 
												AND audio.id = audiodir.audioid 
												AND audiodir.dirid != $binID 
												AND audioartists.artistid = artists.id 
												AND audioartists.audioid = audio.id 
												AND artists.name ILIKE '%$searchValue%' ";
			if($sust != '') {
				$count_query = $count_query . " AND audio.sustainer = '$sust' ";
			}
			$count_query = $count_query . "GROUP BY audio.id)as a1";
			
			$rNum = $db->getOne($count_query);
		} else if($searchType == "Album") {
			$count_query = "SELECT count(*) FROM (
												SELECT min(audio.id) 
												FROM audio, artists, audioartists, audiodir, audiotypes, albums 
												WHERE audio.type = audiotypes.id 
												AND audio.music_album = albums.id 
												AND audiotypes.name = 'Music' 
												AND audio.id = audiodir.audioid 
												AND audiodir.dirid != $binID 
												AND audioartists.artistid = artists.id 
												AND audioartists.audioid = audio.id 
												AND albums.name ILIKE '%$searchValue%' ";
			if($sust != '') {
				$count_query = $count_query . " AND audio.sustainer = '$sust' ";
			}
			$count_query = $count_query . "GROUP BY audio.id)as a1";
			
			$rNum = $db->getOne($count_query);
		} else if($searchType == "Letter") {
			$count_query = "SELECT count(*) FROM (
												SELECT min(audio.id) 
												FROM audio, artists, audioartists, audiodir, audiotypes, albums 
												WHERE audio.type = audiotypes.id 
												AND audio.music_album = albums.id 
												AND audiotypes.name = 'Music' 
												AND audio.id = audiodir.audioid 
												AND audiodir.dirid != $binID 
												AND audioartists.artistid = artists.id 
												AND audioartists.audioid = audio.id 
												AND artists.name ILIKE '$searchValue%' ";
			if($sust != '') {
				$count_query = $count_query . " AND audio.sustainer = '$sust' ";
			}
			$count_query = $count_query . "GROUP BY audio.id)as a1";
			
			$rNum = $db->getOne($count_query);
		} else if($searchType == "Number") {
			$count_query = "SELECT count(*) FROM (
												SELECT min(audio.id) 
												FROM audio, artists, audioartists, audiodir, audiotypes, albums 
												WHERE audio.type = audiotypes.id 
												AND audio.music_album = albums.id 
												AND audiotypes.name = 'Music' 
												AND audio.id = audiodir.audioid 
												AND audiodir.dirid != $binID 
												AND audioartists.artistid = artists.id 
												AND audioartists.audioid = audio.id 
												AND( artists.name ILIKE '0%' OR 
														artists.name ILIKE '1%' OR 
														artists.name ILIKE '2%' OR 
														artists.name ILIKE '3%' OR 
														artists.name ILIKE '4%' OR 
														artists.name ILIKE '5%' OR 
														artists.name ILIKE '6%' OR 
														artists.name ILIKE '7%' OR 
														artists.name ILIKE '8%' OR 
														artists.name ILIKE '9%') "; 
			if($sust != '') {
				$count_query = $count_query . " AND audio.sustainer = '$sust' ";
			}
			$count_query = $count_query . "GROUP BY audio.id)as a1";
			
			$rNum = $db->getOne($count_query);
		}
		return $rNum;
	}

	public static function searchPlaylistAudio($searchValue,$searchType,$sortType,$offset,$sust,$playlistID) {
        global $cfg;
        $db = Database::getInstance($cfg['DPS']['dsn']);

        $searchResult = DPS::searchAudio($searchValue,$searchType,$sortType,$offset,$sust);
        foreach($searchResult as $key => &$track) {
            $query = "SELECT count(*)
                      FROM audioplaylists
                      WHERE audioid = ".$track['id']."
                      AND playlistid = $playlistID";
            $rows = $db->GetOne($query);
            if ($rows == 1) {
                $track['playlist'] = 't';
            }
        }

        return $searchResult;
    }

    public static function countPlaylist($playlistID) {
        global $cfg;
        $db = Database::getInstance($cfg['DPS']['dsn']);

        $query = "SELECT count(audio.id)
			      FROM audio, audiotypes, audioplaylists, audiodir
			      WHERE audio.type = audiotypes.id 
				  AND audiotypes.name = 'Music' 
				  AND audio.id = audiodir.audioid 
	              AND audioplaylists.audioid = audio.id
                  AND audioplaylists.playlistid = $playlistID";

		return $db->getOne($query);
    }

    public static function showPlaylist($playlistID, $sortType, $offset) {
        global $cfg;
        $db = Database::getInstance($cfg['DPS']['dsn']);
        $resultOffset = $offset * $cfg['DPS']['resultLimit'];
        $resultLimit = pg_escape_string($cfg['DPS']['resultLimit']);
        $sortType = pg_escape_string($sortType);

        $query = "SELECT audio.title AS title, audio.id AS id,
                  't' as playlist, audio.flagged as flagged,
				  audio.censor as censor, artists.name as artist, 
				  audio.reclibid as reclibid, audio.end_smpl as end_smpl,
				  audio.origin as origin, albums.name as album, 
				  audio.start_smpl as start_smpl
			      FROM audio, artists, audioartists, audiodir, audiotypes, albums, audioplaylists 
			      WHERE audio.type = audiotypes.id 
				  AND audio.music_album = albums.id 
				  AND audiotypes.name = 'Music' 
				  AND audio.id = audiodir.audioid 
				  AND audioartists.artistid = artists.id 
				  AND audioartists.audioid = audio.id 
	              AND audioplaylists.audioid = audio.id
                  AND audioplaylists.playlistid = $playlistID
                  ORDER BY $sortType
                  LIMIT $resultLimit OFFSET $resultOffset";

		$searchResult = $db->getAll($query);

        $number = 0;
        foreach($searchResult as $key => &$track) {
            $samples = $track['end_smpl'] - $track['start_smpl'];
            $track['length'] = floor((($samples/44100)/60)) . "mins " . ceil((($samples/44100)%60)) . "secs.";
            $track['searchNumber'] = $number;
            $number = $number + 1;
        }

		return $searchResult;
    }

}


?>
