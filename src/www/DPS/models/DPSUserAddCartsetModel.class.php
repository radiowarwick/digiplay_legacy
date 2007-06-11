<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
* Model for user management
*/
class DPSUserAddCartsetModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid(){
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);

		$name = pg_escape_string($this->fieldData['name']);
		$desc = pg_escape_string($this->fieldData['desc']);
		
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

	protected function processInvalid(){
		//No invalid processing required
	}
}

?>
