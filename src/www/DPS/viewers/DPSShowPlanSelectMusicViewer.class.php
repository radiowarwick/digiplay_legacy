<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['Auth']['dir']['root'] . '/AuthUtil.class.php');
class DPSShowPlanSelectMusicViewer extends Viewer {
	
	const module = 'DPS';
	
	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$itemID = pg_escape_string($this->fieldData['itemID']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$date = time();
		if(is_numeric($itemID) && isset($itemID)) {
			$show_query = "SELECT bit_or(permissions)
				FROM (SELECT showplanusers.permissions
				FROM showplanusers, showitems
				WHERE showitems.showplanid = showplanusers.showplanid
				AND showplanusers.userid = " . $userID . "
				AND showitems.id = " . $itemID . "
				UNION(SELECT showplangroups.permissions
				FROM showplangroups, groupmembers, showitems
				WHERE showplangroups.groupid = groupmembers.groupid
				AND showplangroups.showplanid = showitems.showplanid
				AND showitems.id = $itemID
				AND groupmembers.userid = $userID)) AS Q1";
			$checkShows = $db->getOne($show_query);
			if(substr($checkShows,0,1) == "1") {
				if(substr($checkShows,1,1) == "1") {
					$this->assign('write', 't');
				} else {
					$this->assign('write', 'f');
				}
				$show_sql = "SELECT showplans.*
					FROM showplans, showitems
					WHERE showitems.showplanid = showplans.id
					AND showitems.id = " . $itemID;
				$show = $db->getRow($show_sql);

				$show['niceAirDate'] = date("d/m/y",$show['showdate']);
				$show['niceAirTime'] = date("g a",$show['showdate']);
				$show['niceCreateDate'] = date("d/m/y",$show['creationdate']);
				$show['niceCreateTime'] = date("g a",$show['creationdate']);
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
						$item['niceLength'] = ((int)($item['length'] / 60)) .
							":" . ($item['length'] -
							(((int)($item['length'] / 60))*60));
						if($item['audio'] != '') {
							$sql = "SELECT audio.title AS title,
								audiotypes.name AS type,
								audio.length_smpl AS len FROM audio, audiotypes
								WHERE audio.type = audiotypes.id
								AND audio.id = " . $item['audio'];
							$stuff = $db->getRow($sql);
							$item['audioTitle'] = $stuff['title'];
							$item['nature'] = $stuff['type'];
							$item['niceAudioLength'] =
								round((($stuff['len']/44100)/60)) .  ":" .
								(($stuff['len']/44100)%60);
						} else {
							$item['nature'] = 'unknown';
						}
						if($item['script'] != '') {
							$sql = "SELECT name, length from scripts
								WHERE id = " . $item['script'];
							$stuff = $db->getRow($sql);
							$item['scriptName'] = $stuff['name'];
							$item['niceScriptLength'] =
								((int)($stuff['length'] / 60)) . ":" .
								($stuff['length'] -
								(((int)($stuff['length'] / 60))*60));
						}
						break;
					}
					$time = $time + $item['length'];
					$i++;
				}
				$offset = $this->fieldData['dpsSearchPage'];
				if($offset == "") {
					$offset = 0;
				} else {
					$offset--;
				}
				$searchValue = $this->fieldData['dpsSearchVal'];
				$searchType = $this->fieldData['dpsSearchType'];
				if($this->fieldData['dpsSortType'] != '') {
					$sesh = Session::getInstance();
					$sortType = $this->fieldData['dpsSortType'];
					$sesh->setValue("dpsSortType",$sortType);
				} else {
					$sesh = Session::getInstance();
					if($sesh->keyExists("dpsSortType")) {
						$sortType=$sesh->getValue("dpsSortType");
					} else {
						$sortType="title";
					}
				}

				$searchResult = DPS::searchAudio($searchValue,$searchType,
					$sortType,$offset,'');
				$rNum = searchPageAudio($searchValue,$searchType,'');

				$pages = 1; 
				$pageArray[] = $pages;
				$rNum = $rNum-$cfg['DPS']['resultLimit'];
				while($rNum > $cfg['DPS']['resultLimit']) {
					$pages++;
					$pageArray[] = $pages;
					$rNum = $rNum-$cfg['DPS']['resultLimit'];
				}
		
				$this->assign('page', $offset);
				$this->assign('searchResult', $searchResult);
				$this->assign('searchInfo', $searchInfo);
				$this->assign('pages', $pageArray);
				$this->assign('searchType', $searchType);
				$this->assign('searchValue', $searchValue);
				$this->assign('sortType',$sortType);
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
