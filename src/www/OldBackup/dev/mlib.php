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
$sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username' AND users.id = useraccess.userid AND users.enabled = 't' AND (useraccess.privilage=3 OR useraccess.privilage=5 OR useraccess.privilage=6)";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
if ($count[0] == 0) {
  $report = false;
} else {
  $report = true;
}

$sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username' AND users.id = useraccess.userid AND
 (useraccess.privilage=4 or useraccess.privilage=8 or useraccess.privilage=3)";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
if ($count[0] == 0) {
  $playlist = false;
} else {
  $playlist = true;
  //Check which section they're looking at
  if($_POST['change'] == "true") { //if they are changing something
  	//echo "Changing<br>";
        //Add or Remove the tracks as appropriate
        $max = pg_escape_string($_POST['max']);
//      $track = pg_escape_string($track);
        for ($i=1; $i<=$max; $i++) {
          if (($_POST['song'.$i] == "on" && $_POST['original'.$i] == "false") || ($_POST['song'.$i] == "" && $_POST['original'.$i] == "true")) { //something has changed
	    //echo "#" . $_POST['song'.$i] . "," . $_POST['original'.$i] . "#";
            $track = pg_escape_string($_POST['id'.$i]);
            $query = "SELECT count(*) FROM audio WHERE audio.id = '$track' AND audio.sustainer = 't'";
//          echo $query;
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
  }
}
if($playlist) {
	$searchZone = $_GET['searchZone'];
} else {
	$searchZone = "lib";
}
if($searchZone == "") {
	$searchZone = "lib";
}
//Grab the data of what the user wants to do from the path
$offset = $_GET['offset'];
if (!isset($offset)) {
  $offset = 0;
}
if (isset($_GET['field'])) {
  $search = true;
  $field = pg_escape_string($_GET['field']);
  if($field != "AT" && $field != "A" && $field != "T") {
    $search = false;
  }
  if(strlen(pg_escape_string($_GET['terms'])) == 1) {
    $terms = pg_escape_string($_GET['terms']) . "%";
  } else {
    $terms = "%" . pg_escape_string($_GET['terms']) . "%";
  }
}

?>
<h1>Music Library</h1>
<hr>
	    <!-- Display selection links at all times -->
	    <a name='results'>
	    <a href="mlib.php?terms=0&field=T">0</a>
	    <a href="mlib.php?terms=1&field=T">1</a>
	    <a href="mlib.php?terms=2&field=T">2</a>
	    <a href="mlib.php?terms=3&field=T">3</a>
	    <a href="mlib.php?terms=4&field=T">4</a>
	    <a href="mlib.php?terms=5&field=T">5</a>
	    <a href="mlib.php?terms=6&field=T">6</a>
	    <a href="mlib.php?terms=7&field=T">7</a>
	    <a href="mlib.php?terms=8&field=T">8</a>
	    <a href="mlib.php?terms=9&field=T">9</a>
	    <a href="mlib.php?terms=a&field=T">A</a>
	    <a href="mlib.php?terms=b&field=T">B</a>
	    <a href="mlib.php?terms=c&field=T">C</a>
	    <a href="mlib.php?terms=d&field=T">D</a>
	    <a href="mlib.php?terms=e&field=T">E</a>
	    <a href="mlib.php?terms=f&field=T">F</a>
	    <a href="mlib.php?terms=g&field=T">G</a>
	    <a href="mlib.php?terms=h&field=T">H</a>
	    <a href="mlib.php?terms=i&field=T">I</a>
	    <a href="mlib.php?terms=j&field=T">J</a>
	    <a href="mlib.php?terms=k&field=T">K</a>
	    <a href="mlib.php?terms=l&field=T">L</a>
	    <a href="mlib.php?terms=m&field=T">M</a>
	    <a href="mlib.php?terms=n&field=T">N</a>
	    <a href="mlib.php?terms=o&field=T">O</a>
	    <a href="mlib.php?terms=p&field=T">P</a>
	    <a href="mlib.php?terms=q&field=T">Q</a>
	    <a href="mlib.php?terms=r&field=T">R</a>
	    <a href="mlib.php?terms=s&field=T">S</a>
	    <a href="mlib.php?terms=t&field=T">T</a>
	    <a href="mlib.php?terms=u&field=T">U</a>
	    <a href="mlib.php?terms=v&field=T">V</a>
	    <a href="mlib.php?terms=w&field=T">W</a>
	    <a href="mlib.php?terms=x&field=T">X</a>
	    <a href="mlib.php?terms=y&field=T">Y</a>
	    <a href="mlib.php?terms=z&field=T">Z</a>
	    <p>
		<!-- search form -->
		<FORM METHOD=GET ACTION='mlib.php'>
		  Find songs where the 
		  <SELECT NAME='field'>
		  <OPTION VALUE='AT'>Both</OPTION>
		  <OPTION VALUE='A'>Artist</OPTION>
		  <OPTION VALUE='T'>Track</OPTION>
		  </SELECT>
		  contains
		  <INPUT TYPE='text' NAME='terms'>
		  <INPUT TYPE='submit' VALUE='Search'>
		  <?
		   if($playlist) {
		  ?>
		  <br>Search Domain: 	Library<INPUT TYPE='radio' NAME='searchZone' VALUE='lib' CHECKED>
		  			Sue Playlist<INPUT TYPE='radio' NAME='searchZone' VALUE='sue'>
		  <?
		   }
		   if (($terms == '') & ($search == true)) { 
		    echo("<br>Please enter a search term.");
		    $search = false;
		   }
		  ?>
		</FORM>
	    </p>
<?

	if ($search) {
	  if ($searchZone == "lib") {
	  //SQL Query to get no. of search results
	    if($field=="AT") {
  	      $count_query = pg_query("SELECT COUNT(audio.id) FROM artists,audio,audioartists WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND (artists.name ILIKE '$terms' OR audio.title ILIKE '$terms') AND audio.censor = 'f'");
	      //SQL Query to get search results
	      $query = pg_query("SELECT DISTINCT artists.name AS artist,audio.title AS title,audio.id AS id, audio.sustainer as sust WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND (artists.name ILIKE '$terms' or audio.title ILIKE '$terms') AND audio.censor = 'f' ORDER BY audio.title LIMIT 200 OFFSET ".$offset*200);
	    } else if($field=="T") {
              $count_query = pg_query("SELECT COUNT(audio.id) FROM artists,audio,audioartists WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND audio.title ILIKE '$terms' AND audio.censor = 'f'");
	      //SQL Query to get search results
	      $query = pg_query("SELECT DISTINCT artists.name AS artist,audio.title AS title,audio.id AS id, audio.sustainer as sust WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND audio.title ILIKE '$terms' AND audio.censor = 'f' ORDER BY audio.title LIMIT 200 OFFSET ".$offset*200);
	    } else if($field=="A") {
              $count_query = pg_query("SELECT COUNT(audio.id) FROM artists,audio,audioartists WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND artists.name ILIKE '$terms' AND audio.censor = 'f'");
	      //SQL Query to get search results
	      $query = pg_query("SELECT DISTINCT artists.name AS artist,audio.title AS title,audio.id AS id, audio.sustainer as sust WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND artists.name ILIKE '$terms' AND audio.censor = 'f' ORDER BY artists.name LIMIT 200 OFFSET ".$offset*200);
	    }
	  } else if($searchZone == "sue") {
            if($field=="AT") {
	      $count_query = pg_query("SELECT COUNT(audio.id) FROM artists,audio,audioartists WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND (artists.name ILIKE '$terms' OR audio.title ILIKE '$terms') AND audio.censor = 'f' AND audio.sustainer='t'");
	      //SQL Query to get search results
	      $query = pg_query("SELECT DISTINCT artists.name AS artist,audio.title AS title,audio.id AS id, audio.sustainer as sust WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND (artists.name ILIKE '$terms' or audio.title ILIKE '$terms') AND audio.censor = 'f'  AND audio.sustainer='t' ORDER BY audio.title LIMIT 200 OFFSET ".$offset*200);
	    } else if($field=="T") {
	      $count_query = pg_query("SELECT COUNT(audio.id) FROM artists,audio,audioartists WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND audio.title ILIKE '$terms' AND audio.censor = 'f' AND audio.sustainer='t'");
	      //SQL Query to get search results
	      $query = pg_query("SELECT DISTINCT artists.name AS artist,audio.title AS title,audio.id AS id, audio.sustainer as sust WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND audio.title ILIKE '$terms' AND audio.censor = 'f' AND audio.sustainer='t' ORDER BY audio.title LIMIT 200 OFFSET ".$offset*200);
	    } else if($field=="A") {
	      $count_query = pg_query("SELECT COUNT(audio.id) FROM artists,audio,audioartists WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND artists.name ILIKE '$terms' AND audio.censor = 'f' AND audio.sustainer='t'");
	      //SQL Query to get search results
	      $query = pg_query("SELECT DISTINCT artists.name AS artist,audio.title AS title,audio.id AS id, audio.sustainer as sust HERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND artists.name ILIKE '$terms' AND audio.censor = 'f' AND audio.sustainer='t' ORDER BY artists.name LIMIT 200 OFFSET ".$offset*200);
	    }
	  }
	//Count no of results
	  $rowarray = pg_fetch_row($count_query,0);
	  $rowcount = $rowarray[0];
	  if ($rowcount > 200) {  //if more that 200 results
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
	        $pagestr .= "&nbsp;<A HREF='mlib.php?terms=" . $_GET['terms'] . "&field=" . $_GET['field'] . "&offset=";
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
	  //end of paging, start table layout
	?>

		<b>The search returned the following results:</b><br /><br />
		<form method=POST action='mlib.php?searchZone=<?=$_GET['searchZone']?>&terms=<?=$_GET['terms']?>&field=<?=$_GET['field']?>&offset=<?=$_GET['offset']?>'>
		<input type="hidden" name="change" value="true">
      		<table cellspacing="0" cellpadding="2" border="2" align="center" width="100%">
				<tr>
				  <th width="40%">
				    Title
				  </th>
				  <th width="40%">
				    Artist
				  </th>
				  <th width="5%">
				  	30s Preview
				  </th>
				  <th width="5%">
				  	Edit
				  </th>
				  <th width="5%">
					Sustainer
				  </th>
				  <? if($report) {?>
				  <th width=5%>
				  	Report
				  </th>
				  <? } ?>
				</tr>
			<?
			$total = 0;
			while($tracks = pg_fetch_array($query)) {
				$total++;
				?>
				<tr>
				  <td>
				    <? // echo $tracks['id']." - ".$tracks['artist'] 
				    echo $tracks['title']
				    ?>
				  </td>
				  <td>
				    <?=$tracks['artist']?>
				  </td>
				  <td>
				    <a href="suemp3.php?get=<?echo $tracks['id']?>">Preview</a>
				  </td>
				  <td>
				    <a href="editTrack.php?trackID=<?echo $tracks['id']?>">Edit</a>
				  </td>
				  <td>
				    <?
				    if($playlist) {
				      if($tracks['sust'] == 't') {
				        echo "<input type='checkbox' name='song$total' checked><input type=hidden name='id$total' value='" . $tracks['id'] . "'><input type=hidden name='original$total' value='true'> ";
				      } else {
					echo "<input type='checkbox' name='song$total'><input type=hidden name='id$total' value='" . $tracks['id'] . "'><input type=hidden name='original$total' value='false'> ";
				      }
				    } else {
				      if($tracks['sust'] == 't') {
					echo "Yes";
				      } else {
					echo "No";
				      }
				    }
				    ?>
				  </td>
				  <? if($report) {?>
				  <td>
				  	<a href="report.php?trackID=<?echo $tracks['id']?>">Report</a>
				  </td>
				  <? } ?>
				</tr>
				<?
			}
			if($total == 0) {
			  echo("<tr><td colspan=4><b>Sorry, no results were found.</b></td></tr>");
			} else {
			  if($playlist) {
			?>
                         <tr>
                           <td style='text-align:center;'>
                             <input type=hidden name='max' value='<?=$total?>'>
                             <input type=submit value='Submit'>
                           </td>
                           <td colspan=4>
                             &laquo;&laquo; Click to submit your changes to the playlist before changing pages. &laquo;&laquo;
                           </td>
                         </tr>
                         <tr>
                           <td style='text-align:center'>
                             <input type=reset value='Reset'>
                           </td>
                           <td colspan=4>
                             &laquo;&laquo; Click to reset all the boxes to their original state. &laquo;&laquo;
                           </td>
                         </tr>
		        <? }
			}?>
		      </table>
		     </form>
		      <br />
	<?
	echo $pagestr;
	// close no track set section
	}
	?>
	    <!-- Display selection links at all times -->
	    <a href="mlib.php?terms=0&field=T">0</a>
	    <a href="mlib.php?terms=1&field=T">1</a>
	    <a href="mlib.php?terms=2&field=T">2</a>
	    <a href="mlib.php?terms=3&field=T">3</a>
	    <a href="mlib.php?terms=4&field=T">4</a>
	    <a href="mlib.php?terms=5&field=T">5</a>
	    <a href="mlib.php?terms=6&field=T">6</a>
	    <a href="mlib.php?terms=7&field=T">7</a>
	    <a href="mlib.php?terms=8&field=T">8</a>
	    <a href="mlib.php?terms=9&field=T">9</a>
	    <a href="mlib.php?terms=a&field=T">A</a>
	    <a href="mlib.php?terms=b&field=T">B</a>
	    <a href="mlib.php?terms=c&field=T">C</a>
	    <a href="mlib.php?terms=d&field=T">D</a>
	    <a href="mlib.php?terms=e&field=T">E</a>
	    <a href="mlib.php?terms=f&field=T">F</a>
	    <a href="mlib.php?terms=g&field=T">G</a>
	    <a href="mlib.php?terms=h&field=T">H</a>
	    <a href="mlib.php?terms=i&field=T">I</a>
	    <a href="mlib.php?terms=j&field=T">J</a>
	    <a href="mlib.php?terms=k&field=T">K</a>
	    <a href="mlib.php?terms=l&field=T">L</a>
	    <a href="mlib.php?terms=m&field=T">M</a>
	    <a href="mlib.php?terms=n&field=T">N</a>
	    <a href="mlib.php?terms=o&field=T">O</a>
	    <a href="mlib.php?terms=p&field=T">P</a>
	    <a href="mlib.php?terms=q&field=T">Q</a>
	    <a href="mlib.php?terms=r&field=T">R</a>
	    <a href="mlib.php?terms=s&field=T">S</a>
	    <a href="mlib.php?terms=t&field=T">T</a>
	    <a href="mlib.php?terms=u&field=T">U</a>
	    <a href="mlib.php?terms=v&field=T">V</a>
	    <a href="mlib.php?terms=w&field=T">W</a>
	    <a href="mlib.php?terms=x&field=T">X</a>
	    <a href="mlib.php?terms=y&field=T">Y</a>
	    <a href="mlib.php?terms=z&field=T">Z</a>
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
