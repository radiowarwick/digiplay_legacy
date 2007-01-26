<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSCreateDirectoryModel extends Model {
	
  const module = 'DPS';
	
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
		$dir = $this->fieldData['rootdir'];
    if(is_numeric($dir)) {
      $sql_insert['parent'] = $dir;
			$sql_insert['name'] = $this->fieldData['dirtext'];
			$sql_insert['id'] = "#id#";
      $id = $db->insert('dir',$sql_insert,true);
			$sql_perm['directory'] = $id;
			$sql_perm['permissions'] = 'o';
			$auth = Auth::getInstance();
			$sql_perm['userid'] = $auth->getUserID();
			$id = $db->insert('dirusers',$sql_perm,true);
    }
    
  }	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
