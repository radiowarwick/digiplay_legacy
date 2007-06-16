<?PHP
/**
 * @package Session
 */
include_once($cfg['Logger']['dir']['root'] . '/BasicLogger.class.php');
include_once($cfg['Logger']['dir']['root'] . '/LoggedException.class.php');
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');


/**
 * A class for implementing persistant sessions
 * 
 * 
 * @todo Implement session value caching
 * @todo IP address should only be validated on the first 24 bits
 */
class Session {
	
	/**
	 * The array of cookie data supplied by the super global $_COOKIE
	 * @var array
	 * @access private
	 */
	private $cookie;
	/**
	 * The user agent string passed from the browser
	 * @var string
	 * @access private
	 */
	private $useragent;
	/**
	 * The IP address of the user
	 * @var string
	 * @access private
	 */
	private $ip;
	/**
	 * True if a new session was created, false if the users session 
	 * already exists
	 * @var boolean
	 * @access private
	 */
	private $sessionIsNew = false;
	/**
	 * The ID of this session in the database
	 * @var int
	 * @access private
	 */
	private $sessionID;
	/**
	 * The Cached values for this session
	 * @var array
	 * @access private
	 */
	private $sessionCache = array();
	
	const module = 'Session';
	
	/**
	 * Return the Database object by reference
	 * 
	 * This should be the first method called when using this class. A
	 * Session object will be returned. Internally, this method 
	 * ensures that only one session object  is ever in existance. 
	 * This allows for accessing the session anywhere in the program
	 * using Session::getInstance();
	 * 
	 * @return Session
	 * 
	*/
	public function getInstance(){
		static $objAuth;
		if($objAuth == null){
			$objAuth = new Session();
		}
		return $objAuth;
	}
	/**
	 * Initialise the Session object
	 * 
	 * An existing session is checked for and validated if it exists. If no 
	 * session exists then one will be created. If a valid session exists 
	 * then it will be updated with the new keys for the next request.
	 * 
	 */
	private function __construct(){
		$this->cookie = $_COOKIE;
		if(!isset($_SERVER['HTTP_USER_AGENT']) || !isset($_SERVER['REMOTE_ADDR'])){
			throw new LoggedException('The values $_SERVER[\'HTTP_USER_AGENT\'] and/or $_SERVER[\'REMOTE_ADDR\'] were not set', 0, self::module, 'error');
		}
		$this->useragent = $_SERVER['HTTP_USER_AGENT'];
		$this->ip = $_SERVER['REMOTE_ADDR'];
		if(!$this->exists()){
			$this->sessionIsNew = true;
			$this->sessionID = $this->create();
		}else{
			if($this->isValid()){
				$this->sessionID = $this->cookie['key1'];
				if($cfg['Session']['keypersession'] == 't') {
					$this->update();
				}
			}else{
				$this->destroy();
				$this->sessionIsNew = true;
				$this->sessionID = $this->create();
			}
		}
	}
	/**
	 * Checks the validity of a session
	 * 
	 * Checks the validity of the current session. Returns true if valid,
	 * false if not valid.
	 *
	 * @return boolean
	 */
	public function isValid(){
		global $cfg;
		$db = Database::getInstance($cfg['Session']['dsn']);
		$dbsession = $db->getRow("SELECT sessionid, useragent, rndidentifier, ip, lastaccess FROM sessions WHERE sessionid = '{$this->cookie['key1']}'");
		
		$this->purgeExpiredSessions();
		
		$valid = true;
		//remember to do ip check also
		$correctHash = $this->getHash($dbsession['sessionid'], $dbsession['useragent'], $dbsession['rndidentifier']);
		if($dbsession['useragent'] != $this->useragent){
			$valid = false;
		}elseif($dbsession['rndidentifier'] != $this->cookie['key3']){
			$valid = false;
		}elseif($correctHash != $this->cookie['key2']){
			$valid = false;
		}elseif(!$this->checkIP($dbsession['ip'], $this->ip)){
			$valid = false;
		}elseif(($dbsession['lastaccess'] + $cfg['Session']['lifetime']) < time()) {
			$valid = false;
		}
		return $valid;
		
	}
	
	
	private function checkIP($ipA, $ipB){
		//Check IPs are valid
		if(!ip2long($ipA)){
			throw new LoggedException("An invalid IP was specified ($ipA)", 0, self::module, 'error');
			return false;
		}elseif(!ip2long($ipB)){
			throw new LoggedException("An invalid IP was specified ($ipB)", 0, self::module, 'error');
			return false;
		}else{
			//Ensure IPs are in corrent format
			$ipA = long2ip(ip2long($ipA));
			$ipB = long2ip(ip2long($ipB));
			$aParts = split('.', $ipA);
			$bParts = split('.', $ipB);
			$match = true;
			//Only match the first 3 bytes (24 bits)
			for($i=0; $i<3; $i++){
				if($aParts[$i] != $bParts[$i]){
					$match = false;
				}
			}
			return $match;
		}
		
	}
	
