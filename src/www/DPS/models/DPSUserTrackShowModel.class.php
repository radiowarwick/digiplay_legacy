<?php
/**
 * @package DPS
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSUserTrackShowModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid(){
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
        $query = "SELECT length, scriptid FROM showitems
                  WHERE id = " . pg_escape_string($this->fieldData['itemID']);
        $showiteminfo = $db->getRow($query);
		$where = "id = " . pg_escape_string($this->fieldData['itemID']);
		$show['audioid'] = pg_escape_string($this->fieldData['audioID']);
		$query = "SELECT length_smpl FROM audio
                  WHERE id = ". $show['audioid'];
        $audioitemlength = ceil($db->getone($query)/44100);
        if($showiteminfo['scriptid'] == null){
            $show['length'] = $audioitemlength;
        }
        $db->update('showitems',$show,$where,true);
	}
	
	protected function processInvalid(){
		//No invalid processing required
	}
}

?>
