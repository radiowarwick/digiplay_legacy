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
class DPSStationAddCartsetModel extends Model {
	
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
			$dirID = $db->insert('dir',$newdir,true);
			$newperm['dirid'] = $dirID;
			$newperm['userid'] = $cfg['DPS']['systemUserID'];
			$newperm['permissions'] = 'B' . $cfg['DPS']['fileRW'] . 'B';
			$db->insert('dirusers',$newperm,false); //for binary insert
		}
		$name = pg_escape_string($this->fieldData['name']);
		$desc = pg_escape_string($this->fieldData['desc']);
		if($name != '') {
			$cartset = array();
			$perm = array();
			$cartset['name'] = $name;
			$cartset['description'] = $desc;
			$cartset['id'] = "#id#";
			$cartsetID = $db->insert('cartsets',$cartset,true);
			$perm['userid'] = $cfg['DPS']['systemUserID'];
			$perm['cartsetid'] = $cartsetID;
			$perm['permissions'] = 'B' . $cfg['DPS']['fileRWO'] . 'B';
			$db->insert('cartsetsusers',$perm,false);
			$gperm['groupid'] = $cfg['DPS']['allusersgroupid'];
			$gperm['cartsetid'] = $cartsetID;
			$gperm['permissions'] = 'B' . $cfg['DPS']['fileR'] . 'B';
			$db->insert('cartsetsgroups',$gperm,false);
			$dir['cartsetid'] = $cartsetID;
			$dir['dirid'] = $dirID;
			$dir['linktype'] = 0;
			$db->insert('cartsetsdir',$dir,true);
			$cartwall = array();
			$cartwall['name'] = "New Page";
			$cartwall['cartsetid'] = $cartsetID;
			$cartwall['page'] = 0;
			$db->insert('cartwalls',$cartwall,true);
		}
	}
		
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
