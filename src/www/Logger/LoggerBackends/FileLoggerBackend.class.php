<?PHP

/**
 * @package Logger
 * @subpackage LoggerBackends
 */

include_once($cfg['Logger']['dir']['backends'] . '/LoggerBackend.class.php');

class FileLoggerBackend extends LoggerBackend {
	
	protected $file;
	protected $fileHandle;
	
	/**
	 * Construct the object
	 * 
	 * Will throw an excpetion if $cfg['Logger']['File']['logfile'] is not defined
	 */
	public function __construct(){
		global $cfg;
		if(isset($cfg['Logger']['File']['logfile'])){
			$this->file = $cfg['Logger']['File']['logfile'];
		}else{
			//Don't throw a logged exception!!!
			throw new Exception("No log file specified in the configuration file");
		}
		$this->fileHandle = @fopen($this->file, 'a+');
		if(!is_resource($this->fileHandle)){
			//Don't throw a logged exception!!!
			throw new Exception("Failed to open log file '{$this->file}' for writing.");
		}
	}
	
	/**
	 * Append a log message to the text file
	 * 
	 * Note: Although a $notes parameter is avaliable, notes will not be 
	 * stored to a text file.
	 * 
	 * @param string $message The message to be logged
	 * @param string $module The module associated with the message
	 * @param string $severity The severity of the message
	 * @param string $notes Extra information about the message (e.g. stack traces)
	 * @internal Notes are not saved - this is intentional. A text file is too limited for this feature.
	 */
	public function logMessage($message, $logLevel = null, $module = null, $notes = ''){
		
		$time = strftime('%x %X', time());
		
		$line = "$time\t$logLevel\t$module\t$message\n";
		
		fwrite($this->fileHandle, $line);
	}
}

?>