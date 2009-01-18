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
class DPSUserDelScriptShowModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
        $itemID = pg_escape_string($this->fieldData['itemID']);
		$where = "id = $itemID";
		$show['scriptid'] = null;

        //lookup item length
        $items_sql = "SELECT * FROM showitems
                      WHERE id = $itemID";
        $item = $db->getRow($items_sql);
        $item_length = $item['length'];
        $audio_id = $item['audioid'];

        if ($audio_id == "")
        {
            $show['length'] = 0;
        }
        else
        {
            $audio_sql = "SELECT audio.length_smpl AS length
                          FROM audio
                          WHERE audio.id = $audio_id";
            $audio_item = $db->getRow($audio_sql);
            $audio_length = $audio_item['length'];
            $show['length'] = ceil($audio_length/44100);
        }

		$db->update('showitems',$show,$where,true);
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
