<?
include('session.php');
$sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username' AND users.id = useraccess.userid AND
 (useraccess.privilage=4 or useraccess.privilage=8 or useraccess.privilage=3)";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
if ($count[0] == 0) {
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

?>
<h1>Sue Play List</h1><hr>
	    <!-- Display selection links at all times -->
	    <a href="/dps/suePlaylist.php?section=0">0</a>
	    <a href="/dps/suePlaylist.php?section=1">1</a>
	    <a href="/dps/suePlaylist.php?section=2">2</a>
	    <a href="/dps/suePlaylist.php?section=3">3</a>
	    <a href="/dps/suePlaylist.php?section=4">4</a>
	    <a href="/dps/suePlaylist.php?section=5">5</a>
	    <a href="/dps/suePlaylist.php?section=6">6</a>
	    <a href="/dps/suePlaylist.php?section=7">7</a>
	    <a href="/dps/suePlaylist.php?section=8">8</a>
	    <a href="/dps/suePlaylist.php?section=9">9</a>
	    <a href="/dps/suePlaylist.php?section=a">A</a>
	    <a href="/dps/suePlaylist.php?section=b">B</a>
	    <a href="/dps/suePlaylist.php?section=c">C</a>
	    <a href="/dps/suePlaylist.php?section=d">D</a>
	    <a href="/dps/suePlaylist.php?section=e">E</a>
	    <a href="/dps/suePlaylist.php?section=f">F</a>
	    <a href="/dps/suePlaylist.php?section=g">G</a>
	    <a href="/dps/suePlaylist.php?section=h">H</a>
	    <a href="/dps/suePlaylist.php?section=i">I</a>
	    <a href="/dps/suePlaylist.php?section=j">J</a>
	    <a href="/dps/suePlaylist.php?section=k">K</a>
	    <a href="/dps/suePlaylist.php?section=l">L</a>
	    <a href="/dps/suePlaylist.php?section=m">M</a>
	    <a href="/dps/suePlaylist.php?section=n">N</a>
	    <a href="/dps/suePlaylist.php?section=o">O</a>
	    <a href="/dps/suePlaylist.php?section=p">P</a>
	    <a href="/dps/suePlaylist.php?section=q">Q</a>
	    <a href="/dps/suePlaylist.php?section=r">R</a>
	    <a href="/dps/suePlaylist.php?section=s">S</a>
	    <a href="/dps/suePlaylist.php?section=t">T</a>
	    <a href="/dps/suePlaylist.php?section=u">U</a>
	    <a href="/dps/suePlaylist.php?section=v">V</a>
	    <a href="/dps/suePlaylist.php?section=w">W</a>
	    <a href="/dps/suePlaylist.php?section=x">X</a>
	    <a href="/dps/suePlaylist.php?section=y">Y</a>
	    <a href="/dps/suePlaylist.php?section=z">Z</a>
	    <p>
		<!-- search form -->
		<FORM METHOD=POST ACTION='/dps/suePlaylist.php?search=1'>
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
if(isset($change)) { //if they are changing something
	//Add or Remove the tracks as appropriate
	$max = pg_escape_string($_POST['max']);
//	$track = pg_escape_string($track);
	for ($i=1; $i<=$max; $i++) {
	  if (isset($_POST['song'.$i]) != $_POST['original'.$i]) { //something has changed
	    $track = pg_escape_string($_POST['id'.$i]);
	    $query = "SELECT count(*) FROM audio WHERE audio.id = '$track' AND audio.sustainer = 't'";
//	    echo $query;
            $result = pg_query($dbconn1, $query);
            $count = pg_fetch_row($result, 0);
	    if ($count[0] == 0) { 
	      $insert = pg_query($dbconn1, "UPDATE audio set sustainer = 't' WHERE audio.id='$track'") or die("Error!!");
              $name = "SELECT title FROM audio WHERE id=$track";
              $name = pg_query($dbconn1, $name);
              $name = pg_fetch_row($name, 0);
	      echo "<font color='red'>Track '" . $name[0] . "' added</font><br />";
            } else {
	      $remove = pg_query($dbconn1, "UPDATE audio SET sustainer = 'f' WHERE id = '$track'") or die("Error!!");
              $name = "SELECT title FROM audio WHERE id=$track";
              $name = pg_query($dbconn1, $name);
              $name = pg_fetch_row($name, 0);
	      echo "<font color='red'>Track '" . $name[0] ."' removed</font><br />";
            } //end $count etc etc
	  } //end something has changed
	} //end loop
echo "<b>Playlist Successfully Updated</b><br><p>";
} //end if isset($change)

	if (!isset($track) && (isset($search) || isset($section))) {
		//Start seaching and paging
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
  		  $query = pg_query("SELECT DISTINCT artists.name AS artist,audio.title AS title,audio.id AS id, audio.length_smpl as length FROM audio,artists,audioartists WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND $field ILIKE '%$terms%' AND audio.censor = 'f' ORDER BY $field LIMIT 200 OFFSET ".$offset*200);
		} else {
		  //SQL Query to get no. of tracks for this section
                  $count_query = pg_query("SELECT COUNT(audio.id) FROM artists,audio,audioartists WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND artists.name ILIKE '$section%' AND audio.censor = 'f'");
                  //SQL Query to get search results
                  $query = pg_query("SELECT DISTINCT artists.name AS artist,audio.title AS title,audio.id AS id, audio.length_smpl AS length WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND artists.name ILIKE '$section%' AND audio.censor = 'f' ORDER BY artists.name ASC LIMIT 200 OFFSET ".$offset*200);
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
		        $pagestr .= "&nbsp;<A HREF='/dps/suePlaylist.php?section=$section&offset=";
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
		<form method=POST action='/dps/suePlaylist.php?change=1'>
      		<table cellspacing="0" cellpadding="2" border="2" align="center" width="100%">
				<tr>
				  <th width="15%">
				    Add/Remove
				  </th>
				  <th width="30%">
				    Artist
				  </th>
				  <th width="30%">
				    Title
				  </th>
				  <th>
				    Length
				  </th>
				  <th width="15%">
				  	30s Preview
				  </th>
				</tr>
			<?
			$total = 0;
			while($tracks = pg_fetch_array($query)) {
				$total++;
				?>
				<tr>
				  <td style='text-align:center;'>
				    <?
				    //Check if it is in the playlist
				    $result = pg_query($dbconn1, "SELECT COUNT(*) FROM audio WHERE audio.id = '$tracks[id]' AND sustainer = 't'");
				    $count = pg_fetch_row($result, 0);
				    if ($count[0] == 0) { 
					    echo "<input type='checkbox' name='song$total'><input type=hidden name='id$total' value='$tracks[id]'><input type=hidden name='origianl$total' value='false'> ";
					    //<a href="/dps/suePlaylist.php?track=$tracks['id']">Add Track</a>
			            } else {
					    echo "<input type='checkbox' name='song$total' checked><input type=hidden name='id$total' value='$tracks[id]'> <input type=hidden name='original$total' value='true'>";
					    //<a href="/dps/suePlaylist.php?track=$tracks['id']">Remove Track</a>
				    }	    
				    ?>
				  </td>
				  <td>
				    <?// echo $tracks['id']." - ".$tracks['artist'] 
				    echo $tracks['artist']
				    ?>
				  </td>
				  <td>
				    <?=$tracks['title']?>
				  </td>
				  <td>
				    <?
					$timearray = getdate(round($tracks['length'] / 44100));
					echo $timearray['minutes'] . "m " . $timearray['seconds'] . "s";
				    ?>
				  </td>
				  <td>
				    <a href="suemp3.php?get=<?echo $tracks['id']?>">Preview</a>
				  </td>
				</tr>
				<?
			}
			if($total == 0) {
			  echo("<tr><td colspan=4><b>Sorry, no results were found.</b></td></tr>");
			} else {
			?>
		       <tr>
			<td style='text-align:center;'>
			 <input type=hidden name='max' value='<?=$total?>'>
			 <input type=submit value='Submit'>
			</td>
			<td colspan=3>
			 &laquo;&laquo; Click to submit your changes to the playlist before changing pages. &laquo;&laquo;
			</td>
		       </tr>
		       <tr>
			<td style='text-align:center'>
			 <input type=reset value='Reset'>
			</td>
			<td colspan=3>
			 &laquo;&laquo; Click to reset all the boxes to their original state. &laquo;&laquo;
			</td>
		       </tr>
		        <? } ?>
		      </table>
		     </form>
		      <br />
	<?
	echo $pagestr;
	// close no track set section
	}
	?>
	    <!-- Display selection links at all times -->
	    <a href="/dps/suePlaylist.php?section=0">0</a>
	    <a href="/dps/suePlaylist.php?section=1">1</a>
	    <a href="/dps/suePlaylist.php?section=2">2</a>
	    <a href="/dps/suePlaylist.php?section=3">3</a>
	    <a href="/dps/suePlaylist.php?section=4">4</a>
	    <a href="/dps/suePlaylist.php?section=5">5</a>
	    <a href="/dps/suePlaylist.php?section=6">6</a>
	    <a href="/dps/suePlaylist.php?section=7">7</a>
	    <a href="/dps/suePlaylist.php?section=8">8</a>
	    <a href="/dps/suePlaylist.php?section=9">9</a>
	    <a href="/dps/suePlaylist.php?section=a">A</a>
	    <a href="/dps/suePlaylist.php?section=b">B</a>
	    <a href="/dps/suePlaylist.php?section=c">C</a>
	    <a href="/dps/suePlaylist.php?section=d">D</a>
	    <a href="/dps/suePlaylist.php?section=e">E</a>
	    <a href="/dps/suePlaylist.php?section=f">F</a>
	    <a href="/dps/suePlaylist.php?section=g">G</a>
	    <a href="/dps/suePlaylist.php?section=h">H</a>
	    <a href="/dps/suePlaylist.php?section=i">I</a>
	    <a href="/dps/suePlaylist.php?section=j">J</a>
	    <a href="/dps/suePlaylist.php?section=k">K</a>
	    <a href="/dps/suePlaylist.php?section=l">L</a>
	    <a href="/dps/suePlaylist.php?section=m">M</a>
	    <a href="/dps/suePlaylist.php?section=n">N</a>
	    <a href="/dps/suePlaylist.php?section=o">O</a>
	    <a href="/dps/suePlaylist.php?section=p">P</a>
	    <a href="/dps/suePlaylist.php?section=q">Q</a>
	    <a href="/dps/suePlaylist.php?section=r">R</a>
	    <a href="/dps/suePlaylist.php?section=s">S</a>
	    <a href="/dps/suePlaylist.php?section=t">T</a>
	    <a href="/dps/suePlaylist.php?section=u">U</a>
	    <a href="/dps/suePlaylist.php?section=v">V</a>
	    <a href="/dps/suePlaylist.php?section=w">W</a>
	    <a href="/dps/suePlaylist.php?section=x">X</a>
	    <a href="/dps/suePlaylist.php?section=y">Y</a>
	    <a href="/dps/suePlaylist.php?section=z">Z</a>
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
