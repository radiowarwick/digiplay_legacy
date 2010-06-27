<?php

######################
## Auth Config
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
$cfg['Auth']['dsn']     = null;

// The specific authentication mechanism to use (AuthDB, AuthLDAP)
$cfg['Auth']['authClassModule'] = 'AuthDB';

// The auth utilities module to use (AuthUtil)
$cfg['Auth']['authUtilClassModule'] = 'AuthUtil';

// === LDAP Authentication options ===
// The hostname of the LDAP server to use (e.g. ldap.example.com)
$cfg['Auth']['LDAPDS']="ldapserver";
// The LDAP DN where the required user entries are found
$cfg['Auth']['LDAPsr']="ou=People,dc=example,dc=com";
// ===================================

//The path to the Auth module
$cfg['Auth']['dir']['root'] = $cfg['general']['toolkitRoot'] . '/Auth';

//The maximum idle time before a user is logged out (in seconds)
$cfg['Auth']['lifetime'] = 600;

// The name of the template to be used for displaying permission errors. This is
// either a file name or a template id. This must not contain sensitive
// information as it is not always secured
$cfg['Auth']['permissionErrorTemplate'] = 'dpspermissionError.tpl';

// The module in which the "permissionErrorTemplate" resides
$cfg['Auth']['permissionErrorTemplateModule'] = 'tkfecommon';

// The name of the template to be used for displaying permission errors. This
// is either a file name or a template id. This must not contain sensitive
// information as it is not always secured
$cfg['Auth']['rendererPermissionErrorTemplate'] = 'rPermissionError.tpl';

// It is possible to add columns to the Auth tables to store extra data.
// The arrays below store a list of these extra fields that you wish to be
// editable in the front end for the Auth module. The key is the field name,
// the value is a user friendly name.       

// The anonymous user for the site. This user account is what non-loggedin users
// browse as.
$cfg['Auth']['anonuser'] = 'Guest';
$cfg['Auth']['anonuserID'] = 2;
// redirect user to login if they fail auth and are logged in as the guest
// account (y/n)
$cfg['Auth']['anonuserredirect'] = 'y';
// template to redirect users from above too
$cfg['Auth']['anonuserRedirectTemplateID'] = 11;

// Editable fields in the users table
$cfg['Auth']['userfields']  = array('username' => 'Username');

// Editable fields in the groups table
$cfg['Auth']['groupfields'] = array('groupname' => 'Group Name',
                                    'description' => 'Description');

// Editable fields in the realms table
$cfg['Auth']['realmfields'] = array('name' => 'Realm Name',
                                    'description' => 'Description');   

// Default group for new users (1=everyone)
$cfg['Auth']['defaultNewUserGroup'] = 1;

// Admin group id (2)
$cfg['Auth']['AdminGroup'] = 2;

?>
