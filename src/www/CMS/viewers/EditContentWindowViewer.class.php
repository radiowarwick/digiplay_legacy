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
class EditContentWindowViewer extends Viewer {
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
			                      $regionData['editrealm'])){
			    //...then the cannot edit it!
				$error = "You do not have permission to edit this data";
			//if the user has permission to edit...
			}else{
			    //...they can edit the region as long as a 
			    //region was specified
				if($regionData['windowtoolbar'] == ''){
					$error = "This region is not configured for windowed editing";
				}else{
					$sesh = Session::getInstance();
					$perm = 'edit';
					if($sesh->keyExists("CMSShowInLine")) {
						if($sesh->getValue("CMSShowInLine") == "y") {
							$this->assign('showInLineEditing', "CHECKED");
						} else {
							$this->assign('showInLineEditing', "");
						}
					} else {
						$sesh->setValue("CMSShowInLine","y");
						$this->assign('showInLineEditing', "CHECKED");
					}
				  $editor = new FCKeditor('contentEditor') ;
				  //FCKEditor does not seem to include the trailing slash,
				  //so add it here
				  $editor->BasePath = $cfg['CMS']['fckURL'] . '/';
				  $editor->Value = $regionData['content'];
				  //Use the config file based on the setting in the specified module
				  $configURLModule = $cfg['CMS']['configURLModule'];
				  $editor->Config['CustomConfigurationsPath'] =  $cfg[$configURLModule]['configURL'];
				  $editor->ToolbarSet = $regionData['windowtoolbar'];
				  $editor->Height = $cfg['CMS']['editorHeight'];
				  $out = $editor->CreateHtml();
				}
			// Otherwise the user has view permissions
			}
		}
		$this->assign('editorCode', $out);
		$this->assign('regionID',$this->fieldData['regionID']);	
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
