<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSDeleteDirectoryModel extends Model {
	
  const module = 'DPS';
	
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
		$dir = $this->fieldData['rootdir'];
    if(is_numeric($dir)) {
			$where = "dirid = " .  pg_escape_string($dir);
			$db->delete('dirusers',$where,true);
			$db->delete('dirgroups',$where,true);
			$where = "id = " .  pg_escape_string($dir);
			$db->delete('dir',$where,true);
    }
    
  }	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
