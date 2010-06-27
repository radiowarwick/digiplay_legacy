<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['Auth']['dir']['root'] . '/AuthUtil.class.php');
class DPSTrackRequestViewer extends Viewer {
	
	const module = 'DPS';
	
	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		
		$db = Database::getInstance($cfg['DPS']['dsn']);
	
		$count_query = "SELECT count(*) FROM requests";
		$requestedNum = $db->getOne($count_query);
		
		$query = "SELECT * FROM requests ORDER BY date DESC";
		$requestedResult = $db->getAll($query);
		$i=0;
		
		foreach($requestedResult as $key => &$track) { 
			$track['number'] = $i;
			$track['rtime'] = date("m/d/y",$track['date']);
			$track['user'] = AuthUtil::getUsername($track['userid']);
			$i++;
		}
		$trackCount = $i;
		
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$this->assign('CensorTrack',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,30), $userID));
		$this->assign('RequestTrack','t');
		$this->assign('RemoveRequestTrack',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,29), $userID));
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(
			array(1), $userID));
		$this->assign('requestedTracks', $requestedResult);
		$this->assign('requestedNum', $requestedNum);
	}
}

?>
