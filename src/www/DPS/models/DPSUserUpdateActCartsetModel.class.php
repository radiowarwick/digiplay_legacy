<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSUserUpdateActCartsetModel extends Model {
	
  const module = 'DPS';
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
    $cartsetID = pg_escape_string($this->fieldData['cartset']);
    
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
    $sql = "SELECT usersconfigs.id from configs, usersconfigs where configs.id = usersconfigs.configid and configs.name = 'default_cartset' and usersconfigs.userid = " . $userID;
    $userset = $db->getOne($sql);
    if(is_null($userset)){
      $cartset = array();
      $sql = "SELECT id from configs where configs.name = 'default_cartset'";
      $cartset['configid'] = $db->getOne($sql);
      $cartset['val'] = $cartsetID;
      $cartset['userid'] = $userID;
      $db->insert('usersconfigs', $cartset, true);
    } else {
      $cartset = array();
      $cartset['val'] = $cartsetID;
      $atWhere = "id = " . $userset;
      $db->update('usersconfigs', $cartset, $atWhere, true);
    }
  }
	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
