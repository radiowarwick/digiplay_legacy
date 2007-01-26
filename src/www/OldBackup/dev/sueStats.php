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
    <td valign=top>
<?
$sql = "select sum(length_smpl) from audio where sustainer ='t'";
$result = pg_query($dbconn1, $sql);
$samples = pg_fetch_row($result, 0);
$sql = "select sum(length_smpl) from audio";
$result = pg_query($dbconn1, $sql);
$Tsamples = pg_fetch_row($result, 0);
$sql = "select count(*) from audio where sustainer ='t'";
$result = pg_query($dbconn1, $sql);
$count = pg_fetch_row($result, 0);
$sql = "select count(*) from audio";
$result = pg_query($dbconn1,$sql);
$totaltracks = pg_fetch_row($result,0);
?>
<h1>Playout Statistics</h1>
<table width=75% border=1>
  <tr>
    <th align=left>
      Sue Version Number
    </th>
    <td>
      32C
    </td>
  </tr>
  <tr>
    <th align=left>
      Tracks currently on Sue Playlist
    </th>
    <td>
      <?=$count[0]?>
    </td>
  </tr>
  <tr>
    <th align=left>
      Time currently on Sue Playlist
    </th>
    <td>
	  <? echo round(((($samples[0]/44100)/60)/60) - ((($samples[0]/44100)/60)%60)/60) . "hrs " .
 ((($samples[0]/44100)/60)%60) . "mins.";?>
    </td>
  </tr>
  <tr>
    <th align=left>
      Total tracks currently on system.
    </th>
    <td>
      <? echo $totaltracks[0]; ?> tracks
    </td>
  </tr>
  <tr>
    <th align=left>
      Total time currently on system.
    </th>
    <td>
    <? 	$days = floor($Tsamples[0]/44100/60/60/24);
	$hours = floor($Tsamples[0]/44100/60/60 - $days*24);
	$mins = floor($Tsamples[0]/44100/60 - $hours*60 - $days*24*60);
	$secs = floor($Tsamples[0]/44100 - $mins*60 - $hours*60*60 - $days*24*60*60);
	$samples = ($Tsamples[0] - $secs*44100 - $mins*60*44100 - $hours*60*60*44100 - $days*24*60*60*44100);
    ?>
    <?=$days ?> Days <?=$hours ?> Hours <?=$mins ?> Minutes <?=$secs ?> Seconds <?=$samples ?> Samples
    </td>
  </tr>
</table>

<h2>Coming up on Sue</h2>
<table width=75% border=1>
  <tr>
    <th align=left>
      Track
    </th>
    <th>
      Artist
    </th>
  </tr>
<?
$sql = "SELECT audio.title AS title, artists.name AS artist FROM sustschedule, audio, audioartists, artists WHERE 
sustschedule.audio = audio.id AND audio.id = 
audioartists.audio AND 
audioartists.artist = artists.id order by sustschedule.id asc";
$tracks = pg_query($dbconn1, $sql);
while($value=pg_fetch_array($tracks)) {
?>
  <tr>
    <td align=left>
      <?=$value[0]?>
    </td>
    <td>
      <?=$value[1]?>
    </td>
  </tr>
<?
}
?>

</table>

<h2>RaW Network Status</h2>
<table width=75% border=1>
<tr>
<th>
Server
</th>
<th>
Status
</th>
</tr>
<tr>
   <td align=left>
    Digital Playout System Uptime
   </td>
  <td>
  <? echo str_replace(",","",exec("uptime | cut -c 13-28")) ?>
  </td>
</tr>
<tr>
   <td align=left>
     Primary Digital Playout Server Status
   </td>
  <td>
    <font color='green'>UP</font>
  </td>
</tr>
<tr>
   <td align=left>
     Studio 1 Playout System Status
   </td>
  <td>
  <? if(exec("ping -c 1 -W 1 playout1 | grep '1 packets' | cut -c 24-25") == "1") {
  ?>
      <font color='green'>UP</font>
  <?} else {?>
      <font color='red'>DOWN</font>
  <?}?>
  </td>
