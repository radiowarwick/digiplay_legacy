<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSMoveDirectoryModel extends Model {

  const module = 'DPS';

  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
		$dir = $this->fieldData['dirID'];
    if(is_numeric($dir) && is_numeric($this->fieldData['newParent'])) {
			$sql_update['parent'] = $this->fieldData['newParent'];
			$swhere = "id = " . pg_escape_string($dir);
      $db->update('dir',$sql_update,$swhere,true);
    }
    
  }	
  protected function processInvalid(){
    //No invalid processing required
		if($this->errors['form']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpsuserdirmove.tpl'),array("rootdir" => $this->fieldData['dirID'], "error" => "form"));
		} else {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpsuserdirmove.tpl'),array("rootdir" => $this->fieldData['dirID'], "error" => "perm"));
		}
  }
	
}

?>
