<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserCartsetMoveViewer extends Viewer {

	const module = 'DPS';
	protected $activeNode = 'foldersTree';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$cartsetID = pg_escape_string($this->fieldData['cartsetID']);
		$flag = false;
		if(!is_numeric($cartsetID)) {
			$this->assign('permError', 't');
		} else {
			$sql = "SELECT count(*) FROM v_tree_cartset
				WHERE id = $cartsetID
					AND	userid = $userID
					AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '"
						. $cfg['DPS']['fileW'] . "'";
			if($db->getOne($sql) > 0) {
				$sql = "SELECT dirid FROM cartsetsdir
					WHERE cartsetid = $cartsetID";
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
			$sql = "SELECT * FROM cartsets 
				WHERE id = " . pg_escape_string($cartsetID);
			$cartset = $db->getRow($sql);
			
			$sql = "SELECT count(*) FROM v_tree_cartset
				WHERE id = $cartsetID
					AND	userid = $userID
					AND permissions & B'" . $cfg['DPS']['fileO'] . "' = '".
						$cfg['DPS']['fileO'] . "'";
			$check = $db->getOne($sql);
			if($check > 0) {
				$this->assign('own', 't');
			}
			
			$this->assign('cartset', $cartset);
			$this->assign('treeType', '');
		} else {
			$this->assign('permError', 't');
		}
	}
}
?>
