<?PHP
/**
 * @package Auth
 */
include_once($cfg['Auth']['dir']['root'] . '/AuthBase.class.php');
/**
 * Authentication against a database
 * 
 * This class allows for authentication against an database. This 
 * system is acheived using users, groups, and realms.
 * @todo Futher structure documentation required
 */
class Auth extends AuthBase {
	
	/**
	 * The username to authenticate
	 * @access private
	 * @var String
	 */
	//protected $user;
	/**
	 * Array of groups to which $user belongs.
	 * <i>Never</i> write this variable directly, use {@link setUser}
	 * @access private
	 * @var array
	 */
	//protected $groups;
	/**
	 * The proposed password for $user - i.e. the password to be verrified
	 * @access private
	 * @var string
	 */
	//protected $password;
	/**
	 * True if the user is logged in, false if not.
	 * @access private
	 * @var boolean
	 */
	//protected $loggedIn = false;
	/**
	 * The ID of $user in the database
	 * @access private
	 * @var int
	 */
	//protected $userID;
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
	//private $failureReason = -1;
	
	const module = 'AuthLDAP';
	
	/**
	 * Initialise the Auth object
	 * 
	 * @param string $user The username to login
	 * @param string $password The password (in clear text) to be verrified
	 */
	function __construct(){
		parent::__construct();
	}
	
	/**
	 *
	 * @param string $username The username of the user
	 * @param string $password The plain password (non-md5)
	 * @return boolean True if userexists and user/pass match
	 */
	protected function checkUserPass($username, $password){
		global $cfg;
		//ldapserver
		$ds=@ldap_connect($cfg['Auth']['LDAPDS']);
		$ldapUser = "uid=" . $username . "," . $cfg['Auth']['LDAPsr'];
		if ($ds) { 
			ldap_set_option($ds, LDAP_OPT_PROTOCOL_VERSION, 3);
			$ldapbind = @ldap_bind($ds, $ldapUser, $password);
			ldap_close($ds);
			if($ldapbind) {
				return true;
			} else {
				return false;
			}
		} else {
			BasicLogger::logMessage("Unable to connect to LDAP server",self::module,"notice");
			return false;
		}
	}

	public function checkUserDPSAccess($perm) {
	  global $cfg;
	  $db = Database::getInstance($cfg['DPS']['dsn']);
	  $sql = "SELECT COUNT(*) FROM privilages, groupaccess, groups, groupmembers, users
	    WHERE privilages.name = '" . $perm . "' 
	      AND privilages.id = groupaccess.privilage 
	      AND groupaccess.groupid = groups.id 
	      AND groups.id = groupmembers.groupid 
	      AND groupmembers.userid = users.id
	      AND users.username = '" . pg_escape_string($this->user) . "' 
	      AND users.enabled = 't'";
	  $check = $db->getOne($sql);
	  if($check > 0) {
	    return true;
	  }
	  $sql = "SELECT COUNT(*) FROM privilages, useraccess, users
	    WHERE privilages.name = '" . $perm . "' 
	      AND privilages.id = useraccess.privilage 
	      AND useraccess.userid = users.id 
	      AND users.username = '" . pg_escape_string($this->user) . "' 
	      AND users.enabled = 't'";
	  $check = $db->getOne($sql);
	  if($check > 0) {
	    return true;
	  }
	  return false;
	  
	}
}
