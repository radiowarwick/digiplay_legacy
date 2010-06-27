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
				if($this->fieldData['name'] != ''){
					$pkgUpdates['name'] = $this->fieldData['name'];
				}
				if($this->fieldData['description'] != ''){
					$pkgUpdates['description'] = $this->fieldData['description'];
				}

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
				
				$sql = "SELECT COUNT(*) from audiojinglepkgs WHERE jinglepkgid = $jinglepkgID";
				$remainingjingles = $db->getOne($sql);
				if ($remainingjingles == 0) {
					$Where = "id = ". $jinglepkgID;
					$db->delete('jinglepkgs',$Where,true);
				}	

				$sql = "SELECT COUNT(*) from audiojinglepkgs WHERE audioid = $jingleID";
				$remainingpkgs = $db->getOne($sql);
				if ($remainingpkgs == 0) {
					$sql = "SELECT id FROM jinglepkgs WHERE name = ''";
					$defaultid = $db->getOne($sql);
					$newpkg['audioid'] = $jingleID;
					$newpkg['jinglepkgid'] = $defaultid;
					$newpkg['jingletypeid'] = 1;
					$db->insert('audiojinglepkgs',$newpkg,true);
				}
			}
		}
		
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
