<?php
/**
 * 
 * @package MVC
 */
 
 
include_once($cfg['DBAL']['dir']['root'] . '/BasicGenericObjectCollection.class.php');
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/IController.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeViewer('Viewer', 'MVC');
//include_once($cfg['MVC']['dir']['root'] . '/validators/EmailValidator.class.php');

/**
 * Processes request data and constructs an aparopiate model or viewer
 * 
 * This class is used by simply initialising. Input data is taken 
 * from superglobals.
 * 
 * 
 * @package MVC
 */
class Page implements IController {
	
  
  /**
   * The module of this class, used in debugging
   */
  const module = 'MVC';
	
  /**
   * The ID of the template to use. The ID is that of the row in the database
   * @var int
   */
  protected $templateID;
  
  protected $moduleName;
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
	
  protected $model;
  
  protected $modelModuleName;
	
  /**
   * Initialise the Page object
   * 
   * Will determine if the required request variables are present.
   * If not present an exception will be thrown and caught 
   * 
   * @var string
   */
  public function __construct(){
	
    list($usec, $sec) = explode(" ", microtime()); 
    $startTime = ((float)$usec + (float)$sec);
	
    global $cfg;
	
    try{
			
      ##############
      ## Include the Auth and AuthUtil classes
			
      $modulePath  = $cfg['general']['toolkitRoot'] . '/' . $cfg['Auth']['authClassModule'];
			
      //Check that the classes are not already loaded
			/*if(class_exists("Auth")){
				throw new Exception("The Auth class seems to have been included already! This should not have happened.");
			}
			
			if(class_exists("AuthUtil")){
				throw new Exception("The AuthUtil class seems to have been included already! This should not have happened.");
			}*/
			
      // try to include Auth
      if(!include_once("$modulePath/Auth.class.php")){
	throw new Exception("It was not possible to include Auth.class.php. I tried to find it here: $modulePath/Auth.class.php");
      }
			
      if(!class_exists("Auth")){
	throw new Exception("The Auth.class.php ($modulePath/Auth.class.php) file was included but the Auth class could not be found");
      }
			
      // try to include AuthUtil
      if(!include_once("$modulePath/AuthUtil.class.php")){
	throw new Exception("It was not possible to include AuthUtil.class.php. I tried to find it here: $modulePath/AuthUtil.class.php");
      }
			
      if(!class_exists("AuthUtil")){
	throw new Exception("The AuthUtil.class.php ($modulePath/AuthUtil.class.php) file was included but the AuthUtil class could not be found");
      }
			
      // DONE!
			
      $db = Database::getInstance($cfg['MVC']['dsn']);
      $errors = array();
			
      //Load data from superglobals
      $this->loadFieldData();
			
			/*if($_SERVER['HTTP_HOST'] != $cfg['general']['domain']){
				$url = $cfg['general']['protocol'] . 
				       $cfg['general']['domain'] . 
				       $cfg['general']['siteRoot'];
				
				header("Location: $url");
				exit();
			}*/
			
      if(isset($this->fieldData['templateID']) && $this->fieldData['templateID'] != ''){
	$this->templateID = $this->fieldData['templateID'];
      }else{
	$this->templateID = MVCUtils::getTemplateID($cfg['smarty']['defaultTemplate']);
      }
			
      //Load form name
      if(isset($this->fieldData['formName'])){
	$this->formName = $this->fieldData['formName'];
      }else{
	//formName is not required, so set to empty string
	//note that forms will be ignored if this is not passed
	$this->fieldData['formName'] = null;
      }
			
			
      //Load the module names
      $this->viewerModuleName = $db->getOne("SELECT modulename FROM templates WHERE templateid = ?", 
      array($this->templateID));
				
      if(isset($this->fieldData['moduleName']) && $this->fieldData['moduleName'] != ''){
	$this->modelModuleName = $this->fieldData['moduleName'];
      }else{
	$this->modelModuleName = 'MVC';
      }
			
			
      //Load template ID
      if(isset($this->fieldData['templateID']) && $this->fieldData['templateID'] != ''){
	$this->templateID = $this->fieldData['templateID'];
      }elseif(isset($cfg['smarty']['defaultTemplate'])){
	$this->templateID = MVCUtils::getTemplateID($cfg['smarty']['defaultTemplate']);
      }else{
	//Template ID is required. Therefore throw an exception
	throw new LoggedException('No template ID or default template specified', 0, self::module);
      }
			
      ### Check that the user has permission to use the submitted form
			
      // get the realmid of the submitted form
      $sql = 'SELECT realmid FROM forms WHERE formname = ? AND modulename = ?';
      $realmid = $db->getOne($sql, array($this->formName, $this->modelModuleName));
      $auth  = Auth::getInstance();
      
      // If the realm id could not found then allow access
      // (this will cause 'Model' to be used - so no processing occurs)
      if(!$realmid){
	//Access is allowed
	$modelAccess = true;
      } else {
	//Check if the user has access to the realm associated with the form
	if(!$auth->isLoggedIn()){
	  BasicLogger::logMessage("Logging in user as default(Form Login)", self::module, 'debug');
	  $auth->attemptLogin($cfg['Auth']['anonuser']);
        }else{
	  BasicLogger::logMessage("User is logged in', realm:'$realmid', user:'{$auth->getUserID()}'", self::module, 'debug');
	  $auth->attemptLogin();
        }
        $path = AuthUtil::getRealmPath($realmid);
        BasicLogger::logMessage("Checking User access for form:'{$this->formName}', realm:'$realmid', user:'{$auth->getUserID()}'", self::module, 'debug');
        if(!AuthUtil::getDetailedUserrealmAccess($path, $auth->getUserID())){
          //If the user does not have permission, show an error
          $modelAccess = false;
	  $errors = array('permission' => 'You do not have permission to use the submited form');
        } else {
          //Set access flag to false
          $modelAccess = true;
        }
      }
            
      //If access to the requested form is allowed
      if($modelAccess) {
	//If a form was submitted
	if(isset($this->formName) && !is_null($this->formName)){
	  //Then validate the form data
	  //Store any errors in $errors
	  $errors = $this->validate();
	}
      }
			
      //If the user has access to the requested template
      if($this->checkAuth()){
	if($modelAccess) {
	  BasicLogger::logMessage("Auth successfull for model for template: '{$this->templateID}'", self::module, 'debug');
          $newModel = MVCUtils::initializeModel(array($this->templateID), $this->formName, $this->modelModuleName, $this->viewerModuleName, $this->fieldData, $errors);
        } else {
          $this->templateID = MVCUtils::getPermErrorTemplateID();
	  $newModel = MVCUtils::initializeModel(array($this->templateID), null, 'MVC','Auth', $this->fieldData, $errors);
        }
	//If there are errors then these will be passed in the $errors array,
	//if there are no errors then $errors will simple be an empty array
	//If no form name was passed, $this->formName will be null				
      }else {
	//The user is not authorised to access this area
	$auth = Auth::getInstance();
	BasicLogger::logMessage("Auth failed for user '{$auth->getUser()}', template id '{$this->templateID}'", self::module, 'debug');
				
	//Set the template ID to that of the permission error template
	$this->templateID = MVCUtils::getPermErrorTemplateID();
				
	//Get the reason for failure and specify an error message
	$reason = $auth->getFailureReason();
	if(count($errors) == 0) {
	  if($reason == 2){
	    $errors = array('permission' => 'Your session has been inactive for too long');
	  }elseif($reason != 0){
	    $errors = array('permission' => 'Unfortunately, an error has occurred. Please attempt logging in again.');
	  }else{
	    $errors = array('permission' => 'You do not have permission to view this page');
	  }
	}
	//Initialise the viewer for the permission error template
	//$newModel = MVCUtils::initializeModel(array($this->templateID), null, 'MVC',$cfg['Auth']['permissionErrorTemplateModule'], $this->fieldData, $errors);
	if($auth->getUserID() == $cfg['Auth']['anonuserID'] && $cfg['Auth']['anonuserredirect'] == 'y') {
	  $permErrorTID = $cfg['Auth']['anonuserRedirectTemplateID'];
	  $newModel = MVCUtils::initializeViewer(array($permErrorTID), null, 'tkfecommon', null, $errors);
	} else {
	  $permErrorTID = MVCUtils::getTemplateID($cfg['Auth']['permissionErrorTemplate']);
	  $newModel = MVCUtils::initializeViewer(array($permErrorTID), null, 'tkfecommon', null, $errors);
	}		
      }
			
      echo $newModel->getCode();
      //If a problem occured then create an error page
    } catch (Exception $e){
      $ev = new ExceptionViewer($e);
      $ev->printTemplate();
      exit;
  }
		
  //Show the execution time if set in config file
  if($cfg['smarty']['showExecTime']){
    list($usec, $sec) = explode(" ", microtime());
    $endTime = ((float)$usec + (float)$sec);
    $totalTime = round($endTime - $startTime, 3);
    $log = Database::getQueryLog();
    echo "Total time to parse page: $totalTime seconds<br />\n";
    echo "Total number of queries: " . Database::getTotalQueries();
    echo "<br />Log: ";
    print_r($log);
  }
}
	
/**
 * Checks authorisation for a template
 *
 */
protected function checkAuth(){
  global $cfg;
		
  $auth = Auth::getInstance();
		
  if(!$auth->isLoggedIn()){
    BasicLogger::logMessage("Logging in user as default (checkAuth)", self::module, 'debug');
    $auth->attemptLogin($cfg['Auth']['anonuser']);
  }else{
  	BasicLogger::logMessage("Attempting Login (checkAuth)", self::module, 'debug');
    $auth->attemptLogin(); 
  }
  if(is_null($auth->getUserID())) {
    $Nuser = array();
    $Nuser['username'] = $auth->getUser();
    $Nuser['enabled'] = 't';
    $Nuser['id'] = "#id#";
    $db = Database::getInstance($cfg['Auth']['dsn']);
    $userID = $db->insert('users',$Nuser, true);
    if(isset($cfg['Auth']['defaultNewUserGroup'])) {
      $group = array();
      $group['groupid'] = $cfg['Auth']['defaultNewUserGroup'];
      $group['userid'] = $userID;
      $db->insert('groupmembers',$group, true);
    }
    $auth->attemptLogin();
    BasicLogger::logMessage("new user created for for '$user'", self::module, 'debug');
  }	
  BasicLogger::logMessage("logged in as '{$auth->getUser()}'", self::module, 'debug');
  return AuthUtil::templateAccessAllowed($this->templateID, $auth->getUser());
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
		
  if(isset($this->fieldData['moduleName']) && $this->fieldData['moduleName'] != '' && 
      (!isset($this->fieldData['formName'])  || is_null($this->fieldData['formName']))){
    throw new LoggedException('You seem to have passed the module name but no form name');
  }
		
  if(isset($this->fieldData['formName']) && $this->fieldData['formName'] != '' && 
      (!isset($this->fieldData['moduleName'])  || $this->fieldData['moduleName']   == '')){
    throw new LoggedException('You seem to have passed the form name but no module name, no processing has occurred');
  }
		
  if(count($_POST) > 0 && !isset($this->fieldData['templateID'])){
    throw new LoggedException('It seems that you have submitted form/post data but 
      no templateID, which seems very odd. You should make sure that you form specifies 
      a templateID field');
  }
		
  //If magic quotes is turned on, then stip all the silly little 
  //slashes it has added
  if(get_magic_quotes_gpc()){
    foreach($this->fieldData as &$data){
      $data = stripslashes($data);
    }
  }
}
	
/**
 * Validate fields
 *
 * Will validate entries in the formData array that have validator objects 
 * specified in the database.
 *
 * @return array An associative array of erroneous fields in the format field/error
 */
protected function validate(){
  global $cfg;
		
  $db = Database::getInstance($cfg['MVC']['dsn']);
  $rules = $db->getRow("SELECT validatorname, validatormodule FROM
    forms WHERE
    modulename = '{$this->fieldData['moduleName']}' AND 
    formname = '{$this->formName}'");
		
  if( isset($rules['validatorname']) && isset($rules['validatormodule'])) {
    include_once($cfg['general']['toolkitRoot'] . '/' . $rules['validatormodule'] . '/validators/form/' . $rules['validatorname'] . '.class.php');
    eval("\$FormValidatorObj = new {$rules['validatorname']}(\$this->formName,\$this->fieldData);");
    return $FormValidatorObj->isValid();
  } else {
    include_once($cfg['general']['toolkitRoot'] . '/tkfecommon/validators/form/FormValidator.class.php');
    eval("\$FormValidatorObj = new FormValidator(\$this->formName,\$this->fieldData);");
    return $FormValidatorObj->isValid();
  }
}
	
}

?>
