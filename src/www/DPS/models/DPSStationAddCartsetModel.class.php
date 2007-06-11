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
