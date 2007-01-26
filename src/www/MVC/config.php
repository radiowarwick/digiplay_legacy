<?php

######################################
## MVC Config (and Templating config)
######################################

/*
 * These are the DSNs for each module. If a value is set to null 
 * then the default value will be used ($cfg['DBAL']['dsn']), 
 * and therefore it must be set.
 * 
 * For information on DSNs please see: 
 * http://pear.php.net/manual/en/package.database.db.intro-dsn.php
 *
 */
$cfg['MVC']['dsn']      = null;

//The path the MVC module directory
$cfg['MVC']['dir']['root'] = $cfg['general']['toolkitRoot'] . '/MVC';

//It is possible to add columns to the templates table to store extra data.
//The arrays below store a list of these extra fields that you wish to be
//editable in the front end for the MVC module. The key is the field name,
//the value is a user friendly name.
$cfg['MVC']['templatefields'] = array('filename' => 'File Name',
 'modelclassname' => 'Model Class Name',
 'viewerclassname' => 'Viewer Class Name');

######################
## Templating Config
######################

//The path to the Smarty package (download from http://smarty.php.net)
$cfg['smarty']['dir']['root'] = '/var/www/Smarty'; #CHANGE

//The path to the smarty templates that will be used
//Seperate multiple paths with a semi-colon
$cfg['smarty']['templatePath']  = "Auth/templates;";
$cfg['smarty']['templatePath'] .= "CMS/templates;";
$cfg['smarty']['templatePath'] .= "MVC/templates;";
$cfg['smarty']['templatePath'] .= "tkfecommon/templates;";

//The path to the smarty templates that will be used.
//Seperate multiple paths with a semi-colon
//Each path listed will be searched recursively
$cfg['smarty']['recTemplatePath'] = "";

//Default template name to be used if non is specified
$cfg['smarty']['defaultTemplate'] = 'dpshome.tpl';

//The name of the template to be used to handle exceptions
$cfg['smarty']['exceptionTemplateFile'] = 'exception.tpl';

//The name of the module in which the exception template resides
$cfg['smarty']['exceptionTemplateModule'] = 'tkfecommon';

//Renderer exception error message. It may be usefull to change 
//this to somthing more descriptive when debugging.
$cfg['smarty']['rendererExceptionError'] = 'A error has occured';

//The name of the template to be used to handle Renderer exceptions
$cfg['smarty']['RenderedexceptionTemplateFile'] = 'Rexception.tpl';

//Should exception info be shown in the browser when an exception occurs?
//This should be set to false for production sites
$cfg['smarty']['showExceptionInfo'] = true; #CHECK

//Should the execution time for a request be appended to each page?
//This should only realy be used in debugging as it produces invalid html
$cfg['smarty']['showExecTime'] = true; #CHECK

//This will cause smarty's template cache to be cleared each time a 
//request is made. This is usefull in debugging when making many changes, 
//but should be set to false when in production as it results in much 
//better performance.
$cfg['smarty']['debug'] = true; #CHECK

//The directory in which smarty should compile its templates. Write permissions
//are required for this directory. For security reasons, this directory should
//be readable by only the user that apache runs as (i.e. not /tmp).
//Also, it should idealy be outside of the web root.
$cfg['smarty']['compiledir'] = '/var/www/Smarty/tmp'; #CHECK
#$cfg['smarty']['compiledir'] = 'C:/WINNT/Temp';

?>
