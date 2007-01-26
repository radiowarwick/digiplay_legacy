<?
include('session.php');
$sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username' AND users.id = useraccess.userid AND
 (useraccess.privilage=8 OR useraccess.privilage=3)";
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
if(is_numeric($_GET['uid'])) {
$sql = "select username from users where id=" . pg_escape_string($_GET['uid']);
$result = pg_query($dbconn1, $sql);
if(pg_num_rows($result) != 0) {
$user = pg_fetch_row($result, 0);
?>
<form action='/dps/userperms.php?uid=<?=$_GET['uid']?>' method='post'>
<b>Editing permissions for User: <?=$user[0]?></b><hr>
<?
    $sql = "SELECT count(*) FROM useraccess WHERE userid=" . pg_escape_string($_GET['uid']) . " AND useraccess.privilage=3";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] != 0) {
      echo "<font color=red><b>This user is an Administrator. You do not have access to edit their permissions.</b></font>";
    } else {
?>
<input type=hidden name=action value=update>
<table width=100% border=0>
<?
$sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username' AND users.id = useraccess.userid AND (useraccess.privilage=8 OR useraccess.privilage=3)";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
//Have to at least have permission to manage users to view page
if ($count[0] != 0) {
//do form processing for this level of access
if($_POST['action'] == 'update') {
  if($_POST['vStats'] == 'on') {
    $sql = "SELECT count(*) FROM useraccess WHERE userid=" . pg_escape_string($_GET['uid']) . " AND useraccess.privilage=1";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into useraccess(userid, privilage) values (" . pg_escape_string($_GET['uid']) . ",1)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from useraccess where userid=" . pg_escape_string($_GET['uid']) . " AND privilage =1";
    $delete = pg_query($dbconn1, $sql);
  }
  if($_POST['fAbusive'] == 'on') {
    $sql = "SELECT count(*) FROM useraccess WHERE userid=" . pg_escape_string($_GET['uid']) . " AND useraccess.privilage=5";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into useraccess(userid, privilage) values (" . pg_escape_string($_GET['uid']) . ",5)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from useraccess where userid=" . pg_escape_string($_GET['uid']) . " AND privilage =5";
    $delete = pg_query($dbconn1, $sql);
  }
  if($_POST['sAbusive'] == 'on') {
    $sql = "SELECT count(*) FROM useraccess WHERE userid=" . pg_escape_string($_GET['uid']) . " AND useraccess.privilage=6";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into useraccess(userid, privilage) values (" . pg_escape_string($_GET['uid']) . ",6)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from useraccess where userid=" . pg_escape_string($_GET['uid']) . " AND privilage =6";
    $delete = pg_query($dbconn1, $sql);
  }
  if($_POST['eTrack'] == 'on') {
    $sql = "SELECT count(*) FROM useraccess WHERE userid=" . pg_escape_string($_GET['uid']) . " AND useraccess.privilage=7";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into useraccess(userid, privilage) values (" . pg_escape_string($_GET['uid']) . ",7)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from useraccess where userid=" . pg_escape_string($_GET['uid']) . " AND privilage =7";
    $delete = pg_query($dbconn1, $sql);
  }
  if($_POST['eSue'] == 'on') {
    $sql = "SELECT count(*) FROM useraccess WHERE userid=" . pg_escape_string($_GET['uid']) . " AND useraccess.privilage=4";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into useraccess(userid, privilage) values (" . pg_escape_string($_GET['uid']) . ",4)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from useraccess where userid=" . pg_escape_string($_GET['uid']) . " AND privilage =4";
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
$sql = "SELECT count(*) FROM users, useraccess WHERE users.id=" . pg_escape_string($_GET['uid']) . " AND users.id = useraccess.userid AND useraccess.privilage=1";
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
$sql = "SELECT count(*) FROM users, useraccess WHERE users.id=" . pg_escape_string($_GET['uid']) . " AND users.id = useraccess.userid AND useraccess.privilage=4";
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
$sql = "SELECT count(*) FROM users, useraccess WHERE users.id=" . pg_escape_string($_GET['uid']) . " AND users.id = useraccess.userid AND useraccess.privilage=5";
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
$sql = "SELECT count(*) FROM users, useraccess WHERE users.id=" . pg_escape_string($_GET['uid']) . " AND users.id = useraccess.userid AND useraccess.privilage=6";
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
$sql = "SELECT count(*) FROM users, useraccess WHERE users.id=" . pg_escape_string($_GET['uid']) . " AND users.id = useraccess.userid AND useraccess.privilage=7";
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
$sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username' AND users.id = useraccess.userid AND useraccess.privilage=3";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
//Have to at least have permission to manage users to view page
if ($count[0] != 0) {
if($_POST['action'] == 'update') {
  if($_POST['musicMan'] == 'on') {
    $sql = "SELECT count(*) FROM useraccess WHERE userid=" . pg_escape_string($_GET['uid']) . " AND useraccess.privilage=8";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into useraccess(userid, privilage) values (" . pg_escape_string($_GET['uid']) . ",8)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from useraccess where userid=" . pg_escape_string($_GET['uid']) . " AND privilage =8";
    $delete = pg_query($dbconn1, $sql);
  }
  if($_POST['prodMan'] == 'on') {
    $sql = "SELECT count(*) FROM useraccess WHERE userid=" . pg_escape_string($_GET['uid']) . " AND useraccess.privilage=9";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into useraccess(userid, privilage) values (" . pg_escape_string($_GET['uid']) . ",9)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from useraccess where userid=" . pg_escape_string($_GET['uid']) . " AND privilage =9";
    $delete = pg_query($dbconn1, $sql);
  }
  if($_POST['marketMan'] == 'on') {
    $sql = "SELECT count(*) FROM useraccess WHERE userid=" . pg_escape_string($_GET['uid']) . " AND useraccess.privilage=10";
    $result = pg_query($dbconn1, $sql);
    $count = pg_fetch_row($result, 0);
    if ($count[0] == 0) {
      $sql = "insert into useraccess(userid, privilage) values (" . pg_escape_string($_GET['uid']) . ",10)";
      $insert = pg_query($dbconn1, $sql);
    }
  } else {
    $sql = "delete from useraccess where userid=" . pg_escape_string($_GET['uid']) . " AND privilage =10";
    $delete = pg_query($dbconn1, $sql);
  }
  if($_POST['disabledUser'] == 'on') {
      $sql = "UPDATE users SET enabled = 'f' WHERE id=" . pg_escape_string($_GET['uid']);
      $update = pg_query($dbconn1, $sql);
  } else {
      $sql = "UPDATE users SET enabled = 't' WHERE id=" . pg_escape_string($_GET['uid']);
      $update = pg_query($dbconn1, $sql);
  }
}
?>
  <tr>
    <td>
      Music Manager
    </td>
    <td>
<?
$sql = "SELECT count(*) FROM users, useraccess WHERE users.id=" . pg_escape_string($_GET['uid']) . " AND users.id = useraccess.userid AND useraccess.privilage=8";
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
$sql = "SELECT count(*) FROM users, useraccess WHERE users.id=" . pg_escape_string($_GET['uid']) . " AND users.id = useraccess.userid AND useraccess.privilage=9";
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
$sql = "SELECT count(*) FROM users, useraccess WHERE users.id=" . pg_escape_string($_GET['uid']) . " AND users.id = useraccess.userid AND useraccess.privilage=10";
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
  <tr>
    <td>
      Account Disabled
    </td>
    <td>
<?
$sql = "SELECT count(*) FROM users WHERE users.id=" . pg_escape_string($_GET['uid']) . " AND users.enabled = 'f'";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
//Have to at least have permission to manage users to view page
if ($count[0] == 0) {
?>
      <input type='checkbox' name=disabledUser >
<?
} else {
?>
      <input type='checkbox' name=disabledUser checked>
<?
}
?>
    </td>
  </tr>
  <tr>
    <td>
</td>
</tr>
<?
}
?>
</table>
<?
$sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username' AND users.id = useraccess.userid AND useraccess.privilage=3";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
//Have to at least have permission to manage users to view page
if ($count[0] != 0) {
?>
  <b>Groups</b> Does not update db yet
  <hr>
  <table width=100% border=0>
<?
$sql = "SELECT name, id from groups";
$result = pg_query($dbconn1, $sql);
while($count = pg_fetch_row($result)) {
  $sql = "SELECT * from groupmembers where groupid='$count[1]' and userid =" . pg_escape_string($_GET['uid']);
  $result = pg_query($dbconn1, $sql);
  if(pg_num_rows($result) == 0) {
    echo "<tr><td>" . $count[0] . "</td><td><input type='checkbox' name='$count[0]' ></td></tr>";
  } else {
    echo "<tr><td>" . $count[0] . "</td><td><input type='checkbox' name='$count[0]' check></td></tr>";
  }
}
?>
  </table>
  <hr>
  <?
}
?>
<input type='submit' nae='submit' value='   Save   '>
</form>
<?
}
} else {
echo "<b> That user does not exist in the database </b>";
}
} else {
echo "<b>Invalid user id</b>";
}
} else {
echo "<b> You do not have permission to view this page</b>";
}
include('footer.php');
pg_close($dbconn1);
?>
