<?php
/**
* @package FrontEnds
* @subpackage MVC
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSStudioPlaylistViewer extends Viewer {
	
	const module = 'DPS';
	
	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		
		$db = Database::getInstance($cfg['DPS']['dsn']);

		$playlistID = pg_escape_string($this->fieldData['dpsPlaylistID']);
		if($playlistID == '' || !is_numeric($playlistID)) {
			$playlistID = 1;
		}
		$offset = $this->fieldData['dpsSearchPage'];
		if($offset == "") {
			$offset = 0;
		} else {
			$offset--;
		}

		$searchValue = $this->fieldData['dpsSearchVal'];
		$searchType = $this->fieldData['dpsSearchType'];
		$letter = $this->fieldData['dpsSearchLetter'];
		if($searchType == '' && $letter != '') {
			if($letter == "*") {
				$searchType = 'Number';
			} else {
				$searchType = 'Letter';
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
			$searchResult = DPS::searchAudio($searchValue,$searchType,$sortType,$offset,'');
			$rNum = DPS::searchPageAudio($searchValue,$searchType,'');
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

		$sql = "select * from playlists";
		$playlists = $db->getAll($sql);

		$sql = "select * from playlists where id = " . pg_escape_string($playlistID);
		$playlist = $db->getRow($sql);

		$auth = Auth::getInstance();
		$userID = $auth->getUserID();

		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		$this->assign('studioAccess',AuthUtil::getDetailedUserrealmAccess(array(3,21,34), $userID));
		$this->assign('playlists',$playlists);
		$this->assign('playlist',$playlist);
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
