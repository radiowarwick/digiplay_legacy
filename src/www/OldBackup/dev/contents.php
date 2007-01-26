
<table width=168px border=0 cellpadding=6 cellspacing=0>
  <tr height=16px>
    <td 
background="images/top.png">
    </td>
  </tr>
  <tr height=33px>
    <td class=sidebarH background="images/item.png">
    <b>Contents</b></br>
    </td>
  </tr>
  <tr height=33px>
    <td class=sidebar background="images/item.png">
      <a href='index.php'>Home</a><br>
    </td>
  </tr>
  <tr height=33px>
    <td class=sidebar background="images/item.png">
      <a href='mlib.php'>Music Library</a><br>
    </td>
  </tr>
  <?
      $sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username'AND users.id=useraccess.userid AND users.enabled = 't'
              AND (useraccess.privilage=3 or useraccess.privilage=8  or useraccess.privilage=5)";
      $result = pg_query($dbconn1, $sql);
      $count = pg_fetch_row($result, 0);
      //Have to at least have permission to manage users to view page
      if ($count[0] != 0) {
        ?>
      <tr height=23px>
        <td class=ssidebar background="images/item.png">
          <a href='playList.php'>Edit Playlist</a><br>
        </td>
      </tr>
        <?
      }

      $sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username'AND users.id=useraccess.userid AND  users.enabled = 't'
              AND (useraccess.privilage=3 OR useraccess.privilage=5 OR useraccess.privilage=6 OR useraccess.privilage=8)";
      $result = pg_query($dbconn1, $sql);
      $count = pg_fetch_row($result, 0);
      //Have to at least have permission to manage users to view page
      if ($count[0] != 0) {
        ?>
      <tr height=23px>
        <td class=ssidebar background="images/item.png">
          <a href='fAbuseTrack.php'>Report Track</a><br>
        </td>
      </tr>
        <?
      }

      $sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username'AND users.id=useraccess.userid
 AND  users.enabled = 't'
              AND (useraccess.privilage=3 OR useraccess.privilage=6 OR useraccess.privilage=8)";
      $result = pg_query($dbconn1, $sql);
      $count = pg_fetch_row($result, 0);
      //Have to at least have permission to manage users to view page
      if ($count[0] != 0) {
        ?>
      <tr height=23px>
        <td class=ssidebar background="images/item.png">
          <a href='sAbuseTrack.php'>Censor Tracks</a><br>
        </td>
      </tr>
        <?
      }

?>
      <tr height=33px>
        <td class=sidebar background="images/item.png">
          Sue<br>
        </td>
      </tr>
      <tr height=23px>
        <td class=ssidebar background="images/item.png">
          <a href='sueStats.php'>Statistics</a><br>
        </td>
      </tr>
<?
      $sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username'AND users.id=useraccess.userid AND users.enabled = 't'
              AND (useraccess.privilage=8 OR useraccess.privilage=3)";
      $result = pg_query($dbconn1, $sql);
      $count = pg_fetch_row($result, 0);
      //Have to at least have permission to manage users to view page
      if ($count[0] != 0) {
        ?>
      <tr height=33px>
        <td class=sidebar background="images/item.png">
          Administration<br>
        </td>
      </tr>
      <tr height=23px>
        <td class=ssidebar background="images/item.png">
          <a href='/dps/userManager.php'>User Management</a><br>
        </td>
      </tr>
        <?
      }

      $sql = "SELECT count(*) FROM users, useraccess WHERE users.username='$username'AND users.id=useraccess.userid AND
		 users.enabled = 't'
              AND (useraccess.privilage=3)";
      $result = pg_query($dbconn1, $sql);
      $count = pg_fetch_row($result, 0);
      //Have to at least have permission to manage users to view page
      if ($count[0] != 0) {
        ?>
      <tr height=23px>
        <td class=ssidebar background="images/sitem.png">
          <a href='/dps/todo.php'>To Do List</a><br>
        </td>
      </tr>
      <tr height=23px>
        <td class=ssidebar background="images/sitem.png">
          <a href='/dps/stationCartset.php'>Station Cartwall (dev)</a><br>
        </td>
      </tr>
      <tr height=23px>
        <td class=ssidebar background="images/sitem.png">
          <a href='/dps/dirtest.php'>Dir Test Rig</a><br>
        </td>
      </tr>
        <?
      }

      ?>
  <tr height=33px>
    <td class=sidebar background="images/item.png">
      <a href='/dps/dps.php?action=logout'>Logout</a><br>
    </td>
  </tr>
  <tr height=296px>
    <td background="images/sue.png">

    </td>
  </tr>
</table>
