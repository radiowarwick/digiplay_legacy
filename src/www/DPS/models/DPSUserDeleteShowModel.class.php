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
class DPSUserDeleteShowModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$showID = pg_escape_string($this->fieldData['showID']);
		if(is_numeric($showID)) {
			$where = "showplanid = " . $showID;
			$db->delete('showitems',$where,true);
			$db->delete('showplandir',$where,true);
			$db->delete('showplanusers',$where,true);
			$db->delete('showplangroups',$where,true);
			$where = "id = " . $showID;
			$db->delete('showplans',$where,true);
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
