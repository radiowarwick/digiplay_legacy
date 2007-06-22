<?php
/**
* @package DPS
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
			
			$sql = "SELECT count(*) FROM v_tree_showplan
				WHERE id = $showID
					AND	userid = $userID
					AND permissions & B'" . $cfg['DPS']['fileR'] .
						"' = '" . $cfg['DPS']['fileR'] . "'";
			if($db->getOne($sql) > 0) {
				$sql = "SELECT count(*) FROM v_tree_showplan
					WHERE id = $showID
						AND	userid = $userID
						AND permissions & B'" . $cfg['DPS']['fileW'] .
							"' = '" . $cfg['DPS']['fileW'] . "'";
				if($db->getOne($sql) > 0) {
					$this->assign('write', 't');
				} else {
					$this->assign('write', 'f');
				}
				$show_sql = "SELECT * FROM showplans WHERE id = " . $showID;
				$show = $db->getRow($show_sql);
				
				$show['niceAirDate'] = date("d/m/y",$show['showdate']);
				$show['niceAirTime'] = date("g a",$show['showdate']);
				$show['niceCreateDate'] = date("d/m/y",$show['creationdate']);
				$show['niceCreateTime'] = date("g a",$show['creationdate']);
				
				$items_sql = "SELECT * FROM showitems 
					WHERE showplanid = " . $showID . " 
					ORDER BY position asc";
				$items = $db->getAll($items_sql);
				$time = $show['showdate'];
				foreach($items as &$item) {
					$item['time'] = $time;
					$item['niceTime'] = date("H:i:s",$item['time']);
					$item['niceLength'] = str_pad(((int)($item['length'] / 60)),2,"0",STR_PAD_LEFT) . 
						":" . str_pad(($item['length'] - (((int)($item['length'] / 60))*60)),2,"0", STR_PAD_LEFT);
					$time = $time + $item['length'];
					if($item['audioid'] != '') {
						$sql = "SELECT audio.title AS title, audiotypes.name AS type 
							FROM audio, audiotypes 
							WHERE audio.type = audiotypes.id 
								AND audio.id = " . $item['audioid'];
						$stuff = $db->getRow($sql);
						$item['audioTitle'] = $stuff['title'];
						$item['nature'] = $stuff['type'];
					} else {
						$item['nature'] = 'unknown';
					}
					if($item['scriptid'] != '') {
						$sql = "SELECT name FROM scripts 
							WHERE id = " . $item['scriptid'];
						$item['scriptName'] = $db->getOne($sql);
					}
				}
				$time = $time - $show['showdate'];
				$show['niceLength'] = (int)($time / 60) . "mins " . 
					($time - ((int)($time / 60)*60)) . "s";
				$show['niceProducer'] = AuthUtil::getUsername($show['userid']);
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
