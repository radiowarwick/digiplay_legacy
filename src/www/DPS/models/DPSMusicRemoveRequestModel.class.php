<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSMusicRemoveRequestModel extends Model {
	
  const module = 'DPS';
	
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);

    if(is_numeric($this->fieldData['tracknum'])) {
      for($i=0;$i<$_POST['tracknum'];$i++) {
	$tracknum = "track" . $i;
	$tracknumid = $tracknum . "id";
	if($this->fieldData[$tracknum] == "on") {
	  $tWhere = " id = " . pg_escape_string($this->fieldData[$tracknumid]);
	  $db->delete('requests',$tWhere);
	}
      }
    }
  }
	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
