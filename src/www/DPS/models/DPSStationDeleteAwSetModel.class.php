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
class DPSStationDeleteAwSetModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$loc = 1;
		$AwSetID = pg_escape_string($this->fieldData['awset']);
		if($AwSetID != '' && is_numeric($AwSetID)) {
			$sql = "SELECT val, id FROM configuration 
				WHERE location = $loc AND parameter = 'station_aw_set'";
			$userset = $db->getRow($sql);
			if($userset['val'] == $AwSetID) {
				$conf['val'] = '';
				$where = "id = " . $userset['id'];
				$db->update('configuration',$conf,$where,true);
			}
			$where = "id = " . $AwSetID;
			$db->delete('aw_sets',$where,true);
		}
	}
		
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
