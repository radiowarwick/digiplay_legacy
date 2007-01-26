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
if(isset($_GET['cartID']) && is_numeric($_GET['cartID'])) {
  if(isset($_POST['submit'])) {
    if($_POST['submit'] == "Update" && $_POST['name'] != "" && $_POST['desc'] != "") {
	$sql = "UPDATE cartset set name='" . pg_escape_string($_POST['name']) . "', description='" . pg_escape_string($_POST['desc']) . "' WHERE id=" . pg_escape_string($_GET['cartID']);
        //echo $sql . "<br>";
        pg_query($sql);
    } else if($_POST['submit'] == "Delete") {
        $sql = "SELECT * FROM cartwalls where id=" . pg_escape_string($_GET['cartwallID']);
        $dcartwall = pg_query($sql);
        $end = false;
        if(pg_num_rows($dcartwall) > 0) {
          $dcartwall = pg_fetch_row($dcartwall,0);
          $page = $dcartwall[3];
          do {
            $page++;
            $sql = "SELECT * FROM cartwalls where cartset=" . $dcartwall[2] . " and page=" . $page;
            //echo $sql . "<br>";
            $ucartwall = pg_query($sql);
            if(pg_num_rows($ucartwall) > 0) {
              $sql="UPDATE cartwalls SET page=" . ($page-1) . " WHERE cartset=" . $dcartwall[2] . " and page=" . $page;
              //echo $sql . "<br>";
              pg_query($sql);
            } else {
              $end = true;
            }
          } while ($end == false);
          $sql="delete from cartsaudio where cartwall = " . pg_escape_string($_GET['cartwallID']);
          //echo $sql . "<br>";
          pg_query($sql);
          $sql="delete from cartwalls where id = " . pg_escape_string($_GET['cartwallID']);
          //echo $sql . "<br>";
          pg_query($sql);
        }
    } else if($_POST['name'] != "" && $_POST['desc'] != "") {
        $sql = "select page from cartwalls where cartset=" . $_GET['cartID'] . " order by page desc limit 1";
        $lastpage = pg_query($sql);
        if(pg_num_rows ($lastpage) != 0) {
  	  $newpage = pg_fetch_row($lastpage,0);
  	  $newpage = $newpage[0]+1;
        } else {
  	  $newpage = 0;
        }
        $sql = "INSERT INTO cartwalls (name,cartset,page,description) VALUES ('" . pg_escape_string($_POST['name']) . "'," . pg_escape_string($_GET['cartID']) . ",$newpage,'" . pg_escape_string($_POST['desc']) . "')";
        //echo $sql . "<br>";
        pg_query($sql);
    }
  }
  $sql = "select * from cartsets where id =" . pg_escape_string($_GET['cartID']);
  $currentCartset = pg_query($sql);
  if(pg_num_rows ($currentCartset) != 0) {
    $currentCartset = pg_fetch_row($currentCartset,0);
?>
    <h1><?=$currentCartset[1] ?> Cartset</h1>
    <hr>
    <a href='stationCartset.php'>Station Cartwalls</a> -> <?=$currentCartset[1] ?> Cartset
    <hr>
    <form action=editCartset.php?cartID=<?=$_GET['cartID']?> method=post>
    Name: <input type=text name='name' value='<?=$currentCartset[1]?>'><br>
    Description: <input type=text name='desc' size=30 value='<?=$currentCartset[4]?>'><br>
    <input type=submit name='submit' value='Update'>
    </form>
    <form action=stationCartset.php?cartID=<?=$_GET['cartID']?> method=post>
    <input type=submit name='submit' value='Delete'>
    </form>
    <table border=1>
      <tr>
        <th>
	  Page
        </th>
        <th>
          Carts
        </th>
       </tr>
<?
$sql = "select * from cartwalls where cartset=" . pg_escape_string($_GET['cartID']) . " order by page asc";
$cartwalls = pg_query($sql);
while($cWall = pg_fetch_array($cartwalls)) {
?>
      <tr>
	<td valign=top>
	  <?=$cWall[4]?>
	</td>
        <td>
          <table>
<?
          $sql = "select * from cartsaudio, audio where cartsaudio.audio = audio.id and cartsaudio.cartwall=" . $cWall[0] . " order by cartsaudio.cart asc";
	  $carts = pg_query($sql);
	  while($cart = pg_fetch_array($carts)) {
	    echo "<tr><td>" . $cart['title'] . "</td></tr>";
	  }
?>
	    <tr><td><a href='editCartwall.php?cartwallID=<?=$cWall[0]?>'>edit</a></td></tr>
	  </table>
        </td>
      </tr>
<?
}
?>
    </table>
    <b>New Cartwall</b><br>
    <form action=editCartset.php?cartID=<?=$_GET['cartID']?> method=post>
    Name: <input type=text name='name' value=''><br>
    Description: <input type=text name='desc' value=''><br>
    <input type=submit name='submit' value='Add new'>
    </form>
<?
  } else {
?>
    <h1>Edit A Cartset</h1>
    <hr>
    The selected cartset does not exist...
<?
  }
} else {
?>
    <h1>Edit A Cartset</h1>
    <hr>
    Invalid cartset ID...
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
