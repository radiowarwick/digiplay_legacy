<?php
/**
 * @package FrontEnds
 * @subpackage Auth
 */
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeViewer('Viewer', 'tkfecommon');

class ConfigurationViewer extends Viewer {
	
	protected function setupTemplate(){
		
		parent::setupTemplate();
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$sql = "SELECT * FROM configuration ORDER BY location, parameter ASC";
		$configs = $db->getAll($sql);
		
		$sql = "SELECT DISTINCT location FROM configuration ORDER BY location ASC";
		$locs = $db->getAll($sql);
		
		$this->assign('configs', $configs);
		$this->assign('locs', $locs);
		
	}
}
?>