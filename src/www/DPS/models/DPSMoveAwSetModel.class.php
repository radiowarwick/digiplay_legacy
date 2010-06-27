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
class DPSMoveAwSetModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
			$AwSet = $this->fieldData['AwSetID'];
		if(is_numeric($AwSet) && is_numeric($this->fieldData['newParent'])) {
			$sql_insert['dirid'] = $this->fieldData['newParent'];
			$sql_insert['AwSetid'] = $AwSet;
			$sql_insert['linktype'] = 0;
			$swhere = "set_id = " . pg_escape_string($AwSet);
			$db->delete('aw_sets_dir',$swhere,true);
			$db->insert('aw_sets_dir',$sql_insert,true);
		}
		
	}	
	protected function processInvalid() {
		//No invalid processing required
		MVCUtils::redirect(
			MVCUtils::getTemplateID('dpsuserawsetmove.tpl'),
			array("AwSetID" => $this->fieldData['AwSetID'], "error" => "perm"));
	}
}
?>
