<?php
/**
 * 
 * @package MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class MVCUtils {
	
	const module = 'MVC';
	
	/**
	 * @todo Should return false if no template is found
	 */
	public static function getTemplateID($filename){
		
		global $cfg;
		
		static $idCache = array();
		
		if(!isset($idCache[$filename])){
			$db = Database::getInstance($cfg['MVC']['dsn']);
			$sql = "SELECT templateid FROM templates WHERE filename = '$filename'";
			$idCache[$filename] = $db->getOne($sql);
		}
		return $idCache[$filename];
	}
	
	/**
	 * Get a templates name based on its id
	 *
	 * Note: This is only the name of the file, not the path of the file. 
	 * If you require the path to a template you should use 
	 * {@link findTemplate}
	 */
	public static function getTemplateFileName($templateID){
		
		global $cfg;
		
		static $nameCache = array();
		
		if(!isset($nameCache[$templateID])){
			$db = Database::getInstance($cfg['MVC']['dsn']);
			$sql = "SELECT filename FROM templates WHERE templateid = $templateID";
			//echo "#" . $sql . "#<br>";
			$nameCache[$templateID] = $db->getOne($sql);
		}
		$file = $nameCache[$templateID];
		return $file;
	}
	
	public static function getTemplateModule($templateIDorFileName){
		global $cfg;
		
		if(is_numeric($templateIDorFileName)){
			$sql = "SELECT modulename FROM templates WHERE templateid = ?";
		}else{
			$sql = "SELECT modulename FROM templates WHERE filename = ?";
		}
		
		$db = Database::getInstance($cfg['MVC']['dsn']);
		$name = $db->getOne($sql, array($templateIDorFileName));
		
		return $name;
	}
	
	public static function includeViewer($className, $viewerModuleName){
		global $cfg;
		self::includeClass($className, $viewerModuleName, 'viewers');	
	}
	
	public static function includeModel($className,$moduleName){
		global $cfg;
		self::includeClass($className, $moduleName, 'models');
	}
	
	public static function includeValidator($className, $moduleName){
		global $cfg;
		self::includeClass($className, $moduleName, 'validators/field');
	}
	
	public static function includeFormValidator($className, $moduleName){
		global $cfg;
		self::includeClass($className, $moduleName, 'validators/form');
	}
	/**
	 * Include a class
	 *
	 * @param string $className The name of the class to include
	 * @param string $module The module in which the class resides
	 * @param string $type The type of the class (any of; models, validators, viewers)
	 */
	private  static function includeClass($className, $module, $type){
		global $cfg;
		
		$possibleTypes = array('models', 'viewers', 'validators/field', 'validators/form');
		if(!in_array($type, $possibleTypes)){
			throw new LoggedException("An invalid class type was passed ($type)", 0, self::module, 'error');
		}
		
		$pathParts = pathinfo($className);
		$subDir    = $pathParts['dirname'];
		$realClassName = $pathParts['basename'];
		
		$path = $cfg['general']['toolkitRoot'] . "/$module/$type/$subDir/$realClassName.class.php";
		
		if(!file_exists($path)){
			//If the file could not be found then check in the tkfecommon module
			$path = $cfg['general']['toolkitRoot'] . "/tkfecommon/$type/$className.class.php";
			if(!file_exists($path)){
				throw new LoggedException("The file for the requested class ($realClassName) could not be found. I was looking here '$path', and in the tkfecommon module", 0, self::module);
			}
		}
		
		include_once($path);
		
		if(!class_exists($realClassName)){
			throw new LoggedException("The file was loaded, but the requested class ($realClassName) could not be found", 0, self::module);
		}
	}
	
	public static function getPermErrorTemplateID(){
		global $cfg;
		if(is_numeric($cfg['Auth']['permissionErrorTemplate'])){
			$id = $cfg['Auth']['logintemplate'];
		}else{
			$db = Database::getInstance($cfg['Auth']['dsn']);
			$sql = "SELECT templateid FROM templates WHERE 
			        filename = '{$cfg['Auth']['permissionErrorTemplate']}'";
			$id = $db->getOne($sql);
		}
		if(is_null($id)){
			throw new LoggedException("Could not find template '{$cfg['Auth']['permissionErrorTemplate']}' as specified in \$cfg['Auth']['permissionErrorTemplate']");
		}
		return $id;
	}
	
	/**
	 * Gets the name of the model class
	 *
	 * Will return the model name from the database based upon the 
	 * template ID passed to it.
	 *
	 */
	protected static function getModelClassNameFromDB($formname=null,$modulename=null){
		global $cfg;
		$db = Database::getInstance($cfg['MVC']['dsn']);
		if (is_null($formname) || is_null($modulename)) {
            return "Model";
        } else {
            $Rmodel = $db->getOne("SELECT modelclass
		                    FROM forms
		                    WHERE formname = '$formname'
                            AND modulename = '$modulename'");
            if(is_null($Rmodel)) {
                return "Model";
            } elseif ($Rmodel == '') {
                return "Model";
            } else {
                return $Rmodel;
            }
        }
	}
	
	/**
	 * Gets the name of the viewer class
	 *
	 * Will return the viewer name from the database based upon the 
	 * template ID passed to it.
	 *
	 */
	protected function getViewerClassNameFromDB($templateID){
		global $cfg;
		$db = Database::getInstance($cfg['MVC']['dsn']);
		return $db->getOne("SELECT viewerclassname 
		                    FROM templates 
		                    WHERE templateid = '$templateID'");
	}
	
	/**
	 * Gets the realm ID of the template
	 *
	 * Will return the realm ID from the database based upon the 
	 * template ID passed to it.
	 *
	 */
	protected function getRealmIDFromDB($templateID){
		global $cfg;
		$db = Database::getInstance($cfg['MVC']['dsn']);
		return $db->getOne("SELECT realmid 
		                    FROM templates 
		                    WHERE templateid = '$templateID'");
	}
	
	/**
	 * Initialise the model
	 *
	 * Will initialise the model class. The class name is stored in the 
	 * $modelClassName class variable.
	 * 
	 * @return Model Returns the initialised model for use if required
	 */
	public static function initializeModel($templateIDS,
	  $formName = null, 
	  $modelModuleName, 
	  $viewerModuleName,
	  $fieldData = array(), 
	  $errors = array()){
		global $cfg;
		if(isset($fieldData['moduleName'])) {
		  $modelClassName = MVCUtils::getModelClassNameFromDB($formName,$fieldData['moduleName']);
		  MVCUtils::includeModel($modelClassName,$modelModuleName);
		} else {
		  $modelClassName = MVCUtils::getModelClassNameFromDB();
		  MVCUtils::includeModel($modelClassName,$modelModuleName);
        }
        
		$pathParts = pathinfo($modelClassName);
		$realClassName = $pathParts['basename'];
        
		eval("\$model = new " . $realClassName . "(\$templateIDS, \$formName, \$modelModuleName, \$viewerModuleName, \$fieldData, \$errors);");
		return $model;
	}
	
	/**
	 * Initialise a viewer object
	 *
	 * This method will intialise the viewer class associated with the specified  
	 * model and template. The name of the class is loaded from the database,
	 * the file is included, an instance is initialised, and finally assigned
	 * to the $viewer class variable.
	 *
	 */
	public static function initializeViewer($templateIDS,
	  $formName = null, 
	  $viewerModuleName,
	  $fieldData = array(), 
	  $errors = array()){
		global $cfg;
		$db = Database::getInstance($cfg['MVC']['dsn']);
		$sql = "SELECT viewerclassname FROM templates WHERE templateid = ?";
		$classname = $db->getOne($sql, array(end($templateIDS)));
		
		MVCUtils::includeViewer($classname, $viewerModuleName);
		
		$pathParts = pathinfo($classname);
		$realClassName = $pathParts['basename'];
		
		eval("\$newViewer = new $realClassName(\$templateIDS, \$formName, \$viewerModuleName, \$fieldData, \$errors);");
		return $newViewer;
	}
	
	
	/**
	 * Creates an object of type $className
	 * 
	 * This will return an object of type $className. The $className parameter 
	 * may be in the form of a directory path such as:
	 * 
	 * subFolder/ClassName
	 *  
	 * The $constructorString arguement will be the parameters passed to the 
	 * object for construction. An example could be:
	 * $params[0] = 'param1'
	 * $params[1] = 'param2'
	 * 
	 * This has been provided to allow for additional structuring of the 
	 * deveoper's models and viewers, so that the classes in a module's 
	 * 'templates' or 'models' directory can be organised into sub-folders.
	 *
	 * @param string $className
	 * @param Array $constructorString
	 * @return unknown
	 */
	//This function has been commented out becuase the added complexity does not 
	//justify the reduced code duplication!
	/*protected static function initializeObject($className, $constructorString){
		
		$pathParts = pathinfo($className);
		$realClassName = $pathParts['basename'];
		
		eval("\$outObject = new $realClassName($constructorString);");
		return $outObject;
	}*/
	
	/**
	 * Find a template
	 *
	 * This will look in the module for the specified template to try and find
	 * a path to the template. If it cannot be found, each module will be 
	 * serched for the file. The the full path to the requested template will
	 * be returned.
	 * 
	 * @param mixed $template Either a template ID or file name
	 * @return string The full path to the template including the file name, or false if not found
	 */
	public static function findTemplate($template){
		//Make sure $template is a name, not id
		if(is_numeric($template)){
			$template = self::getTemplateFileName($template);
		}
		
		$fullPath = false;
		
		//Check for windows and unix-type full path
		if(eregi('[A-Z]:', $template) !== false){
			$fullPath = true;
		}else if(substr($template, 0, 1) == '/'){
			$fullPath = true;
		}
		
		if($fullPath && file_exists($template)){
		 	return $template;
		}
		
		static $cache = array();
		global $cfg;
		
		//Check for cached result
		if(isset($cache[$template])){
			return $cache[$template]; //if cached, execution stops here
		}
		
		//Get the module in which the template reisdes
		$module = MVCUtils::getTemplateModule($template);
		

		//If the template was found in the database then look for it in the 
		//module specified in the database.
		if(!is_null($module)){
			//Generate the path of the template file
			$path = $cfg['general']['toolkitRoot']. "/$module/templates/$template";
			$path = realpath($path);
			
			//Check the template exists where it should
			if(!file_exists($path)){
				BasicLogger::logMessage("Template '$template' could not be found. I was looking here: $path", self::module, 'error');
				return false;
			}
			
			//Cache the return value
			$cache[$template] = $path;
			
			return $path;
		//If the template was not found in the database then start searching
		//each modules template directory. The is because templates can 
		//request to include a file which is not in the database. This could 
		//be more efficiet if there was some method of knowing the directory
		//of the parent template, because only that directory would then need 
		//to be searched			
		}else{
			foreach ($cfg['modules'] as $module){		
				$path = $cfg['general']['toolkitRoot']. '/' . $module . '/templates/';
				//Convert relative paths to full paths
				$path = realpath($path);
				if(strlen($path) > 0){
					//Recursively search the directory
					$path = self::findFile($path, $template);
					if($path !== false){
						//cache the return value
						$cache[$template] = $path;
						return $path;
					}
				}
			}
			
			return false;
		}
		
		
/*
		
		//If execution has got this far then the file has not been found
		
		BasicLogger::logMessage("Template '$template' could not be found", self::module, 'error');
		
		return false;*/
	}
	
	/**
	 * A recursive breadth first file search
	 * 
	 * @param string $basedirectory The starting directory for the search
	 * @param string $basedirectory The name of the file to search for
	 */
	public static function findFile($basedirectory, $needle) { 
		$handle=opendir($basedirectory);
		$searchDirs = array();
		while ($file = readdir($handle)) {
			if (substr($file, 0, 1) != '.'){
				if (is_dir($basedirectory . '/' . $file)) {
					$searchDirs[] = $basedirectory . '/' . $file;
				}elseif (strcmp($file, $needle) == 0) {
					closedir($handle);
					return $basedirectory . '/' . $needle;
				}
	
			}
		}
		closedir($handle);
		
		foreach ($searchDirs as $searchDir){
			$subDirResult = self::findFile($searchDir, $needle);
			if ($subDirResult !== false) {
				 return $subDirResult;
			}
		}
		return false;
		
	}
	
	/**
	 * List the files present within the directory structure
	 *
	 * This will list the files present in the directory structure as 
	 * specified by the values in $cfg['smarty']. This is not related
	 * to the data stored in the database. This function uses the 
	 * search method (also in this class). As a result, all directories 
	 * starting with a '.' are ignored (due to . , .. , .svn etc.)
	 *
	 * @param string $fileType Either template, model, viewer, controller, or validator
	 * @return A list of physical files present
	 * @todo Remove some of the redundant code
	 * @todo The self::search method should not return null, rather an empty array. When this is fixed the is_null calls can be removed
	 */
	public static function listPresent($fileType) {
		global $cfg;
		#$dir,$needle,$recurse=false
		$files = array();
		
		$paths = $cfg['modules'];
		
		if($fileType == 'template'){
			foreach ($paths as $path){
				$path = $cfg['general']['toolkitRoot']. '/' . $path . '/templates/';
				$searchResult = self::search($path, '.*.tpl', true);
				if(is_array($searchResult)){
					$files = array_merge($searchResult, $files);
				}
			}
		}else if($fileType == 'model'){
			foreach ($paths as $path){
				$path = $cfg['general']['toolkitRoot']. '/' . $path . '/models/';
				$searchResult = self::search($path, '.*.class.php', true);
				if(!is_null($searchResult)){
					$files = array_merge($searchResult, $files);
				}
			}
		}else if($fileType == 'viewer'){
			foreach ($paths as $path){
				$path = $cfg['general']['toolkitRoot']. '/' . $path . '/viewers/';
				$searchResult = self::search($path, '.*.class.php', true);
				if(!is_null($searchResult)){
					$files = array_merge($searchResult, $files);
				}
			}
		}else if($fileType == 'validator'){
			foreach ($paths as $path){
				$path = $cfg['general']['toolkitRoot']. '/' . $path . '/validators/';
				$searchResult = self::search($path, '.*.class.php', true);
				if(!is_null($searchResult)){
					$files = array_merge($searchResult, $files);
				}
			}
		}else{
			throw new LoggedException("An invalid fileType ($fileType) was passed to listPresent()", 0, self::module, "error");	
		}
		
		return $files;

	}

	/**
	 * Search for files
	 *
	 * This method will search a directory $dir recursively or non-recursively,
	 * as specified by $recurse, matching files against the regular 
	 * expression $needle. Any file starting with a '.' is ignored. This 
	 * search is depth first.
	 *
	 * @return An array of matched file names (without paths)
	 * @todo This should be a breadth first. The best option would be to merger with findFile()
	 * 
	 */
	protected static function search($dir,$needle,$recurse=false) {
		if(is_dir($dir)) {
			$handle = @opendir($dir);
			$o		= array();
			while($file = readdir($handle)) {
				if (substr($file, 0, 1) == '.') continue;
	       		if(eregi($needle, $file) !== false) {
	       			#$o[] = $dir.$file;
	       			$o[] = $file;
	       		}
				if(is_dir($dir.'/'.$file)&&$recurse==true) {
					$subresults = self::search($dir.'/'.$file,$needle,true);
	       			if(!empty($subresults)) {       	 
						$o = array_merge($o,$subresults);
					}
	       		}
			}
			if(!empty($o)) {
				return $o;
			} else {
				return false;
			}
		}
	}
	
	public static function redirect($templateID, $args = array()){
		global $cfg;
		
		if(!isset($templateID) || is_null($templateID) || $templateID == ''){
			throw new LoggedException("An invalid template ID ($templateID) was passed to redirect", 0, self::module , 'error');
		}
		
		$url  = $cfg['general']['protocol'];
		$url .= $cfg['general']['domain'];
		$url .= $cfg['general']['siteRoot'];
		$url .= "?templateID=$templateID";
		
		foreach($args as $k => $v){
			$url .= "&$k=$v";
		}
		
		header("Location: $url");
		exit(0);
	}
	
}

?>
