<?php
/**
* @package DPS
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
		$sql = "SELECT * from v_tree_cartset 
			WHERE v_tree_cartset.userid = " . $cfg['DPS']['systemUserID'] . " 
				AND v_tree_cartset.permissions & B'" . $cfg['DPS']['fileR'] .
					"' = '" . $cfg['DPS']['fileR'] . "'";
		// station cartsets
		$cartsets = $db->getAll($sql);

		$sql = "SELECT val FROM configuration 
			WHERE location = $loc 
				AND parameter = 'station_cartset'";
		$userset = $db->getOne($sql);

		foreach ($cartsets as &$cartset) {
			if($userset == $cartset['id']) {
				$cartset['active'] = 't';
			} else {
				$cartset['active'] = 'f';
			}
			$sql = "SELECT BIT_OR(permissions) 
				FROM v_tree_dir 
				WHERE v_tree_dir.id = {$cartset['parent']}
					AND v_tree_dir.userid = {$cfg['DPS']['systemUserID']}";
			$cartset['parentperm'] = $db->getOne($sql);
		}

		$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,33), $userID));
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		$this->assign('cartsets', $cartsets);
	}
}
?>
