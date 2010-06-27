<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserAudioMoveViewer extends Viewer {

	const module = 'DPS';
	protected $activeNode = 'foldersTree';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$trackID = $this->fieldData['audioID'];
		if(!is_numeric($trackID)) {
			$this->assign('permError', 't');
		} else {
			//As there is no general audio view
			$sql = "SELECT count(*) FROM v_tree_jingle 
				WHERE id = " . pg_escape_string($trackID) . " 
					AND userid = " . $userID . " 
					AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '" .
						$cfg['DPS']['fileW'] . "'";
			$check = $db->getOne($sql);
			$sql = "SELECT count(*) FROM v_tree_advert 
				WHERE id = " . pg_escape_string($trackID) . " 
					AND userid = " . $userID . " 
					AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '" .
						$cfg['DPS']['fileW'] . "'";
			$check = $check + $db->getOne($sql);
			$sql = "SELECT count(*) FROM v_tree_prerec 
				WHERE id = " . pg_escape_string($trackID) . " 
					AND userid = " . $userID . " 
					AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '" .
						$cfg['DPS']['fileW'] . "'";
			$check = $check + $db->getOne($sql);
			if($check > 0) {
				$flag = true;
			}
			if($flag) {
				$sql = "SELECT * FROM audio 
					WHERE id = " . pg_escape_string($trackID);
				$audio = $db->getRow($sql);

				//As there is no general audio view
				$sql = "SELECT count(*) FROM v_tree_jingle 
					WHERE id = " . pg_escape_string($trackID) . " 
						AND userid = " . $userID . " 
						AND permissions & B'" . $cfg['DPS']['fileO'] . "' = '" .
							$cfg['DPS']['fileO'] . "'";
				$check = $db->getOne($sql);
				$sql = "SELECT count(*) FROM v_tree_advert 
					WHERE id = " . pg_escape_string($trackID) . " 
						AND userid = " . $userID . " 
						AND permissions & B'" . $cfg['DPS']['fileO'] . "' = '" .
							$cfg['DPS']['fileO'] . "'";
				$check = $check + $db->getOne($sql);
				$sql = "SELECT count(*) FROM v_tree_prerec 
					WHERE id = " . pg_escape_string($trackID) . " 
						AND userid = " . $userID . " 
						AND permissions & B'" . $cfg['DPS']['fileO'] . "' = '" .
							$cfg['DPS']['fileO'] . "'";
				$check = $check + $db->getOne($sql);
				if($check > 0) {
					$this->assign('own', 't');
				}
				$this->assign('audio', $audio);
				$this->assign('treeType', '');
			} else {
				$this->assign('permError', 't');
			}
		}
	}
}
?>