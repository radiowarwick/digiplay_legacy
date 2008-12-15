<?php
/**
 * @package DPS
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');


class DPSStationMoveJingleModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();

		if ($this->formName == "dpsStationMoveJingleForm") {

			$jingleID = pg_escape_string($this->fieldData['jingleID']);
			$jinglepkgID = pg_escape_string($this->fieldData['jinglepkgID']);
			
			if(AuthUtil::getDetailedUserrealmAccess(array(35,22,3), $userID)) {
				$sql = "SELECT jinglepkgid FROM audiojinglepkgs WHERE audioid = $jingleID";
				$oldjinglepkgID = $db->getOne($sql);
				
				if (($jinglepkgID == $oldjinglepkgID) && ($this->fieldData['newPackageName'] == '')) {
					return;
				}
	
				$sql = "SELECT id FROM audiojinglepkgs WHERE audioid = $jingleID AND jinglepkgid = $oldjinglepkgID";
				$rowID = $db->getOne($sql);
				if ($rowID != 0) {
					$Where = "id = $rowID";
					$db->delete('audiojinglepkgs',$Where,true);
				}
				
				$sql = "SELECT COUNT(*) from audiojinglepkgs WHERE jinglepkgid = $oldjinglepkgID";
				$remainingjingles = $db->getOne($sql);
				if ($remainingjingles == 0) {
					$Where = "id = ". $oldjinglepkgID;
					$db->delete('jinglepkgs',$Where,true);
				}	

				if($this->fieldData['newPackageName'] != '') {
					$jinglePkgName = pg_escape_string($this->fieldData['newPackageName']);
					$sql = "SELECT id FROM jinglepkgs WHERE name = '$jinglePkgName'";
					$numRows = count($db->getAll($sql));
					if($numRows != 0) {
						$jinglepkgID = $db->getOne($sql);
					} else {
						$newjinglepkg['name'] = $jinglePkgName;
						$newjinglepkg['description'] = pg_escape_string($this->fieldData['newPackageDesc']);
						$newjinglepkg['enabled'] = 'f';
						$db->insert('jinglepkgs',$newjinglepkg,true);

						$sql = "SELECT id FROM jinglepkgs WHERE name = '$jinglePkgName'";
						$jinglepkgID = $db->getOne($sql);
					}
				}
 
				$newpkg['audioid'] = $jingleID;
				$newpkg['jinglepkgid'] = $jinglepkgID;
				$newpkg['jingletypeid'] = 1;
				$db->insert('audiojinglepkgs',$newpkg,true);
			}
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
