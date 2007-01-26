<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSUserDeleteScriptModel extends Model {
	
  const module = 'DPS';
	
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
		$scriptID = pg_escape_string($this->fieldData['scriptID']);
		if(is_numeric($scriptID)) {
			$where = "scriptid = " . $scriptID;
			$db->delete('scriptsdir',$where,true);
			$db->delete('scriptusers',$where,true);
			$db->delete('scriptgroups',$where,true);
			$where = "id = " . $scriptID;
			$db->delete('scripts',$where,true);
		}
  }	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
