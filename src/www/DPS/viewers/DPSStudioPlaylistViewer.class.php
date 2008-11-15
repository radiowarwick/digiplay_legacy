<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['DPS']['dir']['root'] . '/DPS.class.php');

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

        $resultType = $this->fieldData['dpsResultType'];
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

		if ($resultType == 'Search') {
			if($searchValue != '') {
				$searchResult = DPS::searchPlaylistAudio($searchValue,$searchType,
					$sortType,$offset,'',$playlistID);
				$rNum = DPS::searchPageAudio($searchValue,$searchType,'');
				$searchInfo = "Found $rNum results matching your query";
            }
        } else if ($resultType == 'View') {
			$searchResult = DPS::showPlaylist($playlistID);
		}

		$pages = ceil($rNum / $cfg['DPS']['resultLimit']);
        //fill the array $pageArray with values from 1 to $pages (default increment is 1)
        $pageArray = range(1, $pages);

		$sql = "SELECT * FROM playlists";
		$playlists = $db->getAll($sql);

		$auth = Auth::getInstance();
		$userID = $auth->getUserID();

        $sql = "SELECT * FROM playlists WHERE id = ".pg_escape_string($playlistID);
        $playlist = $db->getRow($sql);


		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		$this->assign('studioAccess',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,34), $userID));
		$this->assign('playlists',$playlists);
		$this->assign('playlist',$playlist);
		$this->assign('page', $offset);
		$this->assign('searchResult', $searchResult);
		$this->assign('searchInfo', $searchInfo);
		$this->assign('pages', $pageArray);
		$this->assign('searchType', $searchType);
		$this->assign('searchValue', $searchValue);
		$this->assign('sortType',$sortType);
        $this->assign('resultType',$resultType);
	}
}
?>
