<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserEditCartsetViewer extends Viewer {

  const module = 'DPS';

  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();

    $db = Database::getInstance($cfg['DPS']['dsn']);
  

    $cartset = pg_escape_string($this->fieldData['cartset']);
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
    $flag = false;
    if($cartset != '' && is_numeric($cartset)) {
      $sql = "select count(*) from cartsetsusers where cartsetsusers.userid = $userID 
            AND cartsetsusers.cartsetid = $cartset 
	    AND (cartsetsusers.permissions = 'o' or cartsetsusers.permissions = 'w' or cartsetsusers.permissions = 'rw')";
      $check = $db->getOne($sql);
      if($check > 0) {
	$flag = true;
      } else {
	$sql = "select count(*) from cartsetsgroups, groupmembers where cartsetsgroups.groupid = groupmembers.groupid
	      AND groupmembers.userid = $userID AND cartsetsgroups.cartsetid = $cartset 
	      AND (cartsetsgroups.permissions = 'o' or cartsetsgroups.permissions = 'w' or cartsetsgroups.permissions = 'rw')";
	$check = $db->getOne($sql);
	if($check > 0) {
	  $flag = true;
	}
      }
    }

    if($flag) {
    $page = pg_escape_string($this->fieldData['page']);

    if($page == "" || !is_numeric($page)){
      $page = 0;
    }
    
    $sql = "select * from cartwalls where cartset = $cartset AND page = $page";
    $cartwall = $db->getRow($sql);
    if($cartwall == null) {
      $page = 0;
      $sql = "select * from cartwalls where cartset = $cartset AND page = $page";
      $cartwall = $db->getRow($sql);
    }

    $sql = "select count(*) from cartwalls where cartset = " . $cartset;
    $pages = $db->getOne($sql);
    $pageArray = array();
    for($i=0; $i < $pages; $i++) {
      $pageArray[$i]['num'] = $i+1;
      $pageArray[$i]['id'] = $i;
    }
    for($i=0; $i<12; $i++) {
      $tcart = array();
      $sql = "SELECT cartsaudio.id as id, cartsaudio.audio as audio, cartsaudio.text as name, 
	      cartsaudio.cart as cart, audio.length_smpl as len, audio.title as title 
	      FROM cartwalls, cartsaudio, audio 
	      WHERE cartwalls.cartset = " . $cartset . " 
	      AND cartwalls.id = cartsaudio.cartwall 
	      AND cartsaudio.audio = audio.id 
	      AND cartwalls.page = " . $page . " 
	      AND cartsaudio.cart = " . $i;
      $tcart = $db->getRow($sql);
      $tcart['name'] = str_replace("\n","<br>",$tcart['name']);
      if(isset($tcart['id'])) {
	$mins = floor($tcart['len']/44100/60);
	$secs = round(($tcart['len'] - $mins*44100*60)/44100);
	if($mins != 0) {
	  $tcart['length'] = $mins . "m " . $secs . "s";
	} else {
	  $tcart['length'] = $secs . "s";
	}
	$sql = "SELECT cartstyleprops.value as value, cartproperties.name as name
	    FROM cartsaudio, cartstyle, cartstyleprops, cartproperties
	    WHERE cartsaudio.id = " . $tcart['id'] . "  
	    AND cartsaudio.style = cartstyle.id  
	    AND cartstyle.id = cartstyleprops.style  
	    AND cartstyleprops.property = cartproperties.id"; 
	$cartprop = $db->getAll($sql);
	foreach($cartprop as $prop) {
	  if($prop['name'] == 'ForeColourRGB') {
	    $tcart['ForeColour']['r'] = (int)((int)$prop['value'] / (256*256));
	    $tcart['ForeColour']['g'] = (int)(($prop['value']-$tcart['ForeColour']['r']*256*256) / 256);
	    $tcart['ForeColour']['b'] = (int)(($prop['value']-$tcart['ForeColour']['r']*256*256-$tcart['ForeColour']['g']*256));
	  } elseif($prop['name'] == 'BackColourRGB') {
	    $tcart['BackColour']['r'] = (int)((int)$prop['value'] / (256*256));
	    $tcart['BackColour']['g'] = (int)(($prop['value']-$tcart['BackColour']['r']*256*256) / 256);
	    $tcart['BackColour']['b'] = ($prop['value']-$tcart['BackColour']['r']*256*256-$tcart['BackColour']['g']*256);
	  }
	}
      } else {
	$tcart['name'] = '';
	$tcart['audioid'] = 'none';
	$tcart['ForeColour']['r'] = 0;
	$tcart['ForeColour']['g'] = 0;
	$tcart['ForeColour']['b'] = 0;
	$tcart['BackColour']['r'] = 255;
	$tcart['BackColour']['g'] = 255;
	$tcart['BackColour']['b'] = 255;
      }
      $this->assign('cart' . ($i+1), $tcart);
    }

    $auth = Auth::getInstance();
    $userID = $auth->getUserID();


    $sql = "select count(*) from cartsetsusers where userid = $userID AND cartsetid = $cartset AND permissions = 'o'";
    $check = $db->getOne($sql);
    if($check > 0) {
      $this->assign('owner','t');
      $sql = "select count(*) from cartsetsgroups where groupid = " . $cfg['DPS']['allusersgroupid'] . " AND cartsetid = $cartset AND permissions = 'r'"; 
      $check = $db->getOne($sql);
      if($check > 0) {
	$this->assign('groupread','t');
      } else {
	$sql = "select count(*) from cartsetsgroups where groupid = " . $cfg['DPS']['allusersgroupid'] . " AND cartsetid = $cartset AND permissions = 'rw'"; 
	$check = $db->getOne($sql);
	if($check > 0) {
	  $this->assign('groupread','t');
	  $this->assign('groupwrite','t');
	} else {
	  $sql = "select count(*) from cartsetsgroups where groupid = " . $cfg['DPS']['allusersgroupid'] . " AND cartsetid = $cartset AND permissions = 'w'"; 
	  $check = $db->getOne($sql);
	  if($check > 0) {
	    $this->assign('groupwrite','t');
	  }
	}
      }
    }


    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
    $this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(array(58,69,4), $userID));
    $this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
    $this->assign('studioAccess',AuthUtil::getDetailedUserrealmAccess(array(58,69,70), $userID));
    $this->assign('pagelink',$pageArray);
    $this->assign('cartwall',$cartwall);
    $this->assign('cartsetID',$cartset);
    } else {
      $this->assign('permerror','t');
    }
  }

}

?>
		    
