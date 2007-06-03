<?php
/**
 * @package FrontEnds
 * @subpackage MVC
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
			$script_query = "SELECT bit_or(permissions) FROM (SELECT scriptsusers.permissions FROM scriptsusers where 
										scriptsusers.userid = " . $userID . " AND
										scriptsusers.scriptid = " . $scriptID . "  
										UNION( SELECT scriptsgroups.permissions FROM scriptsgroups, usersgroups where 
										usersgroups.userid = " . $userID . " AND 
										scriptsgroups.groupid = usersgroups.groupid AND 
										scriptsgroups.scriptid = " . $scriptID . ")) AS Q1"; 
    	$checkScripts = $db->getOne($script_query);
			if(substr($checkScripts,0,1) == "1") {
				if(substr($checkScripts,1,1) == "1") {
					$this->assign('write', 't');
				} else {
					$this->assign('write', 'f');
				}
				$script_sql = "SELECT * FROM scripts where id = " . $scriptID;
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
