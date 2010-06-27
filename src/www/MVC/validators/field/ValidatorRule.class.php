<?php
/**
 * 
 * @package MVC
 */
 
/**
 * Abstract class defining requirements for validators
 * 
 */
abstract class ValidatorRule {
	
	protected $fieldData;
	
	const module = 'MVC';
	
	public function __construct(&$fieldData){
		$this->fieldData = $fieldData;
	}
	
	/**
	 * Validate $data
	 * 
	 * This function must be overridden. It should return boolean true 
	 * if no error is found, or a descriptive error (i.e. A string).
	 * 
	 * Any modifications made to the $data parameter will be reflected in 
	 * the data passed to the model.
	 * 
	 * Note: Due to the return values for this function, you should use the 
	 * strict comparison operators (===, !==) to check for a true return  value
	 * @return boolean true if valid, error message if invalid
	 * 
	 */
	public abstract function isValid(&$data);
	
	
}

?>