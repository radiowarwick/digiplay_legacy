<?php
/**
 * @package FrontEnds
 * @subpackage Auth
 */
//include_once($cfg['dir']['tkfrontends.auth'] . '/config.php');
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for config management
 */
class ConfigsModel extends Model {
	
	const module = 'AuthFrontEnd';
	
	protected function processValid(){
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$sql = "SELECT * FROM configuration ORDER BY location, parameter ASC";
		$configs = $db->getAll($sql);
		
		foreach($configs as $config) {
			$configU['val'] = $this->fieldData['val' . $config['id']];
			$configU['location'] = $this->fieldData['loc' . $config['id']];
			$where = "id = " . $config['id'];
			if($configU['val'] != '' && $configU['location'] != '' && $config['id'] != '') {
				$db->update('configuration',$configU,$where);
			}
		}
	}

	protected function processInvalid(){
		//No invalid processing required
	}
}
?>
