<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSStationCartsetsViewer extends Viewer {

  const module = 'DPS';

  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();

    $db = Database::getInstance($cfg['DPS']['dsn']);
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
    $loc = 1;
    // station cartsets
    $sql = "SELECT cartsets.id as id,cartsets.name as name,cartsets.description as desc, cartsetsusers.permissions as permissions 
	    FROM cartsets, cartsetsusers, users 
	    WHERE cartsets.id = cartsetsusers.cartsetid and cartsetsusers.userid = users.id 
	    and (cartsetsusers.permissions = 'r' or cartsetsusers.permissions = 'w' or cartsetsusers.permissions = 'rw' or cartsetsusers.permissions = 'o')
	    and users.id = " . $cfg['DPS']['systemUserID'] . "order by cartsets.name asc;";
    $cartsets = $db->getAll($sql);

    $sql = "SELECT cartsets.id as id,cartsets.name as name,cartsets.description as desc, cartsetsgroups.permissions as permissions 
	    FROM cartsets, cartsetsgroups, groupmembers
	    WHERE cartsets.id = cartsetsgroups.cartsetid and cartsetsgroups.groupid = groupmembers.groupid and 
		  groupmembers.userid = " . $cfg['DPS']['systemUserID'] . "   
		  and (cartsetsgroups.permissions = 'r' or cartsetsgroups.permissions = 'w' or cartsetsgroups.permissions = 'rw')
		  order by cartsets.name asc;";
    $cartsetsg = $db->getAll($sql);

    $sql = "SELECT val from configuration where location = $loc and parameter = 'station_cartset'";
    $userset = $db->getOne($sql);

    foreach ($cartsetsg as &$cartsetg) {
      $flag = false;
      foreach ($cartsets as &$cartset) {
	if($cartsetg['id'] == $cartset['id']) {
	  $flag = true;
	  if(($cartset['permissions'] == 'r ' || $cartset['permissions'] == 'w ') && ($cartsetg['permissions'] == 'rw')) {
	    $cartset['permissions'] == 'rw';
	  } elseif(($cartset['permissions'] == 'r ') && ($cartsetg['permissions'] == 'w ')) {
	    $cartset['permissions'] == 'rw';
	  } elseif(($cartset['permissions'] == 'w ') && ($cartsetg['permissions'] == 'r ')) {
	    $cartset['permissions'] == 'rw';
	  }
	  break;
	}
      }
      if(!$flag){
	$cartsets[] = &$cartsetg;
      }
    }

    foreach ($cartsets as &$cartset) {
      if($userset == $cartset['id']) {
	$cartset['active'] = 't';
      } else {
	$cartset['active'] = 'f';
      }
    }
	$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(array(58,69,4), $userID));
    $this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
    $this->assign('cartsets', $cartsets);
   }
}

?>
		    
