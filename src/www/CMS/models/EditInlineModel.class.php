<?php
/**
 * @package FrontEnds
 * @subpackage Common
 */
include_once($cfg['Logger']['dir']['root'] . '/BasicLogger.class.php');

MVCUtils::includeModel('Model', 'tkfecommon');

class EditInlineModel extends Model {
	
	protected function processValid(){
		global $cfg;
		$db = Database::getInstance($cfg['CMS']['dsn']);
		$auth = Auth::getInstance();
		$sql = 'SELECT content FROM cmscontent WHERE regionid = 1 ORDER BY timestamp DESC';
		$oldContent = $db->getOne($sql);
		
		//If the content hasn't changed, then don't store it
		if($oldContent != $this->fieldData['contentEditor']){
			// string replace is a bodge fix
			$ins = array('regionid'  => $this->fieldData['regionID'],
						 'timestamp' => time(),
						 'content'   => str_replace(array("\015\012"),'',$this->fieldData['contentEditor']),
						 'userid'    => $auth->getUserID()
						 );
						 
			$db->insert('cmscontent', $ins);
		
		}
		$sesh = Session::getInstance();
		if($this->fieldData['alwaysInLine'] == "on") {
		    $sesh->setValue("CMSShowInLine","y");
		} else {
		    $sesh->setValue("CMSShowInLine","n");
		}
	}
	
	protected function processInvalid(){
		
	}
	
}

?>
