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
class DPSUserAddCartsetModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$name = pg_escape_string($this->fieldData['name']);
		$desc = pg_escape_string($this->fieldData['desc']);
		
		$auth = Auth::getInstance();
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
		
		if($name != '') {
			$cartset = array();
			$perm = array();
			$cartset['name'] = $name;
			$cartset['description'] = $desc;
			$cartset['id'] = "#id#";
			$cartsetID = $db->insert('cartsets',$cartset,true);
			$auth = Auth::getInstance();
			$userID = $auth->getUserID();
			$perm['userid'] = $userID;
			$perm['cartsetid'] = $cartsetID;
			$perm['permissions'] = "B" . $cfg['DPS']['fileRWO'] . "B";
			$db->insert('cartsetsusers',$perm,false);
			$gperm['groupid'] = $cfg['Auth']['AdminGroup'];
			$gperm['cartsetid'] = $cartsetID;
			$gperm['permissions'] = 'B' . $cfg['DPS']['fileRWO'] . 'B';
			$db->insert('cartsetsgroups',$gperm,false);
			$cartwall = array();
			$cartwall['name'] = "New Page";
			$cartwall['cartsetid'] = $cartsetID;
			$cartwall['page'] = 0;
			$db->insert('cartwalls',$cartwall,true);
			$scriptdir['cartsetid'] = $cartsetID;
			$scriptdir['dirid'] = $dirID;
			$scriptdir['linktype'] = 0;
			$db->insert('cartsetsdir',$scriptdir,true);
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}

?>