	protected function purgeExpiredSessions(){
		global $cfg;
		
		if($cfg['Session']['deleteExpiredProb'] >= rand(0, 1)){
			$sql = "SELECT sessionid from sessions where lastaccess < ?";
			/*$sql = "DELETE sessions, sessionvalues
			        FROM sessions, sessionvalues 
			        WHERE sessions.sessionid = sessionvalues.sessionid 
			        AND sessions.lastaccess < ?";
			*/
			$db = Database::getInstance($cfg['Session']['dsn']);
			
			$result = $db->getAll($sql, array(gmmktime() - $cfg['Session']['lifetime']));

			foreach ($result as $row) {
				$sesID = $row['sessionid'];
				$where = "sessionid = " . $sesID;
				$db->delete('sessionvalues', $where, true);
				$db->delete('sessions', $where, true);
			}
			BasicLogger::logMessage("Purged expired sessions", self::module, 'notice');
		}
		
	}
	
	/**
	 * Determine if a session is new
	 * 
	 * Returns true if a new session was created for this request, rather 
	 * than loading an existing session.
	 *
	 * @return boolean True if session is new, false if loaded from cookie
	 */
	public function isSessionNew(){
		return $this->sessionIsNew;
	}
	
	/**
	 * Check if a session exists
	 * 
	 * Detects if a session already exists within the cookie data passed 
	 * from the browser
	 * 
	 * @return boolean True if session has been passed in cookie data, false if not.
	 */
	private function exists() {
		return isset($this->cookie['key1']) && isset($this->cookie['key2']);
	}
	
	/**
	 * Update session keys
	 * 
	 * Will update the session keys in the database and cookie for the next request.
	 * This provides added security checks as keys can be monitored between requests.
	 * 
	 */
	private function update(){
		global $cfg;
		$rndidentifier = $this->getRandomString();
		//update random identifier in database
		$db = Database::getInstance($cfg['Session']['dsn']);
		$updates = array('rndidentifier' => $rndidentifier);
		$db->update('sessions', $updates, "sessionid = '{$this->sessionID}'");
		
		//update random identifier in cookie
		$md5 = $this->getHash($this->sessionID, $this->useragent, $rndidentifier);
		setcookie('key2', $md5, time() + $cfg['Session']['lifetime'], $cfg['Session']['path'], $cfg['Session']['domain']);
		setcookie('key3', $rndidentifier, $cfg['Session']['lifetime'] + time(), $cfg['Session']['path'], $cfg['Session']['domain']);
	}
	
	/**
	 * Create a new session
	 * 
	 * Will set cookied values and create database entries for a new session.
	 * 
	 * @return int The sessionID of the new session.
	 */
	private function create(){
		global $cfg;
		//Insert into DB
		$db = Database::getInstance($cfg['Session']['dsn']);
		$rndidentifier = $this->getRandomString();
		$values = array('sessionid' => '#id#',
		                'useragent' => $this->useragent,
		                'ip' => $this->ip,
		                'rndidentifier' => $rndidentifier,
		                'lastaccess' => gmmktime());
		$sessionid = $db->insert('sessions', $values);
		
		//Store cookie
		$md5 = $this->getHash($sessionid, $this->useragent, $rndidentifier);
		
		setcookie('key1', $sessionid, time() + $cfg['Session']['lifetime'], $cfg['Session']['path'], $cfg['Session']['domain']);
		setcookie('key2', $md5, time() + $cfg['Session']['lifetime'], $cfg['Session']['path'], $cfg['Session']['domain']);
		setcookie('key3', $rndidentifier, time() + $cfg['Session']['lifetime'], $cfg['Session']['path'], $cfg['Session']['domain']);		
		return $sessionid;
		
	}
	
