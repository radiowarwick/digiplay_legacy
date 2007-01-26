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
//Connect to the database

//Grab the data of what the user wants to do from the path
$offset = $_GET['offset'];
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

echo "<h1>Digiplay Search</h1>";
$sql = "SELECT playlist.id, audio.title FROM playlist, audio WHERE playlist = 'A' AND audio.id = playlist.audio";
$PLA = pg_query($sql);
$sql = "SELECT playlist.id, audio.title FROM playlist, audio WHERE playlist = 'B' AND audio.id = playlist.audio";
$PLB = pg_query($sql);
?>
<b>The current playlist.</b>
<table width=100% border=1>
  <tr>
    <th width=50%>A</th><th width=50%>B</th>
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
<?
    } else {
?>
    <td></td>
<?
    }
    if($trackB) {
?>
    <td>
      <?=$trackB[1]?>
    </td>
<?
    } else {
?>
    <td></td>
<?
    }
?>
  </tr>
  <? } ?>
</table>
<hr>

	    <!-- Display selection links at all times -->
	    <a name='results'>
	    <a href="/dps/search.php?section=0">0</a>
	    <a href="/dps/search.php?section=1">1</a>
	    <a href="/dps/search.php?section=2">2</a>
	    <a href="/dps/search.php?section=3">3</a>
	    <a href="/dps/search.php?section=4">4</a>
	    <a href="/dps/search.php?section=5">5</a>
	    <a href="/dps/search.php?section=6">6</a>
	    <a href="/dps/search.php?section=7">7</a>
	    <a href="/dps/search.php?section=8">8</a>
	    <a href="/dps/search.php?section=9">9</a>
	    <a href="/dps/search.php?section=a">A</a>
	    <a href="/dps/search.php?section=b">B</a>
	    <a href="/dps/search.php?section=c">C</a>
	    <a href="/dps/search.php?section=d">D</a>
	    <a href="/dps/search.php?section=e">E</a>
	    <a href="/dps/search.php?section=f">F</a>
	    <a href="/dps/search.php?section=g">G</a>
	    <a href="/dps/search.php?section=h">H</a>
	    <a href="/dps/search.php?section=i">I</a>
	    <a href="/dps/search.php?section=j">J</a>
	    <a href="/dps/search.php?section=k">K</a>
	    <a href="/dps/search.php?section=l">L</a>
	    <a href="/dps/search.php?section=m">M</a>
	    <a href="/dps/search.php?section=n">N</a>
	    <a href="/dps/search.php?section=o">O</a>
	    <a href="/dps/search.php?section=p">P</a>
	    <a href="/dps/search.php?section=q">Q</a>
	    <a href="/dps/search.php?section=r">R</a>
	    <a href="/dps/search.php?section=s">S</a>
	    <a href="/dps/search.php?section=t">T</a>
	    <a href="/dps/search.php?section=u">U</a>
	    <a href="/dps/search.php?section=v">V</a>
	    <a href="/dps/search.php?section=w">W</a>
	    <a href="/dps/search.php?section=x">X</a>
	    <a href="/dps/search.php?section=y">Y</a>
	    <a href="/dps/search.php?section=z">Z</a>
	    <p>
		<!-- search form -->
		<FORM METHOD=POST ACTION='/dps/search.php?search=1#results'>
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
		        $pagestr .= "&nbsp;<A HREF='/dps/search.php?section=$section&offset=";
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
		<form method=POST action='/dps/search.php?change=1'>
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
				</tr>
			<?
			$total = 0;
			while($tracks = pg_fetch_array($query)) {
				$total++;
				?>
				<tr>
				  <td>
				    <? // echo $tracks['id']." - ".$tracks['artist'] 
				    echo $tracks['artist']
				    ?>
				  </td>
				  <td>
				    <?=$tracks['title']?>
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
	    <a href="/dps/search.php?section=0">0</a>
	    <a href="/dps/search.php?section=1">1</a>
	    <a href="/dps/search.php?section=2">2</a>
	    <a href="/dps/search.php?section=3">3</a>
	    <a href="/dps/search.php?section=4">4</a>
	    <a href="/dps/search.php?section=5">5</a>
	    <a href="/dps/search.php?section=6">6</a>
	    <a href="/dps/search.php?section=7">7</a>
	    <a href="/dps/search.php?section=8">8</a>
	    <a href="/dps/search.php?section=9">9</a>
	    <a href="/dps/search.php?section=a">A</a>
	    <a href="/dps/search.php?section=b">B</a>
	    <a href="/dps/search.php?section=c">C</a>
	    <a href="/dps/search.php?section=d">D</a>
	    <a href="/dps/search.php?section=e">E</a>
	    <a href="/dps/search.php?section=f">F</a>
	    <a href="/dps/search.php?section=g">G</a>
	    <a href="/dps/search.php?section=h">H</a>
	    <a href="/dps/search.php?section=i">I</a>
	    <a href="/dps/search.php?section=j">J</a>
	    <a href="/dps/search.php?section=k">K</a>
	    <a href="/dps/search.php?section=l">L</a>
	    <a href="/dps/search.php?section=m">M</a>
	    <a href="/dps/search.php?section=n">N</a>
	    <a href="/dps/search.php?section=o">O</a>
	    <a href="/dps/search.php?section=p">P</a>
	    <a href="/dps/search.php?section=q">Q</a>
	    <a href="/dps/search.php?section=r">R</a>
	    <a href="/dps/search.php?section=s">S</a>
	    <a href="/dps/search.php?section=t">T</a>
	    <a href="/dps/search.php?section=u">U</a>
	    <a href="/dps/search.php?section=v">V</a>
	    <a href="/dps/search.php?section=w">W</a>
	    <a href="/dps/search.php?section=x">X</a>
	    <a href="/dps/search.php?section=y">Y</a>
	    <a href="/dps/search.php?section=z">Z</a>
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
