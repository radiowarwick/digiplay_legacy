<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSUserAddScriptModel extends Model {
	
  const module = 'DPS';
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$userName = $auth->getUser();
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
		
		$newscript['name'] = "New Script";
		$newscript['userid'] = $userID;
		$newscript['creationdate'] = time();
		$newscript['id'] = '#id#';
		$newscript['length'] = 0;
		$scriptID = $db->insert('scripts',$newscript,true);
		$newsperm['scriptid'] = $scriptID;
		$newsperm['userid'] = $userID;
		$newsperm['permissions'] = 'B11100000B'; //own
		$db->insert('scriptsusers',$newsperm,false); //for binary insert
		$scriptdir['scriptid'] = $scriptID;
		$scriptdir['dirid'] = $dirID;
		$scriptdir['linktype'] = 0;
		$db->insert('scriptsdir',$scriptdir,true);
  }
	
  protected function processInvalid(){
  
	}
	
}

?>
