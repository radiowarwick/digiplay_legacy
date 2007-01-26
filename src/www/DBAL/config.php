<?PHP

######################
## Database Config
######################

/*
 * This is the default DSN for all modules. This may only be null if all 
 * other modules have a setting for any required DSNs.
 * 
 * For information on DSNs please see: 
 * http://pear.php.net/manual/en/package.database.db.intro-dsn.php
 *
 */
//$cfg['DBAL']['dsn']     = 'pgsql:///dpsdev'; #CHANGEL
$cfg['DBAL']['dsn']     = 'pgsql://www@localhost/digiplaydev';
$cfg['DBAL']['pgsqlhack']     = true;


// The path to the DBAL module
$cfg['DBAL']['dir']['root'] = $cfg['general']['toolkitRoot'] . '/DBAL';

?>
