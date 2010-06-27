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
class DPSUserUpdateAwItemModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid(){
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$awitemID = pg_escape_string($this->fieldData['awitemID']);
		
		if($awitemID != '') {
			$audio = $this->fieldData['audioID'];
			$style = $this->fieldData['style'];
			$text="";
			$subStr = explode("\n",$_POST["text"]);
			foreach($subStr as $value){
				$text = $text . pg_escape_string($value) . "\n";
			}
			$text = rtrim($text,"\n");
			if($text != '' && $awitemID != '' && is_numeric($awitemID)) {
				$awitem = array();
				$awitem['text'] = $text;
				$awitem['audio_id'] = $audio;
				$awitem['style_id'] = $style;
				$atWhere = "id = " . $awitemID;
				$db->update('aw_items', $awitem, $atWhere, true);
			}
		}
	}
		
	protected function processInvalid(){
		//No invalid processing required
		if($this->errors['text']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditawitem.tpl'),
				array("awitemID" => $this->fieldData['awitemID'], "error" => "text"));
		} elseif($this->errors['style']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditawitem.tpl'),
				array("awitemID" => $this->fieldData['awitemID'], "error" => "style"));
		} elseif($this->errors['audioID']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditawitem.tpl'),
				array("awitemID" => $this->fieldData['awitemID'], "error" => "audioID"));
		}
	}
}
?>
