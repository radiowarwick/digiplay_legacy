<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSStationEditCartsetViewer extends Viewer {

	const module = 'DPS';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();

		$db = Database::getInstance($cfg['DPS']['dsn']);
	
		$cartset = pg_escape_string($this->fieldData['cartset']);
		$page = pg_escape_string($this->fieldData['page']);

		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$flag = false;
		if($cartset != '' && is_numeric($cartset)) {
			$sql = "SELECT count(*) from v_tree_cartset, cartwalls 
				WHERE v_tree_cartset.userid = " . $cfg['DPS']['systemUserID'] . " 
					AND v_tree_cartset.cartsetid = cartwalls.cartsetid 
					AND cartwalls.id = $cartwallID 
					AND v_tree_cartset.permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
			$check = $db->getOne($sql);
			if($check > 0) {
				$flag = true;
			}
		}
		if($flag) {
			if($page == "" || !is_numeric($page)){
				$page = 0;
			}

			$sql = "SELECT * FROM cartwalls 
				WHERE cartsetid = $cartset AND page = $page";
			$cartwall = $db->getRow($sql);
			if($cartwall == null) {
				$page = 0;
				$sql = "SELECT * FROM cartwalls 
					WHERE cartsetid = $cartset AND page = $page";
				$cartwall = $db->getRow($sql);
			}

			$sql = "SELECT count(*) FROM cartwalls WHERE cartsetid = " . $cartset;
			$pages = $db->getOne($sql);
			$pageArray = array();
			for($i=0; $i < $pages; $i++) {
				$pageArray[$i]['num'] = $i+1;
				$pageArray[$i]['id'] = $i;
			}

			for($i=0; $i<12; $i++) {
				$tcart = array();
				$sql = "SELECT cartsaudio.id AS id, cartsaudio.audioid AS audio,
								cartsaudio.text AS name, cartsaudio.cart AS cart,
								audio.length_smpl AS len, audio.title AS title 
							FROM cartwalls, cartsaudio, audio 
							WHERE cartwalls.cartsetid = $cartset 
							AND cartwalls.id = cartsaudio.cartwallid 
							AND cartsaudio.audio = audio.id 
							AND cartwalls.page = $page 
							AND cartsaudio.cart = $i";
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
					$sql = "SELECT cartstyleprops.value as value,
							cartproperties.name as name
						FROM cartsaudio, cartstyle, cartstyleprops, cartproperties
						WHERE cartsaudio.id = " . $tcart['id'] . "
						AND cartsaudio.styleid = cartstyle.id  
						AND cartstyle.id = cartstyleprops.styleid 
						AND cartstyleprops.propertyid = cartproperties.id"; 
					$cartprop = $db->getAll($sql);
					foreach($cartprop as $prop) {
						if($prop['name'] == 'ForeColourRGB') {
							$tcart['ForeColour']['r'] = (int)((int)$prop['value'] / (256*256));
							$tcart['ForeColour']['g'] = (int)(($prop['value']
								-$tcart['ForeColour']['r']*256*256) / 256);
							$tcart['ForeColour']['b'] = (int)(($prop['value']
								-$tcart['ForeColour']['r']*256*256
								-$tcart['ForeColour']['g']*256));
						} elseif($prop['name'] == 'BackColourRGB') {
							$tcart['BackColour']['r'] = (int)((int)$prop['value'] / (256*256));
							$tcart['BackColour']['g'] = (int)(($prop['value']
								-$tcart['BackColour']['r']*256*256) / 256);
							$tcart['BackColour']['b'] = ($prop['value']
								-$tcart['BackColour']['r']*256*256
								-$tcart['BackColour']['g']*256);
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

			//IF SYSTEM OWNS THIS, CHECK TO SEE IF OTHER PEOPLE HAVE READ/WRITE
			$sql = "SELECT count(*) from v_tree_cartset, cartwalls 
				WHERE v_tree_cartset.userid = " . $cfg['DPS']['systemUserID'] . " 
					AND v_tree_cartset.cartsetid = cartwalls.cartsetid 
					AND cartwalls.id = $cartwallID 
					AND v_tree_cartset.permissions & B'" . $cfg['DPS']['fileO'] .
						"' = '" . $cfg['DPS']['fileO'] . "'";
			$check = $db->getOne($sql);
			if($check > 0) {
				$this->assign('owner','t');
				$sql = "SELECT count(*) from v_tree_cartset, cartwalls 
				WHERE v_tree_cartset.userid != " . $cfg['DPS']['systemUserID'] . " 
					AND v_tree_cartset.cartsetid = cartwalls.cartsetid 
					AND cartwalls.id = $cartwallID 
					AND v_tree_cartset.permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
				$check = $db->getOne($sql);
				if($check > 0) {
					$this->assign('groupread','t');
				}
				$sql = "SELECT count(*) from v_tree_cartset, cartwalls 
				WHERE v_tree_cartset.userid != " . $cfg['DPS']['systemUserID'] . " 
					AND v_tree_cartset.cartsetid = cartwalls.cartsetid 
					AND cartwalls.id = $cartwallID 
					AND v_tree_cartset.permissions & B'" . $cfg['DPS']['fileW'] .
						"' = '" . $cfg['DPS']['fileW'] . "'";
				$check = $db->getOne($sql);
				if($check > 0) {
					$this->assign('groupwrite','t');
				}
			}

			$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(
				array(3,21,33), $userID));
			$this->assign('StationCartset','t', $userID));
			$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
			$this->assign('pagelink',$pageArray);
			$this->assign('cartwall',$cartwall);
			$this->assign('cartsetID',$cartset);
		} else {
			$this->assign('permError','t');
		}
	}
}
?>
