<?php
/**
 * @package FrontEnds
 * @subpackage Auth
 */
//include_once($cfg['dir']['tkfrontends.auth'] . '/config.php');
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for location management
 */
class LocationRemoveModel extends Model {
	
	const module = 'AuthFrontEnd';
	
	protected function processValid(){
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$where = "location = " . pg_escape_string($this->fieldData['locationID']);
		if(pg_escape_string($this->fieldData['locationID']) != '' && 
			is_numeric(pg_escape_string($this->fieldData['locationID']))) {
			$db->delete('configuration',$where);
		}
	}

	protected function processInvalid(){
		//No invalid processing required
	}
}
?>
