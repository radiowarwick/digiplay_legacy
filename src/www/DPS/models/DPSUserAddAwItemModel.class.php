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
class DPSUserAddAwItemModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$audio = $this->fieldData['audioID'];
		$style = $this->fieldData['style'];
		$AwWall = $this->fieldData['awwallID'];
		$AwItemPos = $this->fieldData['awitemPos'];
		
		$text="";
		$subStr = explode("\n",$_POST["text"]);
		foreach($subStr as $value){
			$text = $text . pg_escape_string($value) . "\n";
		}
		$text = rtrim($text,"\n");
		if($text != '' && $audio != '' && is_numeric($audio)) {
			$sql = "SELECT COUNT(*) FROM aw_items, aw_walls 
				WHERE aw_walls.id = aw_items.wall_id
				AND aw_walls.id = " . pg_escape_string($AwWall) . " 
				AND aw_items.item = " . pg_escape_string($AwItemPos);
			$count = $db->getOne($sql);
			if($count == 0) {
				$AwItem = array();
				$AwItem['text'] = $text;
				$AwItem['audio_id'] = $audio;
				$AwItem['style_id'] = $style;
				$AwItem['wall_id'] = $AwWall;
				$AwItem['item'] = $AwItemPos;
				$db->insert('aw_items', $AwItem, true);
			} else {
				//do error stuff
			}
		}
	}
		
	protected function processInvalid() {
		//No invalid processing required
		if($this->errors['text']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditawitem.tpl'),
				array("AwItemID" => "New",
					"AwWallID" => $this->fieldData['AwWallID'],
					"AwItemPos" => $this->fieldData['AwItemPos'],
					"error" => "text"));
		} elseif($this->errors['style']) {
			MVCUtils::redirect(
				MVCUtils::getTemplateID('dpssteditawitem.tpl'),
					array("AwItemID" => "New",
						"AwWallID" => $this->fieldData['AwWallID'],
						"AwItemPos" => $this->fieldData['AwItemPos'],
						"error" => "style"));
		} elseif($this->errors['audioID']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditawitem.tpl'),
				array("AwItemID" => "New",
					"AwWallID" => $this->fieldData['AwWallID'],
					"AwItemPos" => $this->fieldData['AwItemPos'],
					"error" => "audioID"));
		}
	}
}
?>
