Testing <br>
<?php
include('./config.php');

//Checking ['CMS']['dsn']
if(!isset($cfg['DBAL']['dsn']) && !isset($cfg['CMS']['dsn'])){
	$cfgCheck['CMS']['dsn'] = "Failed: There is no default (DBAL.dsn) dsn configure, you must therefore provide one here, or set up a default";
}else{
	$cfgCheck['CMS']['dsn'] = "Passed";
}

//Checking ['CMS']['dir']['root']
if(!file_exists($cfg['CMS']['dir']['root'])){
	$cfgCheck['CMS']['dir']['root'] = "Failed: The directory does not seem to exist. I was looking here: " . $cfg['CMS']['dir']['root'];
}else{
	$cfgCheck['CMS']['dir']['root'] = "Passed";
}

//Checking $cfg['CMS']['fckPath']
$path = $cfg['CMS']['fckPath'];
if(!file_exists($path)){
	$cfgCheck['CMS']['fckPath'] = "Failed: The directory does not seem to exist. I was looking here: $path";
}elseif (!file_exists("$path/fckeditor.php")){
	$cfgCheck['CMS']['fckPath'] = "Failed: The fckeditor.php file not seem to exist. fckconfig.js and fckeditor.js should also be in that directory. I was looking here: $path/fckeditor.php";
}else{
	$cfgCheck['CMS']['fckPath'] = "Passed";
}
unset($path);

//Checking ['CMS']['fckURL']
$path = $cfg['CMS']['fckURL'];
$exists = @file($path);
if(!$exists){
	$cfgCheck['CMS']['fckURL'] = "Failed: This setting does not seem to be correct. An error was encountered when trying to access $path";
}else{
	$cfgCheck['CMS']['fckURL'] = "Passed";
}
unset($path, $exists);

//Checking ['CMS']['configURL']
$path = $cfg['CMS']['configURL'];
$exists = @file($path);
if(!$exists){
	$cfgCheck['CMS']['fckURL'] = "Failed: This setting does not seem to be correct. An error was encountered when trying to access $path";
}else{
	$cfgCheck['CMS']['fckURL'] = "Passed";
}
unset($path, $exists);
?>
