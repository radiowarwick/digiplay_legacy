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
			$script_query = "SELECT count(*) FROM scriptusers where 
										scriptusers.userid = " . $userID . " AND
										scriptusers.scriptid = " . $scriptID . " AND 
										(scriptusers.permissions = 'o' OR scriptusers.permissions = 'rw')";
    	$checkScripts = $db->getOne($script_query);
			if($checkScripts > 0) {
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
