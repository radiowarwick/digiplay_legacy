<?php

include_once($cfg['general']['toolkitRoot'] . '/DBAL/Database.class.php');

//Checking ['DBAL']['dsn']
if(!isset($cfg['DBAL']['dsn']) && !isset($cfg['Auth']['dsn'])){
	$cfgCheck['Auth']['dsn'] = "Failed: There is no default (DBAL.dsn) dsn configure, you must therefore provide one here, or set up a default";
}else{
	$cfgCheck['Auth']['dsn'] = "Passed";
}

//Checking ['Auth']['dir']['root']
if(!file_exists($cfg['Auth']['dir']['root'])){
	$cfgCheck['Auth']['dir']['root'] = "Failed: The directory does not seem to exist. I was looking here: " . $cfg['Auth']['dir']['root'];
}else{
	$cfgCheck['Auth']['dir']['root'] = "Passed";
}

//$cfg['Auth']['lifetime'] - unchecked
//$cfg['Auth']['permissionErrorTemplate'] - unchecked
//$cfg['Auth']['permissionErrorTemplateModule'] - unchecked
//$cfg['Auth']['rendererPermissionErrorTemplate'] - unchecked

//checking $cfgCheck['Auth']['anonuser']
$db = Database::getInstance($cfg['Auth']['dsn']);
$userExists = $db->getOne("SELECT COUNT(*) FROM users WHERE username = '{$cfg['Auth']['anonuser']}'");
if($userExists != 1){
	$cfgCheck['Auth']['anonuser'] = "Failed: The specified anonymous user '{$cfg['Auth']['anonuser']}' could not be found in the users table";
}else{
	$cfgCheck['Auth']['anonuser'] = "Passed";
}

//$cfg['Auth']['userfields'] - unchecked
//$cfg['Auth']['groupfields'] - unchecked
//$cfg['Auth']['realmfields'] - unchecked

//Checking ['Auth']['authClassModule']
$path = $cfg['general']['toolkitRoot'] . $cfg['Auth']['authClassModule'];
if(!file_exists($path . '/Auth.class.php')){
	$cfgCheck['Auth']['authClassModule'] = "Failed: Counld not find the Auth file. I was looking here: $path/Auth.class.php";
}elseif(!file_exists($path . '/AuthUtil.class.php')){
	$cfgCheck['Auth']['authClassModule'] = "Failed: Counld not find the AuthUtil file. I was looking here: $path/AuthUtil.class.php";
}else{
	$cfgCheck['Auth']['authClassModule'] = "Passed";
}

?>