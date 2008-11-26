<?php
/**
 * @package DPS
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['Auth']['dir']['root'] . '/AuthUtil.class.php');
include_once($cfg['DPS']['dir']['root'] . '/DPS.class.php');

class DPSShowPlanSelectScriptViewer extends Viewer {
		
	const module = 'DPS';
		
	protected function setupTemplate() {
		global $cfg;
		parent::setupTemplate();
		
		$db = Database::getInstance($cfg['DPS']['dsn']);
		
		$itemID = pg_escape_string($this->fieldData['itemID']);
		$auth = Auth::getInstance();
		$userID = $auth->getUserID();
		$date = time();
        
		if(is_numeric($itemID) && isset($itemID)) {
            // GET SHOW INFO
			$show_query = "SELECT DISTINCT BIT_OR(v_tree_showplan.permissions) 
			FROM showitems, v_tree_showplan 
			WHERE showitems.showplanid = v_tree_showplan.id AND 
				v_tree_showplan.userid = $userID AND 
				showitems.id = $itemID";
			$checkShows = $db->getOne($show_query);
			if(substr($checkShows,0,1) == "1") {
				if(substr($checkShows,1,1) == "1") {	
					$this->assign('write', 't');
				} else {
					$this->assign('write', 'f');
				}
				$show_sql = "SELECT showplans.* FROM showplans, showitems
					WHERE showitems.showplanid = showplans.id
					AND showitems.id = " . $itemID;
				$show = $db->getRow($show_sql);
				$show['niceAirDate'] = date("d/m/y",$show['showdate']);
				$show['niceAirTime'] = date("g a",$show['showdate']);
				$show['niceCreateDate'] = date("d/m/y",$show['creationdate']);
				$show['niceCreateTime'] = date("g a",$show['creationdate']);

                // GET ITEM INFO
				$items_sql = "SELECT * FROM showitems
					WHERE showplanid = " . $show['id'] . "
					ORDER BY position ASC";
				$items = $db->getAll($items_sql);
				$time = $show['showdate'];
				$i = 0;
				foreach($items as &$item) {
					if($item['id'] == $itemID) {
						$item['time'] = $time;
						$item['niceTime'] = date("H:i:s",$item['time']);
						$item['niceLength'] = ((int)($item['length'] / 60)) 
							. ":" . ($item['length'] -
							(((int)($item['length'] / 60))*60));
						if($item['audio'] != '') {
							$sql = "SELECT audio.title AS title,
								audiotypes.name AS type,
								audio.length_smpl AS len
								FROM audio, audiotypes
								WHERE audio.type = audiotypes.id
								AND audio.id = " . $item['audio'];
							$stuff = $db->getRow($sql);
							$item['audioTitle'] = $stuff['title'];
							$item['nature'] = $stuff['type'];
							$item['niceAudioLength'] =
								round((($stuff['len']/44100)/60)) .  ":" .
								(($stuff['len']/44100)%60);
						} else {
							$item['nature'] = 'unknown';
						}
						if($item['script'] != '') {
							$sql = "SELECT name, length FROM scripts
								WHERE id = " . $item['script'];
							$stuff = $db->getRow($sql);
							$item['scriptName'] = $stuff['name'];
							$item['niceScriptLength'] =
								((int)($stuff['length'] / 60)) . ":" .
								($stuff['length'] -
								(((int)($stuff['length'] / 60))*60));
						}
						break;
					}
					$time = $time + $item['length'];
					$i++;
				}
				$this->assign('show', $show);
				$this->assign('item', $items[$i]);

                // GET LIST OF SCRIPTS
                $script_query = "SELECT scripts.*, v_tree_script.permissions
				    FROM v_tree_script, scripts
				    WHERE v_tree_script.userid = $userID
					    AND v_tree_script.id = scripts.id
					    AND v_tree_script.permissions & B'{$cfg['DPS']['fileR']}' = '{$cfg['DPS']['fileR']}'
			        ORDER BY scripts.name asc";
		        $scripts = $db->getAll($script_query);
		
                foreach($scripts as &$script) {
    			    $script['niceCreateDate'] = date("d/m/y",$script['creationdate']);
	    		    $script['niceCreateTime'] = date("g a",$script['creationdate']);
    	    		$script['text'] = $script['name'] . " - " .
	    	    	$script['niceCreateDate'] . " - " . $script['niceCreateTime'];
		    	    $sql = "SELECT BIT_OR(v_tree_dir.permissions) 
			    	    FROM v_tree_script, v_tree_dir 
    				    WHERE v_tree_script.id = {$script['id']}
	    				    AND v_tree_script.parent = v_tree_dir.id
    	    				AND v_tree_dir.userid = $userID";
	    	    	$script['parentperm'] = $db->getOne($sql);
		        }
		
                $this->assign('scripts', $scripts);
			} else {
				$this->assign('error',
					'You do not have permission to edit that item.');
			}
		} else {
			$this->assign('error','Invalid Item ID supplied');
		}
		$this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1),
			$userID));
	}
}
?>
