<?PHP
/**
 * @package Logger
 *
 */
 
include_once($cfg['Logger']['dir']['backends'] . '/DatabaseLoggerBackend.class.php');
include_once($cfg['Logger']['dir']['backends'] . '/FileLoggerBackend.class.php');

/**
 * Class to be used for basic logging
 * 
 * Simply use by statically calling {@link logMessage}, 
 * e.g. BasicLogger::logMessage(...). 
 * 
 * @example logger.eg.php A simple logging example
 * @package Logger
 */
class BasicLogger {
	
	/**
	 * Return the loaded backend instance
	 * @return mixed An object based upon the LoggerBackend abstract class
	 */
	protected static function getInstance(){
		
		static $objBasicLogger;
		
		if(!isset($objBasicLogger)){
			//get a logger backend object
			$objBasicLogger = self::getClass();
		}
		return $objBasicLogger;
	}
	
	/**
	 * Return an object extended from the LoggerBackend object.
	 * 
	 * This class works through the $cfg['Logger']['priorties'] array 
	 * trying to initialise each backend listed. The first backend that 
	 * initialises without issues will be returned. <p>
	 * 
	 * The reason for this method is to create fault tolerance. If an 
	 * error is logged to state the database cannout be found, there is 
	 * no point in trying to log to the database.
	 * 
	 * @return mixed An object based upon the LoggerBackend abstract class. Will return false if no backend could be initialised
	 */
	protected static function getClass(){
		global $cfg;
		foreach($cfg['Logger']['priorties'] as $loggerClass){
			if(!isset($objBasicLogger)){
				try{
					if(class_exists($loggerClass . 'LoggerBackend')){
						eval("\$objBasicLogger = new {$loggerClass}LoggerBackend();");
					}
				}catch (Exception $e){
					
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
	 * Return the module name, default returned if not set.
	 * 
	 * Each message is logged with the module name in which it occurred. If no 
	 * module is specified then the default is used. This function does this - 
	 * it returns the default module module if not set. <p>
	 *
	 * @param string $module The name of the module
	 * @return string the name of the module, the default if $module was empty
	 *
	 */
	protected static function checkModule($module){
		global $cfg;
		if($module == null){
			$module = $cfg['Logger']['defaultmodule'];
		}
		return $module;
	}
	
	/**
	 * Return the message severity, default returned if not set.
	 * 
	 * Each message is logged with its severity. If no severity is specified (or 
	 * is not listed in $cfg['Logger']['levels']) then the default is used. 
	 * This function does this - it returns the default severity if 
	 * not set. <p>
	 *
	 * @param string $severity The severity of the message
	 * @return string the severity of the message, the default if $severity 
	 *
	 */
	protected static function checkLogLevel($severity){
		global $cfg;
		if($severity == null || !in_array($severity, $cfg['Logger']['levels'])){
			$severity = $cfg['Logger']['defaultlevel'];
		}
		return $severity;
	}
	
	/**
	 * Determine if the message should be logged
	 * 
	 * Returns false if the message severity ($severity) is lower than that 
	 * specified in $cfg['Logger']['level'].
	 * 
	 * @return boolean True if the message should be logged
	 */
	protected static function shouldMessageBeLogged($severity){
		global $cfg;
		$msgIndex = array_search($severity, $cfg['Logger']['levels']);
		$rqdIndex = array_search($cfg['Logger']['level'], $cfg['Logger']['levels']);
		return ($msgIndex >= $rqdIndex);
	}
	
	/**
	 * Log a message
	 * 
	 * Will log the message if a backed can be initialised and the severity 
	 * is equal to or greater than $cfg['Logger']['level'].
	 *
	 * @param string $message The message to be logged
	 * @param string $module The module associated with the message
	 * @param string $severity The severity of the message (possible values set by $cfg['Logger']['levels'])
	 */
	public static function logMessage($message, $module = null, $severity = null){
		$log = self::getInstance();
		if($log !== false){
			$module = self::checkModule($module);
			$severity = self::checkLogLevel($severity);
			if(self::shouldMessageBeLogged($severity)){
				$log->logMessage($message, $severity, $module);
			}
		}
	}
}

?>