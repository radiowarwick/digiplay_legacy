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
		$show_query = "SELECT DISTINCT showplans.* FROM showplans, showplanusers 
			WHERE showplans.id = showplanusers.showplanid AND 
			showplanusers.userid = " . $userID . " AND 
			showplans.showdate >= " . $date . " AND 
			showplanusers.permissions & B'" . $cfg['DPS']['fileR'] .
				"' = '" . $cfg['DPS']['fileR'] . "' 
			UNION(SELECT showplans.* FROM showplans, showplangroups, usersgroups 
				WHERE showplans.id = showplangroups.showplanid AND 
				usersgroups.userid = " . $userID . " AND 
				usersgroups.groupid = showplangroups.groupid AND	 
				showplans.showdate >= " . $date . " AND
				showplangroups.permissions & B'" . $cfg['DPS']['fileR'] .
					"' = '" . $cfg['DPS']['fileR'] . "')  
			ORDER BY name asc";
		$partShows = $db->getAll($show_query);
		$show_query = "SELECT DISTINCT showplans.* FROM showplans, showplanusers 
		WHERE showplans.id = showplanusers.showplanid AND 
			showplanusers.userid = " . $userID . " AND 
			showplans.showdate < " . $date . " AND 
			showplanusers.permissions & B'" . $cfg['DPS']['fileR'] .
				"' = '" . $cfg['DPS']['fileR'] . "' 
			UNION(SELECT showplans.* FROM showplans, showplangroups, usersgroups 
				WHERE showplans.id = showplangroups.showplanid AND 
				usersgroups.userid = " . $userID . " AND 
				usersgroups.groupid = showplangroups.groupid AND	 
				showplans.showdate < " . $date . " AND
				showplangroups.permissions & B'" . $cfg['DPS']['fileR'] .
					"' = '" . $cfg['DPS']['fileR'] . "')  
			ORDER BY name asc";
		$doneShows = $db->getAll($show_query);

		foreach($partShows as &$show) {
			$show['niceAirDate'] = date("d/m/y",$show['showdate']);
			$show['niceAirTime'] = date("H:i",$show['showdate']);
			$show['niceCreateDate'] = date("d/m/y",$show['creationdate']);
			$show['niceCreateTime'] = date("H:i",$show['creationdate']);
			$show['text'] = $show['name'] . " - " . $show['niceAirDate'] .
				" - " . $show['niceAirTime'];
		}
		foreach($doneShows as &$show) { 
			$show['niceAirDate'] = date("d/m/y",$show['showdate']);
			$show['niceAirTime'] = date("H:i",$show['showdate']);
			$show['niceCreateDate'] = date("d/m/y",$show['creationdate']);
			$show['niceCreateTime'] = date("H:i",$show['creationdate']);
			$show['text'] = $show['name'] . " - " . $show['niceAirDate'] .
				" - " . $show['niceAirTime'];
		}

		$pShowCount = count($partShows);
		$dShowCount = count($doneShows);
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		$this->assign('partShows', $partShows);
		$this->assign('pShowCount', $pShowCount);
		$this->assign('doneShows', $doneShows);
		$this->assign('dShowCount', $dShowCount);
	}
}

?>
