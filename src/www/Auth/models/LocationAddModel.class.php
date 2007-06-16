<?php
/**
 * @package FrontEnds
 * @subpackage Auth
 */
//include_once($cfg['dir']['tkfrontends.auth'] . '/config.php');
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for location management
 */
class LocationAddModel extends Model {
	
	const module = 'AuthFrontEnd';
	
	protected function processValid(){
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$sql = "SELECT DISTINCT location FROM configuration 
			ORDER BY location DESC LIMIT 1";
		$locID = $db->getOne($sql);
		$locID++;
		$configI['location'] = $locID;
		$configI['parameter'] = 'player1_md5';
		$configI['val'] = '';
		$db->insert('configuration',$configI,true);
		$configI['parameter'] = 'player2_md5';
		$configI['val'] = '';
		$db->insert('configuration',$configI,true);
		$configI['parameter'] = 'player3_md5';
		$configI['val'] = '';
		$db->insert('configuration',$configI,true);
		$configI['parameter'] = 'user_cartset';
		$configI['val'] = '';
		$db->insert('configuration',$configI,true);
		$configI['parameter'] = 'next_on_showplan';
		$configI['val'] = '';
		$db->insert('configuration',$configI,true);
		$configI['parameter'] = 'userid';
		$configI['val'] = '';
		$db->insert('configuration',$configI,true);
		$configI['parameter'] = 'channel_1';
		$configI['val'] = $this->fieldData['channel_1'];
		$db->insert('configuration',$configI,true);
		$configI['parameter'] = 'channel_2';
		$configI['val'] = $this->fieldData['channel_2'];
		$db->insert('configuration',$configI,true);
		$configI['parameter'] = 'channel_3';
		$configI['val'] = $this->fieldData['channel_3'];
		$db->insert('configuration',$configI,true);
		$configI['parameter'] = 'channel_4';
		$configI['val'] = $this->fieldData['channel_4'];
		$db->insert('configuration',$configI,true);
		$configI['parameter'] = 'station_cartset';
		$configI['val'] = '';
		$db->insert('configuration',$configI,true);
	}

	protected function processInvalid(){
		//No invalid processing required
	}
}
?>
