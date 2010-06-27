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
class DPSStationUpdateAwItemModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$AwItemID = pg_escape_string($this->fieldData['awitemID']);
		
		if($AwItemID != '') {
			$audio = $this->fieldData['audioID'];
			$style = $this->fieldData['style'];
			$text="";
			$subStr = explode("\n",$_POST["text"]);
			foreach($subStr as $value){
				$text = $text . pg_escape_string($value) . "\n";
			}
			$text = rtrim($text,"\n");
			if($text != '' && $AwItemID != '' && is_numeric($AwItemID)) {
				$AwItem = array();
				$AwItem['text'] = $text;
				$AwItem['audio_id'] = $audio;
				$AwItem['style_id'] = $style;
				$atWhere = "id = " . $AwItemID;
				$db->update('aw_items', $AwItem, $atWhere, true);
			}
		}
	}
		
	protected function processInvalid() {
		//No invalid processing required
		if($this->errors['text']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditawitem.tpl'),
				array("AwItemID" => $this->fieldData['awitemID'], "error" => "text"));
		} elseif($this->errors['style']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditawitem.tpl'),
				array("AwItemID" => $this->fieldData['awitemID'], "error" => "style"));
		} elseif($this->errors['audioID']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditawitem.tpl'),
				array("AwItemID" => $this->fieldData['awitemID'], "error" => "audioID"));
		}
	}	
}
?>
