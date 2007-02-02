<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSDeleteCommentTrackModel extends Model {
	
  const module = 'DPS';
	
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);

    $commentID = pg_escape_string($this->fieldData['commentID']);
    if(is_numeric($commentID) && $commentID != "" && $commentID != "*") {
      $sql = "select userid from audiocomments where id = $commentID";
      $auth = Auth::getInstance();
      $userID = $auth->getUserID();
      $id = $db->getOne($sql);
      if($id == $userID) {
	$trDelete = "id = " . $commentID;
	$db->delete('audiocomments', $trDelete);
      }
    }
  }
	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>