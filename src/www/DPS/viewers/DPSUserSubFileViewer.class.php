<?php
/**
* @package FrontEnds
* @subpackage MVC
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['DPS']['dir']['root'] . '/DPS.class.php');

class DPSUserSubFileViewer extends Viewer {

	const module = 'DPS';
	protected $activeNode = 'foldersTree';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$dirID = substr($this->fieldData['id'],3);
		$type = $this->fildData['treeUser'];

		if ( stristr($_SERVER["HTTP_ACCEPT"],"application/xhtml+xml") ) {
			header("Content-type: application/xhtml+xml");
		}	else { 
			header("Content-type: text/xml");
		}

		if($type == 'group') {
			$treeInfo = DPS::singleGroupTreeSetup($dirID,$cfg['Auth']['defaultNewUserGroup'],$this->fieldData['treeType']);
		} else {
			$treeInfo = DPS::singleTreeSetup($dirID,$userID,$this->fieldData['treeType']);
		}

		echo("<?xml version='1.0' encoding='iso-8859-1'?>\n");
		if($dirID == 1) {
			$dirID = 0;
		} else {
			$dirID = "dir" . $dirID;
		}
		$treeInfo = '<tree id="' . $dirID . '">' . $treeInfo . '</tree>';
		echo $treeInfo;
	}
}
?>
