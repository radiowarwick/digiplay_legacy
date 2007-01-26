<?
include('session.php');
$sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username' AND users.id = useraccess.userid AND 
(useraccess.privilage=3 OR useraccess.privilage=5 OR useraccess.privilage=8)";
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
//Connect to the database

//Grab the data of what the user wants to do from the path
$offset = $_GET['offset'];
$change = $_GET['change'];
if (!isset($offset)) {
  $offset = 0;
}
if (isset($_GET['search'])) {
  $search = true;
  $field = $_POST['field'];
  $terms = $_POST['terms'];
} else {
  $section = $_GET['section'];
}
if ($_GET['action'] == "del") {
  if(is_numeric($_GET['PLID'])) {
    $sql = "DELETE FROM playlist where id = " . pg_escape_string($_GET['PLID']);
    pg_query($sql);
  } else {
    echo "<p>Don't be a muppet</p>";
   }
}
if ($_GET['action'] == "ins") {
   if(($_GET['playlist'] == 'A' || $_GET['playlist'] == 'B') && is_numeric($_GET['audio'])) {
     $sql = "INSERT INTO playlist (audio,playlist) VALUES (" . pg_escape_string($_GET['audio']) . ",'" . pg_escape_string($_GET['playlist']) . "')";
    pg_query($sql);
   } else {
    echo "<p>Don't be a muppet</p>";
   }
}

$sql = "SELECT playlist.id, audio.title FROM playlist, audio WHERE playlist = 'A' AND audio.id = playlist.audio";
$PLA = pg_query($sql);
$sql = "SELECT playlist.id, audio.title FROM playlist, audio WHERE playlist = 'B' AND audio.id = playlist.audio";
$PLB = pg_query($sql);
?>
<h1>The Playlist</h1><hr>
<b>The current playlist.</b>
<table width=100% border=1>
  <tr>
    <th colspan=2 width=50%>A</th><th colspan=2 width=50%>B</th>
  </tr>
  <?
  while(($trackA = pg_fetch_array($PLA)) | ($trackB = pg_fetch_array($PLB))) {
  ?>
  <tr>
    <?
    if($trackA) {
    ?>
    <td>
      <?=$trackA[1]?>
    </td>
    <td width=10%>
      <a href=/dps/playList.php?action=del&PLID=<?=$trackA[0]?>>Remove</a>
    </td>
    <?
    } else {
?>
    <td></td><td></td>
<?
    }
    if($trackB) {
    ?>
    <td>
      <?=$trackB[1]?>
    </td>
    <td width=10%>
      <a href=/dps/playList.php?action=del&PLID=<?=$trackB[0]?>>Remove</a>
    </td>
    <?
    } else {
?>
    <td></td><td></td>
<?
    }
?>
  </tr>
  <? } ?>
</table>
<hr>
	    <!-- Display selection links at all times -->
	    <a href="/dps/playList.php?section=0">0</a>
	    <a href="/dps/playList.php?section=1">1</a>
	    <a href="/dps/playList.php?section=2">2</a>
	    <a href="/dps/playList.php?section=3">3</a>
	    <a href="/dps/playList.php?section=4">4</a>
	    <a href="/dps/playList.php?section=5">5</a>
	    <a href="/dps/playList.php?section=6">6</a>
	    <a href="/dps/playList.php?section=7">7</a>
	    <a href="/dps/playList.php?section=8">8</a>
	    <a href="/dps/playList.php?section=9">9</a>
	    <a href="/dps/playList.php?section=a">A</a>
	    <a href="/dps/playList.php?section=b">B</a>
	    <a href="/dps/playList.php?section=c">C</a>
	    <a href="/dps/playList.php?section=d">D</a>
	    <a href="/dps/playList.php?section=e">E</a>
	    <a href="/dps/playList.php?section=f">F</a>
	    <a href="/dps/playList.php?section=g">G</a>
	    <a href="/dps/playList.php?section=h">H</a>
	    <a href="/dps/playList.php?section=i">I</a>
	    <a href="/dps/playList.php?section=j">J</a>
	    <a href="/dps/playList.php?section=k">K</a>
	    <a href="/dps/playList.php?section=l">L</a>
	    <a href="/dps/playList.php?section=m">M</a>
	    <a href="/dps/playList.php?section=n">N</a>
	    <a href="/dps/playList.php?section=o">O</a>
	    <a href="/dps/playList.php?section=p">P</a>
	    <a href="/dps/playList.php?section=q">Q</a>
	    <a href="/dps/playList.php?section=r">R</a>
	    <a href="/dps/playList.php?section=s">S</a>
	    <a href="/dps/playList.php?section=t">T</a>
	    <a href="/dps/playList.php?section=u">U</a>
	    <a href="/dps/playList.php?section=v">V</a>
	    <a href="/dps/playList.php?section=w">W</a>
	    <a href="/dps/playList.php?section=x">X</a>
	    <a href="/dps/playList.php?section=y">Y</a>
	    <a href="/dps/playList.php?section=z">Z</a>
	    <p>
		<!-- search form -->
		<FORM METHOD=POST ACTION='/dps/playList.php?search=1'>
		  Find songs where the 
		  <SELECT NAME='field'>
		  <OPTION VALUE='artists.name'>Artist</OPTION>
		  <OPTION VALUE='audio.title'>Track</OPTION>
		  </SELECT>
		  contains
		  <INPUT TYPE='text' NAME='terms'>
		  <INPUT TYPE='submit' VALUE='Search'>
		  <?
		   if (($terms == '') & ($search == true)) { 
		    echo("<br>Please enter a search term.");
		    $search = false; $section = 'nothing';
		   }
		  ?>
		</FORM>
	    </p>
