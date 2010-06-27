<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserShowMoveViewer extends Viewer {

	const module = 'DPS';
	protected $activeNode = 'foldersTree';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$showID = pg_escape_string($this->fieldData['showplanID']);
		if(!is_numeric($showID)) {
			$this->assign('permError', 't');
		} else {
			$sql = "SELECT count(*) FROM v_tree_showplan
				WHERE id = $showID
					AND	userid = $userID
					AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '" .
						$cfg['DPS']['fileW'] . "'";
			if($db->getOne($sql) > 0) {
				$sql = "SELECT dirid FROM showplandir
					WHERE showplanid = $showID";
				$dirID = $db->getOne($sql);
				"SELECT count(*) FROM v_tree_dir
					WHERE id = $dirID
						AND	userid = $userID
						AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '" .
							$cfg['DPS']['fileW'] . "'";
				if($db->getOne($sql) > 0) {
					$flag = true;
				}
			}
			
			if($flag) {
				$sql = "SELECT * FROM showplans WHERE id = $showID";
				$showplan = $db->getRow($sql);
				$sql = "SELECT count(*) FROM v_tree_showplan
					WHERE id = $showID
						AND	userid = $userID
						AND permissions & B'" . $cfg['DPS']['fileO'] . "' = '" .
							$cfg['DPS']['fileO'] . "'";
				$check = $db->getOne($sql);
				if($check > 0) {
					$this->assign('own', 't');
				}
				$this->assign('showplan', $showplan);
				$this->assign('treeType', '');
			} else {
				$this->assign('permError', 't');
			}
		}
	}
}
?>
