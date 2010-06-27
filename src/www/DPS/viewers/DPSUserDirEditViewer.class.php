<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserDirEditViewer extends Viewer {

	const module = 'DPS';
	protected $activeNode = 'foldersTree';

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
			$flag = false;
			$sql = "SELECT count(*) FROM v_tree_dir
				WHERE id = $dirID
					AND	userid = $userID
					AND permissions & B'" . $cfg['DPS']['fileW'] . "' = '" . $cfg['DPS']['fileW'] . "'";
			if($db->getOne($sql) > 0) {
				$flag = true;
			}
			if($flag) {
				$sql = "SELECT * FROM dir WHERE id = $dirID";
				$folder = $db->getRow($sql);
				
				$sql = "SELECT count(*) FROM v_tree_dir
					WHERE id = $dirID
						AND	userid = $userID
						AND permissions & B'" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
				if($db->getOne($sql) > 0) {
					$this->assign('dirown', 't');
				}
				
				$sql = "SELECT bit_or(permissions) FROM (SELECT bit_or(permissions) AS permissions 
					FROM v_tree_dir_explicit 
					WHERE causetype = 'group'
						AND cause = " . $cfg['Auth']['defaultNewUserGroup'] . "
						AND permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "') AS Q1 
				UNION (SELECT bit_or(permissions) AS permissions 
					FROM v_tree_dir_inherited 
					WHERE causetype = 'group'
						AND cause = " . $cfg['Auth']['defaultNewUserGroup'] . "
						AND permissions & B'" . $cfg['DPS']['fileR'] . "' = '" . $cfg['DPS']['fileR'] . "')";
				$perm = $db->getOne($sql);;
				if($perm[0] == "1") {
					$this->assign('dirpub', 't');
				}
				
				
				$sql = "SELECT bit_or(permissions) FROM dirgroups
					WHERE dirid = $dirID
						AND groupid = " . $cfg['Auth']['defaultNewUserGroup'];
					$perm = $db->getOne($sql);
				if($perm[1] == "1") {
					$this->assign('dirrw', 't');
				} elseif($perm[0] == "1") {
					$this->assign('dirr', 't');
				} else {
					$this->assign('priv', 't');
				}
				
				$this->assign('folder', $folder);
			} else {
				$this->assign('permError', 't');
			}
		}
	}
}
