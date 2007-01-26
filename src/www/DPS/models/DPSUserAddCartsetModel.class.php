<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSUserAddCartsetModel extends Model {
	
  const module = 'DPS';
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);

    $name = pg_escape_string($this->fieldData['name']);
    $desc = pg_escape_string($this->fieldData['desc']);
    if($name != '') {
      $cartset = array();
      $perm = array();
      $cartset['name'] = $name;
      $cartset['description'] = $desc;
      $cartset['id'] = "#id#";
      $cartsetID = $db->insert('cartsets',$cartset,true);
      $auth = Auth::getInstance();
      $userID = $auth->getUserID();
      $perm['userid'] = $userID;
      $perm['cartsetid'] = $cartsetID;
      $perm['permissions'] = 'o';
      $db->insert('cartsetsusers',$perm,true);
      $cartwall = array();
      $cartwall['name'] = "New Page";
      $cartwall['cartset'] = $cartsetID;
      $cartwall['page'] = 0;
      $db->insert('cartwalls',$cartwall,true);

    }
  }
	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
