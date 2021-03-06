<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['Auth']['dir']['root'] . '/AuthUtil.class.php');
class DPSUserEditScriptViewer extends Viewer {
	
	const module = 'DPS';
	
	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		
		$db = Database::getInstance($cfg['DPS']['dsn']);
	
		$scriptID = pg_escape_string($this->fieldData['scriptID']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$date = time();
		if(is_numeric($scriptID)) {
			$script_query = "SELECT bit_or(permissions) 
				FROM v_tree_script
				WHERE id = $scriptID
					AND userid = $userID";
			$checkScripts = $db->getOne($script_query);
			if(substr($checkScripts,0,1) == "1") {
				if(substr($checkScripts,1,1) == "1") {
					$this->assign('write', 't');
				} else {
					$this->assign('write', 'f');
				}
				$script_sql = "SELECT * FROM scripts WHERE id = " . $scriptID;
				$script = $db->getRow($script_sql);
				$script['m'] = (int)($script['length']/60);
				$script['s'] = ($script['length']-$script['m']*60);
				$script['niceProducer'] = AuthUtil::getUsername($script['creator']);
				$this->assign('script', $script);
			} else {
				$this->assign('error', 'You do not have permission to edit that script.');
			}
		} else {
			$this->assign('error', 'Invalid Show ID supplied');
		}
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
	}
}
?>
