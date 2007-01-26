<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserCartsetMoveViewer extends Viewer {

  const module = 'DPS';
  protected $activeNode = 'foldersTree';

  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
    $userID = $auth->getUserID();
		$cartsetID = $this->fieldData['cartsetID'];
		if(!is_numeric($cartsetID)) {
			$this->assign('permError', 't');
		} else {
			$flag = false;
			$sql = "select count(*) from cartsetsusers where userid = " . $userID . " and cartsetid = " . pg_escape_string($cartsetID) . "
							and (permissions = 'o' or permissions = 'rw' or permissions = 'w')";
			$check = $db->getOne($sql);
			if($check > 0) {
				$flag = true;
			} else {
				$sql = "select count(*) from cartsetsgroups, groupmembers where groupmembers.userid = " . $userID . " and
						groupmembers.groupid = cartsetsgroups.groupid and cartsetsgroups.cartsetid = " . pg_escape_string($cartsetID) . "
						and (cartsetsgroups.permissions = 'o' or cartsetsgroups.permissions = 'rw' or cartsetsgroups.permissions = 'w')";
				$check = $db->getOne($sql);
				if($check > 0) {
					$flag = true;
				}
			}
			if($flag) {
				$sql = "select * from cartsets where id = " . pg_escape_string($cartsetID);
				$cartset = $db->getRow($sql);
				$treeInfo = $this->treeSetup(0,$userID);
				$treeInfo = '<tree id=\"0\">' . str_replace('"','\"',$treeInfo) . '</tree>';

				$sql = "select count(*) from cartsetsusers where userid = " . $userID . " and cartsetid = " . pg_escape_string($cartsetID) . "
							and (permissions = 'o')";
				$check = $db->getOne($sql);
				if($check > 0) {
					$this->assign('own', 't');
				} else {
					$sql = "select count(*) from cartsetsgroups, groupmembers where groupmembers.userid = " . $userID . " and
						groupmembers.groupid = cartsetsgroups.groupid and cartsetsgroups.cartestid = " . pg_escape_string($cartestID) . "
						and (cartsetsgroups.permissions = 'o')";
					$check = $db->getOne($sql);
					if($check > 0) {
						$this->assign('own', 't');
					}
				}
				$this->assign('cartset', $cartset);
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
