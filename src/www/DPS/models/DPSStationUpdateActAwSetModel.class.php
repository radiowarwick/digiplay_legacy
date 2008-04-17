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
class DPSStationUpdateActCartsetModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$cartsetID = pg_escape_string($this->fieldData['cartset']);
		$cartset = array();
		$cartset['val'] = $cartsetID;
		$atWhere = "parameter = 'station_cartset'";
		$db->update('configuration', $cartset, $atWhere, true);
	}
		
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
