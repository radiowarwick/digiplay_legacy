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
class DPSUserUpdateAwWallModel extends Model {
	
	const module = 'DPS';
	
	protected function processValid() {
		global $cfg;
		$db = Database::getInstance($cfg['DPS']['dsn']);
        		
		$name = pg_escape_string($this->fieldData['name']);
		$desc = pg_escape_string($this->fieldData['desc']);
        
        $awwallID = pg_escape_string($this->fieldData['awwallID']);
		if($this->fieldData['Submit'] == "Remove Page") {
			$sql = "SELECT set_id FROM aw_walls WHERE id=" . $awwallID;
			$awsetID = $db->getOne($sql);
			$sql = "SELECT COUNT(*) FROM aw_walls WHERE set_id=" . $awsetID;
			$check = $db->getOne($sql);
			//cant delete last page
			if($check > 1) {
				$where = "wall_id = " . $awwallID;
				$db->delete('aw_items', $where, true);
				$where = "id = " . $awwallID;
				$db->delete('aw_walls', $where, true);
				$page = pg_escape_string($this->fieldData['page']);
				$sql = "SELECT * FROM aw_walls
					WHERE set_id=" . $awsetID . "
					AND page > $page ORDER BY page asc";
				$pages = $db->getAll($sql);
				foreach($pages as $p) {
					$update['page'] = ($p['page'] - 1);
					$where = "id = " . $p['id'];
					$db->update('aw_walls',$update,$where,true);
				}
			}
		} elseif($name != '' && $awwallID != '' && is_numeric($awwallID)) {
			$awwall = array();
			$awwall['name'] = $name;
			$awwall['description'] = $desc;
			$atWhere = "id = " . $awwallID;
			$db->update('aw_walls', $awwall, $atWhere, true);
			
            $auth = Auth::getInstance();
			$userID = $auth->getUserID();
			$sql = "SELECT COUNT(*) FROM v_tree_aw_sets, aw_walls
				WHERE v_tree_aw_sets.userid = $userID
				AND v_tree_aw_sets.id = aw_walls.set_id
				AND aw_walls.id = $awwallID
				AND v_tree_aw_sets.permissions & B'" . $cfg['DPS']['fileO'] . "' = '" . $cfg['DPS']['fileO'] . "'";
			$check = $db->getOne($sql);
			if($check > 0) {
				$sql = "SELECT set_id FROM aw_walls 
					WHERE id = $awwallID LIMIT 1";
				$awsetID = $db->getOne($sql);
				$where = "set_id = $awsetID 
					AND group_id = " . $cfg['DPS']['allusersgroupid'];
				$db->delete('aw_sets_groups',$where,true);
				
				$sql = "SELECT COUNT(*) FROM aw_items, aw_walls 
					WHERE aw_items.wall_id = aw_walls.id
					AND aw_walls.set_id = " . $awsetID;
				$awitemcount = $db->getOne($sql);
				$sql = "SELECT count(*) FROM (SELECT aw_items.audio_id 
					FROM aw_items, aw_walls, v_tree_audio
					WHERE aw_walls.set_id = $awsetID
						AND aw_items.wall_id = aw_walls.id
						AND aw_items.audio_id = v_tree_audio.id
						AND v_tree_audio.permissions & B'" . $cfg['DPS']['fileR'] . "'
					 = '" . $cfg['DPS']['fileR'] . "'
					GROUP BY aw_items.audio_id) as Q1";
					
				$permCount = $db->getOne($sql);
				if($permCount >= $awitemcount) {
					if($this->fieldData['readAll'] == "on"
						&& $this->fieldData['writeAll'] == "on") {
						$perm = array();
						$perm['group_id'] = $cfg['DPS']['allusersgroupid'];
						$perm['set_id'] = $awsetID;
						$perm['permissions'] = $cfg['DPS']['fileRW'];
						$db->insert('aw_sets_groups',$perm,false);
					}elseif($this->fieldData['writeAll'] == "on") {
						$perm = array();
						$perm['group_id'] = $cfg['DPS']['allusersgroupid'];
						$perm['set_id'] = $awsetID;
						$perm['permissions'] = $cfg['DPS']['fileRW'];
						$db->insert('aw_sets_groups',$perm,false);
					}elseif($this->fieldData['readAll'] == "on") {
						$perm = array();
						$perm['group_id'] = $cfg['DPS']['allusersgroupid'];
						$perm['set_id'] = $awsetID;
						$perm['permissions'] = $cfg['DPS']['fileR'];
						$db->insert('aw_sets_groups',$perm,false);
					}
				} else {
					$this->errors['model'] =
						"All audio elements in this audiowall set must be public";
				}
			}
		}
	}
		
	protected function processInvalid() {
        print "Invalid";
		//No invalid processing required
	}
}
?>
