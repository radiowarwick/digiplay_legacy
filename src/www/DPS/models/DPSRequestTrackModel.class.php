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
class DPSRequestTrackModel extends Model {
	
	const module = 'DPS';
		
	protected function processValid(){
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$rqValues['name'] = $this->fieldData['title'];
		$rqValues['artistname'] = $this->fieldData['artist'];
	
		$auth = Auth::getInstance();
		$rqValues['userid'] = $auth->getUserID();
		$rqValues['date'] = time();
		$db->insert('requests',$rqValues,true);
	}

	protected function processInvalid(){
		//No invalid processing required
	}
}
?>