	/**
	 * Destroys the current session
	 * 
	 * Will delete the client cookie and remove the session entries from 
	 * the database. Don't forget to create a new session if you do this.
	 * 
	 * @return boolean Returns false if the database removal fails, true otherwise.
	 */
	public function destroy(){
		global $cfg;
		$removedFromDB = true;
		$db = Database::getInstance($cfg['Session']['dsn']);
		if(isset($this->sessionID)){
			try{
				$db->delete('sessions', "sessionid = '{$this->sessionID}'");
			}catch(Exception $e){
				$removedFromDB = false;
			}
		}

		setcookie('key1', false);
		setcookie('key2', false);
		setcookie('key3', false);
		return $removedFromDB;
	}
	
	/**
	 * Get the value of a session variable
	 * 
	 * @param string $key The variable name
	 * @return string Will return the value of the session variable specified by $key
	 */
	public function getValue($key){
		$this->cacheData($key);
        return $this->sessionCache[$key];
	}
	
	/**
	 * Delete a session variable
	 * 
	 * @param string $key The variable name
	 */
	public function removeValue($key){
		global $cfg;
		$db = Database::getInstance($cfg['Session']['dsn']);
		$db->delete('sessionvalues', "sessionid = '{$this->sessionID}' AND skey = '$key'");
	}
	
	/**
	 * Set the value of a session variable
	 * 
	 * {@internal This is done by first calling removeValue and then inserting 
	 * a new field. This method seems to involve the least number of queries.}
	 * @param string $key The variable name
	 * @param string $key The value to be assigned
	 */
	public function setValue($key, $value){
		global $cfg;
		$db = Database::getInstance($cfg['Session']['dsn']);
		$this->removeValue($key);
		//Phil change for pgsql changed from ''valueid' => '#id''
		//also added settype to force the quotes (this stops binary stuff from woring)
		settype($value,"string");
		$row = array('valueid' => '#id#',
			     'sessionid' => $this->sessionID,
			     'skey' => $key,
			     'svalue' => $value);
		$db->insert('sessionvalues', $row);
		$this->sessionCache[$key] = $value;
	}
	
	/**
	 * Determine if a session variable exists
	 * 
	 * @param string $key The variable name
	 * @return boolean True if variable $key exists, false if not.
	 */
	public function keyExists($key){
        $this->cacheData($key);
		return (array_key_exists($key,$this->sessionCache));
	}
	
	/**
	 * Get a random string
	 * 
	 * @return Will return a random string consisting of upper/lower case and digits of length $length
	 * 
	 */
	private function getRandomString($length = 14) {
		mt_srand((double)microtime(true) * 10000);
		$str = '';
		for($i=0;$i<$length;$i++) {
			$x = mt_rand(1,3);
			if($x == 1){
				$str .= chr(mt_rand(48,57));
			}elseif($x == 2){
				$str .= chr(mt_rand(65,90));
			}elseif($x == 3){
				$str .= chr(mt_rand(97,122));
			}
		}
		return $str;
	}
	
	/**
	 * Create a hash for cookie "key2"
	 * 
	 * @param string $sessionid The session id
	 * @param string $useragent The user agent as passed by the browser
	 * @param string $rndstring Random data to be included in the hash
	 * @return An md5 hash
	 * 
	 */
	private function getHash($sessionid, $useragent, $rndstring){
		global $cfg;
		$md5 = md5($sessionid . $useragent . $rndstring . $cfg['Session']['randomdata']);
		return $md5;
	}

	/**
	 * Cache the requests session key value, or all values for given session id
	 *
	 * @param string $key The variable name
	 *
	 */
	private function cacheData($key) {
      global $cfg;
      if(!array_key_exists($key,$this->sessionCache)) {
        if($cfg['Session']['cacheAll'] == true) {
		  $db = Database::getInstance($cfg['Session']['dsn']);
		  $sessionValues = $db->getAll("SELECT skey, svalue FROM sessionvalues WHERE sessionid = '{$this->sessionID}'");
		  unset($sessionCache);
		  foreach($sessionValues as $Value){
            $this->sessionCache[$Value['skey']] = $Value['svalue'];
          }
        } else {
		  $db = Database::getInstance($cfg['Session']['dsn']);
		  $this->sessionCache[$key] = $db->getOne("SELECT svalue FROM sessionvalues WHERE sessionid = '{$this->sessionID}' AND skey = '$key'");
        }
      }
    }
	
}


?>
