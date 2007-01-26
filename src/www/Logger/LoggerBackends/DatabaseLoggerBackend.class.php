<?PHP
/**
 * @package Logger
 * @subpackage LoggerBackends
 */
 
include_once($cfg['Logger']['dir']['backends'] . '/LoggerBackend.class.php');
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
/**
 * Log a message to a database
 * 
 * This class is designed to log a message to a database. If 
 * $cfg['Logger']['dsn'] is set then that will be used, otherwise 
 * the database backend's default will be used.
 * 
 * @package Logger
 * @subpackage LoggerBackends
 */
class DatabaseLoggerBackend extends LoggerBackend {
	
	protected $dsn;
	
	/**
	 * Construct the object
	 * 
	 * Decides which DSN to use
	 */
	public function __construct(){
		global $cfg;
		
		//Check that it works. This is important as exceptions are detected.
		Database::getInstance($cfg['Logger']['dsn']);
	}
	
	/**
	 * Store a log message to the database
	 * 
	 * @param string $message The message to be logged
	 * @param string $module The module associated with the message
	 * @param string $severity The severity of the message
	 * @param string $notes Extra information about the message (e.g. stack traces)
	 */
	public function logMessage($message, $logLevel = null, $module = null, $notes = ''){
		global $cfg;
		
		$db = Database::getInstance($this->dsn);
		$row['entryid'] = '#id#';
		$row['message'] = $message;
		$row['level'] = $logLevel;
		$row['module'] = $module;
		$row['notes'] = $notes;
		$db->insert('logentries', $row);
	}
}

?>