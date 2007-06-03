<?php
/**
 * 
 * @package MVC
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
	public static function singleTreeSetup($dirID,$userid,$type) {
  	global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$sql = "SELECT * from v_tree_dir 
						WHERE
							parent = " . pg_escape_string($dirID) . " AND 
							permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "' AND 
							userid = $userid 
						ORDER BY name asc";
    $dirs = $db->getAll($sql);
		$list = '';
   	foreach($dirs as $dir) {
     	if($dir != false) {
				$sql = "SELECT count(*) from v_tree 
								WHERE
									parent = " . $dir['id'] . " AND 
									permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "' AND 
									userid = " . pg_escape_string($userid) . " AND (
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
//					$list = $list . '<item text="' . htmlspecialchars($dir['name']) . '" id="' . $dir['id'] . '" im0="folderClosed.gif" child="1" />';
				} else {
					$list = $list . '<item text="' . htmlspecialchars($dir['name']) . '" id="dir' . $dir['id'] . '" im0="folderClosed.gif" child="0" >';
//					$list = $list . '<item text="' . htmlspecialchars($dir['name']) . '" id="' . $dir['id'] . '" im0="folderClosed.gif" child="0" />';
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
							v_tree_jingle.parent = " . pg_escape_string($dirID) . " AND 
							v_tree_jingle.permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "' AND 
							v_tree_jingle.userid = " . pg_escape_string($userid) . " 
						ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
		  	$list = $list . '<item text="' . htmlspecialchars($file['name']) . '" id="jgl' . $file['id'] . '" im0="jingle16.png"/>';
			}
		}
		//#######
		//ADVERTS
		//#######
		if(strpos($type,'a') !== false) {
			$sql = "SELECT v_tree_advert.* from v_tree_advert 
						WHERE
							v_tree_advert.parent = " . pg_escape_string($dirID) . " AND 
							v_tree_advert.permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "' AND 
							v_tree_advert.userid = " . pg_escape_string($userid) . " 
						ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
		  	$list = $list . '<item text="' . htmlspecialchars($file['name']) . '" id="adv' . $file['id'] . '" im0="jingle16.png"/>';
			}
		}	
		//#######
		//CARTSETS
		//#######
		if(strpos($type,'c') !== false) {
			$sql = "SELECT * from v_tree_cartset 
						WHERE
							parent = " . pg_escape_string($dirID) . " AND 
							permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "' AND 
							userid = " . pg_escape_string($userid) . " 
						ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
		  	$list = $list . '<item text="' . htmlspecialchars($file['name']) . '" id="crt' . $file['id'] . '" im0="cartset16.png"/>';
			}
		}
		//#######
		//SCRIPTS
		//#######
		if(strpos($type,'s') !== false) {
			$sql = "SELECT * from v_tree_script
						WHERE
							parent = " . pg_escape_string($dirID) . " AND 
							permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "' AND 
							userid = " . pg_escape_string($userid) . " 
						ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
		  	$list = $list . '<item text="' . htmlspecialchars($file['name']) . '" id="scr' . $file['id'] . '" im0="script16.png"/>';
			}
		}
		//#######
		//MUSIC
		//#######
		if(strpos($type,'m') !== false) {
			$sql = "SELECT * from v_tree_music
						WHERE
							parent = " . pg_escape_string($dirID) . " AND 
							permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "' AND 
							userid = " . pg_escape_string($userid) . " 
						ORDER BY name asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
		  	$list = $list . '<item text="' . htmlspecialchars($file['name']) . '" id="mus' . $file['id'] . '" im0="music16.png"/>';
			}
		}
  	return $list;
	}
}
?>
