<?php
/**
 * @package FrontEnds
 * @subpackage Auth
 */
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeViewer('AuthViewer', 'Auth');

class GroupViewer extends AuthViewer {
	
	protected function setupTemplate(){
		
		parent::setupTemplate();
		if(isset($this->fieldData['groupToEdit'])){
			$gid = $this->fieldData['groupToEdit'];
		}else{
			$gid = null;
		}
		$this->assignCustomFields('groups', $gid);
		if(isset($this->fieldData['groupToEdit'])){
			
			$this->assign('realminfo', AuthUtil::buildRealmTree($gid,true));
			$this->assign('userinfo', $this->getUserInfoForGroup($gid));
			$this->assign('groupname', AuthUtil::getGroupname($gid));
		}
		
		$this->assign('groups', AuthUtil::getGroupList());
		
	}
	
	/**
	 * Build a realm tree structure
	 * 
	 * This method calls {@link buildRealmTree} to build a realm tree data 
	 * structure for the group specified by $gid. See {@link buildRealmTree} 
	 * for more info about the data structure.
	 * 
	 * @param int $gid
	 * @return array A realm tree data structure
	 */
	protected function buildRealmTreeForGroup($gid){
		return AuthUtil::buildRealmTree($gid, true);
	}
	
	/**
	 * Get users-group link info
	 *
	 * This will return an array of users info, where each element indicates if
	 * the users is a memeber in the specified group
	 * 
	 * Array
	 * (
 	 *    [1] => Array
 	 *        (
 	 *            [username] => adam
 	 *            [realname] => Adam Charnock
     *            [inGroup] => 1
 	 *        )
	 * 
 	 *    [2] => Array
 	 *        (
 	 *            [username] => dan
 	 *            [realname] => Dan Hammond
	 *         )
	 * 
 	 *    [3] => Array
 	 *        (
 	 *            [username] => ella
 	 *            [realname] => Ella Sprung
 	 *        )
	 * 
 	 *    [4] => Array
  	 *       (
  	 *           [username] => kirsty
  	 *           [realname] => Kirsty Longford
 	 *        )
	 * 
	 * )
	 *
	 * @param int $gid The group id for which user membership info is required
	 * @return array
	 */
	protected function getUserInfoForGroup($gid){
		global $cfg;
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$usql = "SELECT * FROM users ORDER BY username";
		$users = $db->getAll($usql);
		
		$ugsql = "SELECT userid FROM groupmembers WHERE id='$gid' ORDER BY id";
		$usergroups = $db->getColumn($ugsql);
		
		$out = array();
		
		foreach($users as $user){
			$out[$user['id']]['username'] = $user['username'];
			//$out[$user['userid']]['realname'] = "{$user['firstName']} {$user['lastName']}";
			if(in_array($user['id'], $usergroups)){
				$out[$user['id']]['inGroup'] = true;
			}
		}
		return $out;
		
	}
	
}

?>
