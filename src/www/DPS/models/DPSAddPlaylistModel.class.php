<?php
/**
 * @package DPS
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
* Model for adding items to the playlist
*/
class DPSAddPlaylistModel extends Model {
	const module = 'DPS';
	
	protected function processValid() {
	global $cfg;
	$db = Database::getInstance($cfg['DPS']['dsn']);
	$dpsPlaylistID = $this->fieldData['dpsPlaylistID'];
	if(is_numeric($dpsPlaylistID)) {
		for($i=0; $i < $cfg['DPS']['resultLimit']; $i++) {
			$cb = 'checkbox_' . $i;
			$id = 'trackID_' . $i;
			$val = 'trackVal_' . $i;
			if($this->fieldData[$cb] == "on" 
				&& is_numeric(pg_escape_string($this->fieldData[$id])) 
				&& pg_escape_string($this->fieldData[$id] != "") 
				&& $this->fieldData[$val] != "on") {
				$trUpdate['audioid'] = $this->fieldData[$id];
				$trUpdate['playlistid'] = $dpsPlaylistID;
				$db->insert('audioplaylists',$trUpdate, true);
			} elseif($this->fieldData[$cb] != "on" 
				&& is_numeric(pg_escape_string($this->fieldData[$id])) 
				&& pg_escape_string($this->fieldData[$id] != "" 
				&& $this->fieldData[$val] == "on")) {
				$trWhere = "audioid = " .
				pg_escape_string($this->fieldData[$id]) .
				" AND playlistid = " . $dpsPlaylistID;
				$db->delete('audioplaylists',$trWhere, true);
				}
			}
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
