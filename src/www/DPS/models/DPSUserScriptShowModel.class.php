<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSUserScriptShowModel extends Model {
	
  const module = 'DPS';
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
		$where = "id = " . pg_escape_string($this->fieldData['itemID']);
		$show['script'] = pg_escape_string($this->fieldData['scriptID']);
		$db->update('showitems',$show,$where,true);
  }
	
  protected function processInvalid(){
	}
	
}

?>
