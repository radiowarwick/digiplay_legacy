<?php
/**
 * Implemented database abstraction layer
 *
 * This file contains a concrete class for interfacing with an SQL database.
 * This file requires the Pear DB module to be in PHP's include path.
 * @package DBAL
 */
include_once('DB.php');
include_once($cfg['Logger']['dir']['root'] . '/LoggedException.class.php');

/**
 * Database abstraction layer class
 * 
 * This class should be used to interface with an SQL database without the
 * OO abstration provided by the GenericObjectCollection class. 
 * This class requires the Pear DB module to be in PHP's include path.
 * To use this class, you should call the {@link getInstance} method statically.
 * <code>
 * $db = Database::instance();
 * </code>
 * @example database.eg.php An example script using this class
 * @package DBAL
 * 
 */
class Database {
	
	/**
	 * The module of this class, used in debugging
	 */
	const module = 'DBAL';
	
	/**
	 * Contains the DB object for the connection.
	 * @access private
	 * @var DB
	 */
	private $conn;
	
	/**
	 * Contains the total number of querues
	 * @access private
	 * @var int
	 */
	private static $totalQ;
	
	protected static $queryLog;
	
	/**
	 * Construct a new Database class instance
	 * 
	 * This takes a Data Source Name, or DSN, as its primary parameter. The format 
	 * for this may be found on the 
	 * {@link http://pear.php.net/manual/en/package.database.db.intro-dsn.php Pear DB documentation}
	 * 
	 * @param string $dsn The DSN for the required data source
	 * @access private
	 */
	private function __construct($dsn) {
		
		//Open a connection using the info in $dsn
		$this->conn = DB::connect($dsn);
		
		if(DB::isError($this->conn)) {
			//We're not connected.	Throw an exception
			throw new LoggedException($this->conn->getMessage() . " # " . $this->conn->getUserInfo(), $this->conn->getCode(), self::module);
		}
		
		//Always fetch data as an associative array
		$this->conn->setFetchMode(DB_FETCHMODE_ASSOC);
	}
	
	/**
	 * Return the Database object by reference
	 * 
	 * This should be the first method called when using this class. A
	 * Database object will be returned. Internally, this method 
	 * ensures that only one database object per DSN is ever in existance. 
	 * This helps to reduce server load. If $dns is omitted then the 
	 * default DSN specified in the config file is used.
	 * 
	 * @param $dsn The DSN for the required data source
	 * 
	*/
	static public function getInstance($dsn = null) {
		global $cfg;
		static $objDB;
		
		//If nothing was passed in, use the value from $cfg
		if($dsn == null) {
			if(isset($cfg['DBAL']['dsn'])){
				$dsn = $cfg['DBAL']['dsn'];
			}else{
				throw new LoggedException('No default DSN was specified in the config file', 0, self::module);
			}
		}
		
		if(! isset($objDB[$dsn])){
			$objDB[$dsn] = new Database($dsn);
		}
		return $objDB[$dsn];
	}
	
	/**
	 * Execute an SQL select statement
	 * 
	 * This function will execute an SQL select statement and return a DB_result object.
	 * Reference for the DB_result object can be found 
	 * {@link http://pear.php.net/manual/en/package.database.db.db-result.php here}.
	 * 
	 * @param string $sql The SQL code to be executed. Must be a SELECT statement
	 * @return DB_result
	 * 
	*/
	public function getDBResult($sql) {
		$result = $this->conn->query($sql);
		self::logQuery();
		
		if(DB::isError($result)) {
			throw new LoggedException($result->getMessage() . ". SQL: $sql", $result->getCode(), self::module);
		}
		
		return $result;
	}
	
	/**
	 * Return a 2D associative arrary
	 * 
	 * The returned array will be based upon the sql specified by $sql. This is 
	 * basically a wrapper for the 
	 * {@link http://pear.php.net/manual/en/package.database.db.db-common.getall.php DB_common::getAll}
	 * method of the Pear DB module.
	 * 
	 * @param string $sql The SQL code to be executed
	 * @return array
	 * 
	*/
	public function getAll($sql, $data = array()) {
		$result = $this->conn->getAll($sql, $data, DB_FETCHMODE_ASSOC);
		self::logQuery();
		
		if(DB::isError($result)) {
			throw new LoggedException($result->getMessage() . ". SQL: $sql", $result->getCode(), self::module);
		}
		
		return $result;
	}
	
