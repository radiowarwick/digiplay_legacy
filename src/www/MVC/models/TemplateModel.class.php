<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
//include_once($cfg['Auth']['dir']['root'] . '/Auth.class.php');
//in/lude_once($cfg['Auth']['dir']['root'] . '/AuthUtil.class.php');


/**
 * Model for template management
 */
class TemplateModel extends Model {
	
	const module = 'MVCFrontEnd';
	
	protected $templateToEdit;
	
	protected function processValid(){
			

	}
	
	protected function processInvalid(){
		//No invalid processing required
	}
	
}

?>
