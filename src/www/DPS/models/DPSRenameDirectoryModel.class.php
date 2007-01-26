<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSRenameDirectoryModel extends Model {

  const module = 'DPS';

  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
		$dir = $this->fieldData['rootdir'];
    if(is_numeric($dir)) {
			$sql_update['name'] = $this->fieldData['dirtext'];
			$swhere = "id = " . pg_escape_string($dir);
      $db->update('dir',$sql_update,$swhere,true);
    }
    
  }	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
