<?php
/**
 *
 * @package FrontEnds
 * @subpackage Auth
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Check that a string is a valid name
 *
 *
 */
class FormValidator {

	protected $fieldData;
	protected $formName;
	protected $errorFormName = false;
	
	const module = 'tkfecommon';

	public function __construct($formName,&$fieldData){
		$this->formName = $formName;
		$this->fieldData = $fieldData;
		
		if(isset($this->fieldData['errorFormName'])){
			$this->errorFormName = $this->fieldData['errorFormName'];
		}
	}
	
	public function isValid() {
		global $cfg;
		
		$db = Database::getInstance($cfg['MVC']['dsn']);
		$rules = $db->getAll("SELECT vrclassname, description, fieldname, fieldvalidators.modulename FROM
		                      fieldvalidators, formfields WHERE
		                      formfields.ruleid = fieldvalidators.ruleid AND
		                      
		                      formname = '{$this->formName}'");
		//This statement has been removed from the where clause:
		//modulename = '{$this->fieldData['moduleName']}' AND
		$invalidFields = array();
		$sess = Session::getInstance();
		
		// Validate the submitted fields
		foreach($rules as $rule){
			MVCUtils::includeValidator($rule['vrclassname'], $rule['modulename']);
			eval("\$validatorObj = new {$rule['vrclassname']}(\$this->fieldData);");
			$vResult = $validatorObj->isValid($this->fieldData[$rule['fieldname']]);
			if($vResult !== true){
				//Put the errors:
				// a) straight into the errors array for backwards compatibility
				// b) into a sub array, whose key is the submitted value for 
				//    errorFormName, otherwise use the form name
				$invalidFields[$rule['fieldname']] = $vResult;
				if(!$this->errorFormName){
					$invalidFields[$this->formName][$rule['fieldname']] = $vResult;
				}else{
					$invalidFields[$this->errorFormName][$rule['fieldname']] = $vResult;
				}
			}
			if($sess->keyExists('auth_user')) {
				BasicLogger::logMessage($sess->getValue('auth_user'),self::module,"debug");
			}
		}
		return $invalidFields;
	}

}

?>
