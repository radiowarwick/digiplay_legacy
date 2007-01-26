<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserCartsetsViewer extends Viewer {

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
	    and (cartsetsusers.permissions = 'r' or cartsetsusers.permissions = 'rw' or cartsetsusers.permissions = 'o')
	    and users.id = " . $userID . "order by cartsets.name asc;";
    $cartsets = $db->getAll($sql);

    $sql = "SELECT cartsets.id as id,cartsets.name as name,cartsets.description as desc, cartsetsgroups.permissions as permissions 
	    FROM cartsets, cartsetsgroups, groupmembers
	    WHERE cartsets.id = cartsetsgroups.cartsetid and cartsetsgroups.groupid = groupmembers.groupid and 
	    groupmembers.userid = $userID and (cartsetsgroups.permissions = 'o' 
	    or cartsetsgroups.permissions = 'r' or cartsetsgroups.permissions = 'rw') order by cartsets.name asc;";
    $cartsetsg = $db->getAll($sql);

    $sql = "SELECT usersconfigs.val from configs, usersconfigs where configs.id = usersconfigs.configoption and configs.name = 'default_cartset' and usersconfigs.userid = " . $userID;
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

    $sql = "SELECT val FROM configuration where location=$loc and parameter='station_cartset'";
    $stationset = $db->getOne($sql);
    if($stationset != '') {
      $sql = "SELECT cartsets.id as id,cartsets.name as name,cartsets.description as desc from cartsets where id = " . $stationset;
      $scartset = $db->getRow($sql);
    } else {
      $scartset = "None";
    }
    $this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(array(58,69,4), $userID));
	$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
    $this->assign('studioAccess',AuthUtil::getDetailedUserrealmAccess(array(58,69,70), $userID));
    $this->assign('cartsets', $cartsets);
    $this->assign('stationcartset', $scartset);

   }
}

?>
		    
