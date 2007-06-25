<?php
/**
 * @package DPS
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');
include_once($cfg['Logger']['dir']['root'] . '/BasicLogger.class.php');

class DPSUserFileDirectoryModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$dirID = pg_escape_string($this->fieldData['dirID']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$uploaddir = $cfg['DPS']['dir']['uploadDir'];
		
		$fname = md5($_FILES['ufile']['name'] . time() . $_FILES['ufile']['tmp_name']);
		$uploadfile = $uploaddir . "/" . $fname;
		
		if (move_uploaded_file($_FILES['ufile']['tmp_name'], $uploadfile)) {
			if($this->fieldData['type'] == "advert") {
				$type="2";
				$typeID = $cfg['DPS']['AdvertTypeID'];
				$package = $auth->getUser();
			} else if($this->fieldData['type'] == "pre-rec") {
				$type="3";
				$typeID = $cfg['DPS']['PrerecTypeID'];
			} else {
				$type="1";
				$typeID = $cfg['DPS']['JingleTypeID'];
				$package = $auth->getUser();
			}
			if($handle = fopen($uploadfile . ".info", "w")) {
				$info = "uid: \n"
				."title: " . $this->fieldData['name'] . "\n"
				."artists: \n"
				."album: $package\n"
				."tracknum: \n"
				."genres: \n"
				."released: \n"
				."lengthfr: \n"
				."mcn: \n"
				."reclibid: \n"
				."origin: " . $auth->getUser() . "\n"
				."type: $type\n"
				."cdpresult: N/A website upload\n"
				."reclibinsert: \n";
				if (fwrite($handle, $info) !== FALSE) {
					exec(
						escapeshellcmd($cfg['DPS']['dir']['scriptsDir'] . '/webimport.pl ') .
						escapeshellarg($fname),$id);
						$id = $id[0];
					if(is_numeric($id) && $id != '') {
						//insert into db stuff
						$audioDir['audioid'] = $id;
						$audioDir['dirid'] = $dirID;
						$audioDir['linktype'] = 0;
						$audioUser['audioid'] = $id;
						$audioUser['userid'] = $userID;
						$audioUser['permissions'] = $cfg['DPS']['fileRWO'];
						$audio['type'] = $typeID;
						$where = "audioid = " . $id;
						$db->delete('audiodir',$where,true);
						$where = "id = " . $id;
						$db->update('audio', $audio, $where, true);
						$db->insert('audiodir',$audioDir,true);
						$db->insert('audiousers',$audioUser,true);
						$gperm['groupid'] = $cfg['Auth']['AdminGroup'];
						$gperm['audioid'] = $id;
						$gperm['permissions'] = 'B' . $cfg['DPS']['fileRWO'] . 'B';
						$db->insert('audiogroups',$gperm,false);
					} else {
						//error
						BasicLogger::logMessage(
							"Error recieved when uploading file: '" . $id . "'",
							'error');
						$this->errors['form'] = "Unable to import file (file may be of invalid type)";
						exec("rm $uploadfile");
						exec("rm $uploadfile.info");
						DPSUserFileDirectoryModel::processInvalid();
					}
				} else {
					//error
					BasicLogger::logMessage(
						"Error recieved when uploading file: Unable to write to $fname.info'",
						'error');
					$this->errors['form'] = "Unable to write to info file";
					exec("rm $uploadfile");
					DPSUserFileDirectoryModel::processInvalid();
				}
				fclose($handle);
			} else {
				//error
				BasicLogger::logMessage(
					"Error recieved when uploading file: Unable to open $fname.info file to write'",
					'error');
				$this->errors['form'] = "Unable to open info file for writing";
				exec("rm $uploadfile");
				DPSUserFileDirectoryModel::processInvalid();
			}
		} else {
			if($_FILES['ufile']['error'] == 1) {
				//error
				$this->errors['form'] = "File too large for upload";
			} else {
				//error
				BasicLogger::logMessage(
					"Error recieved when uploading file: Unable to move file for processing ({$_FILES['ufile']['error']}",
					'error');
				$this->errors['form'] = "Unable to movefile for processing";
			}
			DPSUserFileDirectoryModel::processInvalid();
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
		if($this->errors['form']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpsuserfileupload.tpl'),
				array("rootdir" => $this->fieldData['dirID'], "error" => "form", 
					"Emessage" => $this->errors['form']));
		} else {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpsuserfileupload.tpl'),
				array("rootdir" => $this->fieldData['dirID'], "error" => "perm"));
		}
	}
}
?>
