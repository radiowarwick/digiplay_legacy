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
class DPSStationDeleteAwItemModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$AwItemID = pg_escape_string($this->fieldData['AwItemID']);
		
		if($AwItemID != '' && is_numeric($AwItemID)) {
			$atWhere = "id = " . $AwItemID;
			$db->delete('aw_items', $atWhere, true);
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
		if($this->errors['text']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditawitem.tpl'),
				array("AwItemID" => $this->fieldData['AwItemID'], "error" => "text"));
		} elseif($this->errors['style']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditawitem.tpl'),
				array("AwItemID" => $this->fieldData['AwItemID'], "error" => "style"));
		} elseif($this->errors['audioID']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditawitem.tpl'),
				array("AwItemID" => $this->fieldData['AwItemID'], "error" => "audioID"));
		}
	}
}
?>
