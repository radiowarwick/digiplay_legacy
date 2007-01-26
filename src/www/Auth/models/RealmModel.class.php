<?php
/**
 * The fields required for this Model are:
 * - realmToEdit - The ID of the realm to edit
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
class RealmModel extends Model {
	
	const module = 'AuthFrontEnd';
	
	protected $realmToEdit;
	
	protected function processValid(){
		
		//Load class variable realmToEdit
		if(isset($this->fieldData['realmToEdit'])){
			$this->realmToEdit = $this->fieldData['realmToEdit'];
		
			//The is_numeric call protects against sql injection on this variable
			if(!is_numeric($this->fieldData['realmToEdit'])){
				$badrid = $this->fieldData['realmToEdit'];
				throw new LoggedException("An invalid realm id was passed ($badrid)", 0, self::module, 'error');
			}
		}
		
		if($this->formName == 'addRealmDetailsForm' || $this->formName == 'modifyRealmDetailsForm'){
			//Save the details if the detailsForm is submitted
			if(!isset($this->fieldData['realmToEdit']) || $this->fieldData['realmToEdit'] == ""){
				AuthUtil::addRealm($this->fieldData['parentID'], $this->fieldData['name'], $this->fieldData);
				$this->fieldData['newRealmID'] = $this->realmToEdit;
			}else{
                AuthUtil::modifyRealm($this->realmToEdit,$this->fieldData);
			}
		}elseif($this->formName == 'realmDeleteForm'){
			AuthUtil::deleteRealm($this->fieldData['realmToEdit']);
		}
	}
	
	protected function processInvalid(){
		//No invalid processing required
	}
}

?>
