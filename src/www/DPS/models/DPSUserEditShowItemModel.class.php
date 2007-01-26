<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSUserEditShowItemModel extends Model {
	
  const module = 'DPS';
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
		$where = "id = " . pg_escape_string($this->fieldData['itemID']);
		$item['title'] = $this->fieldData['title'];
		$item['comment'] = $this->fieldData['notes'];
		$item['length'] = (60*$this->fieldData['mins'] + $this->fieldData['secs']);
		$db->update('showitems',$item,$where,true);
  }
	
  protected function processInvalid(){
	}
	
}

?>
