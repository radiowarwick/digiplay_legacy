<?php
/**
 * @package FrontEnds
 * @subpackage Auth
 */
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeViewer('AuthViewer', 'Auth');

class UserViewer extends AuthViewer {
	
	protected function setupTemplate(){
		
		parent::setupTemplate();
		if(isset($this->fieldData['userToEdit'])){
			$uid = $this->fieldData['userToEdit'];
			$this->assign('id', $uid);
		}else{
			$uid = null;
		}
		$this->assignCustomFields('users', $uid);
		
		if(isset($this->fieldData['userToEdit'])){
			$this->assign('treeUser', 'user');
			$this->assign('groupinfo', $this->getGroupInfoForUser($uid));
			$this->assign('username', AuthUtil::getUsername($uid));
		}
		
		$this->assign('users', AuthUtil::getUserList());
		
	}
	
	/**
	 * Get group membership for a user
	 *
	 * This will return an array describing group membership for $user. E.g:
	 * 
	 * Array <br>
	 * ( <br>
	 *     [1] => Array <br>
	 *         ( <br>
	 *             [groupname] => Administrators <br>
	 *             [description] => A group for administrators <br>
	 *         ) <br>
	 *  <br>
	 *     [2] => Array <br>
	 *         ( <br>
	 *             [groupname] => Users <br>
	 *             [description] => A group for users <br>
	 *             [inGroup] => 1 <br>
	 *         ) <br>
	 * ) <br>
	 *
	 * In this example, the user is not a member of Administrators (group id of 
	 * 1), but is a member of Users (group id of 2). Group IDs in given by the 
	 * array indexes - so it is worth noting that they will not always be 
	 * sequential
	 *
	 * @param int $user The user id for which group membership info is required
	 * @return array
	 */
	protected function getGroupInfoForUser($user){
		global $cfg;
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$gsql = "SELECT * FROM groups ORDER BY name";
		$groups = $db->getAll($gsql);
		
		$ugsql = "SELECT groupid FROM usersgroups WHERE userid=$user ORDER BY groupid";
		$usergroups = $db->getColumn($ugsql);
		$out = array();
		
		foreach($groups as $group){
			$out[$group['id']]['groupname'] = $group['name'];
			$out[$group['id']]['description'] = $group['description'];
			if(in_array($group['id'], $usergroups)){
				$out[$group['id']]['inGroup'] = true;
			}
		}
		return $out;
		
	}
	
}

?>
