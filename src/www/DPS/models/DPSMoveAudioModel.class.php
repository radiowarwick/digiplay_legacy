<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSMoveAudioModel extends Model {

  const module = 'DPS';

  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
		$audio = $this->fieldData['audioID'];
    if(is_numeric($audio) && is_numeric($this->fieldData['newParent'])) {
			$sql_insert['dirid'] = $this->fieldData['newParent'];
			$sql_insert['audioid'] = $audio;
			$sql_insert['linktype'] = 0;
			$swhere = "audioid = " . pg_escape_string($audio);
			$db->delete('audiodir',$swhere,true);
      $db->insert('audiodir',$sql_insert,true);
    }
    
  }	
  protected function processInvalid(){
    //No invalid processing required
		MVCUtils::redirect(MVCUtils::getTemplateID('dpsuseraudiomove.tpl'),array("audioID" => $this->fieldData['audioID'], "error" => "perm"));
  }
	
}

?>
