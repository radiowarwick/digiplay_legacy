<?php
/**
* @package Auth
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class AuthUtilBase {


const module = "Auth";
/**
 * Return a users permission for a realm
 * 
 * This method will return the permissions a user has to a specified realm 
 * path. This method considers permissions of parent realms, and the 
 * permissions specifed for the groups to which the user belongs.
 * 
 * @param array $realmPath A realm path (either array of realm IDs or of realm names)
 * @param mixed $user Either a user name or a user id
 * @return boolean True/false if access is allowed/denied respectively
 * @todo Consider adding some caching to this method
 */
public static function getDetailedUserrealmAccess($realmPath, $user){
	global $cfg;
	//echo "Starting Detailed user realm access<br><br>";
	//debug_print_backtrace();
	//echo "<br><br>";
	$q  = Database::getTotalQueries();
	$parentrealmID = 0;
	$allow = null;
	$isIDrealmPath = true;
	foreach($realmPath as $rp){
		if(!is_numeric($rp)){ $isIDrealmPath = false; }
	}
	
	$db = Database::getInstance();
	//echo "Executing: " . "return " . $cfg['Auth']['authUtilClassModule'] . "::getUserID($user);<br>";
	$userID = eval("return " . $cfg['Auth']['authUtilClassModule'] . "::getUserID($user);");
	//echo "Getting detailed realm access for: " . $user . " ID as " . $userID . "<br>";
	for($i = 0; $i < count($realmPath) && $allow !== false; $i++){
		if($isIDrealmPath){
			$realmID = $realmPath[$i];
		}else{
			$sql = "SELECT realmid FROM realms WHERE name = '{$realmPath[$i]}' AND parentid = '$parentrealmID'";
			$realmID = $db->getOne($sql);
		}
		
		$groups = eval("return " . $cfg['Auth']['authUtilClassModule'] . "::getGroupsListForUser($user);");
		if(count($groups) > 0){
				$groupList = join(',', $groups);
				$sql  = "SELECT allow FROM realmgrouplink WHERE realmid = '$realmID' AND groupid IN ($groupList)";
				$groupperms = $db->getColumn($sql);
				
				foreach($groupperms as $gp){
					if($gp == 'y' && $allow !== false){
						$allow = true;
					}elseif($gp == 'n'){
						$allow = false;
					}
				}
			}
			$sql  = "SELECT allow FROM realmuserlink WHERE realmid = '$realmID' AND userid = '$userID'";
			$userperms = $db->getColumn($sql);
			
			foreach($userperms as $up){
				//Deny takes precidence over allow
				if($up == 'y' && $allow !== false){
					$allow = true;
				}elseif($up == 'n'){
					$allow = false;
				}
			}
			
			$parentrealmID = $realmID;
		}
		//echo "Finished getting Detailted user realm access<br>";
		return $allow;
	}
	
	/**
	 * Get a realm path
	 *
	 * Returns an array specifing the path to the realm specified 
	 * by $realmid. A realm path is an array of realm IDs that show a path 
	 * to the specified realm - this is needed because realms have a 
	 * hierarchical/tree structure. Element 0 will always be of value 0, as 
	 * this is the always the root realm.<p />
	 *
	 * @param int $realmid The id of the realm for which the path should be returned
	 * @return array An realm path as described above. Each element is a realm id, not a name.
	 */
	public static function getRealmPath($realmid){
		
		static $loaded = false;
		static $cache = array();
		
		if($loaded && !key_exists($realmid, $cache)){
			throw new LoggedException("An invalid realm ID ('$realmid') was passed", 0, self::module, 'error');
		}
		
		if($loaded){
			return $cache[$realmid];
		}
		
		global $cfg;
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$sql = 'SELECT realmid, realmpath FROM realms';
		$dotPaths = $db->getAll($sql);
		
		foreach($dotPaths as $id => $path){
			$cache[$path['realmid']] = explode('.', $path['realmpath']);
		}
		
		$loaded = true;
		
		return $cache[$realmid];
	}
	
	/**
	 * Returns a generated realm path array
	 * 
	 * Returns an array specifing the path to the realm specified 
	 * by $realmid. A realm path is an array of realm IDs that show a path 
	 * to the specified realm - this is needed because realms have a 
	 * hierarchical/tree structure. Element 0 will always be of value 0, as 
	 * this is the always the root realm.<p />
	 * 
	 * <b>Note:</b> As of rev 102, this function is private. You should instead
	 * use the new getRealmPath(). This new function uses redundant database 
	 * information to reduce processing time and the number of queries.
	 * 
	 * @param int $realmid The id of the realm for which the path should be returned
	 * @return array An realm path as described above. Each element is a realm id, not a name.
	 */
	private static function makeRealmPath($realmid){
		global $cfg;
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$sql = "SELECT parentid FROM realms WHERE realmid = ?";
		$parent = $db->getOne($sql, array($realmid));
		
		if($parent == 0){
			return array($realmid);	
		}else{
			$store = eval("return " . $cfg['Auth']['authUtilClassModule'] . "::makeRealmPath($parent);");
			return array_merge($store, array($realmid));
		}
	}
	
	/**
	 * Get user realm permissions ignoring inheritance
	 * 
	 * This will return the permission as user has for the specified realm. 
	 * This method will only consider permissions that are ecplicitly set 
	 * for the realm. I.e. The permissions of parent realms are ignored
	 * 
	 * @param int $realmid The realm ID
	 * @param int $user The user ID
	 * @return mixed True if access is directly stated, false if directly denied, null otherwise
	 */
	public static function getUserAccess($realmid, $user){
		global $cfg;
		static $cache;
		
		if(isset($cache[$realmid . '_' . $user])){
			return $cache[$realmid . '_' . $user];
		}
		
		$sql = "SELECT allow FROM realmuserlink WHERE realmid='$realmid' AND userid='$user'";
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$allow = $db->getOne($sql);
		if($allow == 'y'){
			$out = 'y';
		}elseif($allow == 'n'){
			$out = 'n';
		}else{
			$out = '-';
		}
		
		$cache[$realmid . '_' . $user] = $out;
		return $cache[$realmid . '_' . $user];
		
	}
	
	/**
	 * Get a users group permissions for a relm
	 * 
	 * This method will analyse all the groups of which $user is a member and 
	 * and return the overall permission as described below:
	 *
	 * - = non specified
	 * y = access directly stated
	 * n = access directly denied
	 * ! = conflicting access directly stated, deny takes priority
	 * 
	 * Note: This method only considers permissioins for groups to which a 
	 * user belongs - not permissions specified for the particular user. If 
	 * this is required then {@link getUserAccess} should be used.
	 * 
	 * @param int $realmid The id of the realm for which permissions should checked
	 * @param int $uid The id of the user whose realms should be checked
	 * @return int $user The user id
	 */
	public static function getGroupAccessForUser($realmid, $uid){
		global $cfg;
		static $cache;
		
		if(isset($cache[$realmid . '_' . $uid])){
			return $cache[$realmid . '_' . $uid];
		}
		
		$sql = "SELECT allow FROM realmgrouplink, usergrouplink WHERE
		        realmgrouplink.groupid = usergrouplink.groupid AND
		        realmgrouplink.realmid = '$realmid' AND
		        usergrouplink.userid = '{$uid}'";
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$allow = $db->getColumn($sql);
		
		if(count($allow) == 0){
			$out = '-';
		}elseif(in_array('y', $allow) && in_array('n', $allow)){
			$out = '!';
		}else{
			//Array must be all y or no - so return the first element
			$out = $allow[0];
		}
		$cache[$realmid . '_' . $uid] = $out;
		return $cache[$realmid . '_' . $uid];
	}
	
	/**
	 * Get a groups permission for a relm
	 * 
	 * This method will return a groups realm permission as described below:
	 *
	 * - = non specified
	 * y = access directly stated
	 * n = access directly denied
	 * ! = conflicting access directly stated, deny takes priority
	 * 
	 * Note: This method does not consider permission inheritance
	 * 
	 * @param int $realmid The id of the realm for which permissions should checked
	 * @return int $gid The id of the group
	 */
	public static function getGroupAccess($realmid, $gid){
		global $cfg;
		$sql = "SELECT allow FROM realmgrouplink 
		        WHERE groupid = '$gid' AND 
		        realmid = '$realmid'";
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$perm = $db->getOne($sql);
		
		if($perm != 'y' && $perm != 'n') {
			$perm = '-';
		}
		
		return $perm;
	}
	
	/**
	 * Get the groups to which a user belongs
	 *
	 * @param mixed $user Either a user name or user id
	 * @return array An array of group IDs, to which the user belongs
	 */
	public static function getGroupsListForUser($user){
		global $cfg;
		static $groups = array();
		if(!isset($groups[$user])){
			$userid = eval("return " . $cfg['Auth']['authUtilClassModule'] . "::getUserID($user);");
			$sql = "SELECT groupid FROM usergrouplink WHERE userid = {$userid}";
			//echo $sql;
			$db = Database::getInstance();
			$groups[$user] = $db->getColumn($sql);
		}
		return $groups[$user];
	}
	
	/**
	 * Get a user id
	 * 
	 * @param mixed $user Either a user name or a user id (in the latter case, $user will simply be returned)
	 * @return int The user ID for the specified user.
	 * 
	 */
	public static function getUserID($user){
		
		static $users = array();
		global $cfg;
		if(!eval("return " . $cfg['Auth']['authUtilClassModule'] . "::isUsername($user);")){
			return $user;
		}else{
			if(!isset($users[$user])){
				$sql = "SELECT userid FROM users WHERE username = '$user'";
				$db = Database::getInstance();
				$users[$user] = $db->getOne($sql);
			}
			return $users[$user];
		}
	}
	
	/**
	 * Get the user name from a userid
	 *
	 * @param int $userid The user id
	 * @return string The user name of the user specified by $userid
	 */
	public static function getUsername($userid){
		static $usernames = array();
		global $cfg;
		if(!eval("return " . $cfg['Auth']['authUtilClassModule'] . "::isUserID($userid);")){
			throw new LoggedException("An invalid user id ($userid) was passed", 0, self::module, 'error');
		}else{
			if(!isset($usernames[$userid])){
				$sql = "SELECT username FROM users WHERE userid = '$userid'";
				$db = Database::getInstance();
				$usernames[$userid] = $db->getOne($sql);
			}
			return $usernames[$userid];
		}
	}
	
	/**
	 * Get the group name from a groupid
	 *
	 * @param int $groupid The group ID
	 * @return string The group name of the group specified by $groupid
	 */
	public static function getGroupname($groupid){
		static $groupnames = array();
		
		if(!is_numeric($groupid)){
			throw new LoggedException("An invalid group id ($groupid) was passed", 0, self::module, 'error');
		}else{
			if(!isset($groupnames[$groupid])){
				$sql = "SELECT groupname FROM groups WHERE groupid = '$groupid'";
				$db = Database::getInstance();
				$groupnames[$groupid] = $db->getOne($sql);
			}
			return $groupnames[$groupid];
		}
	}
	
	/**
	 * Get the group id from a group name
	 *
	 * @param int $groupname The group name
	 * @return string The id of the group specified by $groupname
	 */
	public static function getGroupID($groupname){
		static $cache = array();
		
		if(!isset($cache[$groupname])){
			$sql = "SELECT groupid FROM groups WHERE groupname = ?";
			$db = Database::getInstance();
			$cache[$groupname] = $db->getOne($sql, array($groupname));
		}
		
		return $cache[$groupname];
	}
	
	
	
	/**
	 * Get the realm name from a realm id
	 *
	 * @param int $realmid The realm ID
	 * @return string The realm name of the realm specified by $realmid
	 * @todo Replace call to is_numeric with somthing more robust (to ensure no '.' or '-')
	 */
	public static function getRealmname($realmid){
		static $realmnames = array();
		
		if(!is_numeric($realmid)){
			throw new LoggedException("An invalid realm id ($realmid) was passed", 0, self::module, 'error');
		}else{
			if(!isset($realmnames[$realmid])){
				$sql = "SELECT name FROM realms WHERE realmid = '$realmid'";
				$db = Database::getInstance();
				$realmnames[$realmid] = $db->getOne($sql);
			}
			return $realmnames[$realmid];
		}
	}
	
	/**
	 * Add or remove a user from a group
	 *
	 * @param boolean $add True/false if the user should be added/removed from the group respectively
	 * @param int $userid The id of ther user to add to group $groupid
	 * @param int $groupid The id of the group which $userid should be added to
	 *
	 */
	public static function editUserGroup($userid, $groupid, $add){
		$db = Database::getInstance();
		
		$where = "userid = '$userid' AND groupid = '$groupid'";
		
		if($add){
			$csql = "SELECT COUNT(*) FROM usergrouplink WHERE $where";
			$count = $db->getOne($csql);
			if($count == 0){
				$inserts['userid'] = $userid;
				$inserts['groupid'] = $groupid;
				$db->insert('usergrouplink', $inserts);
			}
		}else{
			$db->delete('usergrouplink', $where);
		}
	}
	
	/**
	 * Set the user permission for a relm
	 *
	 * This will set the user permissions for a relm as specified by $perm. 
	 * $perm should be either 'y', 'n', or null. If a different value is 
	 * passed then an exception will be thrown. <p />
	 * Value for the userid and the relmid are read from the $fieldData array.
	 *
	 * @param string $perm Either 'y', 'n', or null, indiating allow, deny, or ignore respectively
	 * @param int $userid The id of ther user for whom to modify relm permissions
	 * @param int $realmid The id of the ream to apply permission to concerning $userid
	 * 
	 */
	public static function editUserRelmAccess($userid, $realmid, $perm){
		global $cfg;
		
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$where = "userid = '$userid' AND realmid = '$realmid'";
		if(is_null($perm)){
			$db->delete('realmuserlink', $where);
		}elseif($perm == 'y' || $perm == 'n'){
			$csql = "SELECT COUNT(*) FROM realmuserlink WHERE $where";
			$count = $db->getOne($csql);
			
			if($count == 0){
				$inserts['userid'] = $userid;
				$inserts['realmid'] = $realmid;
				$inserts['allow'] = $perm;
				$db->insert('realmuserlink', $inserts);
			}else{
				$db->update('realmuserlink', array('allow' => $perm), $where);
			}
		}else{
			throw new LoggedException("An invalid permission ($perm) was passed", 0, self::module, 'warning');	
		}
	}
	
	/**
	 * Set the group permission for a relm
	 *
	 * This will set the group permissions for a relm as specified by $perm. 
	 * $perm should be either 'y', 'n', or null. If a different value is 
	 * passed then an exception will be thrown. <p />
	 * Value for the groupid and the relmid are read from the $fieldData array.
	 *
	 * @param string $perm Either 'y', 'n', or null, indiating allow, deny, or ignore
	 * @param int $groupid The id of ther group for whom to modify relm permissions
	 * @param int $realmid The id of the ream to apply permission to concerning $groupid
	 * 
	 */
	public static function editGroupRelmAccess($groupid, $realmid, $perm){
		global $cfg;
		
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$where = "groupid = '$groupid' AND realmid = '$realmid'";
		if(is_null($perm)){
			$db->delete('realmgrouplink', $where);
		}elseif($perm == 'y' || $perm == 'n'){
			$csql = "SELECT COUNT(*) FROM realmgrouplink WHERE $where";
			$count = $db->getOne($csql);
			
			if($count == 0){
				$inserts['groupid'] = $groupid;
				$inserts['realmid'] = $realmid;
				$inserts['allow'] = $perm;
				$db->insert('realmgrouplink', $inserts);
			}else{
				$db->update('realmgrouplink', array('allow' => $perm), $where);
			}
		}else{
			throw new LoggedException("An invalid permission ($perm) was passed", 0, self::module, 'warning');	
		}
	}
	
	/**
	 * Determine a users permission for a template
	 * 
	 * This will return the permissions for the user specified by $user for 
	 * the template specified by $templateID. These permissions found using 
	 * calls to {@link getDetailedUserrealmAccess}
	 * 
	 * @param mixed $user The user id or name
	 * @param int $templateID The template ID
	 * @return boolean True/false if access is allowed/denied respectively
	 */
	public static function templateAccessAllowed($templateID, $user){
		global $cfg;
		BasicLogger::logMessage("Checking template access for user: $user for templateID: $templateID",self::module,"debug");
		$db = Database::getInstance($cfg['Auth']['dsn']);
		
		if(eval("return " . $cfg['Auth']['authUtilClassModule'] . "::isUserID($user);")){
			$uid = $user;
		}else{
			$uid = AuthUtil::getUserID($user);
		}
		
		$ridsql = "SELECT realmid FROM templates WHERE templateid = '$templateID'";
		$realm = $db->getOne($ridsql);
		
		$allow = false;
		
		$realmPath = eval("return " . $cfg['Auth']['authUtilClassModule'] . "::getRealmPath($realm);");
		$access = AuthUtil::getDetailedUserrealmAccess($realmPath, $uid);
		if($access) {
			$allow = true;
		}
		BasicLogger::logMessage("Template access for user: $user for templateID: $templateID is $allow",self::module,"debug");
		
		return $allow;
	}
	
	/**
	 * Require access to a realm
	 *
	 * This method will ensure that the current user has access to the 
	 * specified realm before continuing. If the user does not have 
	 * permission, then the permission error template will be initialised 
	 * and exit() called immediatly afterwards.
	 *
	 * @param int $realmID The ID of the realm for which access is required
	 * @return boolean True if access is allowed. Program flow does not contine otherwise
	 *
	 */
	public static function requireRealm($realmID){
		global $cfg;
		
		$auth = Auth::getInstance();
		$uid = $auth->getUserID();
		$realmPath = AuthUtil::getRealmPath($realmID);
		if(AuthUtil::getDetailedUserrealmAccess($realmPath, $uid)){
			return true;
		}else{
			$permissionErrorTemplateID = MVCUtils::getPermErrorTemplateID();
			//$error = array('permission' => 'You do not have permission to perform this action');
			//MVCUtils::initializeViewer(array($permissionErrorTemplateID), null, $cfg['Auth']['permissionErrorTemplateModule'], null, $error);
			MVCUtils::redirect($permissionErrorTemplateID);
		}
		exit(1);
	}
	
	public static function updateRedundantInfo($realmid = array()){
		global $cfg;
		
		$db = Database::getInstance($cfg['Auth']['dsn']);
		
		if(count($realmid) == 0){
			$sql = 'SELECT realmid FROM realms';
			$realmIDs = $db->getColumn($sql);
		}else{
			$realmIDs = $realmid;
		}
		
		$maxID = $db->getOne('SELECT MAX(realmid) FROM realms');
		$maxIDWidth = strlen($maxID);
		
		foreach($realmIDs as $id){
			$realmPath = eval("return " . $cfg['Auth']['authUtilClassModule'] . "::makeRealmPath($id);");
			$depth = count($realmPath) - 1;
			$strPath = array();
			for($i=0;$i<count($realmPath);$i++){
				$strPath[$i] = str_pad($realmPath[$i], $maxIDWidth, '0', STR_PAD_LEFT);
			}
			
			$updates = array('depth' => $depth, 'realmpath' => join('.', $strPath));
			
			$db->update('realms', $updates, " realmid = $id");
		}
	}
	
	public static function checkPassword($user, $pass){
		$md5pass = md5($pass);
		
		global $cfg;
		
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$sql = "SELECT COUNT(*) FROM users WHERE username = '{$user}' AND password = '{$md5pass}'";
		$validCount = $db->getOne($sql);
		
		return ($validCount == 1);
	}
	
	/**
	 * Change a user's password
	 *
	 * @param int $userID The ID of the user
	 * @param string $password The new password (in plain text)
	 */
	public static function changePassword($userID, $password){
		global $cfg;
		
		if(!is_numeric($userID)){
			throw new LoggedException('A non-numeric (invalid) userID was passed', 0, self::module, 'error');
		}
		
		$md5pass = md5($password);
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$update = array('password' => $md5pass);
		
		$db->update('users', $update, "userid = $userID");
	}
	
	public static function isUserID($usernameOrID){
		static $cache = array();
		global $cfg;
		if(!is_numeric($usernameOrID)) {
			return false;
		}
		if(!isset($cache[$usernameOrID])){
			$sql = 'SELECT COUNT(*) FROM users WHERE userid = ?';
			$db = Database::getInstance($cfg['Auth']['dsn']);
			$cache[$usernameOrID] = ($db->getOne($sql, array($usernameOrID)) == 1);
		}
		
		return $cache[$usernameOrID];
	}
	
	public static function isUsername($usernameOrID){
		static $cache = array();
		global $cfg;

		$year = substr($usernameOrID, 0, 2);
		$yearInRange = ($year > 80 || $year < 20);
		
		if(!is_numeric($usernameOrID)){
			return true;
		}
		
		if($yearInRange && (strlen($usernameOrID) == 7)){
			return true;
		}else{
			return false;
		}
	}
	
	public static function addRealm($Rpath, $name, $customVals){
		global $cfg;
		if(!is_numeric($Rpath)) {
            $Rpath = AuthUtil::getRealmIDFromPath($Rpath);
        }
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$sql = "SELECT * FROM realms where parentid = ? AND name = ?";
		if(!$db->getRow($sql,array($Rpath,$name))) {
            $insert['name'] = $name;
    		foreach ($cfg['Auth']['realmfields'] as $fieldName => $niceName){
    			if(array_key_exists($fieldName, $customVals)){
    				$insert[$fieldName] = $customVals[$fieldName];
    			}
    		}
            $insert['realmid'] = '#id#';
            $insert['parentid'] = $Rpath;
            $Rpath = $db->insert('realms', $insert);
    		AuthUtil::updateRedundantInfo(array($Rpath));
    		return $Rpath;
		} else {
            return false;
        }
	}
	
	public static function modifyRealm($Rpath, $customVals) {
		global $cfg;
		if(!is_numeric($Rpath)) {
            $Rpath = AuthUtil::getRealmIDFromPath($Rpath);
        }
		foreach ($cfg['Auth']['realmfields'] as $fieldName => $niceName){
		      if(array_key_exists($fieldName, $customVals)){
		          $customValsInsert[$fieldName] = $customVals[$fieldName];
		      }
		}
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$returnVal = $db->update('realms',$customValsInsert,"realmid = $Rpath");
		return $returnVal;
    }
	
    /**
     * Gets the ID of the realm specified
     *
     *
     *
     *
     * @param array $Rpath
     * @return mixed The ID of the realm if realm was found. False if the realm was not found
     */
	public static function getRealmIDFromPath($Rpath) {
        global $cfg;
        $sql = "SELECT d1.realmid FROM ";
        $where = "";
        $Rpath = array_reverse($Rpath);
        $counter = 1;
        $Alength = count($Rpath);
        if($Alength == 0) {
            return false;
        }
        foreach($Rpath as $oneRealm) {
            if($counter != 1) {
                if ($counter != $Alength) {
                    $sql = $sql . ", realms as d" . $counter;
                    $where = $where . " AND d" . $counter . ".parentid = d" . ($counter + 1) . ".realmid AND d" . $counter . ".name=?";
                } else {
                    $sql = $sql . ", realms as d" . $counter;
                    $where = $where . " AND d" . $counter . ".parentid = 0 AND d" . $counter . ".name=?";
                }
            } else {
                $sql = $sql . "realms as d" . $counter;
                if ($counter != $Alength) {
                    $where = $where . "d1.parentid = d2.realmid AND d1.name=?";
                } else {
                    $where = $where . "d1.parentid = 0 AND d1.name=?";
                }
            }
            $counter++;
        }
		$sql = $sql . " WHERE " . $where;
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$id = $db->getOne($sql,$Rpath);
		if(is_null($id)){
			//return false;
			return null;
		}else{
			return $db->getOne($sql,$Rpath);
		}
    }
	/**
	 * Delete A realm
	 *
	 * This will return false if the specfied realm has children. Use
	 * recursiveDeleteRealm() in order to remove children recursively
	 *
	 * @param array $realmPath The path to the realm to delete
	 * @return boolean True if the realm was added, false if the add failed
	 *
	 *
	 *
	 */
	public static function deleteRealm($realmPath){
		global $cfg;
		
		$db = Database::getInstance($cfg['Auth']['dsn']);
        if(!is_numeric($realmPath)) {
            $realmPath = Auth::getRealmIDFromPath($realmPath);
		}
		$sql = "SELECT COUNT(*) FROM realms WHERE parentid = ?";
		$realmCount = $db->getOne($sql, array($realmPath));

		if($realmCount > 0){
			return false;
		}else{
			$db->delete('realms', " realmid = $realmPath");
		}
	}
	/**
	 * Delete A realm
	 *
	 * This will recursively delete the given realm and all below it
	 * and any permissions asociated with them
	 *
	 * @param mixed $realm The name of id of the realm to delete
	 *
	 *
	 *
	 */
	public static function recursiveDeleteRealm($realm){
		global $cfg;
		
		if(!is_numeric($realm)){
			$realm = Auth::getRealmIDFromPath($realm);
		}

		if(!AuthUtil::deleteRealm($realm)){
			$db = Database::getInstance($cfg['Auth']['dsn']);
			$sql = "SELECT realmid FROM realms WHERE parentid = ?";
			$subRealmIDs = $db->getColumn($sql, 0, array($realm));
			/*if(count($subRealmIDs) == 0){
				throw new LoggedException('Somthing seems to have gone wrong', 0, self::module, 'error');
			}*/

			foreach($subRealmIDs as $rid){
				AuthUtil::recursiveDeleteRealm($rid);
			}
		}
		$db->delete('realmgrouplink',"realmid = $realm");
		$db->delete('realmuserlink',"realmid = $realm");
		AuthUtil::deleteRealm($realm);
	}
	
	/**
	 * Get realm info and permissions
	 *
	 * This method returns an array based tree structure. It is defined as 
	 * follows:
	 
	 * - Each element represents realm, and is indexed by the realm name. 
	 * - Each element contains an array of its child realms.
	 * - In addition to an array of child realms, each element contains an 
	 *   element indexed by the string "_DETAILS_". This element is an array 
	 *   of a format similar too:
	 * 
	 *   [_DETAILS_] => Array
	 *   (
	 *   [realmid] => 3
	 *   [name] => Modify
	 *   [parentid] => 1
	 *   [description] => Administration modification realm
	 *   [userallow] => -   (only present if $group=false)
	 *   [groupallow] => -
	 *   )
	 *
	 * @param int $guid The group or user id on which the [groupallow] (and [userallow] in case of users) info is based
	 * @param boolean $group True/False if the structure should describe group/users permissions respectively
	 *
	 *
	 */
	public static function buildRealmTree($guid, $group){
		global $cfg;
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$sql = "SELECT * FROM realms ORDER BY parentid";
		$data = $db->getAll($sql);
		return AuthUtil::recBuildRealmTree($data, array(0), array(), $guid, $group);
	}
	
	/**
	 * Return an array of group names indexed by their id number
	 *
	 * @return array A simply 1D associative array
	 */
	public static function getGroupList(){
		global $cfg;
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$sql = "SELECT groupid, groupname FROM groups ORDER BY groupname";
		$data = $db->getAll($sql);
		$out = array();
		foreach($data as $user){
			$out[$user['groupid']] = $user['groupname'];
		}
		return $out;
	}
	
	/**
	 * Return an array of user names indexed by their id number
	 *
	 * @return array A simple 1D associative array
	 */
	public static function getUserList(){
		global $cfg;
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$sql = "SELECT userid, username FROM users ORDER BY username";
		$data = $db->getAll($sql);
		$out = array();
		foreach($data as $user){
			$out[$user['userid']] = $user['username'];
		}
		return $out;
	}
	
	/**
	 * Return an array of realm names indexed by their id number
	 *
	 * @return array A simply 1D associative array
	 */
	public static function getRealmList(){
		global $cfg;
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$sql = "SELECT realmid, name FROM realms ORDER BY name";
		$data = $db->getAll($sql);
		$out = array();
		foreach($data as $user){
			$out[$user['realmid']] = $user['name'];
		}
		return $out;
	}
	
	public static function buildRealmTreeForUser($uid){
		return AuthUtil::buildRealmTree($uid, false);
	}
	
	public static function recBuildRealmTree($data, $node, $details, $guid, $group){
		if($group === true){
			$details['groupallow'] = AuthUtil::getGroupAccess($node[0], $guid);
		}elseif($group === false){
			$details['userallow'] = AuthUtil::getUserAccess($node[0], $guid);
			$details['groupallow'] = AuthUtil::getGroupAccessForUser($node[0], $guid);
		}
		$tree = array('_DETAILS_' => $details);
		foreach($data as $row){
			if($row['parentid'] == $node[0]){
				$tree[$row['name']] = $row['name'];
				$tmp = $node;
				array_unshift($tmp, $row['realmid']);
				$tree[$row['name']] = AuthUtil::recBuildrealmTree($data, $tmp, $row, $guid, $group);
			}
		}
		return $tree;
	}
	
	/**
	 * Convert a name based realm path to an ID based name path
	 * 
	 * 
	 * @param array $nameRealmPath An array of 1 or more realm names
	 * @return mixed Boolean flase if the path could not be found, or an ID based realm path if everything went ok
	 * 
	 * 
	 *  
	 */
	public static function convertNamePathToIDPath($nameRealmPath){
		if(!is_array($nameRealmPath)){
			throw new LoggedException("The passed path is not an array", 0, self::module, 'error');
		}elseif(count($nameRealmPath) < 1){
			throw new LoggedException("The passed path was an empty array", 0, self::module, 'error');
		}
		
		global $cfg;
		
		$sql = 'SELECT ';
		$where = array();
		$tables = array();
		$names = array();
		
		for($i=0; $i < count($nameRealmPath); $i++){
			$sql .= "r$i.realmid AS id$i ";
			
			//If its not the first itteration
			if($i > 0){
				$j = $i - 1;
				$where[] = "r$i.parentid = r$j.realmid";
			}
			
			$tables[] = "realms AS r$i";
			$names[] = " r$i.name = ? ";
			
			
			//If its not the last in the array
			if($i != count($nameRealmPath) - 1){
				$sql .= ", ";
			}
		}
		$sql .= 'FROM ' . join(' , ', $tables);
		
		$sql .= ' WHERE ' . join(' AND ', $where);
		
		if(count($where) > 0){
			$sql .= ' AND ';
		}
		
		$sql .= join(' AND ', $names);
		
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$IDs = $db->getRow($sql, $nameRealmPath);
		
		if(is_null($IDs)){
			return false;
		}else{
			return array_values($IDs);
		}
	}
}

?>
