<?
session_start();
$errorMSG = '';
if($_GET['action'] == 'logout') {
  session_unregister("username");
  session_unregister("password");
  session_unregister("timestamp");
}
$username = pg_escape_string($_SESSION['username']);
$password = pg_escape_string($_SESSION['password']);
if($_SESSION['timestamp'] < time() && $username != ''){
  $username = '';
  $password = '';
  $errorMSG = 'Your Session has timed out please log back in';
}
if($_POST['username'] != '') {
  $username = pg_escape_string($_POST['username']);
  $password = pg_escape_string($_POST['password']);
}
$output=@shell_exec("perl bashscripts/auth.pl " . escapeshellarg($username) . " " . escapeshellarg($password));
$dbconn1 = pg_connect("host=dps0 dbname=digiplay user=www");
if( $output != "true" && $username != '') {
  $errorMSG = 'Your Username or Password is incorrect.';
}
if(!$dbconn1) {
  die("AWOOOOOGAH! FAILED TO CONNECT TO DATABASE");
}
if( $output == "true" ) {
  $sql = "SELECT * FROM users where username = '" . $username . "'";
  $result = pg_query($dbconn1,$sql);
  if(pg_num_rows($result) == 0) {
    $sql = "INSERT INTO users (username, enabled) VALUES ('" . $username . "','t')";
    $insert = pg_query($dbconn1, $sql);
    $sql = "SELECT users.id FROM users where username = '" . $username . "'";
    $result = pg_query($dbconn1, $sql);
    $user = pg_fetch_row($result,0);
    $sql = "DELETE FROM useraccess where userid= " . $user[0] . " AND privilage != 1";
    $delete = pg_query($dbconn1, $sql);
  }
  $sql = "SELECT * FROM users where username = '" . $username . "' AND enabled = 't'";
  $result = pg_query($dbconn1,$sql);
  if(pg_num_rows($result) == 0) {
    $output = 'false';
  }
} else {
  $sql = "SELECT count(*) FROM users WHERE users.username='$username' AND users.enabled = 'f'";
  $result = pg_query($dbconn1, $sql);
  $count = pg_fetch_row($result, 0);
  if ($count[0] == 1) {
    $errorMSG = 'Your account has been disabled, please contact access@radio.warwick.ac.uk if you believe
     this is in error.';
  }
}
?>
