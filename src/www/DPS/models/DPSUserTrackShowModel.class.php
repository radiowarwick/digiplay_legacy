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
class DPSUserTrackShowModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid(){
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$where = "id = " . pg_escape_string($this->fieldData['itemID']);
		$show['audioid'] = pg_escape_string($this->fieldData['audioID']);
		$db->update('showitems',$show,$where,true);
	}
	
	protected function processInvalid(){
		//No invalid processing required
	}
}

?>
