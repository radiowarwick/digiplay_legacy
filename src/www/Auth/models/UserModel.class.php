<?php
/**
 * The fields required for this Model are:
 *  - task - The task to be performed:
 *    - realmAllow - Give the user permission for this realm
 *    - realmDeny - Deny the user permission for this realm
 *    - realmIgnore - Do not specify any explicit user premissions for the relm
 *    - groupAdd - Add the user to the specified group
 *    - groupRemove - Remove the user from the specified group
 * - userToEdit - The ID of the user to edit
 * - rguid - The id of the group or relm in question 
 * 
 * @package FrontEnds
 * @subpackage Auth
 */
//include_once($cfg['dir']['tkfrontends.auth'] . '/config.php');
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class UserModel extends Model {
	
	const module = 'AuthFrontEnd';
	
	protected $userToEdit;
	
	protected function processValid(){
			
		//Load class variable userToEdit
		if(isset($this->fieldData['userToEdit'])){
			$this->userToEdit = $this->fieldData['userToEdit'];
		
			//The is_numeric call protects against sql injection on this variable
			if(!is_numeric($this->fieldData['userToEdit'])){
				$baduid = $this->fieldData['userToEdit'];
				throw new LoggedException("An invalid user id was passed ($baduid)", 0, self::module, 'error');
			}
		}
		
		if($this->formName == 'userPermissionForm'){
			//If userToEdit, rguid, and task are specified then conduct the task
			//It is not possible to conduct a task without this information
			if(isset($this->fieldData['userToEdit']) && 
			 $this->fieldData['userToEdit'] != "" &&
			 isset($this->fieldData['rguid']) && 
			 $this->fieldData['rguid'] != "" &&
			 isset($this->fieldData['task']) &&
			 $this->fieldData['task'] != ""){
				$this->conductMainFormTask();
			}
		}elseif($this->formName == 'addUserDetailsForm' || $this->formName == 'modifyUserDetailsForm'){
			//Save the details if the detailsForm is submitted
			if(!isset($this->fieldData['userToEdit']) || $this->fieldData['userToEdit'] == ""){
				$createNew = true;
			}else{
				$createNew =false;
			}
			$this->saveDetails($createNew);
			if($createNew){
				$this->fieldData['newUserID'] = $this->userToEdit;
			}
			
			if(isset($this->fieldData['changePassword']) || $createNew){
				$this->savePassword();
			}
		}elseif($this->formName == 'userDeleteForm'){
			$this->deleteUser($this->fieldData['userToEdit']);
		}
		
	}
	
	protected function processInvalid(){
		//No invalid processing required
	}
	
	/**
	 * Save password to database
	 *
	 * Will update a users password
	 */
	protected function savePassword(){
		global $cfg;
		$md5pass = md5($this->fieldData['password']);
		$updateArray = array('password' => $md5pass);
		$db = Database::getInstance($cfg['Auth']['dsn']);
		
		$db->update('users', $updateArray, "id = '{$this->userToEdit}'");
	}
	
	/**
	 * Save custom database fields
	 *
	 * This will process the fields specified in $cfg['Auth']['userfields']. 
	 * Fields submited (whose names match those in $cfg['Auth']['userfields'])
	 * will be saved to the database. If $createNew is true, then a new user 
	 * will be created with the given details and $this->userToEdit 
	 * will be loaded with the new id.
	 * 
	 * @param boolean $createNew Flag indicating that a new record should be created
	 */
	protected function saveDetails($createNew){
		global $cfg;
		$db = Database::getInstance($cfg['Auth']['dsn']);
		
		foreach ($cfg['Auth']['userfields'] as $fieldName => $niceName){
			if(array_key_exists($fieldName, $this->fieldData)){
				$customFieldsToSave[$fieldName] = $this->fieldData[$fieldName];
			}
		}
		
		if(count($customFieldsToSave) > 0){
			if($createNew){
				$customFieldsToSave['id'] = '#id#';
				$customFieldsToSave['enabled'] = 't';
				$this->userToEdit = $db->insert('users', $customFieldsToSave);
			}else {
				$db->update('users', $customFieldsToSave, "id = '{$this->userToEdit}'");
			}
		}
	}
	
	protected function conductMainFormTask(){
		$uid = $this->fieldData['userToEdit'];
		$rguid = $this->fieldData['rguid'];
		$task = $this->fieldData['task'];
		if($task == 'realmAllow'){
			AuthUtil::editUserRelmAccess($uid, $rguid, 'y');
		} elseif($task == 'realmDeny'){ 
			AuthUtil::editUserRelmAccess($uid, $rguid, 'n');
		} elseif($task == 'realmIgnore'){ 
			AuthUtil::editUserRelmAccess($uid, $rguid, null);
		} elseif($task == 'groupAdd'){ 
			AuthUtil::editUserGroup($uid, $rguid, true);
		} elseif($task == 'groupRemove'){
			AuthUtil::editUserGroup($uid, $rguid, false);
		} else{
			throw new LoggedException("An invalid task ($task) was requested", 0, self::module, 'warning');	
		}
	}
	
	protected function deleteUser($uid){
		global $cfg;
		$db = Database::getInstance($cfg['Auth']['dsn']);
		
		$db->delete('users', "id = $uid");
		$db->delete('usergrouplink', "id = $uid");
		$db->delete('realmuserlink', "id = $uid");
		
		unset($this->userToEdit);
		unset($this->fieldData['userToEdit']);
	}
	
}

?>
