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
class DPSCensorTrackModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if(is_numeric($this->fieldData['resultCount'])) {
			for($i=0; $i < $this->fieldData['resultCount']; $i++) {
				$cb = 'checkbox_' . $i;
				$id = 'trackID_' . $i;
				if($this->fieldData[$cb] == "on"
					&& is_numeric(pg_escape_string($this->fieldData[$id]))
					&& pg_escape_string($this->fieldData[$id] != "")) {
					$trUpdate['censor'] = 'f';
					$trUpdate['flagged'] = 'f';
					$trWhere = "id = " . pg_escape_string($this->fieldData[$id]);
					$db->update('audio',$trUpdate,$trWhere, true);
				}
			}
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
