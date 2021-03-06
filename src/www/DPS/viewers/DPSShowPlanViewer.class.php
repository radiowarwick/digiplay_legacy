<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['Auth']['dir']['root'] . '/AuthUtil.class.php');
class DPSShowPlanViewer extends Viewer {
	
	const module = 'DPS';
	
	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		
		$db = Database::getInstance($cfg['DPS']['dsn']);
	
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$date = time();
		$show_query = "SELECT DISTINCT showplans.*, v_tree_showplan.permissions 
			FROM showplans, v_tree_showplan 
			WHERE showplans.id = v_tree_showplan.id AND 
				v_tree_showplan.userid = $userID AND 
				showplans.showdate >= " . $date . " AND 
				v_tree_showplan.permissions & B'" . $cfg['DPS']['fileR'] .
					"' = '" . $cfg['DPS']['fileR'] . "' 
			ORDER BY name asc";
		$partShows = $db->getAll($show_query);
		$show_query = "SELECT DISTINCT showplans.*, v_tree_showplan.permissions 
			FROM showplans, v_tree_showplan 
			WHERE showplans.id = v_tree_showplan.id AND 
				v_tree_showplan.userid = $userID AND 
				showplans.showdate < " . $date . " AND 
				v_tree_showplan.permissions & B'" . $cfg['DPS']['fileR'] .
					"' = '" . $cfg['DPS']['fileR'] . "' 
			ORDER BY name asc";
		$doneShows = $db->getAll($show_query);

		foreach($partShows as &$show) {
			$show['niceAirDate'] = date("d/m/y",$show['showdate']);
			$show['niceAirTime'] = date("H:i",$show['showdate']);
			$show['niceCreateDate'] = date("d/m/y",$show['creationdate']);
			$show['niceCreateTime'] = date("H:i",$show['creationdate']);
			$show['text'] = $show['name'] . " - " . $show['niceAirDate'] .
				" - " . $show['niceAirTime'] . " (" . AuthUtil::getUsername($show['userid']) . ")";
			$sql = "SELECT BIT_OR(v_tree_dir.permissions) 
				FROM v_tree_showplan, v_tree_dir 
				WHERE v_tree_showplan.id = {$show['id']}
					AND v_tree_showplan.parent = v_tree_dir.id
					AND v_tree_dir.userid = $userID";
			$show['parentperm'] = $db->getOne($sql);
		}
		foreach($doneShows as &$show) { 
			$show['niceAirDate'] = date("d/m/y",$show['showdate']);
			$show['niceAirTime'] = date("H:i",$show['showdate']);
			$show['niceCreateDate'] = date("d/m/y",$show['creationdate']);
			$show['niceCreateTime'] = date("H:i",$show['creationdate']);
			$show['text'] = $show['name'] . " - " . $show['niceAirDate'] .
				" - " . $show['niceAirTime'] . " (" . AuthUtil::getUsername($show['userid']) . ")";
			$sql = "SELECT BIT_OR(v_tree_dir.permissions) 
				FROM v_tree_showplan, v_tree_dir 
				WHERE v_tree_showplan.id = {$show['id']}
					AND v_tree_showplan.parent = v_tree_dir.id
					AND v_tree_dir.userid = $userID";
			$show['parentperm'] = $db->getOne($sql);
		}

		$pShowCount = count($partShows);
		$dShowCount = count($doneShows);
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		$this->assign('partShows', $partShows);
		$this->assign('pShowCount', $pShowCount);
		$this->assign('doneShows', $doneShows);
		$this->assign('dShowCount', $dShowCount);

        $this->assign('deleteID', $this->fieldData['deleteID']);
	}
}

?>