<?

//Check which section they're looking at
unset($change); // till code is sorted
if(isset($change)) { //if they are changing something
	//Add or Remove the tracks as appropriate
	$max = pg_escape_string($_POST['max']);
//	$track = pg_escape_string($track);
	for ($i=1; $i<=$max; $i++) {
	  if (isset($_POST['song'.$i]) != $_POST['original'.$i]) { //something has changed
	    if($_POST['song'.$i] == "A") {
	      $sql = "DELETE FROM playlist WHERE audioid=";
              $sql = "INSERT INTO playlist VALUES(" . pg_escape_string($_POST['id' . $i]) . ",'A');";
	    } else if($_POST['song'.$i] == "B") {
	      $sql = "DELETE FROM playlist WHERE audioid=";
              $sql = "INSERT INTO playlist VALUES(" . pg_escape_string($_POST['id' . $i]) . ",'B');";
            } else if($_POST['song'.$i] == "C") {
	      $sql = "DELETE FROM playlist WHERE audioid=";
	      $sql = "INSERT INTO playlist VALUES(" . pg_escape_string($_POST['id' . $i]) . ",'C');";
            } else {
	      $sql = "DELETE FROM playlist WHERE audioid=" . pg_escape_string($_POST['id' . $i]);
	    }
	  } //end something has changed
	} //end loop
echo "<b>Playlist Successfully Updated</b><br><p>";
} //end if isset($change)

	if (!isset($track) && (isset($search) || isset($section))) {
		//Start seaching anc paging
		$section = htmlspecialchars($section);
		$section = pg_escape_string($section);
		$terms = pg_escape_string($terms);
                $offset = pg_escape_string($offset);
                $section = pg_escape_string($section);
                $field = pg_escape_string($field);
		if ($search) {
		  //SQL Query to get no. of search results
  		  $count_query = pg_query("SELECT COUNT(audio.id) FROM artists,audio,audioartists WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND $field ILIKE '%$terms%' AND audio.censor = 'f'");
		  //SQL Query to get search results
  		  $query = pg_query("SELECT DISTINCT artists.name AS artist,audio.title AS title,audio.id AS id FROM artists,audio,audioartists WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND $field ILIKE '%$terms%' AND audio.censor = 'f' ORDER BY $field LIMIT 200 OFFSET ".$offset*200);
		} else {
		  //SQL Query to get no. of tracks for this section
                  $count_query = pg_query("SELECT COUNT(audio.id) FROM artists,audio,audioartists WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND artists.name ILIKE '$section%' AND audio.censor = 'f'");
                  //SQL Query to get search results
                  $query = pg_query("SELECT DISTINCT artists.name AS artist,audio.title AS title,audio.id AS id WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND artists.name ILIKE '$section%' AND audio.censor = 'f' ORDER BY artists.name ASC LIMIT 200 OFFSET ".$offset*200);
		}
		//Count no of results
		$rowarray = pg_fetch_row($count_query,0);
		$rowcount = $rowarray[0];
		if ($rowcount > 200) {  //if more that 200 results
		  if ($search) {
		    //if doing a search ask them to refine it
		    echo "<b style='color:red'>There are over 200 results. Please refine your search.</b>";
		  } else {
		    //if showing a section do pages & links
		    $pagestr = "<b style='color:red'>There are over 200 results therefore some are on other pages.</b><br />Results: ";
		    //calculate no. of pages
		    $pagecount = ceil($rowcount / 200);
		    //loop through pages
		    for ($loop = 1; $loop <= $pagecount; $loop++) {
		      if ($loop-1 == $offset) {
			//if current page
		        $pagestr .= "&nbsp;";
			$pagestr .= (($loop-1)*200)+1;
			$pagestr .= " - ";
			//if last page put total no not multimple of 200
			if ((($loop-1)*200)+200 > $rowcount) {
			  $pagestr .= $rowcount;
			} else {
			  $pagestr .= (($loop-1)*200)+200;
			}
			$pagestr .= "&nbsp;";
		      } else {
			//if not current page
		        $pagestr .= "&nbsp;<A HREF='/dps/playList.php?section=$section&offset=";
		        $pagestr .= $loop-1;
		        $pagestr .= "'>";
			$pagestr .= (($loop-1)*200)+1;
			$pagestr .= " - ";
			//if last page put total no not multimple of 200
			if ((($loop-1)*200)+200 > $rowcount) {
			  $pagestr .= $rowcount;
			} else {
			  $pagestr .= (($loop-1)*200)+200;
			}
			$pagestr .= "</A>&nbsp;";
		      }
		    }
		    $pagestr .= "<br /><br />";
		    echo $pagestr;
	 	  }
		}
		//end of paging, start table layout
		?>

		<b>The search returned the following results:</b><br /><br />
		<form method=POST action='/dps/playList.php?change=1'>
      		<table cellspacing="0" cellpadding="2" border="2" align="center" width="100%">
				<tr>
				  <th width="30%">
				    Artist
				  </th>
				  <th width="30%">
				    Title
				  </th>
				  <th width="15%">
				  	30s Preview
				  </th>
                                  <th width="15%">
                                        Playlist
                                  </th>
				</tr>
			<?
			$total = 0;
			while($tracks = pg_fetch_array($query)) {
				$total++;
				?>
				<tr>
				  <td>
				    <?
				    echo $tracks['artist']
				    ?>
				  </td>
				  <td>
				    <?=$tracks['title']?>
				  </td>
				  <td>
				    <a href="suemp3.php?get=<?echo $tracks['id']?>">Preview</a>
				  </td>
                                  <td style='text-align:center;'>
				    Add to <a href='playList.php?action=ins&audio=<?=$tracks['id']?>&playlist=A'>A</a> 
					   <a href='playList.php?action=ins&audio=<?=$tracks['id']?>&playlist=B'>B</a>
                                  </td>
				</tr>
				<?
			}
			if($total == 0) {
			  echo("<tr><td colspan=4><b>Sorry, no results were found.</b></td></tr>");
			}?>
		      </table>
		      <br />
	<?
	echo $pagestr;
	// close no track set section
	}
	?>
	    <!-- Display selection links at all times -->
	    <a href="/dps/playList.php?section=0">0</a>
	    <a href="/dps/playList.php?section=1">1</a>
	    <a href="/dps/playList.php?section=2">2</a>
	    <a href="/dps/playList.php?section=3">3</a>
	    <a href="/dps/playList.php?section=4">4</a>
	    <a href="/dps/playList.php?section=5">5</a>
	    <a href="/dps/playList.php?section=6">6</a>
	    <a href="/dps/playList.php?section=7">7</a>
	    <a href="/dps/playList.php?section=8">8</a>
	    <a href="/dps/playList.php?section=9">9</a>
	    <a href="/dps/playList.php?section=a">A</a>
	    <a href="/dps/playList.php?section=b">B</a>
	    <a href="/dps/playList.php?section=c">C</a>
	    <a href="/dps/playList.php?section=d">D</a>
	    <a href="/dps/playList.php?section=e">E</a>
	    <a href="/dps/playList.php?section=f">F</a>
	    <a href="/dps/playList.php?section=g">G</a>
	    <a href="/dps/playList.php?section=h">H</a>
	    <a href="/dps/playList.php?section=i">I</a>
	    <a href="/dps/playList.php?section=j">J</a>
	    <a href="/dps/playList.php?section=k">K</a>
	    <a href="/dps/playList.php?section=l">L</a>
	    <a href="/dps/playList.php?section=m">M</a>
	    <a href="/dps/playList.php?section=n">N</a>
	    <a href="/dps/playList.php?section=o">O</a>
	    <a href="/dps/playList.php?section=p">P</a>
	    <a href="/dps/playList.php?section=q">Q</a>
	    <a href="/dps/playList.php?section=r">R</a>
	    <a href="/dps/playList.php?section=s">S</a>
	    <a href="/dps/playList.php?section=t">T</a>
	    <a href="/dps/playList.php?section=u">U</a>
	    <a href="/dps/playList.php?section=v">V</a>
	    <a href="/dps/playList.php?section=w">W</a>
	    <a href="/dps/playList.php?section=x">X</a>
	    <a href="/dps/playList.php?section=y">Y</a>
	    <a href="/dps/playList.php?section=z">Z</a>
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
