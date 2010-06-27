<?php
/**
 * @package FrontEnds
 * @subpackage CMS
 */
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');

MVCUtils::includeViewer('EditContentWindowViewer', 'CMS');

class EditContentViewer extends EditContentWindowViewer {
	protected function setupTemplate(){
		global $cfg;
		parent::setupTemplate();
		
		$db = Database::getInstance($cfg['MVC']['dsn']);
		
		$sql = 'SELECT regionid FROM cmsregions ORDER BY name';
		$rIDs = $db->getColumn($sql);
		$sql = 'SELECT name FROM cmsregions ORDER BY name';
		$rNames = $db->getColumn($sql);
		
		$regions = array_combine($rIDs, $rNames);
		$this->assign('regions', $regions);
		
		if(isset($this->fieldData['regionID'])){
			$sql ='SELECT cmsregions.inlinetoolbar, 
			               cmsregions.windowtoolbar, 
			               cmsregions.editrealm, 
			               cmsregions.viewrealm,
			               cmsregions.name FROM cmsregions 
			       WHERE cmsregions.regionid = ?';
			$regionData = $db->getRow($sql, array($this->fieldData['regionID']));
			
			$this->assign('inlineToolbar', $regionData['inlinetoolbar']);
			$this->assign('windowToolbar', $regionData['windowtoolbar']);
			
			$this->assign('editRealm', $regionData['editrealm']);
			$this->assign('viewRealm', $regionData['viewrealm']);
			
			$this->assign('name', $regionData['name']);
			
			$sql = 'SELECT realmid, name, depth FROM realms ORDER BY realmpath';
			$realmInfo = $db->getAll($sql);
			
			$realms = array();
			foreach($realmInfo as $row){
				$realms[$row['realmid']] = str_repeat('--', $row['depth']) . ' ' . $row['name'];
			}
			
			$this->assign('realms', $realms);
		}
	}
	
	
}

?>