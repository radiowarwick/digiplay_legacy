<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserFileMoveViewer extends Viewer {

  const module = 'DPS';
  protected $activeNode = 'foldersTree';

  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
    $userID = $auth->getUserID();
		$dirID = $this->fieldData['rootdir'];
		if(!is_numeric($dirID)) {
			$this->assign('permError', 't');
		} else {
			$flag = false;
			$sql = "select count(*) from dirusers where userid = " . $userID . " and directory = " . pg_escape_string($dirID) . "
							and (permissions = 'o' or permissions = 'rw' or permissions = 'w')";
			$check = $db->getOne($sql);
			if($check > 0) {
				$flag = true;
			} else {
				$sql = "select count(*) from dirgroups, groupmembers where groupmembers.userid = " . $userID . " and
						groupmembers.groupid = dirgroups.groupid and directory = " . pg_escape_string($dirID) . "
						and (dirgroups.permissions = 'o' or dirgroups.permissions = 'rw' or dirgroups.permissions = 'w')";
				$check = $db->getOne($sql);
				if($check > 0) {
					$flag = true;
				}
			}
			if($flag) {
			$sql = "select * from dir where id = " . pg_escape_string($dirID);
			$folder = $db->getRow($sql);
			$treeInfo = $this->treeSetup(0,$userID);
			$treeInfo = '<tree id=\"0\">' . str_replace('"','\"',$treeInfo) . '</tree>';
			$this->assign('folder', $folder);
    	$this->assign('treeData', $treeInfo);
			} else {
				$this->assign('permError', 't');
			}
		}
  }

function treeSetup($dirID,$userid) {
  global $cfg;
	$db = Database::getInstance($cfg['DPS']['dsn']);
  if($userid == null) {
    $users = array();
    $sql = "SELECT DISTINCT dir.id, dir.parent, dir.name, dir.notes FROM dir, dirgroups, groups, groupmembers, users WHERE 
            dir.id = dirgroups.directory AND (dirgroups.permissions= 'r' OR dirgroups.permissions = 'w' OR dirgroups.permissions = 'rw' OR dirgroups.permissions = 'o') AND dirgroups.groupid = groups.id AND 
            groups.id = groupmembers.groupid AND groupmembers.groupid = " . $cfg['DPS']['allusersgroupid'] . "  
            AND dir.parent = " . pg_escape_string($dirID);
    $groups = $db->getAll($sql);
  } else {
    $sql = "SELECT DISTINCT dir.id, dir.parent, dir.name, dir.notes FROM dir, users, dirusers WHERE 
    dir.id = dirusers.directory AND (dirusers.permissions = 'r' OR dirusers.permissions = 'w' OR dirusers.permissions = 'rw' OR dirusers.permissions = 'o') AND dirusers.userid = $userid 
    AND dir.parent = " . pg_escape_string($dirID);
    $users = $db->getAll($sql);
    $sql = "SELECT DISTINCT dir.id, dir.parent, dir.name, dir.notes FROM dir, dirgroups, groups, groupmembers, users WHERE
            dir.id = dirgroups.directory AND (dirgroups.permissions= 'r' OR dirgroups.permissions = 'w' OR dirgroups.permissions = 'rw' OR dirgroups.permissions = 'o') AND dirgroups.groupid = groups.id AND
            groups.id = groupmembers.groupid AND groupmembers.userid = $userid
            AND dir.parent = " . pg_escape_string($dirID);
    $groups = $db->getAll($sql);
  }
  $total = 0;
  $done[0] = -1;
  if($userid != null) {
    foreach($users as $user) {
      if($user != false) {
        $total++;
				$list = $list . '<item text="' . htmlspecialchars($user['name']) . '" id="dir' . $user['id'] . '" im0="folderClosed.gif">';
      	$list = $list . $this->treeSetup($user['id'],$userid);
				$list = $list . '</item>';
			}
			$done[$total] = $user['id'];
    }
  }
  foreach($groups as $group) {
    if(!array_search($group['id'],$done)) {
    	$total++;
			$list = $list . '<item text="' . htmlspecialchars($group['name']) . '" id="dir' . $group['id'] . '" im0="folderClosed.gif">';
      $list = $list . $this->treeSetup($group['id'],$userid);
			$list = $list . '</item>';
    }
  }
  return $list;
}
}
?>
