<?php
/**
 * @package DPS
 */
include_once($cfg['Logger']['dir']['root'] . '/BasicLogger.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for logging in users.
 */
class DPSLoginModel extends Model {
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['Auth']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$userName = $auth->getUser();
		$sql = "SELECT usersconfigs.val, usersconfigs.id 
			FROM configs, usersconfigs 
			WHERE configs.id = usersconfigs.configid 
			AND configs.name = 'user_curlogin' 
			AND usersconfigs.userid = " . $userID;
		$usercurlogin = $db->getRow($sql);
		$sql = "SELECT usersconfigs.val, usersconfigs.id
			FROM configs, usersconfigs 
			WHERE configs.id = usersconfigs.configid
			AND configs.name = 'user_lastlogin'
			AND usersconfigs.userid = " . $userID;
		$userlastlogin = $db->getRow($sql);
			
		$sql = "SELECT id FROM dir 
			WHERE parent = " . $cfg['DPS']['userDirectoryID'] . " 
			AND name = '" . $userName . "'";
		$dirID = $db->getOne($sql);
			if($dirID == '') {
				$newdir['name'] = $userName;
				$newdir['parent'] = $cfg['DPS']['userDirectoryID'];
				$newdir['id'] = '#id#';
				$newdir['notes'] = $userName . "'s home directory";
				$newdir['inherit'] = 'f';
				$dirID = $db->insert('dir',$newdir,true);
				$newperm['dirid'] = $dirID;
				$newperm['userid'] = $userID;
				$newperm['permissions'] = 'B' . $cfg['DPS']['fileRW'] . 'B';
				$db->insert('dirusers',$newperm,false); //false for binary insert
				$sql_gperm['dirid'] = $dirID;
				$sql_gperm['permissions'] = 'B' . $cfg['DPS']['fileRWO'] . 'B';
				$sql_gperm['groupid'] = $cfg['Auth']['AdminGroup'];
				$db->insert('dirgroups',$sql_gperm,false);
			}
		if(is_null($userlastlogin) && !is_null($usercurlogin)){
		$awset = array();
		$sql = "SELECT id FROM configs WHERE configs.name = 'user_lastlogin'";
		$awset['configid'] = $db->getOne($sql);
		$awset['val'] = $usercurlogin['val'];
		$awset['userid'] = $userID;
		$db->insert('usersconfigs', $awset, true);
		} elseif(is_null($userlastlogin) && is_null($usercurlogin)) {
		$awset = array();
		$sql = "SELECT id FROM configs WHERE configs.name = 'user_lastlogin'";
		$awset['configid'] = $db->getOne($sql);
		$awset['val'] = time();
		$awset['userid'] = $userID;
		$db->insert('usersconfigs', $awset, true);
		} elseif (!is_null($userlastlogin) && is_null($usercurlogin)){
		$logint = array();
		$logint['val'] = time();
		$atWhere = "id = " . $userlastlogin['id'];
		$db->update('usersconfigs', $logint, $atWhere, true);
		} else {
		$logint = array();
		$logint['val'] = $usercurlogin['val'];
		$atWhere = "id = " . $userlastlogin['id'];
		$db->update('usersconfigs', $logint, $atWhere, true);
		}
	
		if(is_null($usercurlogin)){
		$awset = array();
		$sql = "SELECT id FROM configs WHERE configs.name = 'user_curlogin'";
		$awset['configid'] = $db->getOne($sql);
		$awset['val'] = time();
		$awset['userid'] = $userID;
		$db->insert('usersconfigs', $awset, true);
		} else {
		$logint = array();
		$logint['val'] = time();
		$atWhere = "id = " . $usercurlogin['id'];
		$db->update('usersconfigs', $logint, $atWhere, true);
		}
		BasicLogger::logMessage("Checking access to requested template", 'debug');
		if(isset($this->fieldData['fwdtid']) && 
		$this->fieldData['fwdtid'] != '' && 
		AuthUtil::templateAccessAllowed($this->fieldData['fwdtid'], 
			$auth->getUserID())) {
		BasicLogger::logMessage(
			"Access granted, forwarding user to {$this->fieldData['fwdtid']}",
			'debug');	
		MVCUtils::redirect($this->fieldData['fwdtid']);
			
		//If the fwtid (forward template id) variable is not set, then set the
		//templateID to that default as long as the user has permission
		} elseif(!(isset($this->fieldData['fwdtid'])
			&& $this->fieldData['fwdtid'] == '') &&
			AuthUtil::templateAccessAllowed(
				MVCUtils::getTemplateID($cfg['smarty']['defaultTemplate']), 
					$auth->getUserID())) {
			BasicLogger::logMessage(
				"Access granted, forwarding user to {$cfg['smarty']['defaultTemplate']}",
				'debug');
			MVCUtils::redirect(MVCUtils::getTemplateID(
				$cfg['smarty']['defaultTemplate']));
		//If all the above fails, show the user permission denied
		} else {
			BasicLogger::logMessage("Access denied", 'debug');
			MVCUtils::redirect(
				MVCUtils::getTemplateID($cfg['Auth']['permissionErrorTemplate']));
		}
	}
		
	protected function processInvalid() {
		//Called when a bad username/password is submitted.
		if(isset($this->fieldData['fieldData'])){
		$user = $this->fieldData['fieldData'];
		BasicLogger::logMessage("A login attempt failed for user '$user'.");
		}
	}	
}

?>
