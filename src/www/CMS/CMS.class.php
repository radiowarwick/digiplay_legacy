<?php
/**
 * 
 * @package MVC
 */
 
include_once($cfg['CMS']['fckPath'] . '/fckeditor.php');
include_once($cfg['MVC']['dir']['root'] .'/Renderer.class.php');

class CMS extends Module  {
	
	protected $smarty;
	
	const module = 'MVC';
	
	/**
	 * Initialise the object
	 * 
	 * The constructor simple assigns the Smarty instance to a class variable
	 * 
	 * @param Smarty $smarty The smarty instance in use
	 */
	function __construct(Smarty $smarty, $fieldData, $templateID){
		parent::__construct($smarty, $fieldData, $templateID);
		
		$this->assignSmartyFunction('showRegion', array($this, 'SMARTY_showRegion'));
	}
	
	public static function SMARTY_showRegion($params = array(),$invalidFields = array(), $TIDS){
		return CMS::SMARTY_showRegion1($params, $invalidFields, $TIDS);
	}
	
	public static function SMARTY_showRegion1($params = array(),$invalidFields = array(), $TIDS){
		$Rend = New Renderer(MVCUtils::getTemplateID('editorForm.tpl'), $TIDS, $params, $invalidFields);
        return $Rend->getCode();
	}
			
	public static final function modify_valid(&$fieldData = array(), &$errors = array()){
		global $cfg;
			
			$db = Database::getInstance($cfg['CMS']['dsn']);
			$auth = Auth::getInstance();
			
			$sql = 'SELECT content FROM cmscontent WHERE regionid = 1 ORDER BY timestamp DESC';
			$oldContent = $db->getOne($sql);
			
			$ins = array('contentid' => '#id#',
					 'regionid'  => $fieldData['regionID'],
					 'timestamp' => time(),
					 'content'   => $fieldData['contentEditor'],
					 'userid'    => $auth->getUserID()
					 );
					 
			$db->insert('cmscontent', $ins);

			//The model may only receive HTML to store, so it is not assumed 
			//that the following data is present
			if(isset($fieldData['name'])){
				$ins = array('name'  => $fieldData['name'],
							 'editrealm'  => $fieldData['editRealm'],
							 'viewrealm'  => $fieldData['viewRealm'],
							 'inlinetoolbar'  => $fieldData['inlineToolbar'],
							 'windowtoolbar'  => $fieldData['windowToolbar'],
							 );
							 
				$db->update('cmsregions', $ins, "regionid = {$fieldData['regionID']}");
			}
	}
	
	public static final function modify_invalid(){
		//Does nothing
	}
	
	public static function userCanEdit($userID, $realm){
		$auth = Auth::getInstance();
		$realmPath = AuthUtil::getRealmPath($realm);
		return AuthUtil::getDetailedUserrealmAccess($realmPath, $auth->getUserID());
	}
	
	public function userCanView($userID, $realm){
		$auth = Auth::getInstance($realm);
		$realmPath = AuthUtil::getRealmPath($realm);
		return AuthUtil::getDetailedUserrealmAccess($realmPath, $auth->getUserID());
	}
	
    /**
     *
     * Params should opentially contain:
     *  - 'content' - The initial editor content
     *  - 'name' - The field name for the editor
     *  - 'toolbarset' - The toolbar set that the editor should use
     * 
     * @param array params An array of values to configure the editable area
     *
     */
	public static function SMARTY_showEditRegion($params,$errors) {
        global $cfg;
        if(!isset($params['content'])) {
            $params['content'] = '';
        }
        if(!isset($params['toolbarset'])) {
            $params['toolbarset'] = 'cms_safe';
        }
        if(!isset($params['name'])) {
            $params['name'] = 'contentEditor';
        }
        $editor = new FCKeditor($params['name']) ;
        $editor->BasePath = $cfg['CMS']['fckURL'] . '/'; //add slash because fckEditor expects it
        $editor->Value = $params['content'];
        $editor->Config['CustomConfigurationsPath'] =  $cfg[$cfg['CMS']['configURLModule']]['configURL'];
        $editor->ToolbarSet = $params['toolbarset'];
        $editor->Height = $cfg['CMS']['editorHeight'];
        return $editor->CreateHtml();
    }
}

?>
