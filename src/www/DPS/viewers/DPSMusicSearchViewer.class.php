<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['DPS']['dir']['root'] . '/DPS.class.php');

class DPSMusicSearchViewer extends Viewer {
	
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
		
		$searchValue = trim($this->fieldData['dpsSearchVal']);
		$searchType = $this->fieldData['dpsSearchType'];
		$letter = pg_escape_string($this->fieldData['dpsSearchLetter']);
		
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
			$searchResult = DPS::searchAudio($searchValue,$searchType,
				$sortType,$offset,'');
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
		
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$this->assign('RequestTrack',
			AuthUtil::getDetailedUserrealmAccess(array(3,21,29), $userID));
		$this->assign('CensorTrack',
			AuthUtil::getDetailedUserrealmAccess(array(3,21,30), $userID));
		$this->assign('ReportTrack',
			AuthUtil::getDetailedUserrealmAccess(array(3,21,43), $userID));
		$this->assign('EditTrack',
			AuthUtil::getDetailedUserrealmAccess(array(3,21,27), $userID));
		$this->assign('DeleteTrack',
			AuthUtil::getDetailedUserrealmAccess(array(2,21,32), $userID));
		$this->assign('Admin',
			AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		
		$this->assign('page', $offset);
		$this->assign('searchResult', $searchResult);
		$this->assign('searchInfo', $searchInfo);
		$this->assign('pages', $pageArray);
		$this->assign('searchType', $searchType);
		$this->assign('searchValue', $searchValue);
		$this->assign('sortType',$sortType);
	}
}
?>
