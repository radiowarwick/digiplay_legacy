<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserScriptMoveViewer extends Viewer {

  const module = 'DPS';
  protected $activeNode = 'foldersTree';

  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
    $userID = $auth->getUserID();
		$scriptID = $this->fieldData['scriptID'];
		if(!is_numeric($scriptID)) {
			$this->assign('permError', 't');
		} else {
			$flag = false;
			$sql = "select count(*) from scriptusers where userid = " . $userID . " and scriptid = " . pg_escape_string($scriptID) . "
							and (permissions = 'o' or permissions = 'rw' or permissions = 'w')";
			$check = $db->getOne($sql);
			if($check > 0) {
				$flag = true;
			} else {
				$sql = "select count(*) from scriptgroups, groupmembers where groupmembers.userid = " . $userID . " and
						groupmembers.groupid = scriptgroups.groupid and scriptgroups.scriptid = " . pg_escape_string($scriptID) . "
						and (scriptgroups.permissions = 'o' or scriptgroups.permissions = 'rw' or scriptgroups.permissions = 'w')";
				$check = $db->getOne($sql);
				if($check > 0) {
					$flag = true;
				}
			}
			if($flag) {
				$sql = "select * from scripts where id = " . pg_escape_string($scriptID);
				$script = $db->getRow($sql);
				$treeInfo = $this->treeSetup(0,$userID);
				$treeInfo = '<tree id=\"0\">' . str_replace('"','\"',$treeInfo) . '</tree>';

				$sql = "select count(*) from scriptusers where userid = " . $userID . " and scriptid = " . pg_escape_string($scriptID) . "
							and (permissions = 'o')";
				$check = $db->getOne($sql);
				if($check > 0) {
					$this->assign('own', 't');
				} else {
					$sql = "select count(*) from scriptgroups, groupmembers where groupmembers.userid = " . $userID . " and
						groupmembers.groupid = scriptgroups.groupid and scriptgroups.scriptid = " . pg_escape_string($scriptID) . "
						and (audiogroups.permissions = 'o')";
					$check = $db->getOne($sql);
					if($check > 0) {
						$this->assign('own', 't');
					}
				}
				$this->assign('script', $script);
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
