<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['Auth']['dir']['root'] . '/AuthUtil.class.php');
class DPSShowUserScriptViewer extends Viewer {
	
  const module = 'DPS';
	
  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();
    
    $db = Database::getInstance($cfg['DPS']['dsn']);
   
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
    $date = time();
		$script_query = "SELECT scripts.* FROM scripts, scriptusers where 
										scripts.id = scriptusers.scriptid AND 
										scriptusers.userid = " . $userID . " AND 
										(scriptusers.permissions = 'o' OR scriptusers.permissions = 'rw')
										ORDER BY scripts.name asc";
    $scripts = $db->getAll($script_query);
		$scriptCount = count($scripts);
    
    foreach($scripts as &$script) { 
      $script['niceCreateDate'] = date("d/m/y",$script['creationdate']);
      $script['niceCreateTime'] = date("g a",$script['creationdate']);
			$script['text'] = $script['name'] . " - " . $script['niceCreateDate'] . " - " . $script['niceCreateTime'];
    }
    
    $this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
    $this->assign('scripts', $scripts);
    $this->assign('scriptCount', $scriptCount);
  }
}

?>
