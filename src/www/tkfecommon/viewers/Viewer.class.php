<?php
/**
 * 
 * @package MVC
 */
 
include_once($cfg['smarty']['dir']['root'] . "/libs/Smarty.class.php");
//MVCUtils::includeViewer('IViewer'); cannot be used as IViewer does not contain a class
include_once($cfg['MVC']['dir']['root'] . '/viewers/IViewer.class.php');
include_once($cfg['MVC']['dir']['root'] . '/SmartyResources.class.php');
include_once($cfg['MVC']['dir']['root'] . '/Module.class.php');
include_once($cfg['MVC']['dir']['root'] . '/SmartyResources.class.php');
include_once($cfg['MVC']['dir']['root'] . '/SmartyFunctions.class.php');

/**
 * Interfaces with the Smarty template engine
 * 
 * This class is used by simply initialising and calling the 
 * {@link printTemplate} or {@link getCode} methods
 * 
 * 
 * @package MVC
 */
class Viewer implements IViewer {
	
	/**#@+
	 * @access private
	 */
	/**
	 * An instance of the Smarty class.
	 * @var Smarty
	 */
	protected $template;
	/**
	 * The ID of the template to use. The ID is that of the row in the database
	 * @var int
	 */
	protected $templateIDStack;
	/**
	 * The name of the form (if any) which has been submitted
	 * @var string
	 */
	protected $formName;
	/**
	 * An associative array for field/value pairs from the submitted form (if any)
	 * @var array
	 */
	protected $fieldData;
	/**
	 * An associative array of erroneous fields in the format field/error
	 * @var array
	 */
	protected $invalidFields;
	/**
	 * The file name of the template to be used
	 * @var string
	 */
	protected $templateFileName;
	
	protected $viewerModuleName;
	
	protected $auth = array();
	/**
	 * A associative array of values that will be passed to the template in 
	 * the $VIEWER variable. The assigment of $viewerVars takes place just 
	 * before the template is printed (or code returned)
	 * @var array
	 */
	protected $viewerVars;
	/**#@-*/
	/**
	 * Will initialise the Viewer
	 * 
	 * @param string $templateID The ID of the template for the page to be viewed. This ID is the ID of the template in the database.
	 * @param string $formName The name of the form (if any) which has been submitted
	 * @param array $fieldData An associative array for field/value pairs from the submitted form (if any)
	 * @param array $invalidFields An associative array of erroneous fields in the format field/error
	 *
	 */
	
	const module = 'MVC';
	
	public function __construct($templateS, $formName = '', $viewerModuleName, $fieldData = array(), $invalidFields = array()){
		global $cfg;
		$this->template = new Smarty();
		$this->viewerModuleName = $viewerModuleName;
		if(isset($cfg['smarty']['debug']) && $cfg['smarty']['debug'] == true){
			$this->template->clear_all_cache();
			$this->template->caching = false;
			$this->template->force_compile = true;
		}
		$this->template->compile_dir = $cfg['smarty']['compiledir'];
		//$this->template->template_dir = $cfg['smarty']['tplRoot'];
		$this->templateIDStack = $templateS;
		$this->formName = $formName;
		$this->fieldData = $fieldData;
		$this->invalidFields = $invalidFields;
		$this->templateFileName = MVCUtils::findTemplate(end($this->templateIDStack));
		//echo "#" . $this->templateFileName . "#<br>";
		if($this->templateFileName === false){
			throw new LoggedException(
			  "The template with ID " . end($this->templateIDStack) . " could not be found",
			  0, self::module, 'error');
		}
		$this->setupTemplate();
	}
	
	/**
	 * Will print the template output to the browser
	 */
	public function printTemplate(){
		$this->assignViewerVars();
		$this->template->display('rfile:' . $this->templateFileName);
	}
	
	/**
	 * Will return the template output
	 */
	public function getCode(){
		$this->assignViewerVars();
		return $this->template->fetch('rfile:' . $this->templateFileName);
	}
	
	/**
	 * Assign the $VIEWER template variable
	 *
	 * This assigns the $viewerVars class variable to the $VIEWER template 
	 * variable
	 */
	protected function assignViewerVars(){
		$this->template->assign('VIEWER', $this->viewerVars);
	}
	
