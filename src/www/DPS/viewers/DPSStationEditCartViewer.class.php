<?php
/**
* @package DPS
*
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSStationEditCartViewer extends Viewer {

	const module = 'DPS';
	protected $activeNode = 'foldersTree';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();

		$db = Database::getInstance($cfg['DPS']['dsn']);
		$cartID = pg_escape_string($this->fieldData['cartID']);

		//CHECK USERS PERMISION TO VIEW CART
		if($cartID == "New" || !is_numeric($cartID)) {
			$cartwallID = pg_escape_string($this->fieldData['cartwallID']);
			$flag = false;
			if($cartwallID != '' && is_numeric($cartwallID)) {
				$sql = "SELECT count(*) from v_tree_cartset, cartwalls 
				WHERE v_tree_cartset.userid = " . $cfg['DPS']['systemUserID'] . " 
					AND v_tree_cartset.cartsetid = cartwalls.cartsetid 
					AND cartwalls.id = $cartwallID 
					AND v_tree_cartset.permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
				$check = $db->getOne($sql);
				if($check > 0) {
					$flag = true;
				} else {
					$flag = false;
				}
			}
			if($flag) {
				$this->assign('new', 't');
				$this->assign('cartwallID', $this->fieldData['cartwallID']);
				$this->assign('cartPos', $this->fieldData['cartPos']);
			} else {
				$this->assign('permError', 't');
			}
		} else {
			$flag = false;
			if($cartID != '' && is_numeric($cartID)) {
				$sql = "SELECT count(*) from v_tree_cartset, cartwalls, cartsaudio 
				WHERE v_tree_cartset.userid = " . $cfg['DPS']['systemUserID'] . " 
					AND cartsaudio.cartwallid = cartwalls.id 
					AND v_tree_cartset.cartsetid = cartwalls.cartsetid 
					AND cartsaudio.id = $cartID 
					AND v_tree_cartset.permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
				$check = $db->getOne($sql);
				if($check > 0) {
					$flag = true;
				} else {
					$flag = false;
				}
			}
			if($flag) {
				$sql = "SELECT cartsaudio.id AS id, cartsaudio.text AS text, 
					cartsaudio.audio AS audioID, cartwalls.cartset AS cartset, 
					cartsaudio.style AS styleID,cartsaudio.cart AS cart 
				FROM cartsaudio, cartwalls 
				WHERE cartsaudio.cartwall = cartwalls.id 
					AND cartsaudio.id = " . $cartID;
				$cart = $db->getRow($sql);
				$this->assign('cartInfo', $cart);
			} else {
				$this->assign('permError', 't');
			}
		}

		if($flag) {
			$sql= "SELECT * FROM cartstyle ORDER BY name asc";
			$styles = $db->getAll($sql);

			$auth = Auth::getInstance();
			$userID = $auth->getUserID();

			//CHECK IF ANYONE ELSE CAN READ PERMS (IE NEED TO USE ALL USERS TREE)
			if($cartID == "New") {
				$sql = "SELECT count(*) FROM v_tree_cartset, cartwalls 
				WHERE v_tree_cartset.userid != " . $cfg['DPS']['systemUserID'] . " 
					AND v_tree_cartset.cartsetid = cartwalls.cartsetid 
					AND cartwalls.id = $cartwallID 
					AND v_tree_cartset.permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
				$user_count = $db->getOne($sql);
			} else {
				$sql = "SELECT count(*) FROM v_tree_cartset, cartwalls, cartsaudio 
				WHERE v_tree_cartset.userid = " . $cfg['DPS']['systemUserID'] . " 
					AND cartsaudio.cartwallid = cartwalls.id 
					AND v_tree_cartset.cartsetid = cartwalls.cartsetid 
					AND cartsaudio.id = $cartID 
					AND v_tree_cartset.permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
				$user_count = $db->getOne($sql);
			}

			if($user_count == 0) {
				$this->assign('treeUser', 'system');
			} else {
				$this->assign('treeUser', 'group');
			}

			$this->assign('activeNode', $this->activeNode);
			$this->assign('treeType', 'aj');
			$this->assign('styles', $styles);
		}
	}
}
?>
