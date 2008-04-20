<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSStationAwSetViewer extends Viewer {

	const module = 'DPS';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();

		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$loc = 1;
		$sql = "SELECT * from v_tree_aw_sets 
			WHERE v_tree_aw_sets.userid = " . $cfg['DPS']['systemUserID'] . " 
				AND v_tree_aw_sets.permissions & B'" . $cfg['DPS']['fileR'] .
					"' = '" . $cfg['DPS']['fileR'] . "'";
		// station awsets
		$awsets = $db->getAll($sql);

		$sql = "SELECT val FROM configuration 
			WHERE location = $loc 
				AND parameter = 'station_aw_set'";
		$userset = $db->getOne($sql);

		foreach ($awsets as &$awset) {
			if($userset == $awset['id']) {
				$awset['active'] = 't';
			} else {
				$awset['active'] = 'f';
			}
			$sql = "SELECT BIT_OR(permissions) 
				FROM v_tree_dir 
				WHERE v_tree_dir.id = {$awset['parent']}
					AND v_tree_dir.userid = {$cfg['DPS']['systemUserID']}";
			$awset['parentperm'] = $db->getOne($sql);
		}

		$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,33), $userID));
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		$this->assign('awsets', $awsets);
	}
}
?>
