<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['Auth']['dir']['root'] . '/AuthUtil.class.php');
class DPSShowPlanSelectJingleViewer extends Viewer {
	
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
    $sql = "SELECT dir.id, dir.parent, dir.name, dir.notes 
						FROM dir, users, dirusers 
						WHERE 
    					dir.id = dirusers.directory AND 
							(dirusers.permissions = 'r' OR 
								dirusers.permissions = 'w' OR 
								dirusers.permissions = 'rw' OR 
								dirusers.permissions = 'o') AND 
							dirusers.userid = $userid AND 
							dir.parent = " . pg_escape_string($dirID) . " 
						UNION (SELECT dir.id, dir.parent, dir.name, dir.notes 
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
		//JINGLES
		//#######
		$sql = "SELECT audiodir.id as dir, audio.title as title, audio.id as audio 
						FROM audiodir, audio, audiotypes, audiogroups, groupmembers 
						WHERE audio.id = audiodir.audio AND 
							directory = " . pg_escape_string($dirID) . " AND
							audio.id = audiogroups.audio AND 
							(audiogroups.permissions = 'o' OR audiogroups.permissions = 'r' OR audiogroups.permissions = 'rw') AND 
							audiogroups.groupid = groupmembers.groupid AND 
							groupmembers.userid = $userid AND 
				    	audio.type = audiotypes.id AND (audiotypes.name = 'jingle')
						UNION SELECT audiodir.id as dir, audio.title as title, audio.id as audio 
							FROM audiodir, audio, audiotypes, audiousers 
							WHERE audio.id = audiodir.audio AND 
								directory = " . pg_escape_string($dirID) . " AND
								audio.id = audiousers.audio AND 
								(audiousers.permissions = 'o' OR audiousers.permissions = 'r' OR audiousers.permissions = 'rw') AND 
								audiousers.userid = $userid AND 
				    		audio.type = audiotypes.id AND (audiotypes.name = 'jingle')
				    order by title asc";
		$files = $db->getAll($sql);
		foreach($files as $file) {
		  $list = $list . '<item text="' . htmlspecialchars($file['title']) . '" id="jgl' . $file['audio'] . '"/>';
		}
  	return $list;
	}

}
?>
