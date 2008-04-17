<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserCartsetsViewer extends Viewer {

	const module = 'DPS';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();

		// user cartsets
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$loc = 1;
		
		$sql = "SELECT usersconfigs.val FROM configs, usersconfigs
			WHERE configs.id = usersconfigs.configid
				AND configs.name = 'default_cartset'
				AND usersconfigs.userid = " . $userID;
		$userset = $db->getOne($sql);
		
		$sql = "SELECT val FROM configuration 
			WHERE location = $loc
				AND parameter='station_cartset'";
		$stationset = $db->getOne($sql);
		if($stationset != '') {
			$sql = "SELECT cartsets.id as id, cartsets.name as name,
					cartsets.description as desc
				FROM cartsets
				WHERE id = $stationset";
			$scartset = $db->getRow($sql);
		} else {
			$scartset = "None";
		}
		
		$sql = "SELECT * from v_tree_cartset 
			WHERE v_tree_cartset.userid = $userID 
				AND v_tree_cartset.permissions & B'" . $cfg['DPS']['fileR'] .
					"' = '" . $cfg['DPS']['fileR'] . "'";
		$cartsets = $db->getAll($sql);

		foreach ($cartsets as &$cartset) {
			if($userset == $cartset['id']) {
				$cartset['active'] = 't';
			} else {
				$cartset['active'] = 'f';
			}
			$sql = "SELECT BIT_OR(permissions) 
				FROM v_tree_dir 
				WHERE v_tree_dir.id = {$cartset['parent']}
					AND v_tree_dir.userid = $userID";
			$cartset['parentperm'] = $db->getOne($sql);
		}

		$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,33), $userID));
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(
			array(1), $userID));
		$this->assign('studioAccess',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,34), $userID));
		$this->assign('cartsets', $cartsets);
		$this->assign('stationcartset',$scartset);
	}
}
?>
