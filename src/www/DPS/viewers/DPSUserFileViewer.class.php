<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserFileViewer extends Viewer {

  const module = 'DPS';
  protected $activeNode = 'foldersTree';

  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();
		$auth = Auth::getInstance();
    $userID = $auth->getUserID();
		$treeInfo = $this->singleTreeSetup(0,$userID);
		$treeInfo = '<tree id=\"0\">' . str_replace('"','\"',$treeInfo) . '</tree>';
		$this->assign('activeNode', $this->activeNode);
    $this->assign('treeData', $treeInfo);
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
	}

function singleTreeSetup($dirID,$userid) {
  	global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
    $sql = "SELECT min(id) as id, min(parent) as parent, min(name) as name, min(notes) as notes, bit_or(permissions) as permissions FROM 
						(SELECT min(dir.id) as id, min(dir.parent) as parent, min(dir.name) as name, min(dir.notes) as notes, bit_or(dirusers.permissions) as permissions 
						FROM dir, users, dirusers 
						WHERE 
    					dir.id = dirusers.directory AND 
							dirusers.permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "' AND 
							dirusers.userid = $userid AND 
							dir.parent = " . pg_escape_string($dirID) . " 
						GROUP BY dir.id 
						UNION (SELECT min(dir.id) as id, min(dir.parent) as parent, min(dir.name) as name, min(dir.notes) as notes, bit_or(dirgroups.permissions) as permissions 
						FROM dir, dirgroups, groups, groupmembers, users 
						WHERE
            	dir.id = dirgroups.directory AND 
							dirgroups.permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "' AND 
							dirgroups.groupid = groups.id AND
            	groups.id = groupmembers.groupid AND 
							groupmembers.userid = $userid AND 
							dir.parent = " . pg_escape_string($dirID) . "
						GROUP BY dir.id)) as Q1
						GROUP BY Q1.id 
						ORDER BY name asc";
    $users = $db->getAll($sql);

   	foreach($users as $user) {
     	if($user != false) {
    		$sql = "SELECT count(*) as childCount FROM 
						(SELECT min(dir.id) as id 
						FROM dir, users, dirusers 
						WHERE 
    					dir.id = dirusers.directory AND 
							dirusers.permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "' AND 
							dirusers.userid = $userid AND 
							dir.parent = " . pg_escape_string($user['id']) . " 
						GROUP BY dir.id 
						UNION (SELECT min(dir.id) as id 
						FROM dir, dirgroups, groups, groupmembers, users 
						WHERE
            	dir.id = dirgroups.directory AND 
							dirgroups.permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "' AND 
							dirgroups.groupid = groups.id AND
            	groups.id = groupmembers.groupid AND 
							groupmembers.userid = $userid AND 
							dir.parent = " . pg_escape_string($user['id']) . "
						GROUP BY dir.id)) as Q1";
    		$childCount = $db->getOne($sql);
				if($childCount > 0) {
					$list = $list . '<item text="' . htmlspecialchars($user['name']) . '" id="dir' . $user['id'] . '" im0="folderClosed.gif" child="1" >';
				} else {
					$list = $list . '<item text="' . htmlspecialchars($user['name']) . '" id="dir' . $user['id'] . '" im0="folderClosed.gif" child="0" >';
				}
				$list = $list . '<userdata name="perm">' . $user['permissions'] . '</userdata>';
      	//$list = $list . $this->treeSetup($user['id'],$userid);
				$list = $list . '</item>';
			}
    }
		//#######
		//JINGLES
		//#######
		$sql = "SELECT DISTINCT audiodir.directory as dir, audio.title as title, audio.id as audio 
						FROM audiodir, audio, audiotypes, audiogroups, groupmembers 
						WHERE audio.id = audiodir.audio AND 
							directory = " . pg_escape_string($dirID) . " AND
							audio.id = audiogroups.audio AND 
							audiogroups.permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "' AND 
							audiogroups.groupid = groupmembers.groupid AND 
							groupmembers.userid = $userid AND 
				    	audio.type = audiotypes.id AND (audiotypes.name = 'jingle')
						UNION SELECT DISTINCT audiodir.directory as dir, audio.title as title, audio.id as audio 
							FROM audiodir, audio, audiotypes, audiousers 
							WHERE audio.id = audiodir.audio AND 
								directory = " . pg_escape_string($dirID) . " AND
								audio.id = audiousers.audio AND 
								audiousers.permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "' AND 
								audiousers.userid = $userid AND 
				    		audio.type = audiotypes.id AND (audiotypes.name = 'jingle')
				    order by title asc";
		$files = $db->getAll($sql);
		foreach($files as $file) {
		  $list = $list . '<item text="' . htmlspecialchars($file['title']) . '" id="jgl' . $file['audio'] . '" im0="jingle16.png"/>';
		}
		//#######
		//ADVERTS
		//#######
		$sql = "SELECT audiodir.directory as dir, audio.title as title, audio.id as audio 
						FROM audiodir, audio, audiotypes, audiogroups, groupmembers 
						WHERE audio.id = audiodir.audio AND 
							directory = " . pg_escape_string($dirID) . " AND
							audio.id = audiogroups.audio AND 
							audiogroups.permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "' AND 
							audiogroups.groupid = groupmembers.groupid AND 
							groupmembers.userid = $userid AND 
				    	audio.type = audiotypes.id AND (audiotypes.name = 'advert')
						UNION SELECT audiodir.directory as dir, audio.title as title, audio.id as audio 
							FROM audiodir, audio, audiotypes, audiousers 
							WHERE audio.id = audiodir.audio AND 
								directory = " . pg_escape_string($dirID) . " AND
								audio.id = audiousers.audio AND 
								audiousers.permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "' AND 
								audiousers.userid = $userid AND 
				    		audio.type = audiotypes.id AND (audiotypes.name = 'advert')
				    order by title asc";
		$files = $db->getAll($sql);
		foreach($files as $file) {
		  $list = $list . '<item text="' . htmlspecialchars($file['title']) . '" id="adv' . $file['audio'] . '" im0="jingle16.png"/>';
		}	
		//#######
		//CARTSETS
		//#######
		$sql = "SELECT cartsetsdir.dir as dir, cartsets.name as title, cartsets.id as cartset 
							FROM cartsets, cartsetsdir, cartsetsusers  
							WHERE cartsetsdir.dir = " . pg_escape_string($dirID) . " AND 
								cartsetsdir.cartsetid = cartsets.id AND 
								cartsetsusers.cartsetid = cartsets.id AND 
								cartsetsusers.userid = $userid AND 
								cartsetsusers.permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "'  
						UNION (SELECT cartsetsdir.dir as dir, cartsets.name as title, cartsets.id as cartset 
							FROM cartsets, cartsetsdir, cartsetsgroups, groupmembers 
							WHERE cartsetsdir.dir = " . pg_escape_string($dirID) . " AND 
								cartsetsdir.cartsetid = cartsets.id AND 
								cartsetsgroups.cartsetid = cartsets.id AND 
								cartsetsgroups.groupid = groupmembers.groupid AND 
								groupmembers.userid = $userid AND 
								cartsetsgroups.permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "') 
						order by title asc";
		$files = $db->getAll($sql);
		foreach($files as $file) {
		  $list = $list . '<item text="' . htmlspecialchars($file['title']) . '" id="crt' . $file['cartset'] . '" im0="cartset16.png"/>';
		}
		//#######
		//SCRIPTS
		//#######
		$sql = "SELECT scriptsdir.dir as dir, scripts.name as title, scripts.id as script 
							FROM scripts, scriptsdir, scriptusers  
							WHERE scriptsdir.dir = " . pg_escape_string($dirID) . " AND 
								scriptsdir.scriptid = scripts.id AND 
								scriptusers.scriptid = scripts.id AND 
								scriptusers.userid = $userid AND 
								scriptusers.permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "'  
						UNION (SELECT scriptsdir.dir as dir, scripts.name as title, scripts.id as script 
							FROM scripts, scriptsdir, scriptgroups, groupmembers 
							WHERE scriptsdir.dir = " . pg_escape_string($dirID) . " AND 
								scriptsdir.scriptid = scripts.id AND 
								scriptgroups.scriptid = scripts.id AND 
								scriptgroups.groupid = groupmembers.groupid AND 
								groupmembers.userid = $userid AND 
								scriptgroups.permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "') 
						order by title asc";
		$files = $db->getAll($sql);
		foreach($files as $file) {
		  $list = $list . '<item text="' . htmlspecialchars($file['title']) . '" id="scr' . $file['script'] . '" im0="script16.png"/>';
		}
  	return $list;
	}
}
?>
