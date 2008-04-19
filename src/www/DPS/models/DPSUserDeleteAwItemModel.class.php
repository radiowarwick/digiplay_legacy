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
class DPSUserDeleteAwItemModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$awitemID = pg_escape_string($this->fieldData['awitemID']);
		if($awitemID != '' && is_numeric($awitemID)) {
			$atWhere = "id = " . $awitemID;
			$db->delete('awitems', $atWhere, true);
		}
	}
		
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
