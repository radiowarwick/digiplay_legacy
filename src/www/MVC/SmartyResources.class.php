<?php
/**
 * 
 * @package MVC
 */
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
include_once($cfg['Logger']['dir']['root'] . '/LoggedException.class.php');

class SmartyResources {
	
	const module = 'MVC';
	
	public static function smarty_resource_rfile_source($templateName, &$source, &$smarty) {	
		$file = MVCUtils::findTemplate($templateName);
		if($file === false){
			BasicLogger::logMessage("Failed to return source for template '$templateName'", self::module, 'debug');
			return false;
		}else{
			BasicLogger::logMessage("Source returned for remplate '$templateName'", self::module, 'debug');
			$source = file_get_contents($file);
			return true;
		}
	}
	
	public static function smarty_resource_rfile_timestamp($templateName, &$timestamp, &$smarty) {
		global $cfg;
		$file = MVCUtils::findTemplate($templateName);
		if($file === false){
			return false;
		}else{
			return true;
		}
	}
	
	public static function smarty_resource_rfile_secure($templateName, &$smarty) {
			// assume all templates are secure
			return true;
	}
	
	public static function smarty_resource_rfile_trusted($templateName, &$smarty) {
			// not used for templates
	}
	

	
}

?>