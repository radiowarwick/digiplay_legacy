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
$cfg['DPS']['dsn_web']      = 'pgsql://tcp(dbserver:5433)/rawwww';

$cfg['DPS']['resultLimit'] = 50;
$cfg['DPS']['defaultShowID'] = 0;
$cfg['DPS']['allusersgroupid'] = 1;
$cfg['DPS']['userDirectoryID'] = 7;
$cfg['DPS']['binDirectoryID'] = 3;
$cfg['DPS']['systemUserID'] = 1;
$cfg['DPS']['dir']['root'] = $cfg['general']['toolkitRoot'] . '/DPS';
$cfg['DPS']['dir']['uploadDir'] = $cfg['DPS']['dir']['root'] . "/uploads";
$cfg['DPS']['dir']['scriptsDir'] = "/usr/local/bin";
$cfg['DPS']['playlistInfo'] = array(array('id' => 0,
                                   'name' => 'A'),
								    array('id' => 1,
									'name' => 'B')
									);
$cfg['DPS']['HomeSite'] = $cfg['general']['protocol']
                                            . $cfg['general']['domain'];

$cfg['DPS']['file'] = "00000000";
$cfg['DPS']['fileR'] = "10000000";
$cfg['DPS']['fileW'] = "01000000";
$cfg['DPS']['fileO'] = "00100000";
$cfg['DPS']['fileRW'] = "11000000";
$cfg['DPS']['fileRWO'] = "11100000";

$cfg['DPS']['MusicType'] = "Music";
$cfg['DPS']['JingleType'] = "Jingle";
$cfg['DPS']['AdvertType'] = "Advert";
$cfg['DPS']['PrerecTypeID'] = "Pre-rec";

$cfg['DPS']['MusicTypeID'] = "1";
$cfg['DPS']['JingleTypeID'] = "2";
$cfg['DPS']['AdvertTypeID'] = "3";
$cfg['DPS']['PrerecTypeID'] = "4";
?>
