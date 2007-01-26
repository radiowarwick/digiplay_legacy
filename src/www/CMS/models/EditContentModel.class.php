<?php
/**
 * @package FrontEnds
 * @subpackage Common
 */
include_once($cfg['Logger']['dir']['root'] . '/BasicLogger.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

class EditContentModel extends Model {
	
	protected function processValid(){
		global $cfg;
		
		$db = Database::getInstance($cfg['CMS']['dsn']);
		$auth = Auth::getInstance();
		
		$sql = 'SELECT content FROM cmscontent WHERE regionid = 1 ORDER BY timestamp DESC';
		$oldContent = $db->getOne($sql);
		
		//If the content hasn't changed, then don't store it
		if($oldContent != $this->fieldData['contentEditor']){
		
			$ins = array('contentid' => '#id#',
						 'regionid'  => $this->fieldData['regionID'],
						 'timestamp' => time(),
						 'content'   => str_replace(array("\015\012"),'',$this->fieldData['contentEditor']),
						 'userid'    => $auth->getUserID()
						 );
						 
			$db->insert('cmscontent', $ins);
		
		}
		
		//The model may only receive HTML to store, so it is not assumed 
		//that the following data is present
		if(isset($this->fieldData['name'])){
			$ins = array('name'  => $this->fieldData['name'],
						 'editrealm'  => $this->fieldData['editRealm'],
						 'viewrealm'  => $this->fieldData['viewRealm'],
						 'inlinetoolbar'  => $this->fieldData['inlineToolbar'],
						 'windowtoolbar'  => $this->fieldData['windowToolbar'],
						 );
						 
			$db->update('cmsregions', $ins, "regionid = {$this->fieldData['regionID']}");
		}
			
	}
	
	protected function processInvalid(){
		
	}
	
}

?>
