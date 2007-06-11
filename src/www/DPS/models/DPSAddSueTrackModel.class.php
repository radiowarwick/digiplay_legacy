<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for adding a track to the sustainer
 */
class DPSAddSueTrackModel extends Model {
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		for($i=0; $i < $cfg['DPS']['resultLimit']; $i++) {
			$cb = 'checkbox_' . $i;
			$id = 'trackID_' . $i;
			$val = 'trackVal_' . $i;
			if($this->fieldData[$cb] != "on" 
				&& is_numeric(pg_escape_string($this->fieldData[$id]))
				&& pg_escape_string($this->fieldData[$id] != "")
				&& $this->fieldData[$val] != "off") {
				$trUpdate['sustainer'] = 'f';
				$trWhere = "id = " . pg_escape_string($this->fieldData[$id]);
				$db->update('audio',$trUpdate,$trWhere, true);
			} elseif($this->fieldData[$cb] == "on"
				&& is_numeric(pg_escape_string($this->fieldData[$id]))
				&& pg_escape_string($this->fieldData[$id] != ""
				&& $this->fieldData[$val] != "on")) {
				$trUpdate['sustainer'] = 't';
				$trWhere = "id = " . pg_escape_string($this->fieldData[$id]);
				$db->update('audio',$trUpdate,$trWhere, true);
			}
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
