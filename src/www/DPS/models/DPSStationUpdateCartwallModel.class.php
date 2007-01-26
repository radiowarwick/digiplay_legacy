<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSStationUpdateCartwallModel extends Model {
	
  const module = 'DPS';
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);

    $name = pg_escape_string($this->fieldData['name']);
    $desc = pg_escape_string($this->fieldData['desc']);
    $cartwallID = pg_escape_string($this->fieldData['cartwallID']);
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
    if($this->fieldData['Submit'] == "Remove Page") {
	$sql = "select cartset from cartwalls where id=" . $cartwallID;
	$cartsetID = $db->getOne($sql);
	$sql = "select count(*) from cartwalls where cartset=" . $cartsetID;
	$check = $db->getOne($sql);
	//cant delete last page
	if($check > 1) {
	  $where = "cartwall = " . $cartwallID;
	  $db->delete('cartsaudio', $where, true);
	  $where = "id = " . $cartwallID;
	  $db->delete('cartwalls', $where, true);
	  $page = pg_escape_string($this->fieldData['page']);
	  $sql = "select * from cartwalls where cartset=" . $cartsetID . " AND page > $page order by page asc";
	  $pages = $db->getAll($sql);
	  foreach($pages as $p) {
	    $update['page'] = ($p['page'] - 1);
	    $where = "id = " . $p['id'];
	    $db->update('cartwalls',$update,$where,true);
	  }
	}
    } elseif($name != '' && $cartwallID != '' && is_numeric($cartwallID)) {
      $cartwall = array();
      $cartwall['name'] = $name;
      $cartwall['description'] = $desc;
      $atWhere = "id = " . $cartwallID;
      $db->update('cartwalls', $cartwall, $atWhere, true);
      $sql = "select count(*) from cartsetsusers, cartwalls where cartsetsusers.userid = " . $cfg['DPS']['systemUserID'] . " 
	      AND cartsetsusers.cartsetid = cartwalls.cartset AND cartwalls.ID = $cartwallID AND cartsetsusers.permissions = 'o'";
      $check = $db->getOne($sql);
      if($check > 0) {
	$sql = "select cartset from cartwalls where id = $cartwallID limit 1";
	$cartsetID = $db->getOne($sql);
	$where = "cartsetid = $cartsetID AND groupid = " . $cfg['DPS']['allusersgroupid'];
	$db->delete('cartsetsgroups',$where,true);
	$sql = "select count(*) from cartsaudio, cartwalls where cartsaudio.cartwall = cartwalls.id and cartwalls.cartset = " . $cartsetID;
	$cartcount = $db->getOne($sql);
	$sql = "select count(*) from cartsaudio, cartwalls, audiodir, dirgroups where audiodir.directory = dirgroups.directory and (dirgroups.permissions = 'r' or dirgroups.permissions = 'rw') and dirgroups.groupid = " . $cfg['DPS']['allusersgroupid'] . " and cartsaudio.audio=audiodir.audio AND cartsaudio.cartwall = cartwalls.id and cartwalls.cartset = " . $cartsetID;
	$permCount = $db->getOne($sql);
	if($permCount >= $cartcount) {
	  if($this->fieldData['readAll'] == "on" && $this->fieldData['writeAll'] == "on") {
	    $perm = array();
	    $perm['groupid'] = $cfg['DPS']['allusersgroupid'];
	    $perm['cartsetid'] = $cartsetID;
	    $perm['permissions'] = 'rw';
	    $db->insert('cartsetsgroups',$perm,true);
	  }elseif($this->fieldData['writeAll'] == "on") {
	    $perm = array();
	    $perm['groupid'] = $cfg['DPS']['allusersgroupid'];
	    $perm['cartsetid'] = $cartsetID;
	    $perm['permissions'] = 'rw';
	    $db->insert('cartsetsgroups',$perm,true);
	  }elseif($this->fieldData['readAll'] == "on") {
	    $perm = array();
	    $perm['groupid'] = $cfg['DPS']['allusersgroupid'];
	    $perm['cartsetid'] = $cartsetID;
	    $perm['permissions'] = 'r';
	    $db->insert('cartsetsgroups',$perm,true);
	  }
	} else {
	  $this->errors['model'] = "All audio elements in this cartset must be public";
	}
      }
    }
  }
	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
