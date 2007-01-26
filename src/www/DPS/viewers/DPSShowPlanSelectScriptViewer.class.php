<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['Auth']['dir']['root'] . '/AuthUtil.class.php');
class DPSShowPlanSelectScriptViewer extends Viewer {
	
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
				$treeInfo = $this->treeSetup(0,$userID);
				$treeInfo = '<tree id=\"0\">' . str_replace('"','\"',$treeInfo) . '</tree>';
				$this->assign('folder', $folder);
    		$this->assign('treeData', $treeInfo);
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
						UNION (SELECT DISTINCT dir.id, dir.parent, dir.name, dir.notes 
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
								dir.parent = " . pg_escape_string($dirID) . ")  
						ORDER BY name asc";
    $users = $db->getAll($sql);
   	foreach($users as $user) {
     	if($user != false) {
				$list = $list . '<item text="' . htmlspecialchars($user['name']) . '" id="dir' . $user['id'] . '" im0="folderClosed.gif">';
      	$list = $list . $this->treeSetup($user['id'],$userid);
				$list = $list . '</item>';
			}
    }
		  //#######
			//SCRIPTS
			//#######
			$sql = "SELECT scriptsdir.id as dir, scripts.name as title, scripts.id as script 
								FROM scripts, scriptsdir, scriptusers  
								WHERE scriptsdir.dir = " . pg_escape_string($dirID) . " AND 
									scriptsdir.scriptid = scripts.id AND 
									scriptusers.scriptid = scripts.id AND 
									scriptusers.userid = $userid AND 
									(scriptusers.permissions = 'o' OR scriptusers.permissions = 'r' OR scriptusers.permissions = 'rw') 
							UNION (SELECT scriptsdir.id as dir, scripts.name as title, scripts.id as script 
								FROM scripts, scriptsdir, scriptgroups, groupmembers 
								WHERE scriptsdir.dir = " . pg_escape_string($dirID) . " AND 
									scriptsdir.scriptid = scripts.id AND 
									scriptgroups.scriptid = scripts.id AND 
									scriptgroups.groupid = groupmembers.groupid AND 
									groupmembers.userid = $userid AND 
									(scriptgroups.permissions = 'o' OR scriptgroups.permissions = 'r' OR scriptgroups.permissions = 'rw')) 
							order by title asc";
			$files = $db->getAll($sql);
			foreach($files as $file) {
			  $list = $list . '<item text="' . htmlspecialchars($file['title']) . '" id="scr' . $file['script'] . '"/>';
			}
  	return $list;
	}

}
?>