	/**
	 * Add a an element to the $VIEWER template variable
	 * 
	 * This will add an element to the $VIEWER template variable which can be 
	 * accessed using $name as the key. For example assign('myKey', 'Hello!') 
	 * could be accessed in the template using $VIEWER.myKey, and would 
	 * have the value 'Hello!'
	 * 
	 * @param string $name The name of the value. This will be used to access the value in the template
	 * @param mixed $value Any basic type or an array. Untested with objects
	 */
	public function assign($name, $value){
		$this->viewerVars[$name] = $value;
	}
	
	/**
	 * Assigns values to the template
	 *
	 */
	protected function setupTemplate(){
		global $cfg;
		
		//Get the required utilities
		$sess = Session::getInstance();
		
		//Flag indicating if the session is newly created
		$sessData['isNew'] = $sess->isSessionNew();
		
		$auth = Auth::getInstance();
		$this->auth['user'] = $auth->getUser();
		
		//Assign to smarty variables
		$this->template->assign('DATA', $this->fieldData);
		$this->template->assign('ERRORS', $this->invalidFields);
		$this->template->assign('SESSION', $sessData);
		$this->template->assign('CONFIG', $cfg);
		$this->template->assign('AUTH', $this->auth);
		
		//Assign formName and templateID. Notice that $this->assign is used, ()
		//not $this->template->assign(). Assignments done this way will end up 
		//in the $VIEWER smarty variable array. This is the mechanism though 
		//which a viewer sends data to a template.
		$this->assign('formName', $this->formName);
		$this->assign('templateID', end($this->templateIDStack));
		$this->assign('templateIDStack', $this->templateIDStack);
		
		//Setup file handler. This allows multiple directories to be searched, 
		//instead of using smarties one directory default.
		$this->template->register_resource('rfile',
			array('SmartyResources',
			'smarty_resource_rfile_source',
			'smarty_resource_rfile_timestamp',
			'smarty_resource_rfile_secure',
			'smarty_resource_rfile_trusted'));
		
		//Set this template access method as default. This makes this 
		//process transparent to the smarty coder.
		$this->template->default_resource_type = 'rfile';
		
		//Register functions specific to this application. These may be
		//found in SmartyFunctions.class.php.
		$this->template->register_function('getTemplateID', array('SmartyFunctions', 'SMARTY_getTemplateID'));
		$this->template->register_function('templateLink', array('SmartyFunctions', 'SMARTY_templateLink'));
		$this->template->register_function('use', array($this, 'SMARTY_use'));
	}
	
	final public function SMARTY_use($params) {
		global $cfg;
		$errorFlag = false;
		//Check that the function has been specified
		if(array_key_exists('func',$params)) {
			//Split the function name (about the '::')
			$modInfo = explode("::",$params['func']);
			//Check that the splitting worked, and it was only split in 2 bits
			if($modInfo != false && count($modInfo) == 2){
				//Check that the specified file exists
				if(file_exists($cfg['general']['toolkitRoot'] . "/" . $modInfo[0] . "/" . $modInfo[0] . ".class.php")) {
					include_once($cfg['general']['toolkitRoot'] . "/" . $modInfo[0] . "/" . $modInfo[0] . ".class.php");
					//Check that the class and method have the expected names
					if(is_callable(array($modInfo[0], 'SMARTY_' . $modInfo[1]))) {
						//Pass the method both the form data and 
						//$params combined into the fieldData parameter
						if(is_null($this->fieldData)){
							$fieldD = $params;
						}else{
							$fieldD = array_merge($this->fieldData,$params);
						}
						$code = '$return = ' . $modInfo[0] . '::SMARTY_' . $modInfo[1] . '($fieldD,$this->invalidFields,$this->templateIDStack);';
						eval($code);
						//A return value of false indicates an error
						if ($return === false) {
							$errorFlag = true;
						}
					}
				} else {
					$errorFlag = true;
				}
			} else {
				$errorFlag = true;
			}
			if($errorFlag == false) {
				return $return;
			} else {
				BasicLogger::logMessage("Error in Function Call : " . $params['func'] . ".
					Either the Module / Function does not exist or the passed
					parameters are incorrect.", self::module);
				if($cfg['Logger']['level'] == "debug") {
					return "Error in Function Call : " . $params['func'] . ".
					Either the Module / Function does not exist or the passed
					parameters are incorrect.";
				} else {
					return "Error in Function Call";
				}
			}
		} else {
			BasicLogger::logMessage('No Module or function name defined, please
			use the format {use func="<ModuleName>::<FunctionName>"
			paramlist..}',$this->module);
		  return "No function Defined";
		}
	}
}

?>
