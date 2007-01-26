<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSViewTracksModel extends Model {
	
  const module = 'DPS';
	
	
  protected function processValid(){
    global $cfg;
    
    $trackIDs = "";
    for($i=0; $i < $cfg['DPS']['resultLimit']; $i++) {
      $cb = 'checkbox_' . $i;
      $id = 'trackID_' . $i;
      if($this->fieldData[$cb] == "on") {
	$trackIDs = $trackIDs . $this->fieldData[$id] . ";";
      }
    }
    $trackIDs = rtrim($trackIDs,";");
    
    $this->fieldData['trackID'] = $trackIDs;
  }
	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
