<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSStationAddCartModel extends Model {
	
  const module = 'DPS';
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);

    $audio = $this->fieldData['audioID'];
    $style = $this->fieldData['style'];
    $cartwall = $this->fieldData['cartwallID'];
    $cartPos = $this->fieldData['cartPos'];

      $text="";
      $subStr = explode("\n",$_POST["text"]);
      foreach($subStr as $value){
	$text = $text . pg_escape_string($value) . "\n";
      }
      $text = rtrim($text,"\n");
      if($text != '' && $audio != '' && is_numeric($audio)) {
	$sql = "select count(*) from cartsaudio, cartwalls where 
	      cartwalls.id = cartsaudio.cartwallid
	      AND cartwalls.id = " . pg_escape_string($cartwall) . " 
	      AND cartsaudio.cart = " . pg_escape_string($cartPos);
	$count = $db->getOne($sql);
	if($count == 0) {
	  $cart = array();
	  $cart['text'] = $text;
	  $cart['audioid'] = $audio;
	  $cart['cartstyleid'] = $style;
	  $cart['cartwallid'] = $cartwall;
	  $cart['cart'] = $cartPos;
	  $db->insert('cartsaudio', $cart, true);
	} else {
	//do error stuff
	}
      }	
  }
	
  protected function processInvalid(){
    //No invalid processing required
    if($this->errors['text']) {
      MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditcart.tpl'),array("cartID" => "New", "cartwallID" => $this->fieldData['cartwallID'], "cartPos" => $this->fieldData['cartPos'], "error" => "text"));
    } elseif($this->errors['style']) {
      MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditcart.tpl'),array("cartID" => "New", "cartwallID" => $this->fieldData['cartwallID'], "cartPos" => $this->fieldData['cartPos'], "error" => "style"));
    } elseif($this->errors['audioID']) {
      MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditcart.tpl'),array("cartID" => "New", "cartwallID" => $this->fieldData['cartwallID'], "cartPos" => $this->fieldData['cartPos'], "error" => "audioID"));
    }
  }
	
}

?>
