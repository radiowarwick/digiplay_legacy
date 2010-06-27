<?PHP
/**
 * @package Logger
 */
include_once($cfg['Logger']['dir']['root'] . '/BasicLogger.class.php');
include_once($cfg['Logger']['dir']['backends'] . '/DatabaseLoggerBackend.class.php');
include_once($cfg['Logger']['dir']['backends'] . '/FileLoggerBackend.class.php');

/**
 * Class to be used for exception logging
 *
 * To log using this class you simply need to call the 
 * {@link logMessage} method
 *
 * Important: This class must not throw any LoggedException objects as this 
 * can result in infinate recursive loops
 *
 * @example logger.eg.php A simple example of logging
 * 
 * @package Logger
 */

class ExceptionLogger extends BasicLogger {
	
	/**
	 * Return the loaded backend instance
	 * @return mixed An object based upon the LoggerBackend abstract class
	 * @todo duplicated method. Cannot sort out static scope.
	 */
	protected static function getInstance($modulde){
		
		static $objBasicLogger;
		
		if(!isset($objBasicLogger)){
			$objBasicLogger = self::getClass($modulde);
		}
		return $objBasicLogger;
	}
	
	/**
	 * Return an object extended from the LoggerBackend object which is safe for exception logging.
	 * 
	 * {@inheritdoc}<p>
	 * In addition, the module name must not appear in the 
	 * $cfg['Logger']['unsafe'][<i>loggerClassName</i>] array. For example, 
	 * exceptions from the DBAL module, should not be logged with the Database 
	 * backed. This prevents infinate recursion of exceptions, e.g. if there 
	 * was always a connection failure.
	 */
	protected static function getClass($module){
		global $cfg;
		foreach($cfg['Logger']['priorties'] as $loggerClass){
			if(!isset($objBasicLogger)){
				try{
					if(in_array($module, $cfg['Logger']['unsafe'][$loggerClass])){
						throw new Exception("Exception logging for module '$module' is being attempted with a potentially incompatible logging backend ('$loggerClass')");
					}else if(class_exists($loggerClass . 'LoggerBackend')){
						eval("\$objBasicLogger = new {$loggerClass}LoggerBackend();");
					}
				}catch (Exception $e){
					//do nothing
				}
			}
		}
		if(isset($objBasicLogger)){
			return $objBasicLogger;
		}else{
			return false;
		}
	}
	
	/**
	 * Log a message
	 * 
	 * Will log the details of an exception if a backed can be initialised 
	 * and the severity is equal to or greater than $cfg['Logger']['level'].
	 *
	 * @param string Exception The exception to be logged
	 * @param string $module The module associated with the message
	 * @param string $severity The severity of the message
	 */
	public static function logMessage(Exception $exception, $module = null, $severity = null){
		$log = self::getInstance($module);
		if($log !== false){
			$module = parent::checkModule($module);
			$severity = parent::checkLogLevel($severity);
			
			$message = 'Exception: ' . $exception->getMessage();
			
			$notes  = "Error Code: " . $exception->getCode() . "\n";
			$notes .= "File: " . $exception->getFile() . "\n";
			$notes .= "Line: " . $exception->getLine() . "\n";
			$notes .= "Stack Trace:\n" . $exception->getTraceAsString() . "\n";
			
			if(parent::shouldMessageBeLogged($severity)){
				$log->logMessage($message, $severity, $module, $notes);
			}
		}
	}
	
}

?>