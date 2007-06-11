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
class DPSUserEditScript extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$where = "id = " . pg_escape_string($this->fieldData['scriptID']);
		$item['name'] = $this->fieldData['name'];
		$item['contents'] = $this->fieldData['content'];
		$item['length'] = (60*$this->fieldData['mins'] + $this->fieldData['secs']);
		$db->update('scripts',$item,$where,true);
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
