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
	* c - show cartsets
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
				$sql = "SELECT count(*) from v_tree 
				WHERE
					parent = " . $dir['id'] . " AND 
					permissions & B'$readPerm' = '$readPerm' AND 
					userid = $userID AND (
					itemtype = 'dir' ";
				if(strpos($type,'c') !== false) {
					$sql = $sql . " OR itemtype = 'cartset' ";
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
					$list = $list . '<item text="' . htmlspecialchars($dir['name']) . '" id="dir' . $dir['id'] . '" im0="folderClosed.gif" child="1" >';
				} else {
					$list = $list . '<item text="' . htmlspecialchars($dir['name']) . '" id="dir' . $dir['id'] . '" im0="folderClosed.gif" child="0" >';
				}
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
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . '" id="jgl' . $file['id'] . '" im0="jingle16.png">';
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
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . '" id="adv' . $file['id'] . '" im0="jingle16.png">';
				$list = $list . '<userdata name="perm">' . $file['permissions'] . '</userdata>';
				$list = $list . '</item>';
			}
		}

		//#######
		//CARTSETS
		//#######
		if(strpos($type,'c') !== false) {
			$sql = "SELECT * from v_tree_cartset 
			WHERE
				parent = $dirID AND 
				permissions & B'$readPerm' = '$readPerm' AND 
				userid = $userID 
			ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . '" id="crt' . $file['id'] . '" im0="cartset16.png">';
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
	* c - show cartsets
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
				$sql = "SELECT count(*) from dir, dirgroups 
				WHERE
					dir.parent = " . $dir['id'] . " AND 
					dir.id = dirgroups.dirid AND 
					dirgroups.permissions & B'$readPerm' = '$readPerm' AND 
					dirgroups.groupid = $groupID";
				if(strpos($type,'c') !== false) {
					$sql = $sql . " OR itemtype = 'cartset' ";
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
					$list = $list . '<item text="' . htmlspecialchars($dir['name']) . '" id="dir' . $dir['id'] . '" im0="folderClosed.gif" child="1" >';
				} else {
					$list = $list . '<item text="' . htmlspecialchars($dir['name']) . '" id="dir' . $dir['id'] . '" im0="folderClosed.gif" child="0" >';
				}
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
		//CARTSETS
		//#######
		if(strpos($type,'c') !== false) {
			$sql = "SELECT cartsets.name AS name, cartsets.id AS id 
			FROM cartsets, cartsetsdir, cartsetsgroups 
			WHERE
				cartsetsdir.dirid = $dirID AND 
				cartsetsdir.cartsetid = cartsets.id AND 
				cartsetsgroups.cartsetid = cartsets.id AND 
				cartsetsgroups.permissions & B'$readPerm' = '$readPerm' AND 
				cartsetsgroups.groupid = $groupID 
			ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
				$list = $list . '<item text="' . htmlspecialchars($file['name']) . '" id="crt' . $file['id'] . '" im0="cartset16.png">';
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
			$sortstr = "artist.name";
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
			$number=0;
			foreach($searchResult as $key => &$track) { 
				$sql = "SELECT DISTINCT artists.name as name 
				FROM artists, audioartists 
				WHERE audioartists.audio = " . $track['id'] . " 
					AND audioartists.artist = artists.id 
				ORDER BY artists.name ASC";
				$artists = $db->getAll($sql);
				foreach($artists as $artist) {
					$track['artist'] = $track['artist'] . $artist['name'] . " & "; 
				}
				$track['artist'] = rtrim($track['artist']," & ");
				$track['searchNumber'] = $number;
				$samples = $track['end_smpl'];
				$track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
				$number++;
			}
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
				AND artist.name ILIKE '%$searchValue%' "; 
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
								AND albums.name ILIKE '$searchValue%' "; 
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
									AND( albums.name ILIKE '0%' OR 
											albums.name ILIKE '1%' OR 
											albums.name ILIKE '2%' OR 
											albums.name ILIKE '3%' OR 
											albums.name ILIKE '4%' OR 
											albums.name ILIKE '5%' OR 
											albums.name ILIKE '6%' OR 
											albums.name ILIKE '7%' OR 
											albums.name ILIKE '8%' OR 
											albums.name ILIKE '9%' OR) "; 
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
			$samples = $track['end_smpl'];
			$track['length'] = $tracksLen = round((($samples/44100)/60)) .  "mins " . (($samples/44100)%60) . "secs.";
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
												AND artist.name ILIKE '%$searchValue%' ";
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
												AND albums.name ILIKE '$searchValue%' ";
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
												AND( albums.name ILIKE '0%' OR 
														albums.name ILIKE '1%' OR 
														albums.name ILIKE '2%' OR 
														albums.name ILIKE '3%' OR 
														albums.name ILIKE '4%' OR 
														albums.name ILIKE '5%' OR 
														albums.name ILIKE '6%' OR 
														albums.name ILIKE '7%' OR 
														albums.name ILIKE '8%' OR 
														albums.name ILIKE '9%' OR) "; 
			if($sust != '') {
				$count_query = $count_query . " AND audio.sustainer = '$sust' ";
			}
			$count_query = $count_query . "GROUP BY audio.id)as a1";
			
			$rNum = $db->getOne($count_query);
		}
		return $rNum;
	}

}


?>
