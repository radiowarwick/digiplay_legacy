<?
include('session.php');
$sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username' AND users.id = useraccess.userid AND users.enabled = 't' AND (useraccess.privilage=3 OR useraccess.privilage=5)";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
if ($count[0] == 0) {
  $output="false";
  $errorMSG = 'This page is currently under testing, please login as an admin, or click <a 
href="/dps/sue.php">here</a> to return to the home page.';
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
//Grab the data of what the user wants to do from the path
$offset = $_GET['offset'];
$change = $_GET['change'];
if (!isset($offset)) {
  $offset = 0;
}
if (isset($_GET['search'])) {
  $search = true;
  $field = pg_escape_string($_POST['field']);
  $terms = $_POST['terms'];
} else {
  $section = $_GET['section'];
}
?>
<h1>Report an Unsuitable Track</h1><hr>
<p>Please use the search facilities bellow to locate any tracks that you are aware of that contain profanity,or are about a subject matter that is not radio safe.<Br>More guidelines to follow shortly<p>
<hr>
	    <!-- Display selection links at all times -->
	    <a href="/dps/fAbuseTrack.php?section=0">0</a>
	    <a href="/dps/fAbuseTrack.php?section=1">1</a>
	    <a href="/dps/fAbuseTrack.php?section=2">2</a>

	    <a href="/dps/fAbuseTrack.php?section=3">3</a>
	    <a href="/dps/fAbuseTrack.php?section=4">4</a>
	    <a href="/dps/fAbuseTrack.php?section=5">5</a>
	    <a href="/dps/fAbuseTrack.php?section=6">6</a>
	    <a href="/dps/fAbuseTrack.php?section=7">7</a>
	    <a href="/dps/fAbuseTrack.php?section=8">8</a>

	    <a href="/dps/fAbuseTrack.php?section=9">9</a>
	    <a href="/dps/fAbuseTrack.php?section=a">A</a>
	    <a href="/dps/fAbuseTrack.php?section=b">B</a>
	    <a href="/dps/fAbuseTrack.php?section=c">C</a>
	    <a href="/dps/fAbuseTrack.php?section=d">D</a>
	    <a href="/dps/fAbuseTrack.php?section=e">E</a>

	    <a href="/dps/fAbuseTrack.php?section=f">F</a>
	    <a href="/dps/fAbuseTrack.php?section=g">G</a>
	    <a href="/dps/fAbuseTrack.php?section=h">H</a>
	    <a href="/dps/fAbuseTrack.php?section=i">I</a>
	    <a href="/dps/fAbuseTrack.php?section=j">J</a>
	    <a href="/dps/fAbuseTrack.php?section=k">K</a>

	    <a href="/dps/fAbuseTrack.php?section=l">L</a>
	    <a href="/dps/fAbuseTrack.php?section=m">M</a>
	    <a href="/dps/fAbuseTrack.php?section=n">N</a>
	    <a href="/dps/fAbuseTrack.php?section=o">O</a>
	    <a href="/dps/fAbuseTrack.php?section=p">P</a>
	    <a href="/dps/fAbuseTrack.php?section=q">Q</a>

	    <a href="/dps/fAbuseTrack.php?section=r">R</a>
	    <a href="/dps/fAbuseTrack.php?section=s">S</a>
	    <a href="/dps/fAbuseTrack.php?section=t">T</a>
	    <a href="/dps/fAbuseTrack.php?section=u">U</a>
	    <a href="/dps/fAbuseTrack.php?section=v">V</a>
	    <a href="/dps/fAbuseTrack.php?section=w">W</a>

	    <a href="/dps/fAbuseTrack.php?section=x">X</a>
	    <a href="/dps/fAbuseTrack.php?section=y">Y</a>
	    <a href="/dps/fAbuseTrack.php?section=z">Z</a>
	    <p>
		<!-- search form -->
		<FORM METHOD=POST ACTION='/dps/fAbuseTrack.php?search=1'>
		  Find songs where the 
		  <SELECT NAME='field'>

		  <OPTION VALUE='artists.name'>Artist</OPTION>
		  <OPTION VALUE='audio.title'>Track</OPTION>
		  </SELECT>
		  contains
		  <INPUT TYPE='text' NAME='terms'>
		  <INPUT TYPE='submit' VALUE='Search'>
		  		</FORM>
	    </p>
<?
//Check which section they're looking at
if(isset($change)) { //if they are changing something
        //Add or Remove the tracks as appropriate
        $max = pg_escape_string($_POST['max']);
        for ($i=1; $i<=$max; $i++) {
          if ((!isset($_POST['song'.$i]) && $_POST['original'.$i] == 'on')
               || ($_POST['song'.$i] == 'on' && $_POST['original'.$i] == 'off')) { //something has changed

            if($_POST['song'.$i] == 'on') {
              $sql = "UPDATE audio SET flagged = 't' WHERE id = " . pg_escape_string($_POST['id'.$i]);
              $update = pg_query($dbconn1,$sql);
            } else {
              $sql = "UPDATE audio SET flagged = 'f' WHERE id = " . pg_escape_string($_POST['id'.$i]);
              $update = pg_query($dbconn1,$sql);
            }
            $track = pg_escape_string($_POST['id'.$i]);
            $query = "SELECT title, flagged FROM audio WHERE audio.id = '$track'";
            $result = pg_query($dbconn1, $query);
            $count = pg_fetch_row($result, 0);
            if ($count[1] == 'f') {
              echo "<font color='red'>Track '" . $count[0] . "' un-reported</font><br />";
            } else {
              echo "<font color='red'>Track '" . $count[0] ."' reported</font><br />";
            } //end $count etc etc
          } //end something has changed
        } //end loop
echo "<b>Playlist Successfully Updated</b><br><p>";
}
        if (!isset($track) && (isset($search) || isset($section))) {
                //Start seaching anc paging
                $section = htmlspecialchars($section);
                $section = pg_escape_string($section);
                $terms = pg_escape_string($terms);
                if ($search) {
                  //SQL Query to get no. of search results
                  $count_query = pg_query("SELECT COUNT(audio.id) FROM artists,audio,audioartists WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND $field ILIKE '%$terms%'");
                  //SQL Query to get search results
                  $query = pg_query("SELECT DISTINCT artists.name AS artist,audio.title AS title,audio.id AS id, audio.flagged, audio.censor WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND $field ILIKE '%$terms%' ORDER BY $field LIMIT 200 OFFSET ".$offset*200);
                } else {
                  //SQL Query to get no. of tracks for this section
                  $count_query = pg_query("SELECT COUNT(audio.id) FROM artists,audio,audioartists WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND artists.name ILIKE '$section%'");
                  //SQL Query to get search results
                  $query = pg_query("SELECT DISTINCT artists.name AS artist,audio.title AS title,audio.id AS id, audio.flagged, audio.censor WHERE artists.id = audioartists.artist AND audio.id = audioartists.audio AND artists.name ILIKE '$section%' ORDER BY artists.name ASC LIMIT 200 OFFSET ".$offset*200);
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
                        $pagestr .= "&nbsp;<A HREF='/dps/fAbuseTrack.php?section=$section&offset=";
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
                <form method=POST action='/dps/fAbuseTrack.php?change=1'>
                <table cellspacing="0" cellpadding="2" border="2" align="center">
                                <tr>
                                  <th>
                                    Reported
                                  </th>
                                  <th>
                                    Artist
                                  </th>
                                  <th>
                                    Title
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
                                    if ($tracks[3] == 't') {
                                            echo "<input type='checkbox' name='song$total' checked>
                                                  <input type=hidden name='id$total' value='$tracks[id]'>
                                                  <input type=hidden name='original$total' value='on'> ";
                                    } else if ($tracks[4] == 't') {
                                            echo "Censored";
				    } else {
                                            echo "<input type='checkbox' name='song$total'>
                                                  <input type=hidden name='id$total' value='$tracks[id]'>
                                                  <input type=hidden name='original$total' value='off'>";
                                    }
                                    ?>
                                  </td>
                                  <td>
                                    <?// echo $tracks['id']." - ".$tracks['artist']
                                    echo $tracks['artist'];
                                    ?>
                                  </td>
                                  <td>
                                    <?=$tracks['title']?>
                                  </td>
                                </tr>
                                <?
                        }
                        if($total == 0) {
                          echo("<tr><td colspan=3><b>Sorry, no results were found.</b></td></tr>");
                        }
                        ?>
                       <tr>
                        <td style='text-align:center;'>
                         <input type=hidden name='max' value='<?=$total?>'>
                         <input type=submit value='Submit'>
                        </td>
                        <td colspan=2>
                         &laquo;&laquo; Click to submit your changes to the playlist before changing pages. &laquo;&laquo;
                        </td>
                       </tr>
                       <tr>
                        <td style='text-align:center'>
                         <input type=reset value='Reset'>
                        </td>
                        <td colspan=2>
                         &laquo;&laquo; Click to reset all the boxes to their original state. &laquo;&laquo;
                        </td>
                       </tr>
                      <? //} ?>
                      </table>
                     </form>
                      <br />
        <?
          echo $pagestr;
        // close no track set section
        }
?>
	    <!-- Display selection links at all times -->
	    <a href="/dps/fAbuseTrack.php?section=0">0</a>
	    <a href="/dps/fAbuseTrack.php?section=1">1</a>
	    <a href="/dps/fAbuseTrack.php?section=2">2</a>
	    <a href="/dps/fAbuseTrack.php?section=3">3</a>
	    <a href="/dps/fAbuseTrack.php?section=4">4</a>

	    <a href="/dps/fAbuseTrack.php?section=5">5</a>
	    <a href="/dps/fAbuseTrack.php?section=6">6</a>
	    <a href="/dps/fAbuseTrack.php?section=7">7</a>
	    <a href="/dps/fAbuseTrack.php?section=8">8</a>
	    <a href="/dps/fAbuseTrack.php?section=9">9</a>
	    <a href="/dps/fAbuseTrack.php?section=a">A</a>

	    <a href="/dps/fAbuseTrack.php?section=b">B</a>
	    <a href="/dps/fAbuseTrack.php?section=c">C</a>
	    <a href="/dps/fAbuseTrack.php?section=d">D</a>
	    <a href="/dps/fAbuseTrack.php?section=e">E</a>
	    <a href="/dps/fAbuseTrack.php?section=f">F</a>
	    <a href="/dps/fAbuseTrack.php?section=g">G</a>

	    <a href="/dps/fAbuseTrack.php?section=h">H</a>
	    <a href="/dps/fAbuseTrack.php?section=i">I</a>
	    <a href="/dps/fAbuseTrack.php?section=j">J</a>
	    <a href="/dps/fAbuseTrack.php?section=k">K</a>
	    <a href="/dps/fAbuseTrack.php?section=l">L</a>
	    <a href="/dps/fAbuseTrack.php?section=m">M</a>

	    <a href="/dps/fAbuseTrack.php?section=n">N</a>
	    <a href="/dps/fAbuseTrack.php?section=o">O</a>
	    <a href="/dps/fAbuseTrack.php?section=p">P</a>
	    <a href="/dps/fAbuseTrack.php?section=q">Q</a>
	    <a href="/dps/fAbuseTrack.php?section=r">R</a>
	    <a href="/dps/fAbuseTrack.php?section=s">S</a>

	    <a href="/dps/fAbuseTrack.php?section=t">T</a>
	    <a href="/dps/fAbuseTrack.php?section=u">U</a>
	    <a href="/dps/fAbuseTrack.php?section=v">V</a>
	    <a href="/dps/fAbuseTrack.php?section=w">W</a>
	    <a href="/dps/fAbuseTrack.php?section=x">X</a>
	    <a href="/dps/fAbuseTrack.php?section=y">Y</a>

	    <a href="/dps/fAbuseTrack.php?section=z">Z</a>
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
