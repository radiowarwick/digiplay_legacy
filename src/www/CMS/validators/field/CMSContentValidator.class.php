<?php
/**
 * 
 * @package FrontEnds
 * @subpackage Auth
 */

include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeValidator('ValidatorRule', 'MVC');

/**
 * Validate HTML
 * 
 * @todo This should check that the user has not passed html tags 
 * which are not avaliable on the toolbar
 */
class CMSContentValidator extends ValidatorRule {
	
	public function isValid(&$data){
		
		//Coming soon...
		
		return true;
	}
	
}

?>