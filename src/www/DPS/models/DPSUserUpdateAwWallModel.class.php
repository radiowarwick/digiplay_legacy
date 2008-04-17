<?php
/**
 * @package DPS
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSUserUpdateCartwallModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$name = pg_escape_string($this->fieldData['name']);
		$desc = pg_escape_string($this->fieldData['desc']);
		$cartwallID = pg_escape_string($this->fieldData['cartwallID']);
		if($this->fieldData['Submit'] == "Remove Page") {
			$sql = "SELECT cartsetid FROM cartwalls WHERE id=" . $cartwallID;
			$cartsetID = $db->getOne($sql);
			$sql = "SELECT COUNT(*) FROM cartwalls WHERE cartsetid=" . $cartsetID;
			$check = $db->getOne($sql);
			//cant delete last page
			if($check > 1) {
				$where = "cartwallid = " . $cartwallID;
				$db->delete('cartsaudio', $where, true);
				$where = "id = " . $cartwallID;
				$db->delete('cartwalls', $where, true);
				$page = pg_escape_string($this->fieldData['page']);
				$sql = "SELECT * FROM cartwalls
					WHERE cartsetid=" . $cartsetID . "
					AND page > $page ORDER BY page asc";
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
			
			$auth = Auth::getInstance();
			$userID = $auth->getUserID();
			$sql = "SELECT COUNT(*) FROM v_tree_cartset, cartwalls
				WHERE v_tree_cartset.userid = $userID
				AND v_tree_cartset.id = cartwalls.cartsetid
				AND cartwalls.id = $cartwallID
				AND v_tree_cartset.permissions & B'" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
			$check = $db->getOne($sql);
			if($check > 0) {
				$sql = "SELECT cartsetid FROM cartwalls 
					WHERE id = $cartwallID LIMIT 1";
				$cartsetID = $db->getOne($sql);
				$where = "cartsetid = $cartsetID 
					AND groupid = " . $cfg['DPS']['allusersgroupid'];
				$db->delete('cartsetsgroups',$where,true);
				
				$sql = "SELECT COUNT(*) FROM cartsaudio, cartwalls 
					WHERE cartsaudio.cartwallid = cartwalls.id
					AND cartwalls.cartsetid = " . $cartsetID;
				$cartcount = $db->getOne($sql);
				$sql = "SELECT count(*) FROM (SELECT cartsaudio.audioid 
					FROM cartsaudio, cartwalls, v_tree_audio
					WHERE cartwalls.cartsetid = $cartsetID
						AND cartsaudio.cartwallid = cartwalls.id
						AND cartsaudio.audioid = v_tree_audio.id
						AND v_tree_audio.permissions & B'" . $cfg['DPS']['fileR'] . "'
					 = '" . $cfg['DPS']['fileR'] . "'
					GROUP BY cartsaudio.audioid) as Q1";
					
				$permCount = $db->getOne($sql);
				if($permCount >= $cartcount) {
					if($this->fieldData['readAll'] == "on"
						&& $this->fieldData['writeAll'] == "on") {
						$perm = array();
						$perm['groupid'] = $cfg['DPS']['allusersgroupid'];
						$perm['cartsetid'] = $cartsetID;
						$perm['permissions'] = $cfg['DPS']['fileRW'];
						$db->insert('cartsetsgroups',$perm,false);
					}elseif($this->fieldData['writeAll'] == "on") {
						$perm = array();
						$perm['groupid'] = $cfg['DPS']['allusersgroupid'];
						$perm['cartsetid'] = $cartsetID;
						$perm['permissions'] = $cfg['DPS']['fileRW'];
						$db->insert('cartsetsgroups',$perm,false);
					}elseif($this->fieldData['readAll'] == "on") {
						$perm = array();
						$perm['groupid'] = $cfg['DPS']['allusersgroupid'];
						$perm['cartsetid'] = $cartsetID;
						$perm['permissions'] = $cfg['DPS']['fileR'];
						$db->insert('cartsetsgroups',$perm,false);
					}
				} else {
					$this->errors['model'] =
						"All audio elements in this cartset must be public";
				}
			}
		}
	}
		
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
