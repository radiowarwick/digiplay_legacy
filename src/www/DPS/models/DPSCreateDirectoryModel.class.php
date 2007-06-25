<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSCreateDirectoryModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$dir = $this->fieldData['rootdir'];
		if(is_numeric($dir)) {
			$sql_insert['parent'] = $dir;
			$sql_insert['name'] = $this->fieldData['dirtext'];
			$sql_insert['id'] = "#id#";
			$id = $db->insert('dir',$sql_insert,true);
			$sql_perm['dirid'] = $id;
			$sql_perm['permissions'] = 'B' . $cfg['DPS']['fileRWO'] . 'B';
			$auth = Auth::getInstance();
			$sql_perm['userid'] = $auth->getUserID();
			$db->insert('dirusers',$sql_perm,false);
			$sql_gperm['dirid'] = $id;
			$sql_gperm['permissions'] = 'B' . $cfg['DPS']['fileRWO'] . 'B';
			$sql_gperm['groupid'] = $cfg['Auth']['AdminGroup'];
			$db->insert('dirgroups',$sql_gperm,false);
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