	/**
	 * Returns single scalar value from the first column, first record
	 * 
	 * The returned value will be based upon the sql specified by $sql. This is 
	 * basically a wrapper for the 
	 * {@link http://pear.php.net/manual/en/package.database.db.db-common.getone.php DB_common::getOne}
	 * method of the Pear DB module.
	 * 
	 * @param string $sql The SQL code to be executed
	 * @param array $data If $sql is a paramatised query, then the data for each parameter goes in this array
	 * @return string
	 * 
	*/
	public function getOne($sql, $data = array()) {
		$result = $this->conn->getOne($sql, $data);
		self::logQuery();
		
		if(DB::isError($result)) {
			throw new LoggedException($result->getMessage() . ". SQL: $sql", $result->getCode(), self::module);
		}
		
		return $result;
	}
	
	/**
	 * Returns associative array of values from the first row
	 * 
	 * The returned value will be based upon the sql specified by $sql. This is 
	 * basically a wrapper for the 
	 * {@link http://pear.php.net/manual/en/package.database.db.db-common.getrow.php DB_common::getCol}
	 * method of the Pear DB module, but DB_FETCHMODE_ASSOC is always used.
	 * 
	 * @param string $sql The SQL code to be executed
	 * @param array $data If $sql is a paramatised query, then the data for each parameter goes in this array
	 * @return array
	 * 
	*/
	public function getRow($sql, $data = array()) {
		$result = $this->conn->getRow($sql, $data, DB_FETCHMODE_ASSOC);
		self::logQuery();
		
		if(DB::isError($result)) {
			throw new LoggedException($result->getMessage() . ". SQL: $sql", $result->getCode(), self::module);
		}
		
		return $result;
	}
	
	/**
	 * Returns a numerically indexed 1D array of values from the first column
	 * 
	 * The returned value will be based upon the sql specified by $sql. This is 
	 * basically a wrapper for the 
	 * {@link http://pear.php.net/manual/en/package.database.db.db-common.getcol.php DB_common::getCol}
	 * method of the Pear DB module.
	 * 
	 * @param string $sql The SQL code to be executed
	 * @param array $data If $sql is a paramatised query, then the data for each parameter goes in this array
	 * @return array
	 * 
	*/
	public function getColumn($sql, $col = 0, $data = array()) {
		$result = $this->conn->getCol($sql, $col, $data);
		self::logQuery();
		
		if(DB::isError($result)) {
			throw new LoggedException($result->getMessage() . ". SQL: $sql", $result->getCode(), self::module);
		}
		
		return $result;
	}
	
	/**
	 * Conducts an update without the need to pass SQL code
	 * 
	 * This function will update rows in the the specified table ($tableName) with values specified by 
	 * the array $arUpdates. $arUpdates is associative, where the keys are interpreted as field names.
	 * $sWhere specifies an SQL fragment that, if specified, will form the SQL code following the 'where' 
	 * keyword in the final SQL statement. Use of $sWhere is <b>highly recommended</b> in order to 
	 * avoid modifying the entire table.
	 * 
	 * @param string $tableName The name of the table to update
	 * @param array $arUpdates Associative array of fields/values to be updated
	 * @param string $sWhere An SQL fragment limiting the scope of the update
	 * @return int The number of affected rows
	 * 
	*/
	public function update($tableName, $arUpdates, $sWhere = null, $prepare = true) {

		self::logQuery();
		
		$arSet = array();
		foreach($arUpdates as $name => $value) {
			if($prepare){
				$arSet[] = $name . ' = ?';
			}else{
				if($value == ''){ $value = 'NULL'; }
				$arSet[] = $name . ' = ' . $this->conn->quoteSmart($value);
			}
		}
		$sSet = implode(', ', $arSet);

		//make sure the table name is properly escaped
		$tableName = $this->conn->quoteIdentifier($tableName);	 

		$sql = "UPDATE $tableName SET $sSet";
		if($sWhere) {
			$sql .= " WHERE $sWhere";
		}
		
		if($prepare){
			$res = $this->prepare($sql);
			$result = $this->execute($res, array_values($arUpdates));
		}else{
			$result = $this->conn->query($sql);
		}
		if(DB::isError($result)) {
			throw new LoggedException($result->getMessage(), $result->getCode(), self::module);
		}
		
		//return the number of rows affected
		return $this->conn->affectedRows();
	}
	
