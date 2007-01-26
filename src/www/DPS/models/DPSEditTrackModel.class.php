<?php
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSEditTrackModel extends Model {
	
  const module = 'DPS';
	
	
  protected function processValid(){
    global $cfg;
    $db = Database::getInstance($cfg['DPS']['dsn']);

    $trackID = pg_escape_string($this->fieldData['trackID']);
    if(is_numeric($trackID) && $trackID != "" && $trackID != "*") {
      $trUpdates['title'] = $this->fieldData['title'];
      $trUpdates['reclibid'] = $this->fieldData['reclib'];
      $trUpdates['music_released'] = $this->fieldData['released'];
      $trUpdates['origin'] = $this->fieldData['origin'];
      $auth = Auth::getInstance();
      $userID = $auth->getUserID();
      if(AuthUtil::getDetailedUserrealmAccess(array(58,60,66), $userID)) {
				if($this->fieldData['playlist'] == "on") {
	  			$trUpdates['sustainer'] = 't';
				} else {
	  			$trUpdates['sustainer'] = 'f';
				}
      }
      if($this->fieldData['album'] != '') {
				$sql = "SELECT id FROM albums where name = '" . pg_escape_string($this->fieldData['album']) . "'";
  			$albumID = $db->getOne($sql);
				if(is_null($albumID)) {
	  			$alValues['name'] = $this->fieldData['album'];
	  			$alValues['source'] = 'Web Interface';
	  			$db->insert('albums', $alValues, true);
					$sql = "SELECT last_value FROM albums_id_seq";
					$trUpdates['music_album'] = $db->getOne($sql);
				} else {
					$trUpdates['music_album'] = $albumID;
				}
      } else {
				$trUpdates['music_album'] = 0;
      }
      $atWhere = "audio.id = " . $trackID;
      $db->update('audio', $trUpdates, $atWhere, true);
      
      if(is_numeric($this->fieldData['artistnum'])) {
	for($i=0;$i<=$_POST['artistnum'];$i++) {
	  $arValues = array();
	  $aaValues = array();
	  
	  $artistnum = "artist" . $i;
	  $artistnumid = $artistnum . "id";
	  if($this->fieldData[$artistnum] != "") {
	    $sql = "SELECT * FROM artists where name = '" . pg_escape_string($this->fieldData[$artistnum]) . "'";
	    $artist = $db->getRow($sql);
	    if(is_null($artist)) {
	      $arValues['name'] = $this->fieldData[$artistnum];
	      $db->insert('artists', $arValues, true);
	    
	      $sql = "SELECT last_value FROM artists_id_seq";
	      $newID = $db->getOne($sql);
	    } else {
	      $newID = $artist['id'];
	    }
	    if($i == $this->fieldData['artistnum']) {
	      $aaValues['audio'] = $trackID;
	      $aaValues['artist'] = $newID;
	      $db->insert('audioartists',$aaValues,true);
	    } else {
	      if($newID != $this->fieldData[$artistnumid] && is_numeric($this->fieldData[$artistnumid])) {
					$aaValues['artist'] = $newID;
					$aaWhere = "audio = " . $trackID . " AND artist = " . pg_escape_string($this->fieldData[$artistnumid]);
					$db->update('audioartists', $aaValues, $aaWhere, true);
	      }
	    }
	  } elseif ($i != $this->fieldData['artistnum']) {
	    $aaWhere = "audio = " . $trackID . " AND artist = " . pg_escape_string($this->fieldData[$artistnumid]);
	    $db->delete('audioartists',$aaWhere);
	  }
	}
      }
      
      if(is_numeric($this->fieldData['keywordnum'])) {
	for($i=0;$i<=$_POST['keywordnum'];$i++) {
	  $keValues = array();
	  $akValues = array();
	  
	  $keywordnum = "keyword" . $i;
	  $keywordnumid = $keywordnum . "id";
	  if($this->fieldData[$keywordnum] != "") {
	    $sql = "SELECT * FROM keywords where name = '" . pg_escape_string($this->fieldData[$keywordnum]) . "'";
	    $keyword = $db->getRow($sql);
	    if(is_null($keyword)) {
	      $keValues['name'] = $this->fieldData[$keywordnum];
	      $db->insert('keywords', $keValues, true);
	    
	      $sql = "SELECT last_value FROM keywords_id_seq";
	      $newID = $db->getOne($sql);
	    } else {
	      $newID = $keyword['id'];
	    }
	    if($i == $this->fieldData['keywordnum']) {
	      $akValues['track'] = $trackID;
	      $akValues['keyword'] = $newID;
	      $db->insert('audiokeywords',$akValues,true);
	    } else {
	      if($newID != $this->fieldData[$keywordnumid] && is_numeric($this->fieldData[$keywordnumid])) {
		$akValues['keyword'] = $newID;
		$akWhere = "track = " . $trackID . " AND keyword = " . pg_escape_string($this->fieldData[$keywordnumid]);
		$db->update('audiokeywords',$akWhere, $akValues, true);
	      }
	    }
	  } elseif ($i != $this->fieldData['keywordnum']) {
		$akWhere = "track = " . $trackID . " AND keyword = " . pg_escape_string($this->fieldData[$keywordnumid]);
		$db->delete('audiokeywords',$akWhere);
	  }
	}
      }
      if($this->fieldData['comment'] != '') {
	$text="";
	$subStr = explode("\n",$_POST["comment"]);
	foreach($subStr as $value){
	  $text = $text . pg_escape_string($value) . "\n";
	}
	$text = rtrim($text,"\n");
	$trInsert['comment'] = $text;
	$trInsert['audio'] = $trackID;
	$auth = Auth::getInstance();
	$trInsert['creationdate'] = time();
	$trInsert['userid'] = $auth->getUserID();
	$db->insert('audiocomments', $trInsert, true);
      }
    }
  }
	
  protected function processInvalid(){
    //No invalid processing required
  }
	
}

?>
