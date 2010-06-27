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
class DPSDeleteJingleModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$audioID = $this->fieldData['audioID'];
		if(is_numeric($audioID)) {
			$where = "audioid = " .  pg_escape_string($audioID);
			$db->delete('audiousers',$where,true);
			$db->delete('audiogroups',$where,true);
			$bin['dirid'] = $cfg['DPS']['binDirectoryID'];
			$where = "audioid = " .  pg_escape_string($audioID);
			$db->update('audiodir',$bin,$where,true);
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
