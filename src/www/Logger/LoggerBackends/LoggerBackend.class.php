<?PHP
/**
 * @package Logger
 * @subpackage LoggerBackends
 */

/**
 * Abstract backend class
 * 
 * Each backend must extend this class. This ensures a standard interface
 * 
 * @package Logger
 * @subpackage LoggerBackends
 */
abstract class LoggerBackend {
	/**
	 * Store/display/send a log message
	 * 
	 * @param string $message The message to be logged
	 * @param string $module The module associated with the message
	 * @param string $severity The severity of the message
	 * @param string $notes Extra information about the message (e.g. stack traces)
	 */
	public abstract function logMessage($message, $severity = null, $module = null, $notes = '');
	
	
}

?>