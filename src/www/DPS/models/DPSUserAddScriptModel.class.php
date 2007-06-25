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
class DPSUserAddScriptModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
			$auth = Auth::getInstance();
			$userID = $auth->getUserID();
			$userName = $auth->getUser();
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
				$db->insert('dirusers',$newperm,false); //for binary insert
				$sql_gperm['dirid'] = $dirID;
				$sql_gperm['permissions'] = 'B' . $cfg['DPS']['fileRWO'] . 'B';
				$sql_gperm['groupid'] = $cfg['Auth']['AdminGroup'];
				$db->insert('dirgroups',$sql_gperm,false);
			}
		
		$newscript['name'] = "New Script";
		$newscript['userid'] = $userID;
		$newscript['creationdate'] = time();
		$newscript['id'] = '#id#';
		$newscript['length'] = 0;
		$scriptID = $db->insert('scripts',$newscript,true);
		$newsperm['scriptid'] = $scriptID;
		$newsperm['userid'] = $userID;
		$newsperm['permissions'] = 'B' . $cfg['DPS']['fileRWO'] . 'B'; //own
		$db->insert('scriptsusers',$newsperm,false); //for binary insert
		$gperm['groupid'] = $cfg['Auth']['AdminGroup'];
		$gperm['scriptid'] = $scriptID;
		$gperm['permissions'] = 'B' . $cfg['DPS']['fileRWO'] . 'B';
		$db->insert('scriptsgroups',$gperm,false);
		$scriptdir['scriptid'] = $scriptID;
		$scriptdir['dirid'] = $dirID;
		$scriptdir['linktype'] = 0;
		$db->insert('scriptsdir',$scriptdir,true);
	}
		
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
