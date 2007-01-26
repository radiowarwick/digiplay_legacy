<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSReportTrackModel extends Model {
	
  const module = 'DPS';
	
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
    if(is_numeric($this->fieldData['trackID'])) {
      $sql_update['flagged'] = 't';
      $sql_where = "id = " . pg_escape_string($this->fieldData['trackID']);
      $db->update('audio',$sql_update,$sql_where,true);
    }
    
  }	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
