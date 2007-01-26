<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSStudioFrontViewer extends Viewer {

  const module = 'DPS';

  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();

    $db = Database::getInstance($cfg['DPS']['dsn']);
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
		$this->assign('access_playlist',AuthUtil::getDetailedUserrealmAccess(array(58,69,4), $userID));
    $this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
    $this->assign('studioAccess',AuthUtil::getDetailedUserrealmAccess(array(58,69,70), $userID));
   }
}

?>
		    
