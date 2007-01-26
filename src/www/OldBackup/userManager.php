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
?>
<table width=100%>
  <tr>
    <td valign='top' width=100px>
<?
include('contents.php');
?>
    </td>
    <td valign=top>
<h1>User Management</h1><hr>
<u>Add New User</u>
<?
if( !isset($_GET['uOffset']) || !is_numeric($_GET['uOffset']) ) {
  $uoffset = 0;
} else {
  $uoffset = pg_escape_string($_GET['uOffset']);
}
if( !isset($_GET['gOffset']) || !is_numeric($_GET['gOffset']) ) {
  $goffset = 0;
} else {
  $goffset = pg_escape_string($_GET['gOffset']);
}
if($_POST['action'] == 'uadd') {
  $exists = true;
  $sql = "SELECT * FROM users where username = '" . pg_escape_string($_POST['ausername']) . "'";
  $result = pg_query($dbconn1, $sql);
  if(pg_num_rows($result) == 0) {
    if(shell_exec("perl ucheck.pl " . escapeshellarg($_POST['ausername']))==$_POST['ausername'] . "\n") {
      $sql = "INSERT INTO users (username, enabled) VALUES ('" . pg_escape_string($_POST['ausername']) . "','t')";
      $insert = pg_query($dbconn1, $sql);
      $sql = "SELECT users.id FROM users where username = '" . pg_escape_string($_POST['ausername']) . "'";
      $result = pg_query($dbconn1, $sql);
      $user = pg_fetch_row($result,0);
      $sql = "DELETE FROM useraccess where userid= " . $user[0] . " AND privilage != 1";
      $delete = pg_query($dbconn1, $sql);
      $exists = false;
    } else {
      echo "<br><font color='red'>That username does not exist in the RaW LDAP</font>";
      $exists = false;
    }
  }
  if($exists) {
    echo "<br><font color='green'>" . $_POST['ausername'] . " is already a User</font";
  }
}
?>
  <form action='/dps/userManager.php?uOffset=<?=$uoffset?>&gOffset=<?=$goffset?>' method='post'>
    Username:<input type=text name=ausername>
    <input type=hidden name=action value=uadd>
    <input type=submit name=submit value=submit>
  </form>
<hr>
<u>Edit Current User</u>
  <table border=1>
    <tr>
      <th>
        Users
      </th>
      <th>
        Groups
      </th>
    </tr>
    <tr>
      <td valign=top>
        <?
        $sql = "SELECT COUNT(*) FROM users WHERE users.id != 0;";
	$result = pg_fetch_row(pg_query($dbconn1, $sql),0);
        $uCount = $result[0];
        $sql = "SELECT users.username, users.id FROM users WHERE users.id != 0 order by users.username asc limit 20 offset $uoffset";
        $result = pg_query($dbconn1, $sql);
        while($user=pg_fetch_array($result)) {
          echo $user[0] . " - <A href=\"javascript:createWindow('/dps/userperms.php?uid=$user[1]','window1','width=400,height=300,status=1,location=0,scrollbars=1')\">Edit</a><Br>";
        }
        if($uCount > 20) {
	  echo "<Br>";
	  $noffset = 0;
	  for($i=0; $i<$uCount; $i=$i+20) {
	    if($i+20 > $uCount) {
              echo ("<a href=/dps/userManager?uOffset=$noffset&gOffset=$goffset>" . ($i+1) . "-" . $uCount . "</a>");
	    } else {
	      echo ("<a href=/dps/userManager?uOffset=$noffset&gOffset=$goffset>" . ($i+1) . "-" . ($i+20) . "</a> ");
	    }
	    $noffset = $noffset + 20;
	  }
        }
        ?>
      </td>
      <td valign=top>
        <?
        $sql = "SELECT COUNT(*) FROM groups;";
        $result = pg_fetch_row(pg_query($dbconn1, $sql),0);
        $gCount = $result[0];
        $sql = "SELECT groups.name, groups.id FROM groups order by groups.name asc";
        $result = pg_query($dbconn1, $sql);
        while($groups=pg_fetch_array($result)) {
          echo $groups[0] . " - <A href=\"javascript:createWindow('/dps/groupperms.php?groupid=$groups[1]','window2','width=400,height=300,status=1,location=0,scrollbars=1')\">Edit</a><Br>";
        }
        if($gCount > 20) {
          echo "<Br>";
          $noffset = 0;
          for($i=0; $i<$gCount; $i=$i+20) {
            if($i+20 > $gCount) {
              echo ("<a href=/dps/userManager?uOffset=$uoffset&gOffset=$noffset>" . ($i+1) . "-" . $gCount . "</a>");
            } else {
              echo ("<a href=/dps/userManager?uOffset=$uoffset&gOffset=$noffset>" . ($i+1) . "-" . ($i+20) . "</a> ");
            }
            $noffset = $noffset + 20;
          }
        }
        ?>
      </td>
    </tr>
  </table>
<?
pg_close($dbconn1);
} else {
include('login.php');
}
include('footer.php');
?>
