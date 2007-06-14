<?php
/**
* @package Auth
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class AuthSubRealmViewer extends Viewer {

	const module = 'DPS';
	protected $activeNode = 'foldersTree';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		$auth = Auth::getInstance();
		$ID = $this->fieldData['guid'];
		$realmID = substr($this->fieldData['id'],3);
		$type = $this->fieldData['treeUser'];

		if (stristr($_SERVER["HTTP_ACCEPT"],"application/xhtml+xml") ) {
			header("Content-type: application/xhtml+xml");
		}	else { 
			header("Content-type: text/xml");
		}

		if($type == 'group') {
			$treeInfo = AuthSubRealmViewer::singleRealmTree($realmID, $ID, true);
		} else {
			$treeInfo = AuthSubRealmViewer::singleRealmTree($realmID, $ID, false);
		}

		echo("<?xml version='1.0' encoding='iso-8859-1'?>\n");
		if($realmID == 0) {
			$realmID = 0;
		} else {
			$realmID = "rlm" . $realmID;
		}
		$treeInfo = '<tree id="' . $realmID . '">' . $treeInfo . '</tree>';
		echo $treeInfo;
	}
	
	public static function singleRealmTree($realmID, $ID, $group) {
		global $cfg;
		$db = Database::getInstance($cfg['Auth']['dsn']);
			//get all children of the node specified
		$sql = "SELECT * from realms
			WHERE realms.parentid = $realmID";
		$subRealms = $db->getAll($sql);
		$list = '';
		if($realmID != 0) {
			if($group === false) { //user realmtree
					$uAccess = AuthUtil::getUserAccess($realmID, $ID);
					$gAccess = AuthUtil::getGroupAccessForUser($realmID, $ID);
			} else { //group realmtree
				$gAccess = AuthUtil::getGroupAccess($realmID, $ID);
			}
			if($gAccess == 'y') {
				$list = $list . '<item text="allow" id="opa' . $realmID . '" im0="radio_on.gif" child="0" />';
				$list = $list . '<item text="deny" id="opd' . $realmID . '" im0="radio_off.gif" child="0" />';
				$list = $list . '<item text="ignore" id="opi' . $realmID . '" im0="radio_off.gif" child="0" />';
			} elseif ($gAccess == 'n') {
				$list = $list . '<item text="allow" id="opa' . $realmID . '" im0="radio_off.gif" child="0" />';
				$list = $list . '<item text="deny" id="opd' . $realmID . '" im0="radio_on.gif" child="0" />';
				$list = $list . '<item text="ignore" id="opi' . $realmID . '" im0="radio_off.gif" child="0" />';
			} else {
				$list = $list . '<item text="allow" id="opa' . $realmID . '" im0="radio_off.gif" child="0" />';
				$list = $list . '<item text="deny" id="opd' . $realmID . '" im0="radio_off.gif" child="0" />';
				$list = $list . '<item text="ignore" id="opi' . $realmID . '" im0="radio_on.gif" child="0" />';
			}
		}
		foreach($subRealms as $realm) {
			if($group === false) { //user realmtree
				$uAccess = AuthUtil::getUserAccess($realm['realmid'], $ID);
				$gAccess = AuthUtil::getGroupAccessForUser($realm['realmid'], $ID);
			} else { //group realmtree
				$gAccess = AuthUtil::getGroupAccess($realm['realmid'], $ID);
				if($gAccess == 'y') {
					$list = $list . '<item text="' . htmlspecialchars($realm['name']) .
						'" id="rlm' . $realm['realmid'] . '" im0="green.gif" 
						im1="green.gif" im2="green.gif" child="1" />';
				} elseif ($gAccess == 'n') {
					$list = $list . '<item text="' . htmlspecialchars($realm['name']) .
						'" id="rlm' . $realm['realmid'] . '" im0="red.gif" 
						im1="red.gif" im2="red.gif" child="1" />';
				} else {
					$list = $list . '<item text="' . htmlspecialchars($realm['name']) .
						'" id="rlm' . $realm['realmid'] . '" im0="white.gif"
						im1="white.gif" im2="white.gif" child="1" />';
				}
			}
		}
		return $list;
	}
}
?>