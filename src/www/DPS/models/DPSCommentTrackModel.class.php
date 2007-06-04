<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSCommentTrackModel extends Model {
	
  const module = 'DPS';
	
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);

    $audioID = pg_escape_string($this->fieldData['audioID']);
    if($this->fieldData['comment'] != '' && is_numeric($audioID) && $audioID != "" && $audioID != "*") {
      $text="";
      $subStr = explode("\n",$_POST["comment"]);
      foreach($subStr as $value){
        $text = $text . pg_escape_string($value) . "\n";
      }
      $text = rtrim($text,"\n");
      $trInsert['comment'] = $text;
      $trInsert['audioid'] = $audioID;
      $auth = Auth::getInstance();
      $trInsert['creationdate'] = time();
      $trInsert['userid'] = $auth->getUserID();
      $db->insert('audiocomments', $trInsert, true);
    }
  }
	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
