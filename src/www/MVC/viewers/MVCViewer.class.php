<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');

class MVCViewer extends Viewer {
	
	const module = 'MVCFrontEnd';
	
	protected function setupTemplate(){
		parent::setupTemplate();
	}
	
}

?>
