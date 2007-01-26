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
$cfg['Auth']['LDAPDS']="ldapserver";
$cfg['Auth']['LDAPsr']="ou=people,dc=radio,dc=warwick,dc=ac,dc=uk";
//The path to the Auth module
$cfg['Auth']['dir']['root'] = $cfg['general']['toolkitRoot'] . '/Auth';

//The maximum idle time before a user is logged out (in seconds)q
$cfg['Auth']['lifetime'] = 1800;

//The name of the template to be used for displaying permission errors. This is either a file name
//or a template id. This must not contain sensitive information as it is 
//not always secured
$cfg['Auth']['permissionErrorTemplate'] = 'dpspermissionError.tpl';

//The module in which the "permissionErrorTemplate" resides
$cfg['Auth']['permissionErrorTemplateModule'] = 'tkfecommon';

//The name of the template to be used for displaying permission errors. This is either a file name
//or a template id. This must not contain sensitive information as it is 
//not always secured
$cfg['Auth']['rendererPermissionErrorTemplate'] = 'rPermissionError.tpl';

//It is possible to add columns to the Auth tables to store extra data.
//The arrays below store a list of these extra fields that you wish to be
//editable in the front end for the Auth module. The key is the field name,
//the value is a user friendly name.       

//The anonymous user for the site. This user account is what non-loggedin users
//browse as.
//$cfg['Auth']['anonuser'] = 'visitor';
$cfg['Auth']['anonuser'] = 'guest';
//$cfg['Auth']['anonuserID'] = 2;
$cfg['Auth']['anonuserID'] = -1;
//redirect user to login if they fail auth and are logged in as the guest account (y/n)
$cfg['Auth']['anonuserredirect'] = 'y';
//template to redirect users from above too
$cfg['Auth']['anonuserRedirectTemplateID'] = 46;
//Editable fields in the users table
//$cfg['Auth']['userfields'] = array('firstname' => 'First Name',
//                                   'lastname'  => 'Last Name',
//                                   'username' => 'Username');
$cfg['Auth']['userfields'] = array();

//Editable fields in the groups table
$cfg['Auth']['groupfields'] = array('name' => 'Group Name',
                                   'description' => 'Description');

//Editable fields in the realms table
$cfg['Auth']['realmfields'] = array('name' => 'Realm Name',
                                    'description' => 'Description');   

$cfg['Auth']['authClassModule'] = 'Auth';
$cfg['Auth']['authUtilClassModule'] = 'AuthUtil';

$cfg['Auth']['defaultNewUserGroup'] = 2;
?>
