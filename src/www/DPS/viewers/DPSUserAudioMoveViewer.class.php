<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserAudioMoveViewer extends Viewer {

  const module = 'DPS';
  protected $activeNode = 'foldersTree';

  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
    $userID = $auth->getUserID();
		$audioID = $this->fieldData['audioID'];
		if(!is_numeric($audioID)) {
			$this->assign('permError', 't');
		} else {
			$flag = false;
			$sql = "select count(*) from audiousers where userid = " . $userID . " and audio = " . pg_escape_string($audioID) . "
							and (permissions = 'o' or permissions = 'rw' or permissions = 'w')";
			$check = $db->getOne($sql);
			if($check > 0) {
				$flag = true;
			} else {
				$sql = "select count(*) from audiogroups, groupmembers where groupmembers.userid = " . $userID . " and
						groupmembers.groupid = audiogroups.groupid and audiogroups.audio = " . pg_escape_string($audioID) . "
						and (audiogroups.permissions = 'o' or audiogroups.permissions = 'rw' or audiogroups.permissions = 'w')";
				$check = $db->getOne($sql);
				if($check > 0) {
					$flag = true;
				}
			}
			if($flag) {
				$sql = "select * from audio where id = " . pg_escape_string($audioID);
				$audio = $db->getRow($sql);
				$treeInfo = $this->treeSetup(0,$userID);
				$treeInfo = '<tree id=\"0\">' . str_replace('"','\"',$treeInfo) . '</tree>';

				$sql = "select count(*) from audiousers where userid = " . $userID . " and audio = " . pg_escape_string($audioID) . "
							and (permissions = 'o')";
				$check = $db->getOne($sql);
				if($check > 0) {
					$this->assign('own', 't');
				} else {
					$sql = "select count(*) from audiogroups, groupmembers where groupmembers.userid = " . $userID . " and
						groupmembers.groupid = audiogroups.groupid and audiogroups.audio = " . pg_escape_string($audioID) . "
						and (audiogroups.permissions = 'o')";
					$check = $db->getOne($sql);
					if($check > 0) {
						$this->assign('own', 't');
					}
				}
				$this->assign('audio', $audio);
    		$this->assign('treeData', $treeInfo);
			} else {
				$this->assign('permError', 't');
			}
		}
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
		return $list;
}
}
?>
