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
			$dirID = $db->insert('dir',$newdir,true);
			$newperm['directory'] = $dirID;
			$newperm['userid'] = $userID;
			$newperm['permissions'] = 'o';
			$db->insert('dirusers',$newperm,true);
		}
		
		$newscript['name'] = "New Script";
		$newscript['creator'] = $userID;
		$newscript['creationdate'] = time();
		$newscript['id'] = '#id#';
		$newscript['length'] = 0;
		$scriptID = $db->insert('scripts',$newscript,true);
		$newsperm['scriptid'] = $scriptID;
		$newsperm['userid'] = $userID;
		$newsperm['permissions'] = 'o';
		$db->insert('scriptusers',$newsperm,true);
		$scriptdir['scriptid'] = $scriptID;
		$scriptdir['dir'] = $dirID;
		$scriptdir['linktype'] = 0;
		$db->insert('scriptsdir',$scriptdir,true);
  }
	
  protected function processInvalid(){
  
	}
	
}

?>
