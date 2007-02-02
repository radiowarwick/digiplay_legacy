<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSStationDeleteCartsetModel extends Model {
	
  const module = 'DPS';
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
    $loc = 1;
    $cartsetID = pg_escape_string($this->fieldData['cartset']);
    if($cartsetID != '' && is_numeric($cartsetID)) {
	$sql = "SELECT val, id from configuration where location = $loc and parameter = 'station_cartset'";
	$userset = $db->getRow($sql);
	if($userset['val'] == $cartsetID) {
	  $conf['val'] = '';
	  $where = "id = " . $userset['id'];
	  $db->update('configuration',$conf,$where,true);
	}
	$sql = "select id from cartwalls where cartset = " . $cartsetID;
	$cartwalls = $db->getColumn($sql);
	foreach($cartwalls as $wallID) {
	  $where = "cartwall = " . $wallID;
	  $db->delete('cartsaudio',$where,true);
	}
	$where = "cartset = " . $cartsetID;
	$db->delete('cartwalls',$where,true);
	$where = "cartsetid = " . $cartsetID;
	$db->delete('cartsetsusers',$where,true);
	$db->delete('cartsetsgroups',$where,true);
	$where = "id = " . $cartsetID;
	$db->delete('cartsets',$where,true);
    }
  }
	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>