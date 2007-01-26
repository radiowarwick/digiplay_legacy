<?php
/**
 * 
 * @package MVC
 */
 
include_once($cfg['smarty']['dir']['root'] . "/libs/Smarty.class.php");
include_once($cfg['MVC']['dir']['root'] . '/viewers/IViewer.class.php');

/**
 * Present a friendly exception to the user
 * 
 * This class is designed to handle exceptions in user friendly ways.
 * The value of $cfg['smarty']['showExceptionInfo'] will be passed to 
 * the template, in addition to the message, file, line, code, and trace of
 * the exception (named as shown). They are passed within an array named 
 * exception data.
 * 
 */
class RenderedExceptionViewer implements IViewer {
	
	/**#@+
	 * @access private
	 */
	/**
	 * An instance of the Smarty class.
	 * @var Smarty
	 */
	private $template;
	/**
	 * The exception object
	 * @var Exception
	 */
	private $exception;
	/**
	 * The file name of the template to be used
	 * @var string
	 */
	private $templateFileName;
	
	/**
	 * The exception message
	 * @var string
	 */
	private $message;
	/**
	 * The exception message
	 * @var string
	 */
	private $code;
	/**
	 * The exception code
	 * @var string
	 */
	private $file;
	/**
	 * The fine in which the exception occurred
	 * @var string
	 */
	private $line;
	/**
	 * The stack trace at the time of the exception
	 * @var string
	 */
	private $trace;
	
	/**
	 * Construct the object
	 * 
	 * @param Exception The exception to be made user friendly
	 */
	public function __construct($exception){
		global $cfg;
		$this->template = new Smarty();
		
		$this->template->compile_dir = $cfg['smarty']['compiledir'];
		$this->exception = $exception;
		$this->templateFileName = MVCUtils::findTemplate($cfg['smarty']['RenderedexceptionTemplateFile']);
		
		$this->_setupTemplate();
	}
	/**
	 * Will print the template output to the browser
	 */
	public function printTemplate(){
		$this->template->display('file:' . $this->templateFileName);
	}
	/**
	 * Will return the template output
	 */
	public function getCode(){
		return $this->template->fetch($this->templateFileName);
	}
	/**
	 * Will assign a key/value pair to the template for use in rendering
	 * 
	 * @param string $name The name of the value. This will be used to access the value in the template
	 * @param mixed $value Either any basic type as well as an array
	 */
	private function _assign($name, $value){
		$this->template->assign($name, $value);
	}
	/**
	 * Assigns values to the template by calling {@link _assign}. The details 
	 * of the exception are assigned at this point.
	 */
	private function _setupTemplate(){
		global $cfg;
		$this->_assign('showExceptionInfo', $cfg['smarty']['showExceptionInfo']);
		$exceptionData['message'] = $this->exception->getMessage();
		$exceptionData['code'] = $this->exception->getCode();
		$exceptionData['file'] = $this->exception->getFile();
		$exceptionData['line'] = $this->exception->getLine();
		$exceptionData['trace'] = nl2br($this->exception->getTraceAsString());
		$this->_assign('exceptionData', $exceptionData);
	}
	
}

?>
