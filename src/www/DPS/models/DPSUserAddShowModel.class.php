<?php
/**
 * @package DPS
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSUserAddShowModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
			$auth = Auth::getInstance();
			$userID = $auth->getUserID();
			$userName = $auth->getUser();
			$sql = "SEELCT id FROM dir 
				WHERE parent = " . $cfg['DPS']['userDirectoryID'] . "
				AND name = '" . $userName . "'";
			$dirID = $db->getOne($sql);
			if($dirID == '') {
				$newdir['name'] = $userName;
				$newdir['parent'] = $cfg['DPS']['userDirectoryID'];
				$newdir['id'] = '#id#';
				$newdir['notes'] = $userName . "'s home directory";
				$dirID = $db->insert('dir',$newdir,true);
				$newperm['dirid'] = $dirID;
				$newperm['userid'] = $userID;
				$newperm['permissions'] = 'B' . $cfg['DPS']['fileRW'] . 'B';
				$db->insert('dirusers',$newperm,false); //for binary
			}
			
			$newshow['name'] = "New Show";
			$newshow['userid'] = $userID;
			$newshow['creationdate'] = time();
			$newshow['showdate'] = time() + 604800;
			$newshow['completed'] = 'f';
			$newshow['id'] = '#id#';
			$showID = $db->insert('showplans',$newshow,true);
			$newsperm['showplanid'] = $showID;
			$newsperm['userid'] = $userID;
			$newsperm['permissions'] = 'B' . $cfg['DPS']['fileRWO'] . 'B';
			$db->insert('showplanusers',$newsperm,false); //for binary
			$showdir['showplanid'] = $showID;
			$showdir['dirid'] = $dirID;
			$showdir['linktype'] = 0;
			$db->insert('showplandir',$showdir,true);
	}
		
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
