<?php
/**
 * @package FrontEnds
 * @subpackage MVC
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
		$show_query = "SELECT showplans.* FROM showplans, showplanusers where 
										showplans.id = showplanusers.showplanid AND 
										showplanusers.userid = " . $userID . " AND 
										showplans.showdate >= " . $date . " AND 
										(showplanusers.permissions = 'o' OR showplanusers.permissions = 'rw')
										ORDER BY showplans.name asc";
    $partShows = $db->getAll($show_query);
		$show_query = "SELECT showplans.* FROM showplans, showplangroups, groupmembers where 
										showplans.id = showplangroups.showplanid AND 
										groupmembers.userid = " . $userID . " AND 
										groupmembers.groupid = showplangroups.groupid AND	 
										showplans.showdate >= " . $date . " AND 
										(showplangroups.permissions = 'o' OR showplangroups.permissions = 'rw')
										ORDER BY showplans.name asc";
    $gpartShows = $db->getAll($show_query);
		$show_query = "SELECT showplans.* FROM showplans, showplanusers where 
										showplans.id = showplanusers.showplanid AND 
										showplanusers.userid = " . $userID . " AND 
										showplans.showdate < " . $date . " AND 
										(showplanusers.permissions = 'o' OR showplanusers.permissions = 'rw')
										ORDER BY showplans.name asc";
    $doneShows = $db->getAll($show_query);
		$show_query = "SELECT showplans.* FROM showplans, showplangroups, groupmembers where 
										showplans.id = showplangroups.showplanid AND 
										groupmembers.userid = " . $userID . " AND 
										groupmembers.groupid = showplangroups.groupid AND	 
										showplans.showdate < " . $date . " AND 
										(showplangroups.permissions = 'o' OR showplangroups.permissions = 'rw')
										ORDER BY showplans.name asc";
    $gdoneShows = $db->getAll($show_query);

    $done = array();
    foreach($partShows as &$show) { 
      $show['niceAirDate'] = date("d/m/y",$show['showdate']);
      $show['niceAirTime'] = date("g a",$show['showdate']);
      $show['niceCreateDate'] = date("d/m/y",$show['creationdate']);
      $show['niceCreateTime'] = date("g a",$show['creationdate']);
			$show['text'] = $show['name'] . " - " . $show['niceAirDate'] . " - " . $show['niceAirTime'];
			$done[] = $show['id'];
    }
		foreach($gpartShows as &$show) {
			if(!array_search($show['id'],$done)) {
      	$show['niceAirDate'] = date("d/m/y",$show['showdate']);
      	$show['niceAirTime'] = date("g a",$show['showdate']);
      	$show['niceCreateDate'] = date("d/m/y",$show['creationdate']);
      	$show['niceCreateTime'] = date("g a",$show['creationdate']);
				$show['text'] = $show['name'] . " - " . $show['niceAirDate'] . " - " . $show['niceAirTime'];
				$partShows[] = $show;
			}
		}

		$done = array();    
    foreach($doneShows as &$show) { 
      $show['niceAirDate'] = date("d/m/y",$show['showdate']);
      $show['niceAirTime'] = date("g a",$show['showdate']);
      $show['niceCreateDate'] = date("d/m/y",$show['creationdate']);
      $show['niceCreateTime'] = date("g a",$show['creationdate']);
			$show['text'] = $show['name'] . " - " . $show['niceAirDate'] . " - " . $show['niceAirTime'];
			$done[] = $show['id'];
    }
		foreach($gdoneShows as &$show) {
			if(!array_search($show['id'],$done)) {
      	$show['niceAirDate'] = date("d/m/y",$show['showdate']);
      	$show['niceAirTime'] = date("g a",$show['showdate']);
      	$show['niceCreateDate'] = date("d/m/y",$show['creationdate']);
      	$show['niceCreateTime'] = date("g a",$show['creationdate']);
				$show['text'] = $show['name'] . " - " . $show['niceAirDate'] . " - " . $show['niceAirTime'];
				$doneShows[] = $show;
			}
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
