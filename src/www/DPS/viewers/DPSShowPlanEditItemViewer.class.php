<?php
/**
 * @package DPS
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
			$show_query = "SELECT DISTINCT BIT_OR(v_tree_showplan.permissions) 
			FROM showitems, v_tree_showplan 
			WHERE showitems.showplanid = v_tree_showplan.id AND 
				v_tree_showplan.userid = $userID AND 
				showitems.id = $itemID";
			$checkShows = $db->getOne($show_query);
			if(substr($checkShows,0,1) == "1") {
				if(substr($checkShows,1,1) == "1") {
					$this->assign('write', 't');
				} else {
					$this->assign('write', 'f');
				}
				$show_sql = "SELECT showplans.* FROM showplans, showitems
					WHERE showitems.showplanid = showplans.id 
					AND showitems.id = " . $itemID;
				$show = $db->getRow($show_sql);
				$show['niceAirDate'] = date("d/m/y",$show['showdate']);
				$show['niceAirTime'] = date("H:i",$show['showdate']);
				$show['niceCreateDate'] = date("d/m/y",$show['creationdate']);
				$show['niceCreateTime'] = date("H:i",$show['creationdate']);
				$items_sql = "SELECT * FROM showitems 
					WHERE showplanid = " . $show['id'] . "
					ORDER BY position ASC";
				$items = $db->getAll($items_sql);
				$time = $show['showdate'];
				$i = 0;
				foreach($items as &$item) {
					if($item['id'] == $itemID) {
						$item['time'] = $time;
						$item['niceTime'] = date("H:i:s",$item['time']);
						$item['m'] = str_pad(((int)($item['length'] / 60)),2,"0",STR_PAD_LEFT);
						$item['s'] = str_pad(($item['length'] -
							($item['m'])*60),2,"0",STR_PAD_LEFT);
						$item['niceLength'] = $item['m'] . 
							":" . $item['s'];
						if($item['audioid'] != '') {
							$sql = "SELECT audio.title AS title,
								audiotypes.name AS type,
								audio.length_smpl AS len
								FROM audio, audiotypes
								WHERE audio.type = audiotypes.id
								AND audio.id = " . $item['audioid'];
							$stuff = $db->getRow($sql);
							$item['audioTitle'] = $stuff['title'];
							$item['nature'] = $stuff['type'];
							$item['audioLen'] = $stuff['len'];
							$item['niceAudioLength'] = 
								str_pad(floor((($stuff['len']/44100)/60)),2,"0",STR_PAD_LEFT) .
								":" . str_pad((ceil($stuff['len']/44100)%60),2,"0",STR_PAD_LEFT);
						} else {
							$item['nature'] = 'unknown';
						}
						if($item['scriptid'] != '') {
							$sql = "SELECT NAME, length FROM scripts
								WHERE id = " . $item['scriptid'];
							$stuff = $db->getRow($sql);
							$item['scriptName'] = $stuff['name'];
							$item['sm'] =
								str_pad(((int)($stuff['length'] / 60)),2,"0",STR_PAD_LEFT);
							$item['ss'] =
								str_pad(($stuff['length'] - ($item['sm'])*60),2,"0",STR_PAD_LEFT);
							$item['scriptLen'] = $stuff['length'];
							$item['niceScriptLength'] =
								$item['sm'] . ":" . $item['ss'];
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
				if($items[$i]['length'] < $items[$i]['scriptLen'] 
					|| $items[$i]['length'] < floor(($items[$i]['audioLen']/44100))) {
					$this->assign('short', 't');
				}
				$this->assign('show', $show);
				$this->assign('item', $items[$i]);
			} else {
				$this->assign('error',
					'You do not have permission to edit that item.');
			}
		} else {
			$this->assign('error', 'Invalid Item ID supplied');
		}
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1),
			$userID));
	}
}
?>
