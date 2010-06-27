<?php
/**
 * @package FrontEnds
 * @subpackage Auth
 */
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeViewer('AuthViewer', 'Auth');

class RealmViewer extends AuthViewer {
	
	protected function setupTemplate(){
		
		parent::setupTemplate();
		if(isset($this->fieldData['realmToEdit'])){
			$rid = $this->fieldData['realmToEdit'];
		}else{
			$rid = null;
		}
		$this->assignCustomFields('realms', $rid);
		
		if(isset($this->fieldData['realmToEdit'])){
			
			//$this->assign('groupinfo', $this->getGroupInfoForRealm($rid));
			//$this->assign('userinfo', $this->getUserInfoForRealm($rid));
			$this->assign('realmname', AuthUtil::getRealmname($rid));
		}
		
		$this->assign('realminfo', $this->buildRealmTreeForRealm());
		
	}
	
	/**
	 * Build a realm tree structure
	 * 
	 * This method calls {@link buildRealmTree} to build a realm tree data 
	 * structure. The returned structure does not contain any auth data 
	 * as it would not make sense in this context. The main use for this is 
	 * to get a hierarchical view of all the realms.
	 * 
	 * @return array A realm tree data structure
	 */
	protected function buildRealmTreeForRealm(){
		return AuthUtil::buildRealmTree(null, null);
	}
	
}

?>