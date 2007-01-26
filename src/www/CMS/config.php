<?php

######################
## CMS Config
######################

/*
 * These are the DSNs for each module. If a value is set to null 
 * then the default value will be used ($cfg['DBAL']['dsn']), 
 * and therefore it must be set.
 * 
 * For information on DSNs please see: 
 * http://pear.php.net/manual/en/package.database.db.intro-dsn.php
 *
 */
$cfg['CMS']['dsn'] = null;

//The path to the CMS module
$cfg['CMS']['dir']['root'] = $cfg['general']['toolkitRoot'] . '/CMS';

//The path to the FCKeditor directory
$cfg['CMS']['fckPath'] = '/var/www/FCKeditor'; #CHANGE

//The URL of the FCKEditor directory
$cfg['CMS']['fckURL'] = 'https://www.radio.warwick.ac.uk/dps/FCKeditor'; #CHANGE

//Custom config file url
$cfg['CMS']['configURL'] = $cfg['general']['toolkitRootURL'] . '/CMS/cmsconfig.js'; #CHECK

	//You can overide the above setting, and specify a 'configURL' in a 
	//different module by using this setting. If for example, you specify 
	//TKWiki here, then the $cfg['TKWiki']['configURL'] setting will be used 
	//instead of $cfg['CMS']['configURL']. By default, this should be 
	//left as 'CMS'
	$cfg['CMS']['configURLModule'] = 'CMS';

//Toolbars which can be assumed to be present in the FCKeditor config file.
//By default, the config file is cmsconfig.js
$cfg['CMS']['availableToolbars'] = array('cms_full', 'cms_safe', 'cms_simple', 'cms_none');

//If true, this option will always show the editor if the user has permission to edit.
//If set to false, the editor can be shown by passing edit=1 in the query string
$cfg['CMS']['showEditorByDefault'] = true;

//The height of the editor
$cfg['CMS']['editorHeight'] = 400;
?>
