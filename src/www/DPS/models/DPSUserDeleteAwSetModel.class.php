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
class DPSUserDeleteAwSetModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
	
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$awsetID = pg_escape_string($this->fieldData['awset']);
		if($awsetID != '' && is_numeric($awsetID)) {
			$where = "id = " . $awsetID;
			$db->delete('aw_sets',$where,true);
            print $where;
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
