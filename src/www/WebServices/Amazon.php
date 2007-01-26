<?php

require_once("WebService.php");

class Amazon extends WebService{
	
	/* Standard values sent in most requests */
	public $token = "0525E2PQ81DD7ZTWTK82"; // lets use mine for now ;-)
	
	public $itemSearch = array();
	
	public function ItemSearch($searchIndex, $keywords, $id = NULL){
		
		if(is_null($id)){
			$id = $this->token;
		}
		$ItemSearchParams = array();
		$ItemSearchRequest = array();
		
		$ItemSearchRequest{"ContentType"} = "text/html";
		
		$ItemSearchRequest{"SubscriptionId"} = $id;
		$ItemSearchParams{"SearchIndex"} = $searchIndex;
		$ItemSearchParams{"Keywords"} = $keywords;

		$ItemSearchRequest{"Request"} = array($ItemSearchParams);
		
		$this->_client->ItemSearch($ItemSearchRequest);
	}
	
}

?>