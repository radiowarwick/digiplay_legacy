<?php

include_once('config.php');
include_once('config-tests.php');
//exit;
new configCheck($cfg, $cfgCheck);
set_time_limit(5);
class configCheck {
	
	protected $mainConfig = array();
	protected $checkConfig = array();
	protected $combinedConfig = null;
	
	function __construct($mainConfig, $checkConfig){
		$this->mainConfig = $mainConfig;
		
		$this->checkConfig = $checkConfig;
		
		$this->combinedConfig = $this->makeCombinedTree();
		//print_r($this->combinedConfig);
		echo $this->makeListHTML();
	}
	
	
	protected function makeCombinedTree(){
		return $this->makeCombinedTreeR($this->mainConfig, $this->checkConfig);
	}
	
	protected function makeCombinedTreeR($mConfig, $cConfig){
		$out = array();
		foreach($mConfig as $k => $v){
			if(is_array($v) && $this->isAssociativeArray($v)){
				if(isset($cConfig[$k])){
					$out[$k] = $this->makeCombinedTreeR($v, $cConfig[$k]);
				}else{
					$out[$k] = $this->makeCombinedTreeR($v, null);
				}
			}else{
				if(isset($cConfig[$k])){
					$out[$k] = $cConfig[$k];
				}else{
					$out[$k] = 'Unchecked';
				}
			}
		}
		return $out;
	}
	
	function makeListHTML(){
		$html = '<ul>';
		$html .= $this->makeListHTMLR($this->combinedConfig, "", 0);
		$html .= '</ul>';
		return $html;
	}
	
	protected function makeListHTMLR($tree, $depth){
		$html = '';
		$p = str_repeat(' ', $depth * 2);
		foreach($tree as $k => $v){
			if(is_array($v)){
				$html .= "$p<li>$k</li>\n";
				$html .= "$p<ul>\n";
				$html .= $this->makeListHTMLR($tree[$k], $depth + 1);
				$html .= "$p</ul>\n";
			}else{
				$html .= "$p<li>$k: " . $this->makeStatusCode($v) ."</li>\n";
			}
		}
		return $html;
	}
	
	protected function isAssociativeArray($inArray){
		$isNumeric = true;
		foreach ($inArray as $k => $v){
			if(!is_int($k)){
				$isNumeric = false;
			}
		}
		
		return !$isNumeric;
	}
	
	protected function makeStatusCode($status){
		if(preg_match('/^Passed/', $status)){
			$out = "<font color=\"green\"><strong>$status</strong></font>";
		}elseif(preg_match('/^Failed/', $status)){
			$out = "<font color=\"red\"><strong>$status</strong></font>";
		}elseif(preg_match('/^Unchecked/', $status)){
			$out = "<font color=\"black\"><strong>$status</strong></font>";
		}else{
			$out = "<font color=\"black\">$status</font>";
		}
		return $out;
	}
}






?>