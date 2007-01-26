<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserEditCartViewer extends Viewer {

	const module = 'DPS';
	protected $activeNode = 'foldersTree';

	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();

		$db = Database::getInstance($cfg['DPS']['dsn']);
		$cartID = pg_escape_string($this->fieldData['cartID']);
		if($cartID == "New" || !is_numeric($cartID)) {
			$cartwallID = pg_escape_string($this->fieldData['cartwallID']);
			$auth = Auth::getInstance();
			$userID = $auth->getUserID();
			$flag = false;
			if($cartwallID != '' && is_numeric($cartwallID)) {
				$sql = "select count(*) from cartsetsusers, cartwalls 
								where cartsetsusers.userid = $userID AND 
									cartsetsusers.cartsetid = cartwalls.cartset AND 
									cartwalls.id = $cartwallID AND 
									(cartsetsusers.permissions = 'o' or 
										cartsetsusers.permissions = 'w' or 
										cartsetsusers.permissions = 'rw')";
				$check = $db->getOne($sql);
				if($check > 0) {
					$flag = true;
				} else {
					$sql = "select count(*) from cartsetsgroups, cartwalls, groupmembers 
									where cartsetsgroups.groupid = groupmembers.groupid AND 
										groupmembers.userid = $userID AND 
										cartsetsgroups.cartsetid = cartwalls.cartset AND 
										cartwalls.id = $cartwallID AND 
										(cartsetsgroups.permissions = 'o' or 
											cartsetsgroups.permissions = 'w' or 
											cartsetsgroups.permissions = 'rw')";
					$check = $db->getOne($sql);
					if($check > 0) {
						$flag = true;
					}
				}
			}
			if($flag) {
				$this->assign('new', 't');
				$this->assign('cartwallID', $this->fieldData['cartwallID']);
				$this->assign('cartPos', $this->fieldData['cartPos']);
      } else {
				$this->assign('permError', 't');
      }
		} else {
			$auth = Auth::getInstance();
			$userID = $auth->getUserID();
			$flag = false;
			if($cartID != '' && is_numeric($cartID)) {
				$sql = "select count(*) from cartsetsusers, cartwalls, cartsaudio 
								where cartsetsusers.userid = $userID AND 
								cartsetsusers.cartsetid = cartwalls.cartset AND 
								cartwalls.id = cartsaudio.cartwall AND 
								cartsaudio.id = $cartID AND 
								(cartsetsusers.permissions = 'o' or 
									cartsetsusers.permissions = 'w' or 
									cartsetsusers.permissions = 'rw')";
				$check = $db->getOne($sql);
				if($check > 0) {
					$flag = true;
				} else {
					$sql = "select count(*) from cartsetsgroups, cartwalls, cartsaudio, groupmembers 
									where cartsetsgroups.groupid = groupmembers.groupid AND 
										groupmembers.userid = $userID AND 
										cartsetsgroups.cartsetid = cartwalls.cartset AND 
										cartwalls.id = cartsaudio.cartwall AND 
										cartsaudio.id = $cartID AND 
										(cartsetsgroups.permissions = 'o' or 
											cartsetsgroups.permissions = 'w' or 
											cartsetsgroups.permissions = 'rw')";
					$check = $db->getOne($sql);
					if($check > 0) {
						$flag = true;
					}
				}
			}
			if($flag) {
    		// cartwalls
				$sql = "select cartsaudio.id as id, cartsaudio.text as text,
									cartsaudio.audio as audioID, cartwalls.cartset as cartset, 
	    						cartsaudio.style as styleID,cartsaudio.cart as cart 
								from cartsaudio, cartwalls 
								where cartsaudio.cartwall = cartwalls.id and 
								cartsaudio.id = " . $cartID;
				$cart = $db->getRow($sql);
				$this->assign('cartInfo', $cart);
			} else {
				$this->assign('permError', 't');
			}
		}
		if($flag) {
			$sql= "select * from cartstyle order by name asc";
			$styles = $db->getAll($sql);

      $auth = Auth::getInstance();
      $userID = $auth->getUserID();
      if($cartID == "New") {
				$sql = "select count(*) from cartsetsusers, cartwalls 
								where cartwalls.cartset = cartsetsusers.cartsetid and 
									cartwalls.id = " . $cartwallID . " and 
									cartsetsusers.userid = $userID and 
									cartsetsusers.permissions = 'o'";
				$owner = $db->getOne($sql);
      } else {
				$sql = "select count(*) from cartsetsusers 
								where cartsetid = " . $cart['cartset'] . " and 
								cartsetsusers.userid = $userID and 
								permissions = 'o'";
				$owner = $db->getOne($sql);
      }
      if($owner > 0) {
				$treeInfo = $this->treeSetup(0,$cfg['DPS']['systemUserID']);
				$treeInfo = '<tree id=\"0\">' . str_replace('"','\"',$treeInfo) . '</tree>';
      } else {
				$treeInfo = $this->treeSetup(0,null);
				$treeInfo = '<tree id=\"0\">' . str_replace('"','\"',$treeInfo) . '</tree>';
      }

      $this->assign('activeNode', $this->activeNode);
      $this->assign('treeData', $treeInfo);
      $this->assign('styles', $styles);
    }
  }

	function treeSetup($dirID,$userid) {
  	global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		if($userid != null) {
    	$sql = "SELECT dir.id, dir.parent, dir.name, dir.notes 
						FROM dir, users, dirusers 
						WHERE 
    					dir.id = dirusers.directory AND 
							(dirusers.permissions = 'r' OR 
								dirusers.permissions = 'w' OR 
								dirusers.permissions = 'rw' OR 
								dirusers.permissions = 'o') AND 
							dirusers.userid = $userid AND 
							dir.parent = " . pg_escape_string($dirID) . " 
						UNION (SELECT dir.id, dir.parent, dir.name, dir.notes 
						FROM dir, dirgroups, groups, groupmembers, users 
						WHERE
            	dir.id = dirgroups.directory AND 
							(dirgroups.permissions= 'r' OR 
								dirgroups.permissions = 'w' OR 
								dirgroups.permissions = 'rw' OR 
								dirgroups.permissions = 'o') AND 
							dirgroups.groupid = groups.id AND
            	groups.id = groupmembers.groupid AND 
							groupmembers.userid = $userid AND 
							dir.parent = " . pg_escape_string($dirID) . ") 
						ORDER BY name asc";
		} else {
    	$sql = "SELECT dir.id, dir.parent, dir.name, dir.notes 
						FROM dir, dirgroups 
						WHERE
            	dir.id = dirgroups.directory AND 
							(dirgroups.permissions= 'r' OR 
								dirgroups.permissions = 'w' OR 
								dirgroups.permissions = 'rw' OR 
								dirgroups.permissions = 'o') AND 
							dirgroups.groupid = {$cfg['DPS']['allusersgroupid']} AND 
							dir.parent = " . pg_escape_string($dirID) . " 
						ORDER BY name asc";
		}
    $users = $db->getAll($sql);

   	foreach($users as $user) {
     	if($user != false) {
				$list = $list . '<item text="' . htmlspecialchars($user['name']) . '" id="dir' . $user['id'] . '" im0="folderClosed.gif">';
      	$list = $list . $this->treeSetup($user['id'],$userid);
				$list = $list . '</item>';
			}
    }
		//#######
		//JINGLES
		//#######
		if($userID != null) {
			$sql = "SELECT audiodir.id as dir, audio.title as title, audio.id as audio 
						FROM audiodir, audio, audiotypes, audiogroups, groupmembers 
						WHERE audio.id = audiodir.audio AND 
							directory = " . pg_escape_string($dirID) . " AND
							audio.id = audiogroups.audio AND 
							(audiogroups.permissions = 'o' OR audiogroups.permissions = 'r' OR audiogroups.permissions = 'rw') AND 
							audiogroups.groupid = groupmembers.groupid AND 
							groupmembers.userid = $userid AND 
				    	audio.type = audiotypes.id AND (audiotypes.name = 'jingle')
						UNION SELECT audiodir.id as dir, audio.title as title, audio.id as audio 
							FROM audiodir, audio, audiotypes, audiousers 
							WHERE audio.id = audiodir.audio AND 
								directory = " . pg_escape_string($dirID) . " AND
								audio.id = audiousers.audio AND 
								(audiousers.permissions = 'o' OR audiousers.permissions = 'r' OR audiousers.permissions = 'rw') AND 
								audiousers.userid = $userid AND 
				    		audio.type = audiotypes.id AND (audiotypes.name = 'jingle')
				    order by title asc";
		} else {

			$sql = "SELECT audiodir.id as dir, audio.title as title, audio.id as audio 
						FROM audiodir, audio, audiotypes, audiogroups 
						WHERE audio.id = audiodir.audio AND 
							directory = " . pg_escape_string($dirID) . " AND
							audio.id = audiogroups.audio AND 
							(audiogroups.permissions = 'o' OR audiogroups.permissions = 'r' OR audiogroups.permissions = 'rw') AND 
							audiogroups.groupid = {$cfg['DPS']['allusersgroupid']} AND 
				    	audio.type = audiotypes.id AND (audiotypes.name = 'jingle')
				    order by title asc";
		}
		$files = $db->getAll($sql);
		foreach($files as $file) {
		  $list = $list . '<item text="' . htmlspecialchars($file['title']) . '" id="jgl' . $file['audio'] . '" im0="jingle16.png"/>';
		}
  	return $list;
	}
}
?>
		    
