<?
//Do login
include('session.php');
//Check that they have access to view the page
$sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username' AND users.id = useraccess.userid AND users.enabled = 't' AND
(useraccess.privilage=3 or useraccess.privilage=5 or useraccess.privilage=6)";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
if ($count[0] == 0) {
  $output="false";
  $errorMSG = 'You do not have access to view that page, please login as
          a user that does, or click <a href="index.php">here</a> to return to
	      the home page.';
}

if( $output == "true" ) {
  $_SESSION["username"]=$username;
  $_SESSION["password"]=$password;
  $_SESSION["timestamp"]=time()+900;
include('header.php');
$trackID = pg_escape_string($_GET['trackID']);
?>
<table width=100%>
  <tr>
    <td valign='top' width=100px>
<?
include('contents.php');
?>
    </td>
    <td valign=top>
<h1>Report a Track</h1><hr>
<?
if($trackID != "" && is_numeric($trackID)) {
  $sql = "SELECT id, title from audio where id = $trackID";
  $check = pg_query($dbconn1, $sql);
  if(pg_num_rows($check) == 1) {
    $track = pg_fetch_row($check,0);
    ?>
    <form method=POST action='report.php'>
    Please enter a detailed description of the problem with the track: <?=$track[1]?>, and check the 'Flag' checkbox if you believe this track is unsuitable for broadcasting at all times.<br><br>
    <b>Description</b><br>
    <textarea name=report rows=10 cols=50></textarea><br>
    Flag this track for censoring<input type='checkbox' name='flagged'><br>
    <input type='Submit' value='Submit' name='Submit'>
    </form>
    <?
  } else {
    ?>
    Track ID(<?=$trackID?>) not found. Please return to the <a href=mlib.php>music library</a>.
    <?
  }
} else {
  ?>
  Invalid Track ID passed. Please return to the <a href=mlib.php>music library</a>.
  <?
}
?>
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
