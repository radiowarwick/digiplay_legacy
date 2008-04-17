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
class DPSStationDeleteCartModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$cartID = pg_escape_string($this->fieldData['cartID']);
		
		if($cartID != '' && is_numeric($cartID)) {
			$atWhere = "id = " . $cartID;
			$db->delete('cartsaudio', $atWhere, true);
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
		if($this->errors['text']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditcart.tpl'),
				array("cartID" => $this->fieldData['cartID'], "error" => "text"));
		} elseif($this->errors['style']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditcart.tpl'),
				array("cartID" => $this->fieldData['cartID'], "error" => "style"));
		} elseif($this->errors['audioID']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditcart.tpl'),
				array("cartID" => $this->fieldData['cartID'], "error" => "audioID"));
		}
	}
}
?>
