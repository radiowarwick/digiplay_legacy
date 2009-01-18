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
class DPSUserScriptShowModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$where = "id = " . pg_escape_string($this->fieldData['itemID']);
		$show['scriptid'] = pg_escape_string($this->fieldData['scriptID']);

        $script_sql = "SELECT * FROM scripts
                       WHERE id = " . $show['scriptid'];
        $script = $db->getRow($script_sql);
        $show['length'] = $script['length'];

		$db->update('showitems',$show,$where,true);

        //$query = "SELECT length FROM showitems WHERE id = " . $this->fieldData['itemID'];
        //$elementlength = $db->getone($query); 
	}
		
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
