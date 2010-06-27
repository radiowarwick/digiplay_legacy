<?php
/** 
 * @package Auth
 *
 */

include_once($cfg['Auth']['dir']['root'] . '/AuthUtilBase.class.php');

/**
 * The default AuthUtil class
 * 
 * This class simply extends AuthUtilBase, makeing no changes. 
 * It needs to be here to allow the $cfg['Auth']['authClassModule'] 
 * config option to function properly.
 * 
 */
class AuthUtil extends AuthUtilBase {
	
	
}


?>