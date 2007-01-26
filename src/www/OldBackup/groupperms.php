<?
include('session.php');
$sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username' AND users.id = useraccess.userid 
AND users.enabled = 't' AND
 (useraccess.privilage=3)";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
//Have to at least have permission to manage users to view page
if ($count[0] == 0) {
  $output="false";
    $errorMSG = 'You do not have access to view that page, please login as
    a user that does, or click <a href="/dps/sue.php">here</a> to return to
    the home page.';
}
if( $output == "true" ) {
  $_SESSION["username"]=$username;
  $_SESSION["password"]=$password;
  $_SESSION["timestamp"]=time()+900;
include('header.php');
if(is_numeric($_GET['groupid'])) {
$sql = "select name from groups where id=" . pg_escape_string($_GET['groupid']);
$result = pg_query($dbconn1, $sql);
if(pg_num_rows($result) != 0) {
$group = pg_fetch_row($result, 0);
?>
<b>Editing permissions for Group: <?=$group[0]?></b><hr>
<form action='/dps/groupperms.php?groupid=<?=$_GET['groupid']?>' method='post'>
<input type=hidden name=action value=update>
<table width=100% border=0>
<?
$sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username' AND users.id = useraccess.userid 
AND (useraccess.privilage=8 OR useraccess.privilage=3)";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
//Have to at least have permission to manage users to view page
if ($count[0] != 0) {
//do form processing for this level of access
if($_POST['action'] == 'update') {
  if($_POST['vStats'] == 'on') {
    $sql = "SELECT count(*) FROM groupaccess WHERE id=" . pg_escape_string($_GET['groupid']) . " AND groupaccess.privilage=1";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into groupaccess(groupid, privilage) values (" . pg_escape_string($_GET['groupid']) . ",1)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from groupaccess where id=" . pg_escape_string($_GET['groupid']) . " AND privilage =1";
    $delete = pg_query($dbconn1, $sql);
  }
  if($_POST['fAbusive'] == 'on') {
    $sql = "SELECT count(*) FROM groupaccess WHERE groupid=" . pg_escape_string($_GET['groupid']) . " AND groupaccess.privilage=5";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into groupaccess(groupid, privilage) values (" . pg_escape_string($_GET['groupid']) . ",5)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from groupaccess where groupid=" . pg_escape_string($_GET['groupid']) . " AND privilage =5";
    $delete = pg_query($dbconn1, $sql);
  }
  if($_POST['sAbusive'] == 'on') {
    $sql = "SELECT count(*) FROM groupaccess WHERE groupid=" . pg_escape_string($_GET['groupid']) . " AND groupaccess.privilage=6";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into groupaccess(groupid, privilage) values (" . pg_escape_string($_GET['groupid']) . ",6)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from groupaccess where groupid=" . pg_escape_string($_GET['groupid']) . " AND privilage =6";
    $delete = pg_query($dbconn1, $sql);
  }
  if($_POST['eTrack'] == 'on') {
    $sql = "SELECT count(*) FROM groupaccess WHERE groupid=" . pg_escape_string($_GET['groupid']) . " AND groupaccess.privilage=7";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into groupaccess(groupid, privilage) values (" . pg_escape_string($_GET['groupid']) . ",7)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from groupaccess where groupid=" . pg_escape_string($_GET['groupid']) . " AND privilage =7";
    $delete = pg_query($dbconn1, $sql);
  }
  if($_POST['eSue'] == 'on') {
    $sql = "SELECT count(*) FROM groupaccess WHERE groupid=" . pg_escape_string($_GET['groupid']) . " AND groupaccess.privilage=4";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into groupaccess(groupid, privilage) values (" . pg_escape_string($_GET['groupid']) . ",4)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from groupaccess where groupid=" . pg_escape_string($_GET['groupid']) . " AND privilage =4";
    $delete = pg_query($dbconn1, $sql);
  }
}
?>
  <tr>
    <td>
      View Statistics
    </td>
    <td>
<?
$sql = "SELECT count(*) FROM groups, groupaccess WHERE groups.id=" . pg_escape_string($_GET['groupid']) . " AND groups.id = 
groupaccess.groupid AND groupaccess.privilage=1";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
if ($count[0] == 0) {
?>
      <input type='checkbox' name=vStats >
<?
} else {
?>
      <input type='checkbox' name=vStats checked>
<?
}
?>
    </td>
  </tr>
  <tr>
    <td>
      Edit Sue Playlist
    </td>
    <td>
<?
$sql = "SELECT count(*) FROM groups, groupaccess WHERE groups.id=" . pg_escape_string($_GET['groupid']) . " AND groups.id = 
groupaccess.groupid AND groupaccess.privilage=4";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
//Have to at least have permission to manage users to view page
if ($count[0] == 0) {
?>
      <input type='checkbox' name=eSue >
<?
} else {
?>
      <input type='checkbox' name=eSue checked>
<?
}
?>
    </td>
  </tr>
  <tr>
    <td>
      Flag Track as Abusive
    </td>
    <td>
<?
$sql = "SELECT count(*) FROM groups, groupaccess WHERE groups.id=" . pg_escape_string($_GET['groupid']) . " AND groups.id = 
groupaccess.groupid AND groupaccess.privilage=5";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
//Have to at least have permission to manage users to view page
if ($count[0] == 0) {
?>
      <input type='checkbox' name=fAbusive >
<?
} else {
?>
      <input type='checkbox' name=fAbusive checked>
<?
}
?>
    </td>
  </tr>
  <tr>
    <td>
      Set Track as Abusive
    </td>
    <td>
<?
$sql = "SELECT count(*) FROM groups, groupaccess WHERE groups.id=" . pg_escape_string($_GET['groupid']) . " AND groups.id = 
groupaccess.groupid AND groupaccess.privilage=6";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
//Have to at least have permission to manage users to view page
if ($count[0] == 0) {
?>
      <input type='checkbox' name=sAbusive >
<?
} else {
?>
      <input type='checkbox' name=sAbusive checked>
<?
}
?>
    </td>
  </tr>
  <tr>
    <td>
      Edit Track Info
    </td>
    <td>
<?
$sql = "SELECT count(*) FROM groups, groupaccess WHERE groups.id=" . pg_escape_string($_GET['groupid']) . " AND groups.id = 
groupaccess.groupid AND groupaccess.privilage=7";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
//Have to at least have permission to manage users to view page
if ($count[0] == 0) {
?>
      <input type='checkbox' name=eTrack >
<?
} else {
?>
      <input type='checkbox' name=eTrack checked>
<?
}
?>
    </td>
  </tr>
<?
}
$sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username' AND users.id = useraccess.userid 
AND useraccess.privilage=3";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
//Have to at least have permission to manage users to view page
if ($count[0] != 0) {
if($_POST['action'] == 'update') {
  if($_POST['musicMan'] == 'on') {
    $sql = "SELECT count(*) FROM groupaccess WHERE groupid=" . pg_escape_string($_GET['groupid']) . " AND groupaccess.privilage=8";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into groupaccess(groupid, privilage) values (" . pg_escape_string($_GET['groupid']) . ",8)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from groupaccess where groupid=" . pg_escape_string($_GET['groupid']) . " AND privilage =8";
    $delete = pg_query($dbconn1, $sql);
  }
  if($_POST['prodMan'] == 'on') {
    $sql = "SELECT count(*) FROM groupaccess WHERE groupid=" . pg_escape_string($_GET['groupid']) . " AND groupaccess.privilage=9";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into groupaccess(groupid, privilage) values (" . pg_escape_string($_GET['groupid']) . ",9)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from groupaccess where groupid=" . pg_escape_string($_GET['groupid']) . " AND privilage =9";
    $delete = pg_query($dbconn1, $sql);
  }
  if($_POST['marketMan'] == 'on') {
    $sql = "SELECT count(*) FROM groupaccess WHERE groupid=" . pg_escape_string($_GET['groupid']) . " AND privilage=10";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into groupaccess(groupid, privilage) values (" . pg_escape_string($_GET['groupid']) . ",10)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from groupaccess where groupid=" . pg_escape_string($_GET['groupid']) . " AND privilage =10";
    $delete = pg_query($dbconn1, $sql);
  }
}
?>
  <tr>
    <td>
      Music Manager
    </td>
    <td>
<?
$sql = "SELECT count(*) FROM groupaccess WHERE groupid=" . pg_escape_string($_GET['groupid']) . " AND privilage=8";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
//Have to at least have permission to manage users to view page
if ($count[0] == 0) {
?>
      <input type='checkbox' name=musicMan >
<?
} else {
?>
      <input type='checkbox' name=musicMan checked>
<?
}
?>
    </td>
  </tr>
  <tr>
    <td>
      Production Manager
    </td>
    <td>
<?
$sql = "SELECT count(*) FROM groupaccess WHERE groupid=" . pg_escape_string($_GET['groupid']) . " AND privilage=9";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
//Have to at least have permission to manage users to view page
if ($count[0] == 0) {
?>
      <input type='checkbox' name=prodMan >
<?
} else {
?>
      <input type='checkbox' name=prodMan checked>
<?
}
?>
    </td>
  </tr>
  <tr>
    <td>
      Marketting Manager
    </td>
    <td>
<?
$sql = "SELECT count(*) FROM groupaccess,useraccess WHERE groupid=" . pg_escape_string($_GET['groupid']) . " AND useraccess.privilage=8";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
//Have to at least have permission to manage users to view page
if ($count[0] == 0) {
?>
      <input type='checkbox' name=marketMan >
<?
} else {
?>
      <input type='checkbox' name=marketMan checked>
<?
}
?>
    </td>
  </tr>
<?
}
?>
</table>
<input type='submit' nae='submit' value='   Save   '>
</form>
<?
} else {
echo "<b> That group does not exist in the database </b>";
}
} else {
echo "<b>Invalid group id</b>";
}
} else {
echo "<b> You do not have permission to view this page</b>";
}
include('footer.php');
pg_close($dbconn1);
?>
