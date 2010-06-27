<?php
/**
 * @package FrontEnds
 * @subpackage Auth
 */
include_once($cfg['Logger']['dir']['root'] . '/BasicLogger.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

class LoginModel extends Model {
	
	protected function processValid(){
		global $cfg;
		
		$auth = Auth::getInstance();
		//If the fwtid (forward template id) variable is set, then set the 
		//templateID to that requested as long as the user has permission
		BasicLogger::logMessage("Checking access to requested template", 'debug');
		if(isset($this->fieldData['fwdtid']) && 
		 $this->fieldData['fwdtid'] != '' && 
		 AuthUtil::templateAccessAllowed($this->fieldData['fwdtid'], $auth->getUserID())){
			BasicLogger::logMessage("Access granted, forwarding user to {$this->fieldData['fwdtid']}", 'debug');	
			MVCUtils::redirect($this->fieldData['fwdtid']);
			
		//If the fwtid (forward template id) variable is not set, then set the
		//templateID to that default as long as the user has permission
		}elseif(!(isset($this->fieldData['fwdtid']) && 
		 $this->fieldData['fwdtid'] == '') && 
		 AuthUtil::templateAccessAllowed(MVCUtils::getTemplateID($cfg['smarty']['defaultTemplate']), $auth->getUserID())){
			BasicLogger::logMessage("Access granted, forwarding user to {$cfg['smarty']['defaultTemplate']}", 'debug');
			MVCUtils::redirect(MVCUtils::getTemplateID($cfg['smarty']['defaultTemplate']));
		//If all the above fails, show the user permission denied
		}else{
			BasicLogger::logMessage("Access denied", 'debug');
			MVCUtils::redirect(MVCUtils::getTemplateID($cfg['Auth']['permissionErrorTemplate']));
		}
		
		/*//If the fwtid (forward template id) variable is set, then set the 
		//templateID to that requested as long as the user is allowed access.
		if(isset($this->fieldData['fwdtid']) && 
		 $this->fieldData['fwdtid'] != '' && 
		 AuthUtil::templateAccessAllowed($this->fieldData['fwdtid'], $auth->getUserID())){
		 	
			$this->templateID = $this->fieldData['fwdtid'];
			
		//If now fwtid has not been set, then forward to the default template
		//as long as the user is allowed access
		}elseif((!isset($this->fieldData['fwdtid']) || 
		 $this->fieldData['fwdtid'] == '') &&
		 AuthUtil::templateAccessAllowed(MVCUtils::getTemplateID($cfg['smarty']['defaultTemplate']), $auth->getUserID())){
		 	
			$this->templateID = MVCUtils::getTemplateID($cfg['smarty']['defaultTemplate']);
		}*/
		
	}
	
	protected function processInvalid(){
		//Called when a bad username/password is submitted.
		if(isset($this->fieldData['fieldData'])){
			$user = $this->fieldData['fieldData'];
			BasicLogger::logMessage("A login attempt failed for user '$user'.");
		}
	}
	
}

?>
