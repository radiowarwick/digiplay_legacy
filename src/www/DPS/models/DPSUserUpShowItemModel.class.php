<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSUserUpShowItemModel extends Model {
	
  const module = 'DPS';
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
		$itemID = pg_escape_string($this->fieldData['itemID']);
		$sql = "select showplanid from showitems where id = $itemID";
		$showID = $db->getOne($sql);

		$sql = "SELECT * from showitems where showplanid = $showID order by position asc";
		$showItems = $db->getAll($sql);
		$lastItem = false;
		foreach($showItems as $item) {
			if($item['id'] == $itemID) {
				if($lastItem !== false) {
					$upUpdate = array();
					$downUpdate= array();
					$upWhere = "showplanid = $showID and id = " . $item['id'];
					$downWhere = "showplanid = $showID and id = " . $lastItem['id'];
					$upUpdate['position'] = $lastItem['position'];
					$downUpdate['position'] = $item['position'];
					$db->update('showitems',$upUpdate,$upWhere,true);
					$db->update('showitems',$downUpdate,$downWhere,true);
				}
			}
			$lastItem = $item;
		}
  }
	
  protected function processInvalid(){
	}
	
}

?>
