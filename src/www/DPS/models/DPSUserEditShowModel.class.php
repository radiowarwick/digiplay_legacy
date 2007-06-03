<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSUserEditShowModel extends Model {
	
  const module = 'DPS';
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
		$where = "id = " . pg_escape_string($this->fieldData['showID']);
		$show['name'] = $this->fieldData['name'];
		$show['showdate'] = mktime($this->fieldData['hours'],$this->fieldData['mins'],0,$this->fieldData['month'],$this->fieldData['day'],$this->fieldData['year']);
		$db->update('showplans',$show,$where,true);
  }
	
  protected function processInvalid(){
	}
	
}

?>
