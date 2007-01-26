<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSHelpViewer extends Viewer {

  const module = 'DPS';

  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();

    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
    $this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		if($userID == $cfg['Auth']['anonuserID']) {
			$this->assign('Guest','t');
		} else {
			$this->assign('Guest','f');
		}
   }
}

?>
		    
