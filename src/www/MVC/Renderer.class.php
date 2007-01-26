<?php

include_once($cfg['MVC']['dir']['root'] . '/IController.class.php');
MVCUtils::includeViewer('RenderedExceptionViewer', 'MVC');

class Renderer implements IController {
	
	
	/**
	 * The module of this class, used in debugging
	 */
	const module = 'MVC';
	
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
	
	protected $viewer;
	
	protected $viewerModuleName;
	
	protected $errors;
	/**
	 * Initialise the Renderer object
	 * 
	 * Will determine if the required request variables are present.
	 * If not present an exception will be thrown and caught 
	 * 
	 * @var string
	 */
	public function __construct($templateID, $templateIDS, $fieldData = array(),$errors = array()){
		
		global $cfg;
		
		try{
			$this->templateIDStack = $templateIDS;
			$this->templateIDStack[] = $templateID;
			$this->fieldData = $fieldData;
			$this->errors = $errors;
			
			if($this->checkAuth()){
				$db = Database::getInstance($cfg['MVC']['dsn']);
				$this->viewerModuleName = $db->getOne("SELECT modulename FROM templates WHERE templateid = ?", 
				array(end($this->templateIDStack)));
				$newViewer = MVCUtils::initializeViewer($this->templateIDStack, null,$this->viewerModuleName,$this->fieldData,$this->errors);
			}else {
				$templateID = MVCUtils::getTemplateID($cfg['Auth']['rendererPermissionErrorTemplate']);
				array_pop($this->templateIDStack);
        $this->templateIDStack[] = $templateID;
				$newViewer = MVCUtils::initializeViewer($this->templateIDStack, null,'tkfecommon',$this->fieldData,$this->errors);
			}
			
			$this->viewer = $newViewer;
			
		//If a problem occured then return a textual error
		} catch (Exception $e){
		  $this->viewer = new ExceptionViewer($e);
		}
		
	}
	
	public function getCode(){
		return $this->viewer->getCode();
	}
	
	/**
	 * Checks authorisation for a template
	 *
	 */
	protected function checkAuth(){
		global $cfg;
		
		$auth = Auth::getInstance();
		
		if(!$auth->isLoggedIn()){
			BasicLogger::logMessage("Logging in user as default", self::module, 'debug');
			$auth->attemptLogin($cfg['Auth']['anonuser']);
		}else{
			$auth->attemptLogin();
		}
		
		BasicLogger::logMessage("logged in as '{$auth->getUser()}'", self::module, 'debug');
		return AuthUtil::templateAccessAllowed(end($this->templateIDStack), $auth->getUser());
	}
	
	/**
	 * Loads field data
	 *
	 * Will load the post and get superglobals into the $fieldData class 
	 * variable. When merging, get takes priority
	 *
	 */
	protected function loadFieldData(){
		//Merge get and post arrays. Get overides post if conflict
		$this->fieldData = array_merge($_POST, $_GET);
	}
	
}

?>
