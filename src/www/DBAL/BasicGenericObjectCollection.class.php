<?
/**
 * @package DBAL
 */

/**
 * A collection GenericObjects
 * 
 * This class implements a collection structure for the GenericObjects class.
 * 
 */
class BasicGenericObjectCollection {
	
	/**
	 * The module of this class, used in debugging
	 */
	const module = 'DBAL';
	
	/**#@+
	 * @access private
	 */
	 
	/**
	 * The name of the table to inferface with
	 * @var string
	 */
	private $table_name;
	/**
	 * The name of the class that will represent a table row. Should extend the GenericObject class.
	 * @var string
	 */
	private $class_name;
	/**
	 * The DSN for the database connection
	 * @var dsn
	 */
	private $dsn;
	/**
	 * The number of items stored in $obj_array.
	 * @var int
	 */
	private $item_count = 0;
	/**
	 * An integer array of record IDs
	 * @var array
	 */
	private $id_array;
	/**
	 * An array of objects where the type is defined by $class_name. 
	 * @var array
	 */
	private $obj_array;
	/**#@-*/
	 
	/**
	 * Set the table to interface with and the concrete GenericObject class to use class variables
	 * @param string $table_name The name of the table to inferface with
	 * @param string $class_name The name of the class that will represent a table row. Should extend the GenericObject class.
	 * @param string $dsn The database connection string. Default (as set in config file) used if not passed.
	 */
	public function __construct($table_name, $class_name, $dsn = null) {
		global $cfg;
		
		$this->table_name = $table_name;
		$this->class_name = $class_name;
		//If nothing was passed in, use the value from $cfg
		if($dsn == null) {
			if(isset($cfg['DBAL']['dsn'])){
				$this->dsn = $cfg['DBAL']['dsn'];
			}else{
				throw new LoggedException('No default DSN was specified in the config file', 0,self::module);
			}
		}
	}
    
	/**
	 * Add the id of a record to be represented
	 * @param int $id The id of the record (i.e. The value of the primary key in the database)
	 */
	public function addTuple($id) {
		if (!$this->id_array) {
			$this->id_array = array();
		}
		array_push($this->id_array, $id);
		$this->item_count = sizeof($this->id_array);
	}
	/**
	 * Get the number of rows
	 * @return int Number of rows
	 */
	public function getItemCount() {
		return $this->item_count;
	}
	/**
	 * Return a comma seperated list based upon $id_array.
	 * @return string
	 */
	private function _getCommaSeparatedIDList() {
		return join(',', $this->id_array);
	}
	/**
	 * Returns the index of the array element of value equal to $tuple_id from the $id_array array.
	 * @param int $tuple_id The ID to search for
	 * @return int
	 * @access private
	 */
	private function _getIndexFromTupleID($tuple_id) {
		$index = -1;
		for ($i=0; $i<=sizeof($this->id_array)-1; $i++) {
			if ($this->id_array[$i] == $tuple_id) {
				  $index = $i;
			}
		}
		return $index;
	}
	/**
	 * Populate the objects array from the database.
	 */
	public function populateObjectArray() {
		$db = Database::getInstance($this->dsn);
		eval("\$pk = {$this->class_name}::getPKFieldName();");
		$stmt = "SELECT * FROM `" . $this->table_name . "` WHERE `$pk` IN (" . $this->_GetCommaSeparatedIDList(). ")";
		# Perform SQL query
		$result_rows = $db->getAll($stmt);
		for ($i=0; $i<=sizeof($result_rows)-1; $i++) {
			$this_db_row_id = $result_rows[$i][$pk];
			$this_index = $this->_GetIndexFromTupleID($this_db_row_id);
			if ($this_index >= 0) {
				$refObjArrayIndexObj = &$this->obj_array[$this_index];
				$s = "\$refObjArrayIndexObj = new " . $this->class_name . "(" . $this_db_row_id . ");";
				eval($s);
				$refObjArrayIndexObj->forceLoaded();
				$row = $result_rows[$i];
				foreach ($row as $key => $value) {
					if (!(is_numeric($key))) {
						$refObjArrayIndexObj->setField($key, $value);
					}
				}
			}
		}
	}
	/**
	 * Return an array of objects of the class identified by $class_name.
	 */
	public function retrievePopulatedObjects() {
		return $this->obj_array;
	}
}

?>