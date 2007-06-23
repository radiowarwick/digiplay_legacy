<?php
/**
 * @package DPS
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSMp3PreviewViewer extends Viewer {
	
	const module = 'DPS';
	
	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$trackid = $this->fieldData['trackID'];
		if(is_numeric($trackid)) {
			$query = "SELECT title, artist, md5, path FROM v_audio 
				WHERE id = " . $trackid;
			$file = $db->getRow($query);
			$filename = escapeshellarg($file['path']) . "/" .
				escapeshellarg($file['md5'][0]) . "/" .
				escapeshellarg($file['md5']);
			header('Pragma: public');
			header('Expires: 0');
			header('Content-Transfer-Encoding: binary');
			#header('Cache-Control: no-store,no-cache,must-revalidate');
			header('Content-Length: 180373');
			$fileN=str_replace(' ','_',$file['name']) . '-' .
				str_replace(' ','_',$file['artist']) . '.mp3';
			$fileN=str_replace('"',"",$fileN);
			$headstr = 'Content-Disposition: attachment; filename="' . $fileN . "'";
			header($headstr);
			header('Content-type: audio/mpeg');
			passthru($cfg['general']['toolkitRoot'] .
				"/DPS/encode-digiplay-file.sh " . $filename); 
		}
	}
}
?>
