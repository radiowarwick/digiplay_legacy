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
<h1>Station Cartwall</h1>
<hr>
<b>Available Cartsets for Station Cartwall</b><Br>
<?
$loc = 1;
if(isset($_POST['activeSCW']) && is_numeric($_POST['activeSCW'])) {
  $sql = "SELECT count(*) FROM cartsets where id=" . pg_escape_string($_POST['activeSCW']);
  $cSetCheck = pg_query($sql);
  if(pg_fetch_result($cSetCheck,0,0) == 1) {
    $sql = "UPDATE configuration SET val='" . pg_escape_string($_POST['activeSCW']) . "' where location=$loc and parameter='station_cartset'";
    //echo $sql . "<br>";
    pg_query($sql);
  }  
}
if(isset($_POST['submit'])) {
  if($_POST['submit'] == "Add new" && $_POST['name'] != "" && $_POST['desc'] != "") {
    $sql = "INSERT INTO cartsets (name,description) VALUES ('" . pg_escape_string($_POST['name']) . "','" . pg_escape_string($_POST['desc']) . "')";
    //echo $sql;
    pg_query($sql);
	$sql = "select last_value from cartsets_id_seq";
    $cartsetid_fetch = pg_query($sql);
	$cartsetid = pg_fetch_array($cartsetid_fetch);
	$sql = "INSERT INTO cartsetsusers (cartsetid,userid) VALUES (" . $cartsetid[0] . ",0)";
	pg_query($sql);
	$sql = "INSERT INTO cartsetsdir (cartsetid,dir) VALUES (" . $cartsetid[0] . ",0)";
  } else if($_POST['submit'] == "Delete" && $_GET['cartID'] != 0) {
        $sql = "select id from cartwalls where cartset = " . pg_escape_string($_GET['cartID']);
        $dcartwalls = pg_query($sql);
        while($dcartwall = pg_fetch_array($dcartwalls)) {
                $sql="delete from cartsaudio where cartwall = " . $dcartwall[0];
                //echo $sql . "<br>";
                pg_query($sql);
        }
        $sql="delete from cartwalls where cartset = " . pg_escape_string($_GET['cartID']);
        //echo $sql . "<br>";
        pg_query($sql);
        $sql="delete from cartsets where id = " . pg_escape_string($_GET['cartID']);
        //echo $sql . "<br>";
        pg_query($sql);
   }
}
?>
<form method=post action=stationCartset.php>
<table border=1>
  <tr>
    <th width=120>
      Cartset
    </th>
    <th>
      Status
    </th>
    <th>
      Edit
    </th>
  </tr>
<?
$sql = "SELECT cartsets.id,cartsets.name,cartsets.description FROM cartsets,cartsetsusers WHERE cartsetsusers.userid=0 and cartsetsusers.cartsetid=cartsets.id order by name asc";
$cSets = pg_query($sql);
  while($cSet = pg_fetch_array($cSets)) {
?>
  <tr>
    <td>
      <?=$cSet[1]?>
    </td>
    <td>
<?
$sql = "SELECT count(*) FROM configuration where location=$loc and parameter='station_cartset' and val=$cSet[0]";
$cCheck = pg_query($sql);
if(pg_fetch_result($cCheck,0,0) == 1) {
?>
      <input type='radio' value=<?=$cSet[0]?> name=activeSCW checked>
<?
} else {
?>
      <input type='radio' value=<?=$cSet[0]?> name=activeSCW>
<?
}
?>
    </td>
    <td>
      <a href='editCartset.php?cartID=<?=$cSet[0]?>'>Edit</a>
    </td>
  </tr>
<?
}
?>
</table>
<input type=submit value=Submit name=submit>
</form>
    <b>New Cartset</b><br>
    <form action=stationCartset.php method=post>
    Name: <input type=text name='name' value=''><br>
    Description: <input type=text name='desc' value=''><br>
    <input type=submit name='submit' value='Add new'>
    </form>
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
