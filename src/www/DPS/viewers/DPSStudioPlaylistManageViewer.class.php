<?php
/**
* @package DPS
*/
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['DPS']['dir']['root'] . '/DPS.class.php');

class DPSStudioPlaylistManageViewer extends Viewer {
	
	const module = 'DPS';
	
	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		
		$db = Database::getInstance($cfg['DPS']['dsn']);

		$sql = "SELECT
                    playlists.id, playlists.name, count(audioplaylists.id) AS count
                FROM
                    playlists
                LEFT OUTER JOIN
                    audioplaylists
                ON
                    playlists.id = audioplaylists.playlistid
                GROUP BY
                    playlists.id, playlists.name
                ORDER BY
                    playlists.name";
		$playlists = $db->getAll($sql);

        $playlist = null;
        $playlistID = $this->fieldData['dpsPlaylistID'];
        if ($playlistID != '') {
            $sql = "SELECT * FROM playlists WHERE id = $playlistID";
            $playlist = $db->getRow($sql);
        }

		$auth = Auth::getInstance();
		$userID = $auth->getUserID();

		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
		$this->assign('studioAccess',AuthUtil::getDetailedUserrealmAccess(
			array(3,21,34), $userID));
		$this->assign('playlists',$playlists);
        $this->assign('playlist',$playlist);
        $this->assign('Action', $this->fieldData['dpsAction']);
	}
}
?>
