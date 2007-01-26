<?php
/**
 * 
 * @package MVC
 */
 
include_once($cfg['CMS']['fckPath'] . '/fckeditor.php');
include_once($cfg['MVC']['dir']['root'] .'/Renderer.class.php');

class MVC extends Module  {
	
	const module = 'MVC';
	
	/**
	 * Initialise the object
	 * 
	 */
	function __construct($fieldData, $templateID){
		parent::__construct($smarty, $fieldData, $templateID);
		
		$this->assignSmartyFunction('showRegion', array($this, 'SMARTY_showRegion'));
	}
	
	/**
	 * Get a templates id
	 * 
	 * The only required parameter is 'name', which should the the file 
	 * name of the template in question
	 * 
	 */
	public static function SMARTY_getTemplateID($params){
		if(isset($params['name'])){
			return MVCUtils::getTemplateID($params['name']);
		}else{
			return '';
		}
	}
	
	/**
	 * Create template link
	 * 
	 * Will create a link to a template specified by either an 'id' or 'name' 
	 * parameter. Any parameters starting with '_' will be added to the query 
	 * string (without the _). This allows you to pass extra info in the 
	 * link. use parameter target to set the html target value
	 */
	public static function SMARTY_templateLink($params){
		global $cfg;
		$text = $params['text'];
		if(isset($params['name'])){
			$id = MVCUtils::getTemplateID($params['name']);
		}elseif(isset($params['id'])){
			$id = $params['id'];
		}else{
			//$id = default template
		}
		
		if(isset($params['target'])) {
			$target = "target='" . $params['target'] . "'";
		} else {
			$target = '';
		}
		$extraQueryInfo = "";
		foreach($params as $k => $v){
			if(substr($k, 0, 1) == '_'){
				$k = substr($k, 1);
				$extraQueryInfo .= "&$k=$v";
			}
		}
		
		$path = $cfg['general']['siteRoot'] . "?templateID=$id" . $extraQueryInfo;
		return "<a href='$path' $target>$text</a>";
	}
}

?>
