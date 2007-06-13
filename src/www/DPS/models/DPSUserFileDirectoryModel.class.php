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
		$dirID = pg_escape_string($this->fieldData['newParent']);
		$auth = Auth::getInstance();
		$userID = $auth->UserID();
		$uploaddir = $cfg['DPS']['uploadDir'];
		
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
			if($handle = fopen($uploadfile . ".info", "w")) {
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
					$id = exec(
						escapeshellcmd($cfg['DPS']['dir']['scriptsDir'] . 'webimport.pl ') .
						escapeshellarg($fname));
					if(is_numeric($id) && $id != '') {
						//insert into db stuff
						$audioDir['audioid'] = $id;
						$audioDir['dirid'] = $dirID;
						$audioDir['linktype'] = 0;
						$audioUser['audioid'] = $id;
						$audioUser['userid'] = $userID;
						$audioUser['permissions'] = $cfg['DPS']['fileRWO'];
						$where = "audio = " . $id;
						$db->delete('audioDir',$where,true);
						$db->insert('audioDir',$audioDir,true);
						$db->insert('audioUsers',$audioUser,true);
					} else {
						//error
						BasicLogger::logMessage(
							"Error recieved when uploading file: '" . $id . "'",
							'error');
						$this->errors['form'] = "Invalid audio id returned from import";
						processInvalid(); //This should work(I hope)
					}
				} else {
					//error
					BasicLogger::logMessage(
						"Error recieved when uploading file: Unable to write to $fname.info'",
						'error');
					$this->errors['form'] = "Unable to write to info file";
					processInvalid(); //This should work(I hope)
				}
				fclose($handle);
			} else {
				//error
				BasicLogger::logMessage(
					"Error recieved when uploading file: Unable to open $fname.info file to write'",
					'error');
				$this->errors['form'] = "Unable to open info file for writing";
				processInvalid(); //This should work(I hope)
			}
		}
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
