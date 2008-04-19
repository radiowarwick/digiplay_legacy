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
class DPSUserUpdateActAwSetModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$awsetID = pg_escape_string($this->fieldData['awset']);
		
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$sql = "SELECT usersconfigs.id FROM configs, usersconfigs 
			WHERE configs.id = usersconfigs.configid
			AND configs.name = 'default_aw_set'
			AND usersconfigs.userid = " . $userID;
		$userset = $db->getOne($sql);
		if(is_null($userset)){
			$awset = array();
			$sql = "SELECT id FROM configs WHERE configs.name = 'default_aw_set'";
			$awset['configid'] = $db->getOne($sql);
			$awset['val'] = $awsetID;
			$awset['userid'] = $userID;
			$db->insert('usersconfigs', $awset, true);
		} else {
			$awset = array();
			$awset['val'] = $awsetID;
			$atWhere = "id = " . $userset;
			$db->update('usersconfigs', $awset, $atWhere, true);
		}
	}
		
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
