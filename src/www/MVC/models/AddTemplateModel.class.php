<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
//include_once($cfg['Auth']['dir']['root'] . '/Auth.class.php');
//in/lude_once($cfg['Auth']['dir']['root'] . '/AuthUtil.class.php');
MVCUtils::includeModel('TemplateModel', 'MVC');
/**
 * Model for template management
 */
class AddTemplateModel extends TemplateModel {
	
	const module = 'MVCFrontEnd';
	
	protected function processValid(){
		if(isset($this->fieldData['submit'])){
			
			global $cfg;
			
			$db = Database::getInstance($cfg['MVC']['dsn']);
			
			$insertArray = array(	'filename'        => $this->fieldData['fileName'],
									'modelclassname'  => $this->fieldData['modelName'],
									'viewerclassname' => $this->fieldData['viewerName']);
			$db->insert('templates', $insertArray);
		}
	}
	
	protected function processInvalid(){
		//No invalid processing required
	}

	protected function listPHPClassFiles($path, $recursive){
		
		$out = array();
		
		$simplePaths = split(';', $path);
		foreach ($simplePaths as $path){
			//Convert relative paths to full paths
			$path = realpath($path);
			$handle = opendir($path);
			while (false !== ($file = readdir($handle))) { 
				if(preg_match('/.*\.tpl$/i', $file)){
					$out[] = $file;
				}
			}
			closedir($handle);
		}
		return $out;
	}
	
}

?>
