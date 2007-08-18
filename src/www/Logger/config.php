<?php

######################
## Logging Config
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
$cfg['Logger']['dsn'] = null;

// The path to the Logger module
$cfg['Logger']['dir']['root'] = $cfg['general']['toolkitRoot'] . '/Logger';

// The path to the LoggerBackends directory within the Logger module
$cfg['Logger']['dir']['backends'] = $cfg['Logger']['dir']['root'] . '/LoggerBackends';

//The priorities for logging, where the top is highest priority.
//Comment out logging methods that you never want used
$cfg['Logger']['priorties'][] = 'Database';
$cfg['Logger']['priorties'][] = 'File';

//The file to log to if 'File' logging method is used.
//This should not be the temp directory if on a shared server, as it is 
//publicly accessable
$cfg['Logger']['File']['logfile'] = '/var/www/logs/testLog'; #CHECK

//The logging level the site should run at. Logged messages with lower 
//priority (as set by $cfg['Logger']['levels']) will not be logged.
$cfg['Logger']['level'] = 'notice';

//The default log level if non was specified
$cfg['Logger']['defaultlevel'] = 'warning';

//The default module name if non was specified
$cfg['Logger']['defaultmodule'] = 'unspecified';

//An array of logging levels. These are addressed by value (not index) 
//from withing the code - so it is recommended that you do not modify 
//this. You should be able to add levels if you are so inclined.
$cfg['Logger']['levels'] = array('debug', 'info', 'notice', 'warning', 'error', 'critical', 'none');

// Set unsafe modules for each logger. Do not touch this unless you know what 
// you are doing! This ensures that infinate logging loops do not occur,
//e.g. The DBAL module cannot connect, so logs an exception to the database, 
//only to find it cannot connect, and so logs another message..........
$cfg['Logger']['unsafe']['Database'] = array('DBAL');
$cfg['Logger']['unsafe']['File'] = array();

?>
