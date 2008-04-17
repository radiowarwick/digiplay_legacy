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
class DPSStationAddAwSetModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$sql = "SELECT username FROM users 
			WHERE id = " . $cfg['DPS']['systemUserID'];
		$userName = $db->getOne($sql);
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
			$newperm['userid'] = $cfg['DPS']['systemUserID'];
			$newperm['permissions'] = 'B' . $cfg['DPS']['fileRW'] . 'B';
			$db->insert('dirusers',$newperm,false); //for binary insert
			$sql_gperm['dirid'] = $dirID;
			$sql_gperm['permissions'] = 'B' . $cfg['DPS']['fileRWO'] . 'B';
			$sql_gperm['groupid'] = $cfg['Auth']['AdminGroup'];
			$db->insert('dirgroups',$sql_gperm,false);
		}
		$name = pg_escape_string($this->fieldData['name']);
		$desc = pg_escape_string($this->fieldData['desc']);
		if($name != '') {
			$AwSet = array();
			$perm = array();
			$AwSet['name'] = $name;
			$AwSet['description'] = $desc;
			$AwSet['id'] = "#id#";
			$AwSetID = $db->insert('aw_sets',$AwSet,true);
			$perm['user_id'] = $cfg['DPS']['systemUserID'];
			$perm['set_id'] = $AwSetID;
			$perm['permissions'] = 'B' . $cfg['DPS']['fileRWO'] . 'B';
			$db->insert('aw_sets_users',$perm,false);
			$gperm['group_id'] = $cfg['DPS']['allusersgroupid'];
			$gperm['set_id'] = $AwSetID;
			$gperm['permissions'] = 'B' . $cfg['DPS']['fileR'] . 'B';
			$db->insert('aw_sets_groups',$gperm,false);
			$gperm['group_id'] = $cfg['Auth']['AdminGroup'];
			$gperm['set_id'] = $AwSetID;
			$gperm['permissions'] = 'B' . $cfg['DPS']['fileRWO'] . 'B';
			$db->insert('aw_sets_groups',$gperm,false);
			$dir['set_id'] = $AwSetID;
			$dir['dir_id'] = $dirID;
			$dir['linktype'] = 0;
			$db->insert('aw_sets_dir',$dir,true);
			$AwWall = array();
			$AwWall['name'] = "New Page";
			$AwWall['set_id'] = $AwSetID;
			$AwWall['page'] = 0;
			$db->insert('aw_walls',$AwWall,true);
		}
	}
		
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
