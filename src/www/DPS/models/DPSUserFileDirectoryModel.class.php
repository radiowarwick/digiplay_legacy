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
		
		if (!is_dir($uploaddir)) {
			$this->errors['form'] = "Upload direcotry does not exist. Please
                contact the administrator.";
            BasicLogger::logMessage("$uploaddir is not a directory.", "DPS", "debug");
            DPSUserFileDirectoryModel::processInvalid();
		    return;
        }
		if (!is_writeable($uploaddir)) {
			$this->errors['form'] = "Upload directory is not writeable. Please
                contact the administrator.";
            BasicLogger::logMessage("$uploaddir is not writeable.", "DPS", "debug");
            DPSUserFileDirectoryModel::processInvalid();
			return;
		}

		// Generate MD5 hash for uploaded file
		$fname = md5($_FILES['ufile']['name'] . time() . $_FILES['ufile']['tmp_name']);
		$uploadfile = $uploaddir . "/" . $fname;
		
		// Move the uploaded file from the system tmp dir to the DPS/uploads dir.
		if (move_uploaded_file($_FILES['ufile']['tmp_name'], $uploadfile . ".wav")) {
            // Determine various properties of file
			if($this->fieldData['type'] == "advert") {
				$type="3";
				$typeID = $cfg['DPS']['AdvertTypeID'];
			} else if($this->fieldData['type'] == "pre-rec") {
				$type="4";
				$typeID = $cfg['DPS']['PrerecTypeID'];
			} else {
				$type="2";
				$typeID = $cfg['DPS']['JingleTypeID'];
			}
			$package = $this->fieldData['package'];
			
			// Try to write info file for upload
			if($handle = fopen($uploadfile . ".info", "w")) {
				$info = "uid: $fname\n"
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
				// if successful in writing info, run the import script
				if (fwrite($handle, $info) !== FALSE) {
					exec(
						escapeshellcmd($cfg['DPS']['dir']['scriptsDir'] . '/dpswebimport.pl ') .
						escapeshellarg($fname),$id);
						$id = $id[0];
					// import script returns an ID of the new file in the database
					if(is_numeric($id) && $id != '') {
						//insert into db directory, user, group and permissions stuff
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
						// failed to import the file
						BasicLogger::logMessage(
							"Error recieved when uploading file: '" . $id . "'",
							"DPS", 'error');
						$this->errors['form'] = "Unable to import file (file may be of invalid type): " . $id;
						exec("rm $uploadfile.wav");
						exec("rm $uploadfile.info");
						DPSUserFileDirectoryModel::processInvalid();
					}
				} else {
					// failed to write the info file
					BasicLogger::logMessage(
						"Error recieved when uploading file: Unable to write to $fname.info'",
						'error');
					$this->errors['form'] = "Unable to write to info file";
					exec("rm $uploadfile.wav");
					DPSUserFileDirectoryModel::processInvalid();
				}
				fclose($handle);
			} else {
				// failed to open the info file to write into it
				BasicLogger::logMessage(
					"Error recieved when uploading file: Unable to open $fname.info file to write'",
					'error');
				$this->errors['form'] = "Unable to open info file for writing";
				exec("rm $uploadfile.wav");
				DPSUserFileDirectoryModel::processInvalid();
			}
		} else {
			// failed to move file into uploads directory
			if($_FILES['ufile']['error'] == 1) {
				$this->errors['form'] = "File too large for upload to this server.";
			} else if ($_FILES['ufile']['error'] == 2) {
				$this->errors['form'] = "File too large for upload via this form.";
			} else if ($_FILES['ufile']['error'] == 3) {
				$this->errors['form'] = "The file was only partially uploaded.";
			} else if ($_FILES['ufile']['error'] == 4) {
				$this->errors['form'] = "No file was uploaded.";
			} else if ($_FILES['ufile']['error'] == 6) {
				$this->errors['form'] = "Missing temporary directory to upload file.";
			} else if ($_FILES['ufile']['error'] == 7) {
				$this->errors['form'] = "Failed to write to disk.";
			} else {
				// otherwise throw a boring general error
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
