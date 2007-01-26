<?php

//Ensure $cfg has a value
if(!isset($cfg)){
	$cfg = array();
}
//Include the config file
@include_once('config.php');

//Print test message if requested
if(isset($_GET['showTest'])){
	echo "OK";
	exit(0);
}

//Checking ['general']['domain'], ['general']['siteRoot'], ['general']['protocol']
$url = $cfg['general']['protocol'] . 
       $cfg['general']['domain'] . 
       $cfg['general']['siteRoot'] .
       '?showTest=1';
       
$testData = @file($url);
if(!$testData){
	$err = "Failed: The combined URL could not be accessed. I was looking here: $url";
	$cfgCheck['general']['domain'] = $err;
	$cfgCheck['general']['siteRoot'] = $err;
	$cfgCheck['general']['protocol'] = $err;
}else{
	$cfgCheck['general']['domain'] = 'Passed';
	$cfgCheck['general']['siteRoot'] = 'Passed';
	$cfgCheck['general']['protocol'] = 'Passed';
}

//Checking ['general']['toolkitRootURL']
$url = $cfg['general']['toolkitRootURL'] . '/configCheck.txt';
$testData = @file($url);
$testData = str_replace("\n", '', $testData);
if($testData[0] != 'OK'){
	$cfgCheck['general']['toolkitRootURL'] = "Failed: URL could not be found. Note that there should be no file name in this config option";
}else{
	$cfgCheck['general']['toolkitRootURL'] = "Passed";
}
unset($testData);

//Checking ['general']['toolkitRoot'];

$path = $cfg['general']['toolkitRoot'] . '/configCheck.txt';
$exists = file_exists($path);
if(!$exists && !(@file($path) == 'OK')){
	$cfgCheck['general']['toolkitRoot'] = "This setting does not seem to be correct. This was checked check for a value of 'OK' in $path";
}else{
	$cfgCheck['general']['toolkitRoot'] = "Passed";
}
unset($path, $exists);

//Checking ['modules']
$missingMods = array();
foreach($cfg['modules'] as $mod){
	if(!file_exists($cfg['general']['toolkitRoot'] . '/' . $mod)){
		$missingMods[] = $mod;
	}
}
if(count($missingMods) > 0){
	$cfgCheck['modules'] = "The following modules could not be found:" . 
	                        implode(' ', $missingMods) .
	                        ". I was looking for the directories in: " . 
	                        $cfg['general']['toolkitRoot'];
}else{
	$cfgCheck['modules'] = "Passed";
}
unset($missingModsm, $url);



//Include config tests in other modules
foreach($cfg['modules'] as $module){
	$cfgFile = $cfg['general']['toolkitRoot'] . '/' . $module . '/config-tests.php';
	
	if (file_exists($cfgFile)) {
		include_once($cfgFile);
	}
}

?>