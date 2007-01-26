<?PHP
/**
 * @package Auth
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['Session']['dir']['root'] . '/Session.class.php');
/**
 * Authentication against a database
 * 
 * This class allows for authentication against an database. This 
 * system is acheived using users, groups, and realms.
 * @todo Futher structure documentation required
 */
class AuthBase {
	
	/**
	 * The username to authenticate
	 * @access private
	 * @var String
	 */
	protected $user;
	/**
	 * Array of groups to which $user belongs.
	 * <i>Never</i> write this variable directly, use {@link setUser}
	 * @access private
	 * @var array
	 */
	protected $groups;
	/**
	 * The proposed password for $user - i.e. the password to be verrified
	 * @access private
	 * @var string
	 */
	protected $password;
	/**
	 * True if the user is logged in, false if not.
	 * @access private
	 * @var boolean
	 */
	protected $loggedIn = false;
	/**
	 * The ID of $user in the database
	 * @access private
	 * @var int
	 */
	protected $userID;
	/**
	 * The reason for a failed auth attempt.
	 * -1  :  No attempt was made
	 *  0  :  Attempt did not fail
	 *  1  :  Invalid username/pass
	 *  2  :  Max idle time exceeded
	 *  3  :  Unknown
	 * @access private
	 * @var int
	 */
	private $failureReason = -1;
	
	const module = 'Auth';
	
	/**
	 * Initialise the Auth object
	 * 
	 * @param string $user The username to login
	 * @param string $password The password (in clear text) to be verrified
	 */
	private function __construct(){
		//$this->user = $user;
		//$this->password = $password;
		Session::getInstance();
		//See if the user is logged on through their session
		$sesLoggedIn = $this->isSessionLoggedIn();
		BasicLogger::logMessage("Checking session for valid login(Auth)", self::module, 'debug');
		if($sesLoggedIn !== false){
			BasicLogger::logMessage("Valid session found, user '$sesLoggedIn' now logged in", self::module, 'debug');
			$this->loggedIn = true;
			$this->setUser($sesLoggedIn);
		} else {
		  BasicLogger::logMessage("No valid session found, user '$sesLoggedIn' now logged in", self::module, 'debug');
		}
	}
	
	/**
	 * Sets/updates the user/userID class variables respectively
	 *
	 * @param string $username The username to be stored
	 */
	private function setUser($username){
		$this->user = $username;
		if(is_null($username)){
			$this->userID = null;
		}else{
			$this->userID = AuthUtil::getUserID($username);
		}
	}
	
	/**
	 * Return the Auth object by reference
	 * 
	 * This should be the first method called when using this class. An
	 * Auth object will be returned. Internally, this method 
	 * ensures that only one Auth object  is ever in existance. 
	 * This allows for accessing the session anywhere in the program
	 * using Session::getInstance();
	 *
	 * @param string $password The clear text password associated with the username
	 * 
	 */
	public static function getInstance(){
		
		static $authObj;
		
		if($authObj == null){
			$authObj = new Auth();
		}
		
		return $authObj;
	}
	
	public function isSessionLoggedIn(){
		$sess = Session::getInstance();
		if($sess->keyExists('auth_user')){
			return $sess->getValue('auth_user');
		}else{
			return false;
		}
	}
	
	//True if username/password is valid. False otherwise
	public function attemptLogin($user = null, $password = null){
		$this->setUser($user);
		$this->password = $password;
		
		global $cfg;
		$loggedIn = false;
		$this->failureReason = 0;
		
		$sess = Session::getInstance();
		
		//If this is the anon user then login without checking
		if($this->user == $cfg['Auth']['anonuser']){
			
			$sess->setValue('auth_user', $cfg['Auth']['anonuser']);
			$this->loggedIn = true;
			//Set login_time session value
			$sess->setValue('auth_lastRequestTime', gmmktime());
			return true;
		}else{
			//Dont both trying to login if user or pass is not passed set
			if(!is_null($this->user) && !is_null($this->password)){

				if($this->checkUserPass($this->user, $this->password)){
					BasicLogger::logMessage("Setting session vars for user '{$this->user}'", self::module, 'debug');
					//Set auth_user session value
					if($sess->keyExists('auth_user')) {
						BasicLogger::logMessage($sess->getValue('auth_user'),self::module,"debug");	
					}
					$sess->setValue('auth_user', $this->user);
					if($sess->keyExists('auth_user')) {
						BasicLogger::logMessage($sess->getValue('auth_user'),self::module,"debug");	
					}
					//Set login_time session value
					$sess->setValue('auth_lastRequestTime', gmmktime());
					$loggedIn= true;
				}else{
					//Login failed. Attempt login without new user data.
					//This will either log the user in as the anon user, 
					//or based upon session data
					$this->attemptLogin();
					$this->failureReason = 1;
				}
			//Check that session has not been inactive for too long
			}elseif ($sess->getValue('auth_lastRequestTime') <  gmmktime() - $cfg['Auth']['lifetime']){
				BasicLogger::logMessage("Session timed out",self::module,"notice");
				//...if it has then delete session vars
				$sess->removeValue('auth_user');
				$sess->removeValue('auth_lastRequestTime');
				
				$this->attemptLogin($cfg['Auth']['anonuser']);
				//Not requested, but just to be explicit, set loggedIn to false.
				$loggedIn = false;
				$this->failureReason = 2;
			//Check to see if user has been previous authenticated during session
			}elseif($this->isSessionLoggedIn()){
				BasicLogger::logMessage("Logging in based on session data - {$sess->getValue('auth_user')}",self::module,"debug");
				//Store username to class variable for other methods to use
				$this->setUser($sess->getValue('auth_user'));
				$sess->setValue('auth_lastRequestTime', gmmktime());
				$loggedIn = true;
			}else{
				BasicLogger::logMessage("uncaught auth failure in attempt login",self::module,"notice");
				//Uncaught failure reason
				$this->failureReason = 3;
			}
			$this->loggedIn = $loggedIn;
			return $loggedIn;
		}
	}
	/**
	 *
	 * @param string $username The username of the user
	 * @param string $password The plain password (non-md5)
	 * @return boolean True if userexists and user/pass match
	 */
	protected function checkUserPass($username, $password){
		$md5pass = md5($password);
		$sql = "SELECT COUNT(*) FROM users WHERE username = '{$username}' AND password = '{$md5pass}'";
		$db = Database::getInstance();
		$validCount = $db->getOne($sql);
		
		return ($validCount == 1);
	}
	
	/**
	 * Get the reason for a failed login attempt. Return values are:
	 *  0  :  Attempt did not fail
	 *  1  :  Invalid username/pass
	 *  2  :  Max idle time exceeded
	 *  3  :  Unknown
	 * 
	 * @return int Failure code
	 */
	public function getFailureReason(){
		return $this->failureReason;
	}
	
	public function isLoggedIn(){
		return $this->loggedIn;
	}
	
	public function logout(){
    global $cfg;
		$sess = Session::getInstance();
		$sess->removeValue('auth_user');
		$this->attemptLogin($cfg['Auth']['anonuser']);
	}
	
	/**
	 * 
	 * @param array $realmPath A path to the realm to which access should be checked. E.g. ('admin', 'modify')
	 * @return boolean True if access is allowed, false if access is denied
	 */
	public function getrealmAccess($realmPath){
		return (AuthUtil::getDetailedUserrealmAccess($realmPath, $this->user) === true);
	}
	
	public function getUserID(){
    global $cfg;
		return $this->userID;
	}
	
	public function getUser(){
    	global $cfg;
		return $this->user;
	}
	
}

?>
