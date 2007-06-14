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
		$this->assign('id', $gid);
		if(isset($this->fieldData['groupToEdit'])){
			
			$this->assign('treeUser', 'group');
			$this->assign('userinfo', $this->getUserInfoForGroup($gid));
			$this->assign('groupname', AuthUtil::getGroupname($gid));
		}
		$this->assign('groups', AuthUtil::getGroupList());
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
		
		$ugsql = "SELECT userid FROM usersgroups WHERE groupid='$gid' ORDER BY id";
		$usergroups = $db->getColumn($ugsql);
		
		$out = array();
		
		foreach($users as $user) {
			$out[$user['id']]['username'] = $user['username'];
			//$out[$user['userid']]['realname'] = "{$user['firstName']} {$user['lastName']}";
			if(in_array($user['id'], $usergroups)){
				$out[$user['id']]['inGroup'] = true;
			}
		}
		return $out;
	}
	
	public static function singleRealmTree($realmID, $ID, $group) {
		global $cfg;
		$db = Database::getInstance($cfg['Auth']['dsn']);
			//get all children of the node specified
		$sql = "SELECT * from realms
			WHERE realms.parent = $realmID";
		$subRealms = $db->getAll($sql);
		$list = '';
		foreach($subRealms as $realm) {
			$sql = "SELECT count(*) FROM realms
				WHERE parent = " . $realm['realmid'];
			if($db->getOne($sql) > 0) {
				$child = 1;
			} else {
				$child = 0;
			}
			if(!$group) { //group realmtree
				$uAccess = AuthUtil::getUserAccess($realm['realmid'], $ID);
				$gAccess = AuthUtil::getGroupAccessForUser($realm['realmid'], $ID);
			} else { //user realmtree
				$gAccess = AuthUtil::getGroupAccess($realm['realmid'], $ID);
				if($gAccess = 'y') {
					$list = $list . '<item text="' . htmlspecialchars($realm['name']) .
						' (a,d,i)" id="rlm' . $realm['realmid'] . '" im0="green.gif" child="' .
						$child . '" >';
				} elseif ($gAccess = 'n') {
					$list = $list . '<item text="' . htmlspecialchars($realm['name']) .
						' (a,d,i)" id="rlm' . $realm['realmid'] . '" im0="red.gif" child="' .
						$child . '" >';
				} else {
					$list = $list . '<item text="' . htmlspecialchars($realm['name']) .
						' (a,d,i)" id="rlm' . $realm['realmid'] . '" im0="white.gif" child="' .
						$child . '" >';
				}
			}
		}
		return $list;
	}
}
?>
