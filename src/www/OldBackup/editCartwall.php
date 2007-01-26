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
if(isset($_GET['cartwallID']) && is_numeric($_GET['cartwallID'])) {
  if(isset($_POST['submit'])) {
    if($_POST['submit'] == "Update") {
      if($_POST['name'] != "" && $_POST['desc'] != "") {
        $sql = "UPDATE cartwall set name='" . pg_escape_string($_POST['name']) . "', description='" . pg_escape_string($_POST['desc']) . "' WHERE id=" . pg_escape_string($_GET['cartwallID']);
        //echo $sql;
        pg_query($sql);
      }
    } else {
      for($i=0;$i<12;$i++) {
        if(isset($_POST["Track_" . $i]) && is_numeric($_POST["Track_" . $i])) {
          $sql = "select audio.id, audio.title from audiojinglepkgs, audio where audio.id = audiojinglepkgs.audio 
  		and audio.id=" . pg_escape_string($_POST["Track_" . $i]);
          $cartcheck = pg_query($sql);
          $sql = "select audio.id, audio.title from albums, audio where audio.music_album = albums.id
                and albums.name='Adverts' and audio.id=" . pg_escape_string($_POST["Track_" . $i]);
          $cartcheck_bodge = pg_query($sql);
    	  //check audio exists
          if(pg_num_rows($cartcheck) > 0 || pg_num_rows($cartcheck_bodge) > 0 ) {
            $sql = "select * from cartsaudio where cart=$i and cartwall=" . pg_escape_string($_GET['cartwallID']);
            $cartcheck = pg_query($sql);
            //check if cart already exists
            if(pg_num_rows($cartcheck) > 0) {
	      $text="";
	      $subStr = explode("\n",$_POST["Text_" . $i]);
	      foreach($subStr as $value){
	        $text = $text . pg_escape_string($value) . "\n";
	      }
	      $text = rtrim($text,"\n");
	      $sql = "UPDATE cartsaudio set audio=" . pg_escape_string($_POST["Track_" . $i]) .
		    ", text='" . $text . "'" .
		    ", style=" . pg_escape_string($_POST["Style_" . $i]) .
		    " WHERE cart=$i and cartwall=" . pg_escape_string($_GET['cartwallID']);
	      //echo $sql . "<br>";
	      pg_query($sql);
            } else {
              $subStr = explode("\n",$_POST["Text_" . $i]);
	      $text="";
              foreach($subStr as $value){
                $text = $text . pg_escape_string($value) . "\n";
              }
              $text = rtrim($text,"\n");
	      $sql = "INSERT INTO cartsaudio (audio,style,cart,cartwall,text) VALUES 
		   (" . pg_escape_string($_POST["Track_" . $i]) . "," . pg_escape_string($_POST["Style_" . $i]) . ",$i," . pg_escape_string($_GET['cartwallID']) . ",'" . 
		   $text . "')";
              //echo $sql . "<br>";
              pg_query($sql);
	    }
          }
        } else {
	  // DELETE IT
          $sql = "DELETE FROM cartsaudio WHERE cart=$i and cartwall=" . pg_escape_string($_GET['cartwallID']);
	  //echo $sql . "<br>";
          pg_query($sql);
        }
      }
    }
  }

  $sql = "select * from cartwalls where id =" . pg_escape_string($_GET['cartwallID']);
  $currentCartwall = pg_query($sql);
  if(pg_num_rows ($currentCartwall) != 0) {
    $currentCartwall = pg_fetch_row($currentCartwall,0);
?>
    <h1><?=$currentCartwall[4] ?> Cartwall</h1>
    <hr>
    <a href='stationCartset.php'>Station Cartwalls</a> -> <a href='editCartset.php?cartID=<?=$currentCartwall[2] ?>'>Edit Cartset</a> -> <?=$currentCartwall[4] ?> Cartwall
    <hr>
    <table width = 600px>
      <tr>
        <td>
          <form action=editCartwall.php?cartwallID=<?=$_GET['cartwallID']?> method=post>
          Name: <input type=text name='name' value='<?=$currentCartwall[1]?>'><br>
          Description: <input type=text name='desc' size=30 value='<?=$currentCartwall[4]?>'><br>
          <input type=submit name='submit' value='Update'>
          </form>
          <form action=editCartset.php?cartID=<?=$currentCartwall[2]?>&cartwallID=<?=$_GET['cartwallID']?> 
method=post>
            <input type=submit name='submit' value='Delete'>
          </form>
        </td>
        <td align=centre>
          <table border=1>
	    <tr>
	      <th colspan=3>Cartwall layout</th>
	    </tr>
            <tr>
             <td align=center>Cart 1</td><td align=center>Cart 2</td><td align=center>Cart 3</td>
	    </tr>
            <tr>
             <td align=center>Cart 4</td><td align=center>Cart 5</td><td align=center>Cart 6</td>
            </tr>
            <tr>
             <td align=center>Cart 7</td><td align=center>Cart 8</td><td align=center>Cart 9</td>
            </tr>
            <tr>
             <td align=center>Cart 10</td><td align=center>Cart 11</td><td align=center>Cart 12</td>
            </tr>
	  </table>
	</td>
      </tr>
    </table>
    <form method=post action=editCartwall.php?cartwallID=<?=$_GET['cartwallID']?>>
    <table border=1>
      <tr>
        <th>
	  Cart Position
        </th>
        <th>
          Track
        </th>
        <th>
          Text
        </th>
        <th>
          Style
        </th>
       </tr>
<?
$sql = "select audio.id, audio.title from audiojinglepkgs, audio where audio.id = audiojinglepkgs.audio order by audio.title asc";
$carts = pg_query($sql);
$opstr="<option value='Null'>Blank</option>\n";
while($cart = pg_fetch_array($carts)) {
  $opstr = $opstr . "<option value=" . $cart[0] . ">" . $cart[1] . "</option>\n";
}

// bodge till adverts are sorted out
$sql = "select audio.id, audio.title from audio,albums where albums.name='Adverts' and audio.music_album=albums.id order by audio.title asc";
$carts = pg_query($sql);
while($cart = pg_fetch_array($carts)) {
  $opstr = $opstr . "<option value=" . $cart[0] . ">" . $cart[1] . "</option>\n";
}

$sql = "select * from cartstyle order by name asc";
$styles = pg_query($sql);
$ststr="";
while($style = pg_fetch_array($styles)) {
  $ststr = $ststr . "<option value=" . $style[0] . ">" . $style[1] . "</option>\n";
}

for($i=0;$i<12;$i++) {
$sql = "SELECT audio.id, cartsaudio.* FROM cartsaudio, audio WHERE audio.id = cartsaudio.audio and
               cartsaudio.cartwall=" . pg_escape_string($_GET['cartwallID']) . " and cart = $i";
$activecarts = pg_query($sql);
?>
      <tr>
        <td>
          Cart <?=$i+1?>
        </td>
        <td>
          <select name=Track_<?=$i?>>
	  <?
	  if(pg_num_rows($activecarts) > 0) {
            $c = pg_fetch_row($activecarts,0);
            $cid = $c[0];
            $styleid = $c[3];
	    $ctext = $c[6];
	    echo str_replace("<option value=" . $cid . ">", "<option value=" . $cid . " selected>", $opstr);
	  } else {
            echo str_replace("<option value='Null'>", "<option value='Null' selected>", $opstr);
	    $styleid = "";
	    $ctext = "";
	  }
	  ?>
          </select>
        </td>
        <td>
	  <textarea name=Text_<?=$i?>><?=$ctext?></textarea>
        </td>
        <td>
<? if($styleid == "") { ?>
	  <select name=Style_<?=$i?>>
	    <?=$ststr ?>
	  </select>
<? } else { ?>
          <select name=Style_<?=$i?>>
<? echo str_replace("<option value=" . $styleid . ">", "<option value=" . $styleid . " selected>", $ststr); ?>
          </select>
<? } ?>
        </td>
      </tr>
<?
}
?>
    </table>
    <input type=submit name=submit value=Submit>
    </form>
<?
  } else {
?>
    <h1>Edit A Cartwall</h1>
    <hr>
    The selected cartwall does not exist...
<?
  }
} else {
?>
    <h1>Edit A Cartwall</h1>
    <hr>
    Invalid cartwall ID...
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
