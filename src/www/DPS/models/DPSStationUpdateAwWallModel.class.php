<?php
/**
 * @package DPS
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['MVC']['dir']['root'] . '/MVCUtils.class.php');
MVCUtils::includeModel('Model', 'tkfecommon');

/**
 * Model for user management
 */
class DPSStationUpdateAwWallModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$name = pg_escape_string($this->fieldData['name']);
		$desc = pg_escape_string($this->fieldData['desc']);
		$AwWallID = pg_escape_string($this->fieldData['AwWallID']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		if($this->fieldData['Submit'] == "Remove Page") {
			$sql = "SELECT set_id FROM aw_walls where id=" . $AwWallID;
			$AwSetID = $db->getOne($sql);
			$sql = "select count(*) from aw_walls where set_id=" . $AwSetID;
			$check = $db->getOne($sql);
			//cant delete last page
			if($check > 1) {
				$where = "wall_id = " . $AwWallID;
				$db->delete('aw_items', $where, true);
				$where = "id = " . $AwWallID;
				$db->delete('aw_walls', $where, true);
				$page = pg_escape_string($this->fieldData['page']);
				$sql = "SELECT * FROM aw_walls 
					WHERE set_id=" . $AwSetID . " 
					AND page > $page order by page asc";
				$pages = $db->getAll($sql);
				foreach($pages as $p) {
					$update['page'] = ($p['page'] - 1);
					$where = "id = " . $p['id'];
					$db->update('aw_walls',$update,$where,true);
				}
			}
		} elseif($name != '' && $AwWallID != '' && is_numeric($AwWallID)) {
			$AwWall = array();
			$AwWall['name'] = $name;
			$AwWall['description'] = $desc;
			$atWhere = "id = " . $AwWallID;
			$db->update('aw_walls', $AwWall, $atWhere, true);
			
			$sql = "SELECT set_id FROM aw_walls WHERE id = $AwWallID LIMIT 1";
			$AwSetID = $db->getOne($sql);
			$sql = "SELECT count(*) 
				FROM v_tree_dir 
				WHERE v_tree_dir.id = $AwSetID
					AND v_tree_dir.userid = {$cfg['DPS']['systemUserID']}
					AND v_tree_dir.permissions & B'" . $cfg['DPS']['fileW'] .
						"' = '" . $cfg['DPS']['fileW'] . "'";
			$check = $db->getOne($sql);
			if($check > 0) {
				$where = "set_id = $AwSetID AND groupid = " . $cfg['DPS']['allusersgroupid'];
				$db->delete('aw_sets_groups',$where,true);
				
				$sql = "SELECT COUNT(*) FROM aw_items, aw_walls 
					WHERE aw_items.wall_id = aw_walls.id
					AND aw_walls.set_id = " . $AwSetID;
				$AwItemscount = $db->getOne($sql);
				$sql = "SELECT count(*) FROM (SELECT aw_items.audioid 
					FROM aw_items, aw_walls, v_tree_audio
					WHERE aw_walls.set_id = $AwSetID
						AND aw_items.wall_id = aw_walls.id
						AND aw_items.audioid = v_tree_audio.id
						AND v_tree_audio.permissions & B'" . $cfg['DPS']['fileR'] . "'
					 = '" . $cfg['DPS']['fileR'] . "'
					GROUP BY aw_items.audioid) as Q1";

				$permCount = $db->getOne($sql);
				if($permCount == $AwItemscount) {
					if($this->fieldData['readAll'] == "on"
						&& $this->fieldData['writeAll'] == "on") {
						$perm = array();
						$perm['groupid'] = $cfg['DPS']['allusersgroupid'];
						$perm['set_id'] = $AwSetID;
						$perm['permissions'] = $cfg['DPS']['fileRW'];
						$db->insert('aw_sets_groups',$perm,false);
					} elseif($this->fieldData['writeAll'] == "on") {
						$perm = array();
						$perm['groupid'] = $cfg['DPS']['allusersgroupid'];
						$perm['set_id'] = $AwSetID;
						$perm['permissions'] = $cfg['DPS']['fileRW'];
						$db->insert('aw_sets_groups',$perm,false);
					} elseif($this->fieldData['readAll'] == "on") {
						$perm = array();
						$perm['groupid'] = $cfg['DPS']['allusersgroupid'];
						$perm['set_id'] = $AwSetID;
						$perm['permissions'] = $cfg['DPS']['fileR'];
						$db->insert('aw_sets_groups',$perm,false);
					}
				} else {
					$this->errors['model'] = "All audio elements in this audio wall set must be public";
				}
			}
		}
	}
	
	protected function processInvalid() {
		//No invalid processing required
	}
}
?>
