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
class DPSUserDelTrackShowModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
        $itemID = pg_escape_string($this->fieldData['itemID']);
		$where = "id = $itemID";
		$show['audioid'] = null;

        //lookup item length
        $items_sql = "SELECT * FROM showitems
                      WHERE id = $itemID";
        $item = $db->getRow($items_sql);
        $item_length = $item['length'];
        $script_id = $item['scriptid'];

        if ($script_id == "")
        {
            $show['length'] = 0;
        }
        else
        {
            //no change
        }

		$db->update('showitems',$show,$where,true);
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
