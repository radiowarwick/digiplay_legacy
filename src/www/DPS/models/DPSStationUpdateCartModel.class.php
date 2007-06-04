<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSStationUpdateCartModel extends Model {
	
  const module = 'DPS';
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);
    $cartID = pg_escape_string($this->fieldData['cartID']);
    
    if($cartID != '') {
      $audio = $this->fieldData['audioID'];
      $style = $this->fieldData['style'];
      $text="";
      $subStr = explode("\n",$_POST["text"]);
      foreach($subStr as $value){
        $text = $text . pg_escape_string($value) . "\n";
      }
      $text = rtrim($text,"\n");
      if($text != '' && $cartID != '' && is_numeric($cartID)) {
        $cart = array();
        $cart['text'] = $text;
        $cart['audioid'] = $audio;
        $cart['cartstyleid'] = $style;
        $atWhere = "id = " . $cartID;
        $db->update('cartsaudio', $cart, $atWhere, true);
      }
    }
  }
	
  protected function processInvalid(){
    //No invalid processing required
    if($this->errors['text']) {
      MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditcart.tpl'),array("cartID" => $this->fieldData['cartID'], "error" => "text"));
    } elseif($this->errors['style']) {
      MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditcart.tpl'),array("cartID" => $this->fieldData['cartID'], "error" => "style"));
    } elseif($this->errors['audioID']) {
      MVCUtils::redirect(MVCUtils::getTemplateID('dpssteditcart.tpl'),array("cartID" => $this->fieldData['cartID'], "error" => "audioID"));
    }
  }
	
}

?>