</tr>
<tr>
   <td align=left>
     Studio 1 Management System Status
   </td>
  <td>
  <? if(exec("ping -c 1 -W 1 onair1 | grep '1 packets' | cut -c 24-25") == "1") {
  ?>
      <font color='green'>UP</font>
  <?} else {?>
      <font color='red'>DOWN</font>
  <?}?>
  </td>
</tr>
<tr>
   <td align=left>
     Studio 2 Playout System Status
   </td>
  <td>
  <? if(exec("ping -c 1 -W 1 playout2 | grep '1 packets' | cut -c 24-25") == "1") {
  ?>
      <font color='green'>UP</font>
  <?} else {?>
      <font color='blue'>INTANGIBLE</font>
  <?}?>
  </td>
</tr>
<tr>
   <td align=left>
     Studio 2 Management System Status
   </td>
  <td>
  <? if(exec("ping -c 1 -W 1 onair2 | grep '1 packets' | cut -c 24-25") == "1") {
  ?>
      <font color='green'>UP</font>
  <?} else {?>
      <font color='blue'>INTANGIBLE</font>
  <?}?>
  </td>
</tr>
<tr>
   <td align=left>
     Primary Linux Shell Server 
   </td>
  <td>
  <? if(exec("ping -c 1 -W 1 george | grep '1 packets' | cut -c 24-25") == "1") {
  ?>
      <font color='green'>UP</font>
  <?} else {?>
      <font color='red'>DOWN</font>
  <?}?>
  </td>
</tr>
<tr>
   <td align=left>
     Primary File Server
   </td>
  <td>
  <? if(exec("ping -c 1 -W 1 fs0 | grep '1 packets' | cut -c 24-25") == "1") {
  ?>
      <font color='green'>UP</font>
  <?} else {?>
      <font color='red'>DOWN</font>
  <?}?>
  </td>
</tr>
<tr>
   <td align=left>
     Primary Digital Logging Server
   </td>
  <td>
  <? if(exec("ping -c 1 -W 1 digilog1 | grep '1 packets' | cut -c 24-25") == "1") {
  ?>
      <font color='green'>UP</font>
  <?} else {?>
      <font color='red'>DOWN</font>
  <?}?>
  </td>
</tr>
<tr>
   <td align=left>
     Redundent Digital Logging Server
   </td>
  <td>
  <? if(exec("ping -c 1 -W 1 digilog2 | grep '1 packets' | cut -c 24-25") == "1") {
  ?>
      <font color='green'>UP</font>
  <?} else {?>
      <font color='red'>DOWN</font>
  <?}?>
  </td>
</tr>
<tr>
   <td align=left>
     Video Server
   </td>
  <td>
  <? if(exec("ping -c 1 -W 1 digicam | grep '1 packets' | cut -c 24-25") == "1") {
  ?>
      <font color='green'>UP</font>
  <?} else {?>
      <font color='red'>DOWN</font>
  <?}?>
  </td>
</tr>
<tr>
   <td align=left>
     Station Access & Redundent Account Management Server
   </td>
  <td>
  <? if(exec("ping -c 1 -W 1 doorlock | grep '1 packets' | cut -c 24-25") == "1") {
  ?>
      <font color='green'>UP</font>
  <?} else {?>
      <font color='red'>DOWN</font>
  <?}?>
  </td>
</tr>
<tr>
   <td align=left>
     Record Library Search Terminal
   </td>
  <td>
  <? if(exec("ping -c 1 -W 1 reclib | grep '1 packets' | cut -c 24-25") == "1") {
  ?>
      <font color='green'>UP</font>
  <?} else {?>
      <font color='red'>DOWN</font>
  <?}?>
  </td>
</tr>
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
