<?php
/**
 * 
 * @package MVC
 */
 
/**
 * A third-party module base
 *
 * This class provides an interface to the Smarty templating engine, allowing
 * programmers to easily create their own smarty functions. The purpose of 
 * this to provide a way in which the templating system can be extended. 
 * This modular system should not be used for implementing full systems, 
 * but as an interface to an existing system. For example, a news application 
 * could allow for the management and display of news articles. The management 
 * would be conducted through a seperate system (it does not even have to use)
 * this toolkit. However, this class could be used to register a function such
 * as {news_show}, which would display a list of headlines inside an existing 
 * page which uses this toolkit.
 */
 
 /**
  *  Realy feckin simple class
  */
abstract class Module {
	
    protected $smarty;
    
    protected $fieldData;
    
    protected $templateID;
    
    /**
     * Initialise the object
     *
     * The constructor simple assigns the Smarty instance to a class variable
     *
     * @param Smarty $smarty The smarty instance in use
     */
    function __construct(Smarty $smarty, $fieldData, $templateID){
        $this->smarty = $smarty;
        $this->fieldData = $fieldData;
        $this->templateID = $templateID;
    }
    
    /**
     * Define a smarty function
     *
     * This function defines a smarty function, which can be accessed within
     * a template in the form {funcName arg1="val1" arg2="val2" ...}. The
     * following is roughly taken from smarty.php.net:
     *
     * The php-function callback impl can be either
     *
     * 1. an array of the form array(&$object, $method) with &$object being a reference to an object and $method being a string containing the mehod-name
     * 2. an array of the form array(&$class, $method) with $class being a classname and $method being a class method of that class.
     *
     */
    protected function assignSmartyFunction($name, $impl){
        
        //Run checks to ensure the class or object exists
        //There are no checks to see if the method exists
        list($classOrObject, $method) = $impl;
        $isObj = is_object($classOrObject);
        
        if(is_string($classOrObject)){
            $isClass = class_exists($classOrObject);
        }else{
            $isClass = false;
        }
        
        if(!$isObj && !$isClass){
            throw LoggedException(
              "The class/object you passed does not exist/is not instantiated",
               null,
               module,
               "error");
        }
        
        //Register the function
        $this->smarty->register_function($name, $impl);
        BasicLogger::logMessage("Registered smarty function '$name'", 'debug', self::module);
        
    }
}

?>