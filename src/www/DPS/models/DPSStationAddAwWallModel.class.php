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
class DPSStationAddAwWallModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
	
		$AwSetID = pg_escape_string($this->fieldData['awset']);
		$sql = "SELECT COUNT(*) FROM aw_walls WHERE set_id = $AwSetID";
		$page = $db->getOne($sql);
		
		$pageInfo['set_id'] = $AwSetID;
		$pageInfo['name'] = "New Page";
		$pageInfo['description'] = "";
		$pageInfo['page'] = $page;
		$db->insert('aw_walls',$pageInfo,true);
	}
		
	protected function processInvalid() {
		//No invalid processing required
	}
}

?>
