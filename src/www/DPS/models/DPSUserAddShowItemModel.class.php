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
class DPSUserAddShowItemModel extends Model {
	
	const module = 'DPS';
		
	protected function processValid(){
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$sql = "SELECT COUNT(*) FROM showitems 
			WHERE showplanid = " . $this->fieldData['showID'];
		$pos = $db->getOne($sql);
		$pos++;
		$showitem['showplanid'] = $this->fieldData['showID'];
		$showitem['position'] = $pos;
		$showitem['title'] = 'New Item';
		$showitem['length'] = 0;
        $showitem['id'] = '#id#';
		$itemID = $db->insert('showitems',$showitem,true);

        MVCUtils::redirect("58", array("itemID" => $itemID));
	}
		
	protected function processInvalid(){
		//No invalid processing required
	}
}
?>
