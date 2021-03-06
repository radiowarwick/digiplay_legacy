<?PHP
$cfg = array();

######################
## General Config
######################

// The settings in this section concern general site-wide information. 


/*
 * An example for the $cfg['general']['domain'] and 
 * $cfg['general']['siteRoot'] settings:
 * If the url to your site is:
 * http://hosts.companyname.com/path/to/my/site
 * then the settings should be set as follows:
 * $cfg['general']['domain'] = 'hosts.companyname.com'
 * $cfg['general']['siteRoot'] = '/path/to/my/site'
 * 
 * Also, if (for some odd reason) the url to your site must end in a file name 
 * then this should be appended to $cfg['general']['siteRoot']. Eg:
 * $cfg['general']['siteRoot'] = '/path/to/my/site/mypage.php'
 */
$cfg['general']['domain'] = '127.0.0.1'; #CHECK

/*
 * This is the path to the site. For example, if the url to your index.php 
 * file is:
 * http://www.mysite.com/toolkit/
 * then this would be set to:
 * /toolkit/
 * 
 * Note: This is may be overidden by different config files if required
*/
$cfg['general']['siteRoot'] = '/'; #CHECK

//The protocol to be used. Normally 'http://' (or 'https://' if using SSL)
$cfg['general']['protocol'] = 'http://'; #CHECK

// The path to the toolkit root directory
$cfg['general']['toolkitRoot'] = '/path/to/the/toolkit/directory'; #CHANGE

// The URL to the toolkit. This will need to be changed if 
// $cfg['general']['siteRoot'] ends in a file name (because this 
// option should specifiy the directory)
$cfg['general']['toolkitRootURL'] = $cfg['general']['protocol'] . $cfg['general']['domain'] . $cfg['general']['siteRoot'];

######################
## Module Config
######################

//This section specifies which modules are to be loaded.

//Place any optional modules here
//$cfg['modules'][] = 'CMS';
//$cfg['modules'][] = 'TKFile';
//$cfg['modules'][] = 'TKWiki';

//Core modules, do not remove any lines
$cfg['modules'][] = 'DBAL'; //Needs to be first due to use in config checking
$cfg['modules'][] = 'MVC';
$cfg['modules'][] = 'Logger';
$cfg['modules'][] = 'Session';
$cfg['modules'][] = 'Auth';
$cfg['modules'][] = 'tkfecommon';

//Place any optional modules here
//$cfg['modules'][] = 'CMS';
//$cfg['modules'][] = 'TKWiki';
//$cfg['modules'][] = 'TKFile';

###################################
## DO NOT MODIFY BELOW THIS LINE ##
###################################

//Include config files in other modules
foreach($cfg['modules'] as $module){
	$cfgFile = $cfg['general']['toolkitRoot'] . '/' . $module . '/config.php';
	
	if (file_exists($cfgFile)) {
		include_once($cfg['general']['toolkitRoot'] . '/' . $module . '/config.php');
	}
}

######################################
## DO NOT PLACE ANYTHING BELOW HERE ##
######################################
?>