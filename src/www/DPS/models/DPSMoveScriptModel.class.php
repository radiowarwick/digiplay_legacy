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
class DPSMoveScriptModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$script = $this->fieldData['scriptID'];
		if(is_numeric($script) && is_numeric($this->fieldData['newParent'])) {
			$sql_insert['dirid'] = $this->fieldData['newParent'];
			$sql_insert['scriptid'] = $script;
			$sql_insert['linktype'] = 0;
			$swhere = "scriptid = " . pg_escape_string($script);
			$db->delete('scriptsdir',$swhere,true);
			$db->insert('scriptsdir',$sql_insert,true);
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
		MVCUtils::redirect(
			MVCUtils::getTemplateID('dpsuserscriptmove.tpl'),
			array("scriptID" => $this->fieldData['scriptID'], "error" => "perm"));
	}
}
?>
