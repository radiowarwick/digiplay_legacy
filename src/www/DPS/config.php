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
//$cfg['DPS']['dsn']      = 'pgsql://www@dps0/digiplay';
//$cfg['DPS']['dsn']      = 'pgsql://www@vm4/digiplaydev';

$cfg['DPS']['dsn_web']      = 'pgsql://tcp(dbserver:5433)/rawwww';

$cfg['DPS']['resultLimit'] = 50;
$cfg['DPS']['defaultShowID'] = 0;
$cfg['DPS']['allusersgroupid'] = 2;
$cfg['DPS']['userDirectoryID'] = 5;
$cfg['DPS']['binDirectoryID'] = 6;
$cfg['DPS']['systemUserID'] = 0;
$cfg['DPS']['root'] = $cfg['general']['toolkitRoot'] . '/DPS';
$cfg['DPS']['playlistInfo'] = array(array('id' => 0,
                                   'name' => 'A'),
								    array('id' => 1,
									'name' => 'B')
									);
$cfg['DPS']['HomeSite'] = "https://www.radio.warwick.ac.uk";
?>
