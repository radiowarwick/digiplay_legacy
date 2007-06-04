<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSDeleteTrackModel extends Model {
	
  const module = 'DPS';
	
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
    if(is_numeric($this->fieldData['trackID'])) {
      $where = "audioid = " . pg_escape_string($this->fieldData['trackID']);
      $db->delete('audiodir',$where,true);
      $dir = array();
      $dir['audioid'] = $this->fieldData['trackID'];
      $dir['dirid'] = $cfg['DPS']['binDirectoryID'];
      $dir['linktype'] = 0;
      $db->insert('audiodir',$dir,true);
      $audio['censor'] = 'f';
      $audio['flagged'] = 'f';
      $audio['sustainer'] = 'f';
      $where= "id = " . pg_escape_string($this->fieldData['trackID']);
      $db->update('audio',$audio,$where,true);
    }
    
  }	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
