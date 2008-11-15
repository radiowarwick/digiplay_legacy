<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserAwSetViewer extends Viewer {

	const module = 'DPS';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();

		// user awsets
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$loc = 1;
		
		$sql = "SELECT usersconfigs.val FROM configs, usersconfigs
			WHERE configs.id = usersconfigs.configid
				AND configs.name = 'default_aw_set'
				AND usersconfigs.userid = " . $userID;
		$userset = $db->getOne($sql);
		
		$sql = "SELECT val FROM configuration 
			WHERE location = $loc
				AND parameter='station_aw_set'";
		$stationset = $db->getOne($sql);
		if($stationset != '') {
			$sql = "SELECT aw_sets.id as id, aw_sets.name as name,
					aw_sets.description as desc
				FROM aw_sets
				WHERE id = $stationset";
			$sawset = $db->getRow($sql);
		} else {
			$sawset = "None";
		}
		
		$sql = "SELECT * from v_tree_aw_sets 
			WHERE v_tree_aw_sets.userid = $userID 
				AND v_tree_aw_sets.permissions & B'" . $cfg['DPS']['fileR'] .
					"' = '" . $cfg['DPS']['fileR'] . "'";
		$awsets = $db->getAll($sql);

		foreach ($awsets as &$awset) {
			if($userset == $awset['id']) {
				$awset['active'] = 't';
			} else {
				$awset['active'] = 'f';
			}
			$sql = "SELECT BIT_OR(permissions) 
				FROM v_tree_dir 
				WHERE v_tree_dir.id = {$awset['parent']}
					AND v_tree_dir.userid = $userID";
			$awset['parentperm'] = $db->getOne($sql);
		}

		$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,33), $userID));
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(
			array(1), $userID));
		$this->assign('studioAccess',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,35), $userID));
		$this->assign('awsets', $awsets);
		$this->assign('stationawset',$sawset);
	}
}
?>
