<?
include('session.php');
$sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username' AND users.id = useraccess.userid AND users.enabled = 't' AND
(useraccess.privilage=3 or useraccess.privilage=8 or useraccess.privilage=7)";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
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
<?
//Check which section they're looking at
if(isset($change)) { //if they are changing something
  if(is_numeric($_GET['trackID'])) {
    // normal audio table update
    $updatesql = "UPDATE audio SET " .
		"title = '" . pg_escape_string($_POST['title']) . "', " .
                "reclibid = '" . pg_escape_string($_POST['reclib']) . "', " .
                "music_released = '" . pg_escape_string($_POST['released']) . "', " .
                "origin = '" . pg_escape_string($_POST['origin']) . "', " .
                "notes = '" . pg_escape_string($_POST['notes']) . "' " .
		"WHERE audio.id = " . pg_escape_string($_GET['trackID']);
    //echo $updatesql . "<br>";
    pg_query($updatesql);
    // update the album
    if($_POST['album'] != '') {
      $sql = "SELECT * FROM albums where name = '" . pg_escape_string($_POST['album']) . "'";
      $query = pg_query($sql);
      if(pg_num_rows($query) == 0){
        $inssql = "INSERT INTO albums (name,source) VALUES ('" . pg_escape_string($_POST['album']) . "','Web Interface')";
        //echo $insql . "<br>";
        pg_query($inssql);
	$sql = "SELECT last_value FROM albums_id_seq";
        $newid = pg_query($sql);
        $newid = pg_fetch_row($newid,0);
        $newid = $newid[0];
      } else {
        $newid = pg_fetch_row($query,0);
        $newid = $newid[0];
      }
      $upsql = "UPDATE audio SET music_album = " . $newid . " WHERE id = " . pg_escape_string($_GET['trackID']);
      //echo $upsql . "<br>";
      pg_query($upsql);
    } else {
      $upsql = "UPDATE audio SET music_album = 0 WHERE id = " . pg_escape_string($_GET['trackID']);
      //echo $upsql . "<br>";
      pg_query($upsql);
    }
    //update the artist
    for($i=0;$i<=$_POST['artistnum'];$i++) {
      $artistnum = "artist" . $i;
      $artistnumid = $artistnum . "id";
      //IF BOX IS POPULATED
      if($_POST[$artistnum] != '') {
        $sql = "SELECT * FROM artists where name = '" . pg_escape_string($_POST[$artistnum]) . "'";
        $query = pg_query($sql);
        //IF POPULATED ARTIST DOES NOT EXIST IN DB
        if(pg_num_rows($query) == 0){
          $inssql = "INSERT INTO artists (name) VALUES ('" . pg_escape_string($_POST[$artistnum]) . "')";
          pg_query($inssql);
          $sql = "SELECT last_value FROM artists_id_seq";
          $newid = pg_query($sql);
          $newid = pg_fetch_row($newid,0);
          $newid = $newid[0];
        //IF POPULATED ARTIST DOES EXIST
        } else {
          $newid = pg_fetch_row($query,0);
          $newid = $newid[0];
        }
        if($i == $_POST['artistnum']) {
          $inssql = "INSERT INTO audioartists (audio,artist) VALUES (" . pg_escape_string($_GET['trackID']) . "," . $newid . ")";
          pg_query($inssql);
        } else {
          if($newid != $_POST[$artistnumid] && is_numeric($_POST[$artistnumid])) {
            $upsql = "UPDATE audioartists SET artist = " . $newid . " WHERE audio = " .
                       pg_escape_string($_GET['trackID']) . " and artist = " . pg_escape_string($_POST[$artistnumid]);
            pg_query($upsql);
          }
        }
      } else {
        if($i !=$_POST['artistnum'] && is_numeric($_POST[$artistnumid])) {
          $delsql = "DELETE FROM audioartists WHERE audio = " . pg_escape_string($_GET['trackID']) . " AND artist = " . pg_escape_string($_POST[$artistnumid]);
          pg_query($delsql);
        }
      }
    }
    //update the keywords
    for($i=0;$i<=$_POST['keywordnum'];$i++) {
      $keywordnum = "keyword" . $i;
      $keywordnumid = $keywordnum . "id";
      //IF BOX IS POPULATED
      if($_POST[$keywordnum] != '') {
        $sql = "SELECT * FROM keywords where name = '" . pg_escape_string($_POST[$keywordnum]) . "'";
        $query = pg_query($sql);
        //IF POPULATED KEYWORD DOES NOT EXIST IN DB
        if(pg_num_rows($query) == 0){
          $inssql = "INSERT INTO keywords (name) VALUES ('" . pg_escape_string($_POST[$keywordnum]) . "')";
          pg_query($inssql);
          $sql = "SELECT last_value FROM keywords_id_seq";
          $newid = pg_query($sql);
          $newid = pg_fetch_row($newid,0);
          $newid = $newid[0];
        //IF POPULATED KEYWORD DOES EXIST
        } else {
          $newid = pg_fetch_row($query,0);
          $newid = $newid[0];
        }
        if($i == $_POST['keywordnum']) {
          $inssql = "INSERT INTO audiokeywords (track,keyword) VALUES (" . pg_escape_string($_GET['trackID']) . "," . $newid . ")";
          pg_query($inssql);
        } else {
          if($newid != $_POST[$keywordnumid] && is_numeric($_POST[$keywordnumid])) {
            $upsql = "UPDATE audiokeywords SET keyword = " . $newid . " WHERE track = " .
                       pg_escape_string($_GET['trackID']) . " and keyword = " . pg_escape_string($_POST[$keywordnumid]);
            pg_query($upsql);
          }
        }
      } else {
        if($i !=$_POST['keywordnum'] && is_numeric($_POST[$keywordnumid])) {
          $delsql = "DELETE FROM audiokeywords WHERE track = " . pg_escape_string($_GET['trackID']) . " AND keyword = " . pg_escape_string($_POST[$keywordnumid]);
          pg_query($delsql);                                              
        }
      }
    }
    echo "<b>Track Successfully Updated</b><br><p>";
  } else {
    echo "<b>Invalid Track ID provided</b>";
  }
}
if(isset($_GET['trackID'])) { //display edit page
  if(is_numeric($_GET['trackID'])) {
    $trackID = pg_escape_string($_GET['trackID']);
    $query = pg_query("SELECT DISTINCT audio.title AS title, audio.id AS id, 
                      audio.reclibid as reclib, audio.notes as notes, albums.name as album,
                      audio.music_released as released, audio.origin as origin 
                       FROM audio,albums WHERE audio.music_album = albums.id AND audio.id = $trackID");
    if(pg_num_rows($query) == 0){
      echo "<b>Invalid track ID passed please return to the <a href=mlib.php>music library</a>.<br>";
    } else if (pg_num_rows($query) == 1) {
      $trackinfo = pg_fetch_row($query,0);      
      ?>
      <FORM METHOD=POST ACTION='/dps/editTrack.php?change=true&trackID=<?=$trackinfo[1]?>'>
      <table cellspacing="0" cellpadding="2" border="2" align="center" width="100%">
        <tr>
          <th>Title</th>
          <td><input type=text name=title value="<?=$trackinfo[0]?>"></td>
        </tr>
        <tr>
          <th>Artist</th>
          <td>
      <?
      $query1 = pg_query("SELECT DISTINCT artists.name, artists.id
                       FROM audio,artists,audioartists
		       WHERE audio.id = audioartists.audio AND audioartists.artist = artists.id AND audio.id = $trackID");
      $i = 0;
      while($artist = pg_fetch_array($query1)) {
        ?>
        Artist <?=$i+1?> &nbsp&nbsp&nbsp&nbsp&nbsp : <input type=text name=artist<?=$i?> value="<?=$artist[0]?>"><br>
        <input type=hidden name=artist<?=$i?>id value="<?=$artist[1]?>">
        <?
        $i++;
      }
      ?>
      New Artist : <input type=text name=artist<?=$i?> value=""><br>
      <input type=hidden name=artistnum value=<?=$i?>>
          </td>
        </tr>
        <tr>
          <th>Album</th>
          <td><input type=text name=album value="<?=$trackinfo[4]?>"></td>
        </tr>
        <tr>
          <th>Keywords</th>
          <td>
      <?
      $query1 = pg_query("SELECT DISTINCT keywords.name, keywords.id
                       FROM audio,keywords,audiokeywords
                       WHERE audio.id = audiokeywords.track AND audiokeywords.keyword = keywords.id AND audio.id = $trackID");
      $i = 0;
      while($keyword = pg_fetch_array($query1)) {
        ?>
    Keyword <?=$i+1?> &nbsp&nbsp&nbsp&nbsp&nbsp : <input type=text name=keyword<?=$i?> value="<?=$keyword[0]?>"><br>
    <input type=hidden name=keyword<?=$i?>id value="<?=$keyword[1]?>">
        <?
        $i++;
      }
      ?>
    New Keyword : <input type=text name=keyword<?=$i?> value=""><br>
    <input type=hidden name=keywordnum value=<?=$i?>>
      <?
      $query1 = pg_query("SELECT DISTINCT keywords.name
                       FROM audio,keywords,artistskeywords, audioartists
                       WHERE audio.id = audioartists.audio AND audioartists.artist = artistskeywords.artist
                        AND artistskeywords.keyword = keywords.id AND audio.id = $trackID");
      $i = 0;
      if(pg_num_rows($query1)) {
        echo "<b>Artist keywords</b><br>";
      }
      while($keyword = pg_fetch_array($query1)) {
        ?>
        <?=$keyword[0]?><br>
        <?
        $i++;
      }
      ?>
          </td>
        </tr>
        <tr>
          <th>Released</th>
          <td><input type=text name=released value="<?=$trackinfo[5]?>"></td>
        </tr>
        <tr>
          <th>Reclib</th>
          <td><input type=text name=reclib value="<?=$trackinfo[3]?>"></td>
        </tr>
        <tr>
          <th>Origin</th>
          <td><input type=text name=origin value="<?=$trackinfo[6]?>"></td>
        </tr>
        <tr>
          <th>Notes</th>
          <td><textarea name=notes rows=5><?=$trackinfo[3]?></textarea></td>
        </tr>
        <tr>
          <th>Save</th>
          <td><input type=submit name=Submit value="Submit"></td>
        </tr>
      </table>
      </FORM>
      <?
    } else {
      echo "Database Error: Multiple tracks listed for ID:$trackID<br>";
    }
  } else {
    echo "<b>Invalid track ID passed please return to the <a href=mlib.php>music library</a>.<br>";
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
