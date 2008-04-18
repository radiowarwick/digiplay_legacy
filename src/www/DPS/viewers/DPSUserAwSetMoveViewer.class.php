<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserAwSetMoveViewer extends Viewer {

	const module = 'DPS';
	protected $activeNode = 'foldersTree';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$awsetID = pg_escape_string($this->fieldData['awsetID']);
		$flag = false;
		if(!is_numeric($awsetID)) {
			$this->assign('permError', 't');
		} else {
			$sql = "SELECT count(*) FROM v_tree_aw_set
				WHERE id = $awsetID
					AND	userid = $userID
					AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '"
						. $cfg['DPS']['fileW'] . "'";
			if($db->getOne($sql) > 0) {
				$sql = "SELECT dirid FROM aw_setsdir
					WHERE set_id = $awsetID";
				$dirID = $db->getOne($sql);
				"SELECT count(*) FROM v_tree_dir
					WHERE id = $dirID
						AND	userid = $userID
						AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '"
							. $cfg['DPS']['fileW'] . "'";
				if($db->getOne($sql) > 0) {
					$flag = true;
				}
			}
		}
		
		if($flag) {
			$sql = "SELECT * FROM aw_sets 
				WHERE id = " . pg_escape_string($awsetID);
			$awset = $db->getRow($sql);
			
			$sql = "SELECT count(*) FROM v_tree_aw_set
				WHERE id = $awsetID
					AND	userid = $userID
					AND permissions & B'" . $cfg['DPS']['fileO'] . "' = '".
						$cfg['DPS']['fileO'] . "'";
			$check = $db->getOne($sql);
			if($check > 0) {
				$this->assign('own', 't');
			}
			
			$this->assign('awset', $awset);
			$this->assign('treeType', '');
		} else {
			$this->assign('permError', 't');
		}
	}
}
?>
