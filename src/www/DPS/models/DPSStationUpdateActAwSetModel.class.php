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
class DPSStationUpdateActAwSetModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$AwSetID = pg_escape_string($this->fieldData['awset']);
		$AwSet = array();
		$AwSet['val'] = $AwSetID;
		$atWhere = "parameter = 'station_aw_set'";
		$db->update('configuration', $AwSet, $atWhere, true);
	}
		
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
