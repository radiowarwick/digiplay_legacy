<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSUserDeleteShowItemModel extends Model {
	
  const module = 'DPS';
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
		$itemID = pg_escape_string($this->fieldData['itemID']);
		$sql = "select showplanid from showitems where id = $itemID";
		$showID = $db->getOne($sql);

		$sql = "SELECT * from showitems where showplanid = $showID order by position asc";
		$showItems = $db->getAll($sql);
		$delled = false;
		foreach($showItems as $item) {
			if($delled) {
				$where = "showplanid = $showID and id = " . $item['id'];
				$update['position'] = ($item['position']-1);
				$db->update('showitems',$update,$where,true);
			}
			if($item['id'] == $itemID) {
				$Where = "showplanid = $showID and id = $itemID";
				$db->delete('showitems',$Where,true);
				$delled = true;
			}
		}
  }
	
  protected function processInvalid(){
	}
	
}

?>
