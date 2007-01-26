<?php
/** 
 * @package Auth
 *
 */

include_once($cfg['Auth']['dir']['root'] . '/AuthBase.class.php');

/**
 * The default Auth class
 * 
 * This class simply extends AuthBase, makeing no changes. 
 * It needs to be here to allow the $cfg['Auth']['authClassModule'] 
 * config option to function properly.
 * 
 */
class Auth extends AuthBase {
	
	function __construct(){
		parent::__construct();
	}
}


?>