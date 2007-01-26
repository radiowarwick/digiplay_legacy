<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['Auth']['dir']['root'] . '/AuthUtil.class.php');
class DPSShowPlanEditViewer extends Viewer {
	
  const module = 'DPS';
	
  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();
    
    $db = Database::getInstance($cfg['DPS']['dsn']);
   
	 	$showID = pg_escape_string($this->fieldData['showID']);
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
    $date = time();
		if(is_numeric($showID)) {
			
			$show_query = "SELECT count(*) FROM showplanusers where 
										showplanusers.userid = " . $userID . " AND
										showplanusers.showplanid = " . $showID . " AND 
										(showplanusers.permissions = 'o' OR showplanusers.permissions = 'rw')";
    	$checkShows = $db->getOne($show_query);
			if($checkShows == 0) {
				$show_query = "SELECT count(*) FROM showplangroups, groupmembers where 
										showplangroups.groupid = groupmembers.groupid and 
										showplangroups.showplanid = $showID  and 
										groupmembers.userid =  $userID and 
										(showplangroups.permissions = 'o' OR showplangroups.permissions = 'rw')";
				$checkShows = $db->getOne($show_query);
			}
			if($checkShows > 0) {
				$show_sql = "SELECT * FROM showplans where id = " . $showID;
				$show = $db->getRow($show_sql);
      	$show['niceAirDate'] = date("d/m/y",$show['showdate']);
      	$show['niceAirTime'] = date("g a",$show['showdate']);
      	$show['niceCreateDate'] = date("d/m/y",$show['creationdate']);
      	$show['niceCreateTime'] = date("g a",$show['creationdate']);
				$items_sql = "SELECT * from showitems where showplanid = " . $showID . " ORDER BY position asc";
				$items = $db->getAll($items_sql);
				$time = $show['showdate'];
				foreach($items as &$item) {
					$item['time'] = $time;
					$item['niceTime'] = date("H:i:s",$item['time']);
					$item['niceLength'] = ((int)($item['length'] / 60)) . ":" . ($item['length'] - (((int)($item['length'] / 60))*60));
					$time = $time + $item['length'];
					if($item['audio'] != '') {
						$sql = "select audio.title as title, audiotypes.name as type from audio, audiotypes  where 
										audio.type = audiotypes.id and audio.id = " . $item['audio'];
						$stuff = $db->getRow($sql);
						$item['audioTitle'] = $stuff['title'];
						$item['nature'] = $stuff['type'];
					} else {
						$item['nature'] = 'unknown';
					}
				}
				$time = $time - $show['showdate'];
				$show['niceLength'] = (int)($time / 60) . "mins " . ($time - ((int)($time / 60)*60)) . "s";
				$show['niceProducer'] = AuthUtil::getUsername($show['creator']);
				if($show['showdate'] > $date) {
					$this->assign('done', 'f');
				} else {
					$this->assign('done', 't');
				}
				$this->assign('show', $show);
				$this->assign('showItems', $items);
				$this->assign('itemCount',count($items));
			} else {
				$this->assign('error', 'You do not have permission to edit that show.');
			}
		} else {
			$this->assign('error', 'Invalid Show ID supplied');
		}

    $this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
  }
}

?>
