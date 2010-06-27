<?PHP
/**
 * @package Logger
 */
include_once($cfg['Logger']['dir']['root'] . '/ExceptionLogger.class.php');

/**
 * 
 * An exception that interfaces with the logger
 * 
 * The purpose of this class is to extend the standard exception to 
 * allow for the simple logging of thrown exceptions. Even if an 
 * exception is uncaught, it will still be logged (assuming it meets
 * the requirements in the config file)
 * 
 * @package Logger
 * 
 */
class LoggedException extends Exception {
	
	/**
	 * Construct the parent and call the logger
	 * 
	 * @param string $message An explanatory message explaining why the exception was thrown
	 * @param int $code The error code for the exception. Zero is the default
	 * @param string $module The module to which the exception applies
	 * @param string $severity The severity of the error. Possible values defined in $cfg['Logger']['levels']
	 *  
	 */
	public function __construct($message = null, $code = 0, $module = null, $severity = null){
		ExceptionLogger::logMessage($this, $module, $severity);
		parent::__construct($message, $code);
	}
}

?>