	/**
	 * Conducts an insert without the need to pass SQL code
	 * 
	 * This function will insert a row in the the specified table ($tableName) with values specified by 
	 * the array $arUpdates. $arUpdates is associative, where the keys are interpreted as field names.
	 * Field names that appear in the table but not in $arValues will not be specified in the SQL query.
	 * This may cause problems for fields specified as NOT_NULL or similar. If a value of '#id#' is 
	 * specified then this will be assumed to be an auto increment primary key field, causing the new 
	 * id to be returned.
	 * 
	 * @param string $tableName The name of the table to update
	 * @param array $arValues Associative array of fields/values to be inserted
	 * @param bool $prepare Set to false if you do not wish the query to use prepared statements (not recommended)
	 * @return int The next ID if #id# is specified as a value, otherwise the number of affected rows.
	 * 
	*/
	public function insert($tableName, $arValues, $prepare = true) {
		$id = null;
       	 	//echo "<br> called insert: " . $tableName . print_r($arValues);
		self::logQuery();
		$arValueList = array();
		$count = 0;
		foreach($arValues as $key => &$value) {
			if(strtolower($value) == '#id#') {
				//we need to get the next value from this table's sequence
				$value = $id = $this->conn->nextID($tableName . "_" . $key);
				//Fix as values are not updating correctly
				//$id = $this->conn->nextID($tableName . "_id");
				//echo "<br>" . $tableName . "_id : " . $value;
				if(DB::isError($id)) {
					throw new LoggedException($id->getMessage(), $id->getCode(), self::module);
				}
				//array_splice($arValues,$count,1);
			}// else { //else added as part of fix for value insert
				$bin = false;
				if(strtolower(substr($value,0,1)) == "b" && strtolower(substr($value,strlen($value)-1,1)) == "b") {
					if(Database::binaryCheck(substr($value,1,strlen($value)-2))) {
						$bin = true;
					} else {
						$bin = false;
					}
				}
				if($bin) {
					$arValueList[] = "B'" . substr($value,1,strlen($value)-2) . "'";
				} else {
					$arValueList[] = $this->conn->quoteSmart($value);
				}
			//}
			$count++;
		}
		$sFieldList = join(', ', array_keys($arValues));
		$sValueList = implode(', ', $arValueList);
		//make sure the table name is properly escaped
		$tableName = $this->conn->quoteIdentifier($tableName);
		
		if($prepare){
			$questionMarks = array_pad(array(), count($arValues), '?');
			$qmString = join(', ', $questionMarks);
			$sql = "INSERT INTO $tableName ( $sFieldList) VALUES ( $qmString )";
			$resource = $this->prepare($sql);
			$result = $this->execute($resource, array_values($arValues));
			
		}else{
			
			$sql = "INSERT INTO $tableName ( $sFieldList) VALUES ( $sValueList )";
			$result = $this->conn->query($sql);
		
		}
		if(DB::isError($result)) {
			throw new LoggedException($result->getMessage(), $result->getCode(), self::module);
		}
		
		//return the ID, if there was one, or the number of rows affected
		return $id ? $id : $this->conn->affectedRows();
	}
	private static function binaryCheck($var) {
		for($i=0;$i<strlen($var);$i++) {
			if(substr($str,$i,1) != "1" && substr($str,$i,1) != "0") {
				return false;
			}
		}
		return true;
	}
	public function delete($tableName, $sWhere = null){
		$sql = "DELETE FROM $tableName";
		
		if(! is_null($sWhere)){
			$sql .= " WHERE $sWhere";
		}
		
		$result = $this->conn->query($sql);
		self::logQuery();
		
		if(DB::isError($result)) {
			throw new LoggedException($result->getMessage(), $result->getCode(), self::module);
		}
		
		//Ensure the delete count is returned
		$this->conn->setOption('portability', DB_PORTABILITY_DELETE_COUNT);
		
		//return the number of rows affected
		return $this->conn->affectedRows();
		
	}
	
	/**
	 * Sart a transaction
	 * 
	 * This function will start a transaction. All querys after this will form part of the transaction. 
	 * This transaction can be comitted by calling {@link commit}, or aborted by calling {@link abort}
	 * 
	 * @return bool True on success, exception thrown on failure
	 * 
	*/
	public function startTransaction() {
		$result = $this->conn->autoCommit(false);
		if(DB::isError($result)) {
			throw new LoggedException($result->getMessage(), $result->getCode(), self::module);
		}
		return true;
	}
	
