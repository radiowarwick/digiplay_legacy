<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSDeleteJingleModel extends Model {
	
  const module = 'DPS';
	
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
		$audioID = $this->fieldData['audioID'];
    if(is_numeric($audioID)) {
			$where = "audio = " .  pg_escape_string($audioID);
			$db->delete('audiousers',$where,true);
			$db->delete('audiogroups',$where,true);
			$bin['directory'] = $cfg['DPS']['binDirectoryID'];
			$where = "audio = " .  pg_escape_string($audioID);
			$db->update('dir',$bin,$where,true);
    }
    
  }	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
