<?php

include_once('Database.class.php');

//$cfg['DBAL']['dsn']
if(!is_null($cfg['DBAL']['dsn'])){
	$cfgCheck['DBAL']['dsn'] = "Success";
	try {
		$db = Database::getInstance($cfg['DBAL']['dsn']);
	}catch (Exception $e){
		$cfgCheck['DBAL']['dsn'] = "Faild: Database connect failed when using \$cfg['DBAL']['dsn']";
	}
}else{
	$cfgCheck['DBAL']['dsn'] = "Success: However, no default DSN was specified so each module will need any dsn options setting.";
}

//checking $cfg['DBAL']['dir']['root']
if(!file_exists($cfg['DBAL']['dir']['root'])){
	$cfgCheck['DBAL']['dir']['root'] = "Failed: Could not find the specified directory ({$cfg['DBAL']['dir']['root']})";
}else{
	$cfgCheck['DBAL']['dir']['root'] = "Success";
}

?>