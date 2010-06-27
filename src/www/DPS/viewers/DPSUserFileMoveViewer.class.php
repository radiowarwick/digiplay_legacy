<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserFileMoveViewer extends Viewer {

	const module = 'DPS';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$dirID = pg_escape_string($this->fieldData['rootdir']);
		if(!is_numeric($dirID)) {
			$this->assign('permError', 't');
		} else {
			$sql = "SELECT count(*) FROM v_tree_dir
				WHERE id = $dirID
					AND	userid = $userID
					AND permissions & B'" . $cfg['DPS']['fileW'] .
						"' = '" . $cfg['DPS']['fileW'] . "'";
			if($db->getOne($sql) > 0) {
				$sql = "SELECT parent FROM dir
					WHERE id = $dirID";
				$parentdirID = $db->getOne($sql);
				"SELECT count(*) FROM v_tree_dir
					WHERE id = $parentdirID
						AND	userid = $userID
						AND permissions & B'" . $cfg['DPS']['fileW'] .
							"' = '" . $cfg['DPS']['fileW'] . "'";
				if($db->getOne($sql) > 0) {
					$flag = true;
				}
			}
			if($flag) {
				$sql = "SELECT * FROM dir 
					WHERE id = $dirID";
				$folder = $db->getRow($sql);
				$this->assign('folder', $folder);
				$this->assign('treeType', '');
			} else {
				$this->assign('permError', 't');
			}
		}
	}
}
?>