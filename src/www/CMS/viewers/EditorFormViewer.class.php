<?php
/**
 * @package FrontEnds
 * @subpackage Common
 */
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
include_once($cfg['CMS']['fckPath'] . '/fckeditor.php');


/**
 *
 *
 *
 * @todo Remove the code duplication between userCanEdit/View methods
 * @todo Remove the code duplication between userCanEdit/View in this class and in the CMS class
 */
class EditorFormViewer extends Viewer {
	
	protected function setupTemplate(){
		global $cfg;
		parent::setupTemplate();
		$out = '';
		$perm = false;
		$error = false;
		
		if(!isset($this->fieldData['regionID'])){
			$error = 'No regionID was specified';
		}else if(!is_numeric($this->fieldData['regionID'])){
			$error = 'An invalid region id was specified';
		//Otherwise everything went fine...
		}else{
			$regionID = $this->fieldData['regionID'];
			$this->assign('regionID', $regionID);
			
			//Get region data from the database
			$db = Database::getInstance($cfg['CMS']['dsn']);
			$sql = 'SELECT * FROM cmsregions, cmscontent 
			       WHERE cmscontent.regionid = cmsregions.regionid 
			       AND cmscontent.regionid = ? 
			       ORDER BY cmscontent.timestamp DESC';
			$regionData = $db->getRow($sql, array($regionID));
			
			//If the user is NOT allowed to view this region...
			if(!$this->userCanView($regionData['userid'],
			                       $regionData['viewrealm'])){
			    //...then the cannot edit it!
			    $perm = 'none';
				$error = "You do not have permission to view this data";
			//if the user has permission to edit AND (the showEditorByDefault flag is true OR the query string states edit=1)
			}elseif ($this->userCanEdit($regionData['userid'],
			                            $regionData['editrealm'])) {
//					&& ($cfg['CMS']['showEditorByDefault'] || $this->fieldData['edit'])){
				$sesh = Session::getInstance();
				$perm = 'edit';
				$useEditor = true;	
				//Editing inline options (commented out in template)
				if($sesh->keyExists("CMSShowInLine")) {
					if($sesh->getValue("CMSShowInLine") == "y") {
						$this->assign('showInLineEditing', "CHECKED");
					} else {
						$this->assign('showInLineEditing', "");
						$useEditor = false;
					}
				} else {
					$sesh->setValue("CMSShowInLine","y");
					$this->assign('showInLineEditing', "CHECKED");
				}
				if($useEditor) {
				  $editor = new FCKeditor('contentEditor') ;
				  //FCKEditor does not seem to include the trailing slash,
				  //so add it here
				  $editor->BasePath = $cfg['CMS']['fckURL'] . '/';
				  $editor->Value = $regionData['content'];
				  //Use the config file based on the setting in the specified module
				  $configURLModule = $cfg['CMS']['configURLModule'];
				  $editor->Config['CustomConfigurationsPath'] =  $cfg[$configURLModule]['configURL'];
				  $editor->ToolbarSet = $regionData['inlinetoolbar'];
				  $editor->Height = $cfg['CMS']['editorHeight'];
				  $out = $editor->CreateHtml();
				} else {
				  $out = $regionData['content'];
				}
			//user can only view
			}else{
				$perm = 'view';
				$out = $regionData['content'];
			}
		}
		$this->assign('code', $out);
		$this->assign('regionID',$this->fieldData['regionID']);
		$this->assign('parentID',$this->templateIDStack[0]);		
		$this->assign('error',$error);
		$this->assign('perm',$perm);
	}
	
	protected function userCanEdit($userID, $realm){
		$auth = Auth::getInstance();
		$realmPath = AuthUtil::getRealmPath($realm);
		return AuthUtil::getDetailedUserrealmAccess($realmPath, $auth->getUserID());
	}
	
	public function userCanView($userID, $realm){
		$auth = Auth::getInstance($realm);
		$realmPath = AuthUtil::getRealmPath($realm);
		return AuthUtil::getDetailedUserrealmAccess($realmPath, $auth->getUserID());
	}
	
}

?>
