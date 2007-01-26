<?php

/*
	21:00
	--------------------------------------------
	Ive tested the script using:
		http://webservices.amazon.com/AWSECommerceService/US/AWSECommerceService.wsdl
	..all ok.
	
		- Windows IIS PHP5
	
	19/Sept05
	---------------------------------------------
	Hey, I've been planning this for a while, but I have only just started
	so there isnt much here yet...
	
	More Excuses
	---------------------------------------------
	I still havnt looked into SMARTY yet, so I havnt implemented Module yet...
	
	...alos im not sure if I can use "WebService" as the ID for the
	BasicLogger::logMessage as really the error would be coming from an unpredictable
	class like "Amazon" ...or somthing... ???
	
	About this class
	---------------------------------------------
	
	This class might seem pretty useless on its own (because it is), I just need
	an abstract class which can mime the functions of SOAP so that they can be
	easily used in the concrete/child classes such as Amazon.php
*/

abstract class WebService /* extends Module */{
	
	protected $_client; /* do we need this to be an array for 
						  multiple clients, or are we ok, I cant see the need personally...
					*/
	private $_functionList = array(); // Array of functions provided by the webservice
	private $_responce;
	
	function call($function, $ar){
	
	}
	
	public function setupClient($wsdl){
		echo "Attempting to setup client...<br>";
		$this->_client = new SoapClient($wsdl, array("trace" => 1));
		echo "Setup Ok<br>";
		$this->loadFunctions();
		
	}
	
	private function loadFunctions(){
		/*
			Transfer the functions to the fList
		*/
		$this->_functionList = $this->_client->__getFunctions();
	}
	
	protected function checkMethod($n){
		
		if(isset($this->_functionList[$n])){
			return true;
		}else{
			return false;
		}
	}
	
	/*
		An exhausting (for me) list of functions which mimic the PHP5 SOAP class
	*/
	
	public function getLastResponse(){ // American spelling, remember that! 30 mins of confusion :-S
		return $this->_client->__getLastResponse();
	}
	
	public function getLastRequest(){
		return $this->_client->__getLastRequest();
	}
	
	public function getTypes(){
		return $client->__getTypes();
	}
	
	/*
		WebService specific functions...
	*/
	
	private function storeXML(){
	
	}
	
	private function asSQL(){
	
	}

}

?>