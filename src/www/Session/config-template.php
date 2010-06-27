<?php

######################
## Session Config
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
$cfg['Session']['dsn']  = null;

// The path to the Session module
$cfg['Session']['dir']['root'] = $cfg['general']['toolkitRoot'] . '/Session';

//The domain which sessions should be restricted to. If you are using the 
//Session module for mySite.virtualHost.com, this should be 
//mySite.virtualHost.com, *not* virtualHost.com. This prevents other 
//sites reading/writing your cookies.
$cfg['Session']['domain'] = $cfg['general']['domain'];

//The path that sessions should be restricted to. If you site is hosted 
//under a directory, then this should be set to that directory. This 
//prevents other sites reading/writing your cookies
$cfg['Session']['path'] = '/';

//The lifetime of each session in seconds. If you are very security 
//concious you should should set this to the lowest possible, but 
//this is not essential
$cfg['Session']['lifetime'] = 3600;

//Random data used in storing of session data in cookies. Please change this 
//for each install that your perform.
$cfg['Session']['randomdata'] = 'g9YU9Cnbt3xvL0jrZKr3v5xoW2pLhCpzDc'; #CHANGE

//If true, all session data is retrieved on first access of session data.
//This should be set to false if a large quantity of session data is stored.
$cfg['Session']['cacheAll'] = true;

//The probability that expired sessions will be removed from the datbase 
//when a request is made. This is a simple way of limiting the database load. 
//A value of 0 will mean that the db is never purged, and 1 will mean it is 
//always purged on each request. The default, 0.01 mean it will be purged 
//every 100 requests on average.
$cfg['Session']['deleteExpiredProb'] = 0.01;

?>