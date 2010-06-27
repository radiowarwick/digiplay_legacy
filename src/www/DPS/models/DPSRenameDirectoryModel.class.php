<?php
/**
 * @package DPS
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSRenameDirectoryModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$dir = pg_escape_string($this->fieldData['rootdir']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		
		if(is_numeric($dir)) {
			$sql_update['name'] = $this->fieldData['dirtext'];
			$swhere = "id = " . pg_escape_string($dir);
			$db->update('dir',$sql_update,$swhere,true);
		
			$sql = "SELECT count(*) FROM v_tree_dir
				WHERE id = $dir
					AND	userid = $userID
					AND permissions & B'" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
			if($db->getOne($sql) > 0) {
				$where = "dirid = $dir AND groupid = " . $cfg['DPS']['allusersgroupid'];
				$db->delete('dirgroups',$where,$true);
				if($this->fieldData['dirperm'] == 'pubrw') {
					$dirI['dirid'] = $dir;
					$dirI['groupid'] = $cfg['DPS']['allusersgroupid'];
					$dirI['permissions'] = $cfg['DPS']['fileRW'];
					$db->insert('dirgroups', $dirI, false);
				} elseif($this->fieldData['dirperm'] == 'pubr') {
					$dirI['dirid'] = $dir;
					$dirI['groupid'] = $cfg['DPS']['allusersgroupid'];
					$dirI['permissions'] = $cfg['DPS']['fileR'];
					$db->insert('dirgroups', $dirI, false);
				} else {
					$dirI['dirid'] = $dir;
					$dirI['groupid'] = $cfg['DPS']['allusersgroupid'];
					$dirI['permissions'] = $cfg['DPS']['file'];
					$db->insert('dirgroups', $dirI, false);
				}
			}
		}
		
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
