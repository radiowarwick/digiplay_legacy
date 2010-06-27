<?php
/**
 * 
 * @package MVC
 */
 
 
#include_once($cfg['MVC']['dir']['root'] . '/Viewer.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');

MVCUtils::includeViewer('Viewer', 'MVC');

/**
 * A skeleton Model
 * 
 * This model performs the most minimum operations possible. The 
 * constructor values are loaded into the class variables and the 
 * viewer is then initialised.
 * 
 */
class Model {
	
	/**#@+
	 * @access private
	 */
	/**
	 * Stack of the template to use (last element if the templateid to use)
	 * @var array
	 */
  protected $templateID;
	protected $templateIDStack;
	/**
	 * The name of the form (if any) which has been submitted
	 * @var string
	 */
	protected $formName;
	/**
	 * An associative array for field/value pairs from the submitted form (if any)
	 * @var array
	 */
	protected $fieldData;
	/**
	 * AOn associative array for errors
	 * @var array
	 */
	protected $errors;
	/**
	 * An instance of the Viewer class
	 * @var Viewer
	 */
	protected $viewer;
	/**
	 * The code generated for output
	 * @var String
	 */
	protected $code;
	/**#@-*/
	
	
	const module = 'MVC';
	
	/**
	 * Construct the viewer and load values
	 *
	 * If you intend on overriding this classes constructor you should ensure 
	 * that you call parent::__construct(); to ensure that the class 
	 * is loaded correctly.
	 * 
	 * @param string $templateID The ID of the template for the page to be viewed. This ID is the ID of the template in the database.
	 * @param string $formName The name of the form (if any) which has been submitted
	 * @param array $fieldData An associative array for field/value pairs from the submitted form (if any)
	 * @todo Add authnetication checks to call processInvalid or processInvalid accordingly.
	 */
	public function __construct($templateIDS, $formName = null, $modelModuleName, $viewerModuleName, &$fieldData = array(), &$errors = array()){
		//Store class variables
		$this->templateIDStack = $templateIDS;
		$this->templateID = end($templateIDS);
		$this->formName = $formName;
		$this->fieldData = &$fieldData;
		$this->errors = &$errors;

        if(count($errors) > 0) {
            $this->processInvalid();
        } else {
            $this->processValid();
        }

		//something
		//Initialise the viewer
		$this->viewer = MVCUtils::initializeViewer($this->templateIDStack, $formName, $viewerModuleName, $fieldData, $errors);
		//The $viewer class variable is now loaded
		
		$this->code = $this->viewer->getCode();
	}
	
	public function getCode(){
		return $this->code;
	}
	
	protected function processValid() {
		
    }
    
    protected function processInvalid() {

    }
	
}


?>
