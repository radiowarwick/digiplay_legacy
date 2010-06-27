<?php

class AuthInterface {
	
	const module = 'Auth';
	
	/**
	 *
	 * @param array $realmPath An array of strings 
	 * @param mixed $userID the ID of the user to check permission for
	 * @return boolean True if access is allowed, false otherwise
	 */
	public static function getPremission($realmPath, $userID){
		return AuthUtil::getDetailedUserrealmAccess($realmPath, $userID);
	}
	
	/**
	 *
	 *
	 * @param array $realmPath The path to the parent realm
	 * @param string $newRealmName The name for the new realm name
	 * @return boolean True on success, false on failure
	 */
	public static function addRealm($realmPath, $newRealmName){
		return AuthUtil::addRealm($realmPath, $newRealmName, array());
	}
	
	public static function realmExists($nameRealmPath){
		static $cache = array();
		$join = join('.', $nameRealmPath);
		if(!isset($cache[$join])){
			$cache[$join] = is_array(AuthUtil::convertNamePathToIDPath($nameRealmPath));
		}
		
		return $cache[$join];
	}
	
	/**
	 * Delete A realm
	 * 
	 * This will return false if the specfied realm has children. Use 
	 * recursiveDeleteRealm() in order to remove children recursively
	 * 
	 * @param array $realmPath The path to the realm to delete
	 * @return boolean True if the realm was added, false if the add failed
	 */
	public static function deleteRealm($realmPath){
		return AuthUtil::deleteRealm($realmPath);
	}
	
	public static function recursiveDeleteRealm($realm){
		AuthUtil::recursiveDeleteRealm($realm);
	}
	
	
}

?>
