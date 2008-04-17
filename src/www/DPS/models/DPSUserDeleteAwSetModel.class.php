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
class DPSUserDeleteAwSetModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
	
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$cartsetID = pg_escape_string($this->fieldData['cartset']);
		if($cartsetID != '' && is_numeric($cartsetID)) {
			$sql = "SELECT usersconfigs.id FROM configs, usersconfigs 
			WHERE configs.id = usersconfigs.configid
			AND configs.name = 'default_cartset'
			AND usersconfigs.val = " . $cartsetID;
			$userset = $db->getColumn($sql);
			foreach($userset as $configID) {
				$where = "id = " . $configID;
				$db->delete('usersconfigs',$where,true);
			}
			$sql = "SELECT id FROM cartwalls WHERE cartsetid = " . $cartsetID;
			$cartwalls = $db->getColumn($sql);
			foreach($cartwalls as $wallID) {
				$where = "cartwallid = " . $wallID;
				$db->delete('cartsaudio',$where,true);
			}
			$where = "cartsetid = " . $cartsetID;
			$db->delete('cartwalls',$where,true);
			$db->delete('cartsetsdir',$where,true);
			$db->delete('cartsetsusers',$where,true);
			$db->delete('cartsetsgroups',$where,true);
			$where = "id = " . $cartsetID;
			$db->delete('cartsets',$where,true);
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
