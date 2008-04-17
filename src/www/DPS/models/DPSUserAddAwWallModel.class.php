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
class DPSUserAddAwWallModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
	
		$cartsetID = pg_escape_string($this->fieldData['cartset']);
		$sql = "SELECT COUNT(*) FROM cartwalls WHERE cartsetid = $cartsetID";
		$page = $db->getOne($sql);
		
		$pageInfo['cartsetid'] = $cartsetID;
		$pageInfo['name'] = "New Page";
		$pageInfo['description'] = "";
		$pageInfo['page'] = $page;
		$db->insert('cartwalls',$pageInfo,true);
	}
		
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
