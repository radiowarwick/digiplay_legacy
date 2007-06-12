<?php
/**
* @package FrontEnds
* @subpackage MVC
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserScriptMoveViewer extends Viewer {

	const module = 'DPS';
	protected $activeNode = 'foldersTree';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$scriptID = pg_escape_string($this->fieldData['scriptID']);
		if(!is_numeric($scriptID)) {
			$this->assign('permError', 't');
		} else {
			$sql = "SELECT count(*) FROM v_tree_script
				WHERE id = $scriptID
					AND	userid = $userID
					AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
			if($db->getOne($sql) > 0) {
				$sql = "SELECT dirid FROM scriptsdir
					WHERE scriptid = $scriptID";
				$dirID = $db->getOne($sql);
				"SELECT count(*) FROM v_tree_dir
					WHERE id = $dirID
						AND	userid = $userID
						AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
				if($db->getOne($sql) > 0) {
					$flag = true;
				}
			}
		}
		
		if($flag) {
			$sql = "SELECT * FROM scripts WHERE id = $scriptID";
			$script = $db->getRow($sql);

		$sql = "SELECT count(*) FROM v_tree_script
			WHERE id = $scriptID
				AND	userid = $userID
				AND permissions & B'" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
		$check = $db->getOne($sql);
		if($check > 0) {
			$this->assign('own', 't');
		}

			$this->assign('script', $script);
			$this->assign('treeType', '');
		} else {
			$this->assign('permError', 't');
		}
	}
}
?>
