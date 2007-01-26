<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSUserAddShowModel extends Model {
	
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
		
		$newshow['name'] = "New Show";
		$newshow['creator'] = $userID;
		$newshow['creationdate'] = time();
		$newshow['showdate'] = time() + 604800;
		$newshow['id'] = '#id#';
		$showID = $db->insert('showplans',$newshow,true);
		$newsperm['showplanid'] = $showID;
		$newsperm['userid'] = $userID;
		$newsperm['permissions'] = 'o';
		$db->insert('showplanusers',$newsperm,true);
		$showdir['showplanid'] = $showID;
		$showdir['dir'] = $dirID;
		$showdir['linktype'] = 0;
		$db->insert('showplandir',$showdir,true);
  }
	
  protected function processInvalid(){
  
	}
	
}

?>
