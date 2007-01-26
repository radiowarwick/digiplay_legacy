<?php
/**
 * @package FrontEnds
 * @subpackage MVC
 */
include_once($cfg['DBAL']['dir']['root'] . '/Database.class.php');
include_once($cfg['Auth']['dir']['root'] . '/AuthUtil.class.php');
class DPSShowPlanDetailsViewer extends Viewer {
	
  const module = 'DPS';
	
  protected function setupTemplate() {
    global $cfg;
    parent::setupTemplate();
    
    $db = Database::getInstance($cfg['DPS']['dsn']);
   
	 	$showID = pg_escape_string($this->fieldData['showID']);
    $auth = Auth::getInstance();
    $userID = $auth->getUserID();
    $date = time();
		if(is_numeric($showID)) {
			$show_query = "SELECT count(*) FROM showplanusers where 
										showplanusers.userid = " . $userID . " AND
										showplanusers.showplanid = " . $showID . " AND 
										(showplanusers.permissions = 'o' OR showplanusers.permissions = 'rw')";
    	$checkShows = $db->getOne($show_query);
			if($checkShows == 0) {
				$show_query = "SELECT count(*) FROM showplangroups, groupmembers where 
										showplangroups.groupid = groupmembers.groupid and 
										showplangroups.showplanid = $showID  and 
										groupmembers.userid =  $userID and 
										(showplangroups.permissions = 'o' OR showplangroups.permissions = 'rw')";
				$checkShows = $db->getOne($show_query);
			}
			if($checkShows > 0) {
				$show_sql = "SELECT * FROM showplans where id = " . $showID;
				$show = $db->getRow($show_sql);
      	$show['D'] = date("j",$show['showdate']);
      	$show['M'] = date("n",$show['showdate']);
      	$show['Y'] = date("Y",$show['showdate']);
      	$show['h'] = date("H",$show['showdate']);
      	$show['m'] = date("i",$show['showdate']);
      	//$show['niceAirTime'] = date("g a",$show['showdate']);
      	//$show['niceCreateDate'] = date("m/d/y",$show['creationdate']);
      	//$show['niceCreateTime'] = date("g a",$show['creationdate']);
				$show['niceProducer'] = AuthUtil::getUsername($show['creator']);
				if($show['showdate'] > $date) {
					$this->assign('done', 'f');
				} else {
					$this->assign('done', 't');
				}
				for($i=1;$i<13;$i++){
					switch($i) {
					case 2:
						$month = "Febuary";
						break;
					case 3:
						$month = "March";
						break;
					case 4:
						$month = "April";
						break;
					case 5:
						$month = "May";
						break;
					case 6:
						$month = "June";
						break;
					case 7:
						$month = "July";
						break;
					case 8:
						$month = "August";
						break;
					case 9:
						$month = "September";
						break;
					case 10:
						$month = "October";
						break;
					case 11:
						$month = "November";
						break;
					case 12:
						$month = "December";
						break;
					default:
						$month = "January";
					}
					if($i == $show['M']) {
						$formOpts['month'] = $formOpts['month'] . "<option selected value='$i'>$month</option>";
					} else {
						$formOpts['month'] = $formOpts['month'] . "<option value='$i'>$month</option>";
					}
				}
				for($i=1;$i<32;$i++){
					if($i == $show['D']) {
						$formOpts['date'] = $formOpts['date'] . "<option selected value='$i'>$i</option>";
					} else {
						$formOpts['date'] = $formOpts['date'] . "<option value='$i'>$i</option>";
					}
				}
				for($i=2006;$i<2013;$i++){
					if($i == $show['Y']) {
						$formOpts['year'] = $formOpts['year'] . "<option selected value='$i'>$i</option>";
					} else {
						$formOpts['year'] = $formOpts['year'] . "<option value='$i'>$i</option>";
					}
				}
				$this->assign('formOpts',$formOpts);
				$this->assign('show', $show);
			} else {
				$this->assign('error', 'You do not have permission to edit that show.');
			}
		} else {
			$this->assign('error', 'Invalid Show ID supplied');
		}

    $this->assign('Admin',AuthUtil::getDetailedUserrealmAccess(array(1), $userID));
  }
}

?>
