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
		$audioID = $this->fieldData['audioID'];
		if(!is_numeric($audioID)) {
			$this->assign('permError', 't');
		} else {
			//As there is no general audio view
			$sql = "SELECT count(*) FROM audiousers 
				WHERE audio = " . pg_escape_string($trackID) . " 
					AND userid = " . $userID . " 
					AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '"
						$cfg['DPS']['fileW'] . "'";
			$check = $db->getOne($sql);
			$sql = "SELECT count(*) FROM audiogroups, usersgroups 
				WHERE audiogroups.audio = " . pg_escape_string($trackID) . " 
					AND usersgroups.userid = " . $userID . " 
					AND usersgroups.groupid = audiogroups.groupid 
					AND audiogroups.permissions & B'" . $cfg['DPS']['fileW'] .
						"' = '" . $cfg['DPS']['fileW'] . "'";
			$check = $check + $db->getOne($sql);
			if($check > 0)
				$flag = true;
			}
			if($flag) {
				$sql = "SELECT * FROM audio 
					WHERE id = " . pg_escape_string($audioID);
				$audio = $db->getRow($sql);

					//As there is no general audio view
					$sql = "SELECT count(*) FROM audiousers 
						WHERE audio = " . pg_escape_string($trackID) . " 
							AND userid = " . $userID . " 
							AND permissions & B'" . $cfg['DPS']['fileO'] . "' = '"
								$cfg['DPS']['fileO'] . "'";
					$check = $db->getOne($sql);
					$sql = "SELECT count(*) FROM audiogroups, usersgroups 
						WHERE audiogroups.audio = " . pg_escape_string($trackID) . " 
							AND usersgroups.userid = " . $userID . " 
							AND usersgroups.groupid = audiogroups.groupid 
							AND audiogroups.permissions & B'" . $cfg['DPS']['fileO'] .
								"' = '" . $cfg['DPS']['fileO'] . "'";
					$check = $check + $db->getOne($sql);
					if($check > 0) {
						$this->assign('own', 't');
					}
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