<?php
/**
 * @package FrontEnds
 * @subpackage Auth
 */
include_once($cfg['Logger']['dir']['root'] . '/BasicLogger.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

class DPSLoginModel extends Model {
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['Auth']['dsn']);
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
		$userName = $auth->getUser();
    $sql = "SELECT usersconfigs.val, usersconfigs.id from configs, usersconfigs where configs.id = usersconfigs.configid and configs.name = 'user_curlogin' and usersconfigs.userid = " . $userID;
    $usercurlogin = $db->getRow($sql);
    $sql = "SELECT usersconfigs.val, usersconfigs.id from configs, usersconfigs where configs.id = usersconfigs.configid and configs.name = 'user_lastlogin' and usersconfigs.userid = " . $userID;
    $userlastlogin = $db->getRow($sql);
		
    $sql = "select id from dir where parent = " . $cfg['DPS']['userDirectoryID'] . " AND name = '" . $userName . "'";
    $dirID = $db->getOne($sql);
		if($dirID == '') {
			$newdir['name'] = $userName;
			$newdir['parent'] = $cfg['DPS']['userDirectoryID'];
			$newdir['id'] = '#id#';
			$newdir['notes'] = $userName . "'s home directory";
			$dirID = $db->insert('dir',$newdir,true);
			$newperm['dirid'] = $dirID;
			$newperm['userid'] = $userID;
			$newperm['permissions'] = 'B11000000B'; //read write
			$db->insert('dirusers',$newperm,false); //for binary insert
		}
    if(is_null($userlastlogin) && !is_null($usercurlogin)){
      $cartset = array();
      $sql = "SELECT id from configs where configs.name = 'user_lastlogin'";
      $cartset['configid'] = $db->getOne($sql);
      $cartset['val'] = $usercurlogin['val'];
      $cartset['userid'] = $userID;
      $db->insert('usersconfigs', $cartset, true);
    }elseif(is_null($userlastlogin) && is_null($usercurlogin)){
      $cartset = array();
      $sql = "SELECT id from configs where configs.name = 'user_lastlogin'";
      $cartset['configid'] = $db->getOne($sql);
      $cartset['val'] = time();
      $cartset['userid'] = $userID;
      $db->insert('usersconfigs', $cartset, true);
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
      $cartset = array();
      $sql = "SELECT id from configs where configs.name = 'user_curlogin'";
      $cartset['configid'] = $db->getOne($sql);
      $cartset['val'] = time();
      $cartset['userid'] = $userID;
      $db->insert('usersconfigs', $cartset, true);
    } else {
      $logint = array();
      $logint['val'] = time();
      $atWhere = "id = " . $usercurlogin['id'];
      $db->update('usersconfigs', $logint, $atWhere, true);
    }
    BasicLogger::logMessage("Checking access to requested template", 'debug');
    if(isset($this->fieldData['fwdtid']) && 
      $this->fieldData['fwdtid'] != '' && 
      AuthUtil::templateAccessAllowed($this->fieldData['fwdtid'], $auth->getUserID())){
      BasicLogger::logMessage("Access granted, forwarding user to {$this->fieldData['fwdtid']}", 'debug');	
      MVCUtils::redirect($this->fieldData['fwdtid']);
  		
      //If the fwtid (forward template id) variable is not set, then set the
      //templateID to that default as long as the user has permission
    }elseif(!(isset($this->fieldData['fwdtid']) && 
      $this->fieldData['fwdtid'] == '') && 
      AuthUtil::templateAccessAllowed(MVCUtils::getTemplateID($cfg['smarty']['defaultTemplate']), $auth->getUserID())){
      BasicLogger::logMessage("Access granted, forwarding user to {$cfg['smarty']['defaultTemplate']}", 'debug');
      MVCUtils::redirect(MVCUtils::getTemplateID($cfg['smarty']['defaultTemplate']));
      //If all the above fails, show the user permission denied
    }else{
      BasicLogger::logMessage("Access denied", 'debug');
      MVCUtils::redirect(MVCUtils::getTemplateID($cfg['Auth']['permissionErrorTemplate']));
    }
  }
	
  protected function processInvalid(){
    //Called when a bad username/password is submitted.
    if(isset($this->fieldData['fieldData'])){
      $user = $this->fieldData['fieldData'];
      BasicLogger::logMessage("A login attempt failed for user '$user'.");
    }
  }	
}

?>
