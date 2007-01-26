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
<h1>ToDo List</h1>
<hr>
<pre>
<?
include('todo.txt');
?>
</pre>
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
