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
		$AwSetID = pg_escape_string($this->fieldData['AwSet']);
		if($AwSetID != '' && is_numeric($AwSetID)) {
			
			$sql = "SELECT val, id FROM configuration 
				WHERE location = $loc AND parameter = 'station_aw_set'";
			$userset = $db->getRow($sql);
			if($userset['val'] == $AwSetID) {
				$conf['val'] = '';
				$where = "id = " . $userset['id'];
				$db->update('configuration',$conf,$where,true);
			}
			$sql = "SELECT id FROM aw_walls WHERE set_id = " . $AwSetID;
			$AwWalls = $db->getColumn($sql);
			foreach($AwWalls as $wallID) {
				$where = "wall_id = " . $wallID;
				$db->delete('aw_items',$where,true);
			}
			$where = "set_id = " . $AwSetID;
			$db->delete('aw_walls',$where,true);
			$where = "set_id = " . $AwSetID;
			$db->delete('aw_sets_users',$where,true);
			$db->delete('aw_sets_groups',$where,true);
			$db->delete('aw_sets_dir',$where,true);
			$where = "id = " . $AwSetID;
			$db->delete('aw_sets',$where,true);
		}
	}
		
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
