<?
$username = pg_escape_string($_GET['username']);
$dbconn1 = pg_connect("host=dps0 dbname=digiplay user=www");
if(isset($_GET['folderID'])) {
  $id = pg_escape_string($_GET['folderID']);
} else {
  $id = 0;
}

$sql = 'Select * from dir where id =' . $id;
$dirs = pg_query($dbconn1,$sql);
//SEE IF THE FOLDER
if(pg_num_rows($dirs) == 1) {
  $sql = "Select * from dir as d1, dir as d2, dirusers, users where d1.id = dirusers.directory and dirusers.permissions = 'w'
	and dirusers.userid = users.id and users.username = '$username' and d1.id = d2.parent and d2.id =" . $id;
  $udirtest = pg_query($dbconn1,$sql);
  $sql = "Select * from dir as d1, dir as d2, dirgroups, groups, groupmembers, users where d1.id = dirgroups.directory and 
  	  dirgroups.persmissions = 'w' and dirgroups.groupid = groups.id  and groups.id = groupmembers.groupid 
	  and groupmembers.userid = users.id and users.username = '$username' and d1.id = d2.parent and dir.id =" . $id;
  $gdirtest = pg_query($dbconn1,$sql);
  // see if they own the folder above (highest privlage)
  if(pg_num_rows($udirtest) > 0 || pg_num_rows($gdirtest) > 0) {
    $folder = pg_fetch_row($dirs,0);
    $sql = "Select * from dir, dirusers, users where dir.id = dirusers.directory and dirusers.permissions='w' 
            and dirusers.userid = users.id and users.username='$username' and dir.id !=" . $id;
    $dirs = pg_query($dbconn1,$sql);
    $parent="";
    $thing[0] = -1;
    $c=0;
    while($dir=pg_fetch_array($dirs)) {
      $c++;
      $parent=$parent . "<option value=" . $dir[0] . ">" . $dir[2] . "</option>";
      $thing[c] = $dir[0];
    }
    $sql = "Select * from dir, users, dirgroups, groups, groupmembers where dir.id = dirgroups.directory and 
    	    dirgroups.persmissions='w' and dirgroups.groupid = groups.id and groups.id = groupmembers.groupid and 
	    groupmembers.userid = users.id and users.username = '$username' and dir.id !=" . $id;
    while($dir=pg_fetch_array($dirs)) {
      if(array_search($dir[0],$thing)<1) {
  	$parent=$parent . "<option value=" . $dir[0] . ">" . $dir[2] . "</option>";
      }
    }
    $dirs = pg_query($dbconn1,$sql);
    $parent = str_replace("<option value=" . $folder[1] . ">", "<option value=" . $folder[1] . " selected>", $parent);
    ?>
    <form  target='_top' action='/dps/dirtest.php' method=POST>
    <table border=0>
      <tr><th align="right" width="150px">Folder:</th><td><input type="text" name="name" value="<?=$folder[2]?>"></td></tr>
      <tr><th align="right">Notes: </th><td><textarea name="notes"><?=$folder[3]?></textarea></td></tr>
      <? if($id != 0) {?>
      <tr><th align="right">Parent Folder:  </th><td><select name="parentNode"><?=$parent?></select></td></tr>
      <? } ?>
      <tr><th align="right">Public Security: </th><td>
      <?
        $sql = "SELECT id FROM groups where name = 'everyone'";
        $groupID = pg_query($sql);
	$groupID = pg_fetch_result($groupID,0,0);
	$sql = "select persmissions from dirgroups where directory = " . $id . " and groupid = $groupID";
	$folderState = pg_query($sql);
	if(pg_num_rows($folderState) > 0) {
	  $folderState = pg_fetch_result($folderState,0,0);
	  if($folderState == "w ") {
	    $private = "";
	    $read = "";
	    $write = "checked";
	  } else {
	    $private = "";
	    $read = "checked";
	    $write = "";
	  }
	} else {
	  $private = "checked";
	  $read = "";
	  $write = "";
	}
      ?>
      Private<input type="radio" value="private" name="security" <?=$private?>>
      Read<input type="radio" value="read" name="security" <?=$read?>>
      Write<input type="radio" value="write" name="security" <?=$write?>>
      </td></tr>
      <tr><th></th><td align=right><font size=2>Advanced Security TODO</font></td></tr>
      <tr><th><input type="hidden" value="<?=$folder[0]?>" name="nodeID"></th>
      <td><input type=Submit value="Update" name=Submit></td></tr>
    </table>
    </form>
    <form target='_top' action='/dps/dirtest.php' method=POST>
    <table border=0>
      <tr><th align="right" width="150px">New Sub Folder:</th><td><input type="text" name="name" value=""></td></tr>
      <tr><th align="right">Notes: </th><td><textarea name="notes"></textarea></td></tr>
      <tr><th align="right">Public Security: </th><td>
      Private<input type="radio" value="private" name="security" checked>
      Read<input type="radio" value="read" name="security" >
      Write<input type="radio" value="write" name="security" >
      </td></tr> 
      <tr><input type="hidden" value="<?=$folder[0]?>" name="parentNode"><th></th>
      <td><input type=Submit value="Add" name=Submit></td></tr>
    </table>
    </form>
  <form>
  <table border=0>
    <tr><th width="150px">Upload File</th><td><input type="file" name=uploadFile></td></tr>
    <tr><th align="right">Public Security: </th><td>
       Private<input type="radio" value="private" name="security" checked>
       Read<input type="radio" value="read" name="security">
       Write<input type="radio" value="write" name="security">
    </td></tr>
    <tr><input type="hidden" value="<?=$folder[0]?>" name="parentNode"><th></th>
    <tr><th width="150px"></th><td><input type=Submit value="Upload" name=Submit></td></tr>
  </table>
  </form>
  <form target='_top' action='/dps/dirtest.php' method=POST>
  <?
  $sql = "SELECT * FROM dir WHERE parent = $id";
  $nodeCheck = pg_query($sql);
  $sql = "SELECT * FROM audiodir WHERE directory = $id";
  $fileCheck = pg_query($sql);
  if(pg_num_rows($nodeCheck) == 0 && pg_num_rows($fileCheck) == 0) {
  ?>
  <table border=0>
    <tr><th width="150px"><input type="hidden" value="<?=$folder[0]?>" name="nodeID"></th><td><input type=Submit value="Delete Folder" name=Submit></td></tr>
  </table>
  </form>
  <? } ?>
  <?
  //WIRTE PERMISSIONS ON CURRENT FOLDER BUT NOT THE FOLDER ABOVE
  } else {
    $sql = "Select * from dir, dirusers, users where dir.id = dirusers.directory and dirusers.permissions = 'w'
          and dirusers.userid = users.id and users.username = '$username' and dir.id =" . $id;
    $udirtest = pg_query($dbconn1,$sql);
    $sql = "Select * from dir, dirgroups, groups, groupmembers, users where dir.id = dirgroups.directory and
 	    dirgroups.persmissions = 'w' and dirgroups.groupid = groups.id  and groups.id = groupmembers.groupid
	    and groupmembers.userid = users.id and users.username = '$username' and dir.id =" . $id;
    $gdirtest = pg_query($dbconn1,$sql);
    if(pg_num_rows($udirtest) > 0 || pg_num_rows($gdirtest) > 0) {
      $folder = pg_fetch_row($dirs,0);
    ?>
      <table border=0>
        <tr><th align="right" width="150px">Folder:</th><td><?=$folder[2]?></td></tr>
        <tr><th align="right">Notes: </th><td><pre><?=$folder[3]?></pre></td></tr>
      </table>
      <form target='_top' action='/dps/dirtest.php' method=POST>
      <table border=0>
        <tr><th align="right" width="150px">New Sub Folder:</th><td><input type="text" name="name" value=""></td></tr>
        <tr><th align="right">Notes: </th><td><textarea name="notes"></textarea></td></tr>
        <tr><th align="right">Public Security: </th><td>
          Private<input type="radio" value="private" name="security" checked>
          Read<input type="radio" value="read" name="security">
          Write<input type="radio" value="write" name="security">
        </td></tr>
        <tr><input type="hidden" value="<?=$folder[0]?>" name="parentNode"><th></th>
        <td><input type=Submit value="Add" name=Submit></td></tr>
      </table>
      </form>
      <form>
        <table border=0>
	  <tr><th width="150px">Upload File</th><td><input type="file" name=uploadFile></td></tr>
          <tr><th align="right">Public Security: </th><td>
            Private<input type="radio" value="private" name="security" checked>
            Read<input type="radio" value="read" name="security">
            Write<input type="radio" value="write" name="security">
          </td></tr>
          <tr><input type="hidden" value="<?=$folder[0]?>" name="parentNode"><th></th>
	  <tr><th width="150px"></th><td><input type=Submit value="Upload" name=Submit></td></tr>
	</table>
      </form>
      <?
    // READ PERMISSION ON THE CURRENT FOLDER
    } else {
      $sql = "Select * from dir, dirusers, users where dir.id = dirusers.directory and dirusers.permissions = 'r'
            and dirusers.userid = users.id and users.username = '$username' and dir.id =" . $id;
      $udirtest = pg_query($dbconn1,$sql);
      $sql = "Select * from dir, dirgroups, groups, groupmembers, users where dir.id = dirgroups.directory and
            dirgroups.persmissions = 'r' and dirgroups.groupid = groups.id 
	    and groups.id = groupmembers.groupid and groupmembers.userid = users.id and 
	    users.username = '$username' and dir.id =" . $id;
      $gdirtest = pg_query($dbconn1,$sql);
      if(pg_num_rows($udirtest) > 0 || pg_num_rows($gdirtest) > 0 || $id==0) {
        $folder = pg_fetch_row($dirs,0);
	?>
	<table border=0>
	        <tr><th align="right" width="150px">Folder:</th><td><?=$folder[2]?></td></tr>
	        <tr><th align="right">Notes: </th><td><pre><?=$folder[3]?></pre></td></tr>
	</table>
	<?
      //NO PERMISSIONS ON THE CURRENT FOLDER
      } else {
        echo "<b> You do not have access to view that folder</b>";
      }
    }
  }
} else {
  echo "<b> That folder does not exist</b>";
}
pg_close($dbconn1);
?>
