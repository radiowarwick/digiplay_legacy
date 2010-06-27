<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['DPS']['dir']['root'] . '/DPS.class.php');

class DPSSuePlaylistViewer extends Viewer {

	const module = 'DPS';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$offset = $this->fieldData['dpsSearchPage'];
		if($offset == "") {
			$offset = 0;
		} else {
			$offset--;
		}

		$searchValue = $this->fieldData['dpsSearchVal'];
		$searchType = $this->fieldData['dpsSearchType'];
		$letter = pg_escape_string($this->fieldData['dpsSearchLetter']);

		if($searchValue == '' && $searchType == '' && $letter == '') {
			$letter = '*';
		}

		if($searchType == '' && $letter != '') {
			if($letter == "*") {
				$searchType = 'Number';
				$searchValue = $letter;
			} else {
				$searchType = 'Letter';
				$searchValue = $letter;
			}
		}
		
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

		if($searchValue != '') {
			$searchResult = DPS::searchAudio($searchValue,$searchType,
				$sortType,$offset,'t');
			$rNum = DPS::searchPageAudio($searchValue,$searchType,'t');
			$searchInfo = "Found $rNum results matching your query";
		}

		$pages = 1; 
		$pageArray[] = $pages;
		$rNum = $rNum-$cfg['DPS']['resultLimit'];
		while($rNum > $cfg['DPS']['resultLimit']) {
			$pages++;
			$pageArray[] = $pages;
			$rNum = $rNum-$cfg['DPS']['resultLimit'];
		}

		//Sue playing now/next
		$query = "SELECT audio.title AS title, audio.id AS id 
		FROM sustschedule, audio 
		WHERE sustschedule.audioid = audio.id 
		ORDER BY sustschedule.id asc 
		OFFSET 1 
		LIMIT 1";
		$sueNextTrack = $db->getRow($query);
		if($sueNextTrack != '') {
			$sql = "SELECT DISTINCT artists.name as name 
			FROM artists, audioartists 
			WHERE audioartists.audioid = " . $sueNextTrack['id'] . " AND
				audioartists.artistid = artists.id";
			$artists = $db->getAll($sql);
			foreach($artists as $artist) {
				$sueNextTrack['artist'] = $sueNextTrack['artist'] .
					$artist['name'] . " & ";
			}
			$sueNextTrack['artist'] = rtrim($sueNextTrack['artist']," & ");
		}

		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$this->assign('Access_ViewSue',AuthUtil::getDetailedUserrealmAccess(
			array(26,20,3), $userID));
		$this->assign('Access_EditSue',AuthUtil::getDetailedUserrealmAccess(
			array(24,20,3), $userID));
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(
			array(1), $userID));
		$this->assign('Access_EditTrack',AuthUtil::getDetailedUserrealmAccess(
			array(27,21,3), $userID));
		$this->assign('Access_SueStats',AuthUtil::getDetailedUserrealmAccess(
			array(25,20,3), $userID));
		$this->assign('Access_Delete',AuthUtil::getDetailedUserrealmAccess(
			array(32,21,3), $userID));

		$this->assign('sueNextTrack', $sueNextTrack);
		$this->assign('page', $offset);
		$this->assign('searchResult', $searchResult);
		$this->assign('searchInfo', $searchInfo);
		$this->assign('pages', $pageArray);
		$this->assign('searchType', $searchType);
		$this->assign('searchValue', $searchValue);
		$this->assign('searchLetter', $letter);
		$this->assign('sortType',$sortType);
	}
}
?>
