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
class DPSUserCompleteShowModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$showID = pg_escape_string($this->fieldData['showID']);
		$Where = "id = $showID";
		$Update['completed'] = 't';
		$db->update('showplans',$Update,$Where,true);
	}
		
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
