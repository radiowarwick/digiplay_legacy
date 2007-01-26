<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSAddPlaylistModel extends Model {
	
  const module = 'DPS';
	
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
	$dpsPlaylistID = $this->fieldData['dpsPlaylistID'];
    if(is_numeric($dpsPlaylistID)) {
      for($i=0; $i < $cfg['DPS']['resultLimit']; $i++) {
        $cb = 'checkbox_' . $i;
        $id = 'trackID_' . $i;
        $val = 'trackVal_' . $i;
        if($this->fieldData[$cb] == "on" && is_numeric(pg_escape_string($this->fieldData[$id])) && pg_escape_string($this->fieldData[$id] != "") && $this->fieldData[$val] != "on") {
		  $trUpdate['audio'] = $this->fieldData[$id];
		  $trUpdate['playlist'] = $dpsPlaylistID;
		  $db->insert('audioplaylists',$trUpdate, true);
        } elseif($this->fieldData[$cb] != "on" && is_numeric(pg_escape_string($this->fieldData[$id])) && pg_escape_string($this->fieldData[$id] != "" && $this->fieldData[$val] == "on")) {
		  $trWhere = "audio = " . pg_escape_string($this->fieldData[$id]) . " and playlist = " . $dpsPlaylistID;
		  $db->delete('audioplaylists',$trWhere, true);
      	}	
      }	
	}
  }	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
