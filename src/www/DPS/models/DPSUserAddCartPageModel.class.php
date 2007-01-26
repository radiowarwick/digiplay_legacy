<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSUserAddCartPageModel extends Model {
	
  const module = 'DPS';
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);

    $cartsetID = pg_escape_string($this->fieldData['cartset']);
      $sql = "select count(*) from cartwalls where cartset = $cartsetID";
      $page = $db->getOne($sql);
    
      $pageInfo['cartset'] = $cartsetID;
      $pageInfo['name'] = "New Page";
      $pageInfo['description'] = "";
      $pageInfo['page'] = $page;
      $db->insert('cartwalls',$pageInfo,true);
  }
	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