	/**
	 * Commit a transaction
	 * 
	 * This function will commit a transaction.
	 * 
	 * @return bool True on success, exception thrown on failure
	 * 
	*/
	public function commit() {
		$result = $this->conn->commit();
		
		if(DB::isError($result)) {
			throw new LoggedException($result->getMessage(), $result->getCode(), self::module);
		}
		
		$this->conn->autoCommit(true);
		return true;
	}
	
	/**
	 * Abort a transaction
	 * 
	 * This function will abort a transaction.
	 * 
	 * @return bool True on success, exception thrown on failure
	 * 
	*/
	public function abort() {
		$result = $this->conn->rollback();
		
		if(DB::isError($result)) {
			throw new LoggedException($result->getMessage(), $result->getCode(), self::module);
		}
		
		return true;
	}
	
    /**
     * Prepares a query for multiple execution with the get methods
     *
     * Creates a query that can be run multiple times.  Each time it is run,
     * the placeholders, if any, will be replaced by the contents of
     * get methods $data arguement.
     * 
     * Get methods are: getOne, getAll, getColumn, getRow
     *
     * Three types of placeholders can be used:
     *   + <kbd>?</kbd>  scalar value (i.e. strings, integers).  The system
     *                   will automatically quote and escape the data.
     *   + <kbd>!</kbd>  value is inserted 'as is'
     *   + <kbd>&</kbd>  requires a file name.  The file's contents get
     *                   inserted into the query (i.e. saving binary
     *                   data in a db)
     *
     * Example 1.
     * <code>
     * $sth = $db->prepare('INSERT INTO tbl (a, b, c) VALUES (?, !, &)');
     * $data = array(
     *     "John's text",
     *     "'it''s good'",
     *     'filename.txt'
     * );
     * $res = $db->getAll($sth, $data);
     * </code>
     *
     * Use backslashes to escape placeholder characters if you don't want
     * them to be interpreted as placeholders:
     * <pre>
     *    "UPDATE foo SET col=? WHERE col='over \& under'"
     * </pre>
     *
     * With some database backends, this is emulated.
     *
     * <b>This documentation was taken from: http://pear.php.net/package/DB/docs/1.7.6/DB/DB_common.html#methodprepare and modified</b>
     *
     * @param string $sql  the query to be prepared
     *
     * @throws An exception in the event of an error
     */
	public function prepare($sql){
		$result = $this->conn->prepare($sql);
		
		if(DB::isError($result)) {
			throw new LoggedException($result->getMessage(), $result->getCode(), self::module);
		}
		
		return $result;
	}
	
	/**
	 * Execute a prepared statement
	 * 
	 * This function will execute a prepared statement specified by  
	 * $resource (as returned by prepare()). 
	 * 
	 * @param int $resource The statement resource identifier (returned from prepare())
	 * @param array $data A mixed array relating to the query placeholders. The number of placeholders must match the array size
	 * @return bool This will always return true, as errors a thrown as exceptions
	 * @throws An exception in the event of an error
	 */
	public function execute($resource, $data = array()){
		$result = $this->conn->execute($resource, $data);
		
		if(DB::isError($result)) {
			throw new LoggedException($result->getMessage() . '. SQL: ' . $result->userinfo, $result->getCode(), self::module);
		}
		
		return true;
	}
	
	public function __destruct() {
		if(! DB::isError($this->conn)) {
			$this->conn->disconnect();
		}
	}
	
	/**
	 * Make a piece of data sql safe
	 *
	 * @todo Make this more rigerous
	 */
	public function quoteSmart($value){
	   // Quote if not integer
	   if (!is_numeric($value)) {
	       $value = "'" . addslashes($value) . "'";
	   }
	   return $value;
	}
	
	public static function getTotalQueries(){
		return self::$totalQ;
	}
	
	public static function getQueryLog(){
		return self::$queryLog;
	}
	
	protected static function logQuery(){
		self::$totalQ++;
		$backTrace = debug_backtrace();
		if(isset($backTrace[2])){
			$callingClass = $backTrace[2]['class'];
			$callingFunction = $backTrace[2]['function'];
			if(isset(self::$queryLog[$callingClass][$callingFunction])){
				self::$queryLog[$callingClass][$callingFunction]++;
			}else{
				self::$queryLog[$callingClass][$callingFunction] = 1;
			}
		}
	}
	
}
?>
