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
<h1>Welcome to the Digital Playout Management Website</h1><hr>
<p>This site manages RaW's digital playout system. If this is your first 
time visiting this site, it is unlikely that you will have any 
permissions set. If you believe that you require access to certain 
functionality please contact your head of department (Contact 
information available at <a 
href='/departments'>www.radio.warwick.ac.uk/departments</a>).<br><br>Please 
be aware that the facilities available through this site should not be 
abused as they directly afect the station's output. Any users found to 
be abusing their access will have their access revoked and face 
disciplinary action.<br><br>
If you have any problems, or queries, regarding the operation of this webpage please contact the <a href='mailto:webmaster@radio.warwick.ac.uk'>webmaster</a>.</p>
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
