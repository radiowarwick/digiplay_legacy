<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSMoveCartsetModel extends Model {

  const module = 'DPS';

  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
		$cartset = $this->fieldData['cartsetID'];
    if(is_numeric($cartset) && is_numeric($this->fieldData['newParent'])) {
			$sql_insert['dir'] = $this->fieldData['newParent'];
			$sql_insert['cartsetid'] = $cartset;
			$sql_insert['linktype'] = 0;
			$swhere = "cartsetid = " . pg_escape_string($cartset);
			$db->delete('cartsetsdir',$swhere,true);
      $db->insert('cartsetsdir',$sql_insert,true);
    }
    
  }	
  protected function processInvalid(){
    //No invalid processing required
		MVCUtils::redirect(MVCUtils::getTemplateID('dpsusercartsetmove.tpl'),array("cartsetID" => $this->fieldData['cartsetID'], "error" => "perm"));
  }
	
}

?>
