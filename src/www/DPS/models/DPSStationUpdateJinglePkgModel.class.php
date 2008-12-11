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
class DPSStationUpdateJinglePkgModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();

		if ($this->formName == "dpsStationUpdateJinglePkgForm") {

			$jinglepkgID = pg_escape_string($this->fieldData['jinglepkgID']);
			if(is_numeric($jinglepkgID) && $jinglepkgID != "" && $jinglepkgID != "*") {
				$pkgUpdates['name'] = $this->fieldData['name'];
				$pkgUpdates['description'] = $this->fieldData['description'];


				if(AuthUtil::getDetailedUserrealmAccess(array(24,20,3), $userID)) {
					if($this->fieldData['enabled'] == "on") {
						$pkgUpdates['enabled'] = 't';
					} else {
						$pkgUpdates['enabled'] = 'f';
					}
				}
			
				$atWhere = "jinglepkgs.id = " . $jinglepkgID;
				$db->update('jinglepkgs', $pkgUpdates, $atWhere, true);
				
			}

		} elseif ($this->formName == "dpsStationRemJingleFromPkgForm") {

			$jingleID = pg_escape_string($this->fieldData['jingleID']);
			$jinglepkgID = pg_escape_string($this->fieldData['jinglepkgID']);
			
			if(AuthUtil::getDetailedUserrealmAccess(array(35,22,3), $userID)) {
				$sql = "SELECT id FROM audiojinglepkgs WHERE audioid = $jingleID AND jinglepkgid = $jinglepkgID";
				$rowID = $db->getOne($sql);
				if ($rowID != 0) {
					$Where = "id = $rowID";
					$db->delete('audiojinglepkgs',$Where,true);
				}
			}
		}
		
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
