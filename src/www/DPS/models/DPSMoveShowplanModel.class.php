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
class DPSMoveShowplanModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$showplan = $this->fieldData['showplanID'];
		if(is_numeric($showplan) && is_numeric($this->fieldData['newParent'])) {
			$sql_insert['dirid'] = $this->fieldData['newParent'];
			$sql_insert['showplanid'] = $showplan;
			$sql_insert['linktype'] = 0;
			$swhere = "showplanid = " . pg_escape_string($showplan);
			$db->delete('showplandir',$swhere,true);
			$db->insert('showplandir',$sql_insert,true);
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
		MVCUtils::redirect(
			MVCUtils::getTemplateID('dpsusershowmove.tpl'),
			array("showplanID" => $this->fieldData['showplanID'], "error" => "perm"));
	}
}
?>
