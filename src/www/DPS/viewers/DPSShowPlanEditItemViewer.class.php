<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['Auth']['dir']['root'] . '/AuthUtil.class.php');
class DPSShowPlanEditItemViewer extends Viewer {
	
  const module = 'DPS';
	
  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();
    
    $db = Database::getInstance($cfg['DPS']['dsn']);
   
	 	$itemID = pg_escape_string($this->fieldData['itemID']);
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
    $date = time();
		if(is_numeric($itemID)) {
			$show_query = "select bit_or(permissions) from (SELECT showplanusers.permissions FROM showplanusers, showitems where 
										showitems.showplanid = showplanusers.showplanid AND 
										showplanusers.userid = $userID AND
										showitems.id = $itemID 
										union(SELECT permissions FROM showplangroups, usersgroups, showitems where 
										showplangroups.groupid = usersgroups.groupid and 
										showplangroups.showplanid = showitems.showplanid and 
										showitems.id = $itemID and 
										usersgroups.userid = $userID)) as Q1";
			$checkShows = $db->getOne($show_query);
			if(substr($checkShows,0,1) == "1") {
				if(substr($checkShows,1,1) == "1") {
					$this->assign('write', 't');
				} else {
					$this->assign('write', 'f');
				}
				$show_sql = "SELECT showplans.* FROM showplans, showitems where showitems.showplanid = showplans.id AND showitems.id = " . $itemID;
				$show = $db->getRow($show_sql);
      	$show['niceAirDate'] = date("d/m/y",$show['showdate']);
      	$show['niceAirTime'] = date("g a",$show['showdate']);
      	$show['niceCreateDate'] = date("d/m/y",$show['creationdate']);
      	$show['niceCreateTime'] = date("g a",$show['creationdate']);
				$items_sql = "SELECT * from showitems where showplanid = " . $show['id'] . " order by position asc";
				$items = $db->getAll($items_sql);
				$time = $show['showdate'];
				$i = 0;
				foreach($items as &$item) {
					if($item['id'] == $itemID) {
						$item['time'] = $time;
						$item['niceTime'] = date("H:i:s",$item['time']);
						$item['m'] = (String)((int)($item['length'] / 60));
						$item['s'] = (String)($item['length'] - ($item['m'])*60);
						$item['niceLength'] = ((int)($item['length'] / 60)) . ":" . ($item['length'] - (((int)($item['length'] / 60))*60));
						if($item['audioid'] != '') {
							$sql = "select audio.title as title, audiotypes.name as type, audio.length_smpl as len from audio, audiotypes  where 
										audio.type = audiotypes.id and audio.id = " . $item['audioid'];
							$stuff = $db->getRow($sql);
							$item['audioTitle'] = $stuff['title'];
							$item['nature'] = $stuff['type'];
							$item['audioLen'] = $stuff['len'];
							$item['niceAudioLength'] = round((($stuff['len']/44100)/60)) .  ":" . (($stuff['len']/44100)%60);
						} else {
							$item['nature'] = 'unknown';
						}
						if($item['scriptid'] != '') {
							$sql = "select name, length from scripts where id = " . $item['scriptid'];
							$stuff = $db->getRow($sql);
							$item['scriptName'] = $stuff['name'];
							$item['sm'] = (String)((int)($stuff['length'] / 60));
							$item['ss'] = (String)($stuff['length'] - ($item['sm'])*60);
							$item['scriptLen'] = $stuff['length'];
							$item['niceScriptLength'] = $item['sm'] . ":" . $item['ss'];
						}
						break;
					}
					$time = $time + $item['length'];
					$i++;
				}
				if($show['showdate'] > $date) {
					$this->assign('done', 'f');
				} else {
					$this->assign('done', 't');
				}
				if($items[$i]['length'] < $items[$i]['scriptLen'] || $items[$i]['length'] < ($items[$i]['audioLen']/44100)) {
					$this->assign('short', 't');
				}
				$this->assign('show', $show);
				$this->assign('item', $items[$i]);
			} else {
				$this->assign('error', 'You do not have permission to edit that item.');
			}
		} else {
			$this->assign('error', 'Invalid Item ID supplied');
		}

    $this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
  }
}

?>
