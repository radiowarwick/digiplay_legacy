<?php
/**
 * @package FrontEnds
 * @subpackage MVC
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
      $query = "SELECT audio.md5 as md5, archives.localpath as path from audio, archives WHERE audio.id = " . $trackid . " and audio.archive = archives.id";
      $file = $db->getRow($query);
      $filename = escapeshellarg($file['path'] . "/" . escapeshellarg($file['md5'][0]) . "/" . escapeshellarg($file['md5']);
      header('Pragma: public');
      header('Expires: 0');
      header('Content-Transfer-Encoding: binary');
      #header('Cache-Control: no-store,no-cache,must-revalidate');
      header('Content-Length: 180373');
      header('Content-Disposition: attachment; filename="track.mp3"');
      header('Content-type: audio/mpeg');
      passthru($cfg['general']['toolkitRoot'] . "/DPS/encode-digiplay-file.sh " . $filename); 
    }
  }
}

?>
