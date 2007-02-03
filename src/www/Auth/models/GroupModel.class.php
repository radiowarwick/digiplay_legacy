<?php
/**
 * The fields required for this Model are:
 *  - task - The task to be performed:
 *    - realmAllow - Give the user permission for this realm
 *    - realmDeny - Deny the user permission for this realm
 *    - realmIgnore - Do not specify any explicit user premissions for the relm
 *    - userAdd - Remove the user from the group being edited
 *    - userRemove - Add the user to the group being edited
 * - userToEdit - The ID of the group to edit
 * - rguid - The id of the user or relm in question 
 * 
 * @package FrontEnds
 * @subpackage Auth
 */
//include_once($cfg['dir']['tkfrontends.auth'] . '/config.php');
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for group management
 */
class GroupModel extends Model {
	
	const module = 'AuthFrontEnd';
	
	protected $groupToEdit;
	
	protected function processValid(){
		global $cfg;
		
		//$groupModifyPath = array('Administration', 'Authentication', 'Groups', 'Modify');
		
		//Load class variable groupToEdit
		if(isset($this->fieldData['groupToEdit'])){
			$this->groupToEdit = $this->fieldData['groupToEdit'];
		
			//The is_numeric call protects against sql injection on this variable
			if(!is_numeric($this->fieldData['groupToEdit'])){
				$badgid = $this->fieldData['groupToEdit'];
				throw new LoggedException("An invalid group id was passed ($badgid)", 0, self::module, 'error');
			}
		}
		
		if($this->formName == 'groupRealmForm'){
			AuthUtil::requireRealm(30); //Groups - Modify
			//If groupToEdit, rguid, and task are specified then conduct the task
			//It is not possible to conduct a task without this information
			if(isset($this->fieldData['groupToEdit']) && 
			 $this->fieldData['groupToEdit'] != "" &&
			 isset($this->fieldData['rguid']) && 
			 $this->fieldData['rguid'] != "" &&
			 isset($this->fieldData['task']) &&
			 $this->fieldData['task'] != ""){
				$this->conductMainFormTask();
			}
		}elseif($this->formName == 'groupDetailsForm' || $this->formName == 'addGroupForm'){
			AuthUtil::requireRealm(30); //Group - modify
			//Save the details if the detailsForm is submitted
			if(!isset($this->fieldData['groupToEdit']) || $this->fieldData['groupToEdit'] == ""){
				$createNew = true;
			}else{
				$createNew =false;
			}
			$this->saveDetails($createNew);
			if($createNew){
				$this->fieldData['newGroupID'] = $this->groupToEdit;
			}
		}elseif($this->formName == 'groupDeleteForm'){
			$this->deleteGroup($this->fieldData['groupToEdit']);
		}
		
	}
	
	protected function processInvalid(){
		//No invalid processing required
	}
	
	/**
	 * Save custom database fields
	 *
	 * This will process the fields specified in $cfg['Auth']['groupfields']. 
	 * Fields submited (whose names match those in $cfg['Auth']['groupfields'])
	 * will be saved to the database.
	 *
	 */
	protected function saveDetails($createNew){
		global $cfg;
		$db = Database::getInstance($cfg['Auth']['dsn']);
		
		foreach ($cfg['Auth']['groupfields'] as $fieldName => $niceName){
			if(array_key_exists($fieldName, $this->fieldData)){
				$customFieldsToSave[$fieldName] = $this->fieldData[$fieldName];
			}
		}
		
		if(count($customFieldsToSave) > 0){
			if($createNew){
				$customFieldsToSave['id'] = '#id#';
				$this->groupToEdit = $db->insert('groups', $customFieldsToSave);
			}else {
				$db->update('groups', $customFieldsToSave, "groupid = '{$this->groupToEdit}'");
			}
		}
	}
	
	protected function conductMainFormTask(){
		$gid = $this->fieldData['groupToEdit'];
		$rguid = $this->fieldData['rguid'];
		$task = $this->fieldData['task'];
		if($task == 'realmAllow'){ 
			AuthUtil::editGroupRelmAccess($gid, $rguid, 'y');
		} elseif($task == 'realmDeny'){ 
			AuthUtil::editGroupRelmAccess($gid, $rguid, 'n');
		} elseif($task == 'realmIgnore'){ 
			AuthUtil::editGroupRelmAccess($gid, $rguid, null);
		} elseif($task == 'userAdd'){ 
			AuthUtil::editUserGroup($rguid, $gid, true);
		} elseif($task == 'userRemove'){
			AuthUtil::editUserGroup($rguid, $gid, false);
		} else{
			throw new LoggedException("An invalid task ($task) was requested", 0, self::module, 'warning');	
		}
	}
	
	protected function deleteGroup($gid){
		global $cfg;
		$db = Database::getInstance($cfg['Auth']['dsn']);
		
		$db->delete('realmgrouplink', "groupid = $gid");
		$db->delete('groupmembers', "groupid = $gid");
		$db->delete('groups', "id = $gid");
		unset($this->groupToEdit);
		unset($this->fieldData['groupToEdit']);
	}
	
}

?>
