<?
include('session.php');

if( $output == "true" ) {
  $_SESSION["username"]=$username;
  $_SESSION["password"]=$password;
  $_SESSION["timestamp"]=time()+900;
include('header.php');
  ?>
<table width=100%>
  <tr>
    <td valign='top' width=100px>
<?
include('contents.php');
?>
    </td>
    <td valign=top>
<?
$ActiveID = 0;
if($_POST['Submit'] == "Add") {
  $name = pg_escape_string($_POST['name']);
  $notes = pg_escape_string($_POST['notes']);
  $parentNode = pg_escape_string($_POST['parentNode']);
  $security = pg_escape_string($_POST['security']);
  $sql = "INSERT INTO dir (parent,name, notes) VALUES ($parentNode,'$name','$notes')";
  pg_query($sql);
  $sql = "SELECT last_value from dir_id_seq";
  $lastID = pg_query($sql);
  $lastID = pg_fetch_result($lastID,0,0);
  $ActiveID = $lastID;
  $sql = "SELECT id FROM users WHERE username = '$username'";
  $userID = pg_query($sql);
  $userID = pg_fetch_result($userID,0,0);
  $sql = "INSERT INTO dirusers (directory, userid, permissions) VALUES ($lastID, $userID, 'w')";
  pg_query($sql);
  if($security == 'read') {
    $sql = "SELECT id FROM groups where name = 'everyone'";
    $groupID = pg_query($sql);
    $groupID = pg_fetch_result($groupID,0,0);
    $sql = "INSERT INTO dirgroups (directory, groupid, persmissions) VALUES ($lastID, $groupID, 'r')";
    pg_query($sql);
  } else if ($security == 'write') {
    $sql = "SELECT id FROM groups where name = 'everyone'";
    $groupID = pg_query($sql);
    $groupID = pg_fetch_result($groupID,0,0);
    $sql = "INSERT INTO dirgroups (directory, groupid, persmissions) VALUES ($lastID, $groupID, 'w')";
    pg_query($sql);		    
  }
} else if($_POST['Submit'] == "Update") {
  $name = pg_escape_string($_POST['name']);
  $notes = pg_escape_string($_POST['notes']);
  $parentNode = pg_escape_string($_POST['parentNode']);
  $nodeID = pg_escape_string($_POST['nodeID']);
  $ActiveID = $nodeID;
  $security = pg_escape_string($_POST['security']);
  $sql = "UPDATE dir SET name ='$name', notes='$notes', parent=$parentNode WHERE id = $nodeID";
  pg_query($sql);
  if($security == 'read') {
      $sql = "SELECT id FROM groups where name = 'everyone'";
      $groupID = pg_query($sql);
      $groupID = pg_fetch_result($groupID,0,0);
      $sql = "DELETE FROM dirgroups where directory = $nodeID AND groupid = $groupID";
      pg_query($sql);
      $sql = "INSERT INTO dirgroups (directory, groupid, persmissions) VALUES ($nodeID, $groupID, 'r')";
      pg_query($sql);
  } else if ($security == 'write') { 
      $sql = "SELECT id FROM groups where name = 'everyone'";
      $groupID = pg_query($sql);
      $groupID = pg_fetch_result($groupID,0,0);
      $sql = "DELETE FROM dirgroups where directory = $nodeID AND groupid = $groupID";
      pg_query($sql);
      $sql = "INSERT INTO dirgroups (directory, groupid, persmissions) VALUES ($nodeID, $groupID, 'w')";
      pg_query($sql);
  } else {
      $sql = "SELECT id FROM groups where name = 'everyone'";
      $groupID = pg_query($sql);
      $groupID = pg_fetch_result($groupID,0,0);
      $sql = "DELETE FROM dirgroups where directory = $nodeID AND groupid = $groupID";
      pg_query($sql);			      
  }
} else if($_POST['Submit'] == "Delete Folder") {
  $nodeID = pg_escape_string($_POST['nodeID']);
  $sql = "SELECT * FROM dir WHERE parent = $nodeID";
  $nodeCheck = pg_query($sql);
  $sql = "SELECT * FROM audiodir WHERE directory = $nodeID";
  $fileCheck = pg_query($sql);
  if(pg_num_rows($nodeCheck) == 0 && pg_num_rows($fileCheck) == 0) {
    $sql = "DELETE FROM dirusers where directory = $nodeID";
    pg_query($sql);
    $sql = "DELETE FROM dirgroups where directory = $nodeID";
    pg_query($sql);
    $sql = "DELETE FROM dir where id = $nodeID";
    pg_query($sql);
  }
}
?>
<!-- Code for browser detection -->
<script src="ua.js"></script>
<script LANGUAGE="JavaScript">
function openIFrame(URL){
        //ifId=document.getElementById('basefrm')
        New_URL = "https://www.radio.warwick.ac.uk/dps/folderInfo.php?folderID=" + URL + "&username=<?=$username?>";
        frames['basefrm'].location.href = New_URL;
	//parent.basefrm.href = "www.radio.warwick.ac.uk/dps/folderInfo.php?folderID=" . URL;
}
</script>
<!-- Infrastructure code for the tree -->
<script src="ftiens4.js"></script>

<!-- Execution of the code that actually builds the specific tree.
     The variable foldersTree creates its structure with calls to
	 gFld, insFld, and insDoc -->
<script>
USETEXTLINKS = 1
STARTALLOPEN = 0
PRESERVESTATE = 1
ICONPATH = '' 
HIGHLIGHT = 0
MUSIC = 'note.jpg'
<?
function treeSetup($arg_1,$arg_2,$username) {
  $sql = "SELECT DISTINCT dir.id, dir.parent, dir.name, dir.notes FROM dir, users, dirusers WHERE 
  dir.id = dirusers.directory AND (dirusers.permissions = 'r' OR dirusers.permissions = 'w') AND dirusers.userid = users.id AND users.username = '$username' 
  AND dir.parent = " . pg_escape_string($arg_1);
  $users = pg_query($sql);
  $sql = "SELECT DISTINCT dir.id, dir.parent, dir.name, dir.notes FROM dir, dirgroups, groups, groupmembers, users WHERE
            dir.id = dirgroups.directory AND (dirgroups.persmissions= 'r' OR dirusers.permissions = 'w') AND dirgroups.groupid = groups.id AND
            groups.id = groupmembers.groupid AND groupmembers.userid = users.id AND users.username = '$username'
            AND dir.parent = " . pg_escape_string($arg_1); 
  $groups = pg_query($sql);
  $total = 0;
  $done[0] = -1;
  while($user = pg_fetch_array($users)) {
        if($user != false) {
          $total++;
	  $list = $list . $arg_2 . "Sub" . $total. " = insFld(" . $arg_2 .
	          ', gFld("' . $user[2] . '", "JavaScript:parent.openIFrame(' . $user[0] . ')"))' . "\n";
          $list = $list . treeSetup($user[0],$arg_2 . "Sub" . $total,$username) . "\n";
	}
	$done[$total] = $user[0];
  }
   while($group = pg_fetch_array($groups)) {
         if(!array_search($group[0],$done)) {
             	$total++;
             	$list = $list . $arg_2 . "Sub" . $total. " = insFld(" . $arg_2 .
             	 ', gFld("' . $group[2] . '", "JavaScript:parent.openIFrame(' . $group[0] . ')"))' . "\n";
             	$list = $list . treeSetup($group[0],$arg_2 . "Sub" . $total,$username) . "\n";
         }
  }
															
  $sql = "SELECT audiodir.id, audio.title, audio.id FROM audiodir, audio WHERE
          audio.id = audiodir.audio AND directory = " . pg_escape_string($arg_1);
  $files = pg_query($sql);
  $total=0;
  while($file = pg_fetch_array($files)) {
    $total++;
    $list = $list . $arg_2 . "File" . $total . " = insDoc(" . $arg_2 . ', gLnk("Rs", "' . $file[1] . '", "www.radio.warwick.ac.uk/dps/fileInfo.php?audioID=' 
            . $file[2] . '"))' . "\n";
    $list = $list . $arg_2 . "File" . $total . ".iconSrc = MUSIC";
    //$list = $list . $arg_2 . "File" . $total . " = insDoc(" . $arg_2 . ', gLnk("Rs", "' . $file[1] . '", "www.radio.warwick.ac.uk/dps/fileInfo.php?audioID=' . $file[2] . '"))\n';
  }

  return $list;
}

$temp = treeSetup(0,'foldersTree',$username);
?>
foldersTree = gFld('Digiplay', 'JavaScript:parent.openIFrame(0)')
foldersTree.treeID='phpBrowser'
//foldersTree.xID = 0;
<?=$temp?>
musicLib = insDoc(foldersTree, gLnk("Gs", "Music Library", "www.radio.warwick.ac.uk/dps/"))
musicLib.iconSrc = ICONPATH + "cds.jpg"
// Load a page as if a node on the tree was clicked (synchronize frames)
// (Highlights selection if highlight is available.)
function loadSynchPage(xID) 
{
	var folderObj;
	docObj = parent.treeframe.findObj(xID);
	docObj.forceOpeningOfAncestorFolders();
	parent.treeframe.clickOnLink(xID,docObj.link,'basefrm'); 

    //Scroll the tree window to show the selected node
    //Other code in these functions needs to be changed to work with
    //frameless pages, but this code should, I think, simply be removed
    if (typeof parent.treeframe.document.body != "undefined") //scroll doesn work with NS4, for example
        parent.treeframe.document.body.scrollTop=docObj.navObj.offsetTop
} 
</script>
<h1>Directory template</h1>
<hr>
<table width=300px border=0>
  <tr>
    <td valign=top>
<div style="position:relative; top:0; left:0; "><table border=0><tr><td><font size=-2><a 
style="font-size:7pt;text-decoration:none;color:rgb(50,100,255)" href="http://www.treemenu.net/" target=_blank>JavaScript Tree Menu</a></font></td></tr></table></div>

<!-- Build the browser's objects and display default view of the 
     tree. -->
<script>
initializeDocument()
//Click the Parakeet link
//loadSynchPage(<?=$ActiveID?>)
//JavaScript:parent.openIFrame(<?=$ActiveID?>) 
</script>
<noscript>
A tree for site navigation will open here if you enable JavaScript in your browser.
</noscript>
    </td>
    <td valign=top>
    <iframe
    frameborder="no" 
    name=basefrm
    src ="https://www.radio.warwick.ac.uk/dps/folderInfo.php"
    width="600px"
    height="1000px">
    </iframe>
    </td>
  </tr>
</table>
    <td>
  </tr>
</table>
<?
pg_close($dbconn1);
} else {
include('login.php');
}
include('footer.php');
?>
