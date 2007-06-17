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
				$type="advert";
			} else if($this->fieldData['type'] == "pre-rec") {
				$type="pre-rec";
			} else {
				$type="jingle";
			}
			if($handle = fopen($uploadfile . ".info", "w")) {
				$info = "uid: \n"
				."title: " . $this->fieldData['name'] . "\n"
				."artists: \n"
				."album: \n"
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
						$where = "audioid = " . $id;
						$db->delete('audiodir',$where,true);
						$db->insert('audiodir',$audioDir,true);
						$db->insert('audiousers',$audioUser,true);
					} else {
						//error
						BasicLogger::logMessage(
							"Error recieved when uploading file: '" . $id . "'",
							'error');
						$this->errors['form'] = "Unable to import file (file may be of invalid type)";
						DPSUserFileDirectoryModel::processInvalid(); //This should work(I hope)
					}
				} else {
					//error
					BasicLogger::logMessage(
						"Error recieved when uploading file: Unable to write to $fname.info'",
						'error');
					$this->errors['form'] = "Unable to write to info file";
					DPSUserFileDirectoryModel::processInvalid(); //This should work(I hope)
				}
				fclose($handle);
			} else {
				//error
				BasicLogger::logMessage(
					"Error recieved when uploading file: Unable to open $fname.info file to write'",
					'error');
				$this->errors['form'] = "Unable to open info file for writing";
				DPSUserFileDirectoryModel::processInvalid(); //This should work(I hope)
			}
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
		if($this->errors['form']) {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpsuserfileupload.tpl'),
				array("rootdir" => $this->fieldData['dirID'], "error" => "form"));
		} else {
			MVCUtils::redirect(MVCUtils::getTemplateID('dpsuserfileupload.tpl'),
				array("rootdir" => $this->fieldData['dirID'], "error" => "perm"));
		}
	}
}
?>
