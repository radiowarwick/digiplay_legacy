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
class DPSUserDownShowItemModel extends Model {
		
	const module = 'DPS';
		
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$itemID = pg_escape_string($this->fieldData['itemID']);
		$sql = "SELECT showplanid FROM showitems WHERE id = $itemID";
		$showID = $db->getOne($sql);
	
		$sql = "SELECT * FROM showitems
			WHERE showplanid = $showID ORDER BY position ASC";
		$showItems = $db->getAll($sql);
		$lastItem = false;
		foreach($showItems as $item) {
			if($lastItem['id'] == $itemID) {
				$upWhere = "showplanid = $showID AND id = " . $item['id'];
				$downWhere = "showplanid = $showID AND id = " . $lastItem['id'];
				$upUpdate['position'] = $lastItem['position'];
				$downUpdate['position'] = $item['position'];
				$db->update('showitems',$upUpdate,$upWhere,true);
				$db->update('showitems',$downUpdate,$downWhere, true);
			}
			$lastItem = $item;
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
