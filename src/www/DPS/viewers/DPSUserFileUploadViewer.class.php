<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');

class DPSUserFileUploadViewer extends Viewer {

  const module = 'DPS';
  protected $activeNode = 'foldersTree';

  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();
		$db = Database::getInstance($cfg['DPS']['dsn']);
		$auth = Auth::getInstance();
    $userID = $auth->getUserID();
		$dirID = $this->fieldData['rootdir'];
		if(!is_numeric($dirID)) {
			$this->assign('permError', 't');
		} else {
			$flag = false;
			$sql = "select count(*) from dirusers where userid = " . $userID . " and directory = " . pg_escape_string($dirID) . "
							and (permissions = 'o' or permissions = 'rw' or permissions = 'w')";
			$check = $db->getOne($sql);
			if($check > 0) {
				$flag = true;
			} else {
				$sql = "select count(*) from dirgroups, groupmembers where groupmembers.userid = " . $userID . " and
						groupmembers.groupid = dirgroups.groupid and directory = " . pg_escape_string($dirID) . "
						and (dirgroups.permissions = 'o' or dirgroups.permissions = 'rw' or dirgroups.permissions = 'w')";
				$check = $db->getOne($sql);
				if($check > 0) {
					$flag = true;
				}
			}
			if($flag) {
				$sql = "select * from dir where id = " . pg_escape_string($dirID);
				$folder = $db->getRow($sql);
				$this->assign('folder', $folder);
			} else {
				$this->assign('permError', 't');
			}
		}
  }
}
