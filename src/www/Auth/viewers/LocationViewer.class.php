<?php
/**
 * @package FrontEnds
 * @subpackage Auth
 */
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeViewer('Viewer', 'tkfecommon');

class LocationViewer extends Viewer {
	
	protected function setupTemplate(){
		
		parent::setupTemplate();
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$sql = "SELECT DISTINCT location as locid, location as locname 
			FROM configuration 
			WHERE location != -1 AND 
				location != 0
			ORDER BY location ASC";
		$locs = $db->getAll($sql);
		$this->assign('locs', $locs);
	}
}
?>