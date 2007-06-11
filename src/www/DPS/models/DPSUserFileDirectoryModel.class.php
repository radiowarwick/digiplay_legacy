<?php
/**
 * @package DPS
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');
include_once($cfg['Logger']['dir']['root'] . '/BasicLogger.class.php');

/**
 * Model for user management
 */
class DPSUserFileDirectoryModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$dir = $this->fieldData['newParent'];
		$auth = Auth::getInstance();
		$userID = $auth->UserID();
		$uploaddir = $cfg['DPS']['root'] . '/Uploads/';
		$fname = md5($_FILES['ufile']['name'] . time() . $_FILES['ufile']['tmp_name']);
		$uploadfile = $uploaddir . $fname;
		
		if (move_uploaded_file($_FILES['ufile']['tmp_name'], $uploadfile)) {
			if($this->fieldData['type'] == "advert") {
				$type="advert";
			} else if($this->fieldData['type'] == "pre-rec") {
				$type="pre-rec";
			} else {
				$type="jingle";
			}
			if($handle = fopen($uploaddir . $fname . ".info", "w")) {
				$info = "uid: \n
				title: " . $this->fieldData['name'] . "\n
				artists: \n
				album: \n
				tracknum: \n
				genres: \n
				released: \n
				lengthfr: \n
				mcn: \n
				reclibid: \n
				origin: " . $auth->getUser() . "\n
				type: $type\n 
				cdpresult: N/A website upload\n
				reclibinsert: \n";
				if (fwrite($handle, $info) !== FALSE) {
					$id = exec('webimport.pl ' . $fname);
					if(is_numeric($id) && $id != '') {
						//insert into db stuff
						$audioDir['audioid'] = $id;
						$audioDir['dirid'] = $this->fieldData['dirID'];
						$audioDir['linktype'] = 0;
						$audioUser['audioid'] = $id;
						$audioUser['userid'] = $userID;
						$audioUser['permissions'] = 'o';
						$where = "audio = " . $id;
						$db->delete('audioDir',$where,true);
						$db->insert('audioDir',$audioDir,true);
						$db->insert('audioUsers',$audioUser,true);
					} else {
						//error
						BasicLogger::logMessage(
							"Error recieved when uploading file: '" . $id . "'",
							'error');
					}
				} else {
					//error
					BasicLogger::logMessage(
						"Error recieved when uploading file: Unable to write to $fname.info'",
						'error');
				}
			} else {
				//error
				BasicLogger::logMessage(
					"Error recieved when uploading file: Unable to open $fname.info file to write'",
					'error');
			}
		}
		fclose($handle);
	} else {
	}
	//if(is_numeric($dir) && is_numeric($this->fieldData['newParent'])) {
		//	$sql_update['parent'] = $this->fieldData['newParent'];
		//	$swhere = "id = " . pg_escape_string($dir);
		//  $db->update('dir',$sql_update,$swhere,true);
		//}
	}
	
	protected function processInvalid() {
		//No invalid processing required
		if($this->errors['form']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpsuserdirmove.tpl'),
				array("rootdir" => $this->fieldData['dirID'], "error" => "form"));
		} else {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpsuserdirmove.tpl'),
				array("rootdir" => $this->fieldData['dirID'], "error" => "perm"));
		}
	}
}
?>
