<?php
/**
 * 
 * @package MVC
 */
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVC.class.php');

class SmartyFunctions {
	
	/**
	 * Get a templates id
	 * 
	 * This method is deprecated, please use MVC::SMARTY_getTemplateID()
	 * 
	 */
	public static function SMARTY_getTemplateID($params){
		return MVC::SMARTY_getTemplateID($params);
	}
	
	/**
	 * Create template link
	 * 
	 * This method is deprecated, please use MVC::SMARTY_templateLink()
	 * 
	 */
	public static function SMARTY_templateLink($params){
		return MVC::SMARTY_templateLink($params);
	}
}