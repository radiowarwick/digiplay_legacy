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
class DPSPlaylistManageModel extends Model {
	const module = 'DPS';
	
	protected function processValid() {
	    global $cfg;
    	$db = Database::getInstance($cfg['DPS']['dsn']);

        if ($this->formName == "dpsPlaylistManageAddForm") {
            if (($this->fieldData['add'] == "Add") && ($this->fieldData['playlistName'] != "")){
                $data = array();
                $data['name'] = $this->fieldData['playlistName'];
                $db->insert('playlists', $data, true);
            }
        } else if ($this->formName == "dpsPlaylistManageRenameForm"){
            if ($this->fieldData['rename'] == "Rename"){
                $data = array();
                $data['name'] = $this->fieldData['playlistName'];
                $where = "id = ".$this->fieldData['playlistID'];
                $db->update('playlists', $data, $where, true);
            }
        } else if ($this->formName == "dpsPlaylistManageDeleteForm"){
            if ($this->fieldData['yes'] == "Yes"){
                $db->delete('audioplaylists', "playlistid = ".$this->fieldData['playlistID']); 
                $db->delete('playlists', "id = ".$this->fieldData['playlistID']);
            }
        } //else if something else then do nothing
    }
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
