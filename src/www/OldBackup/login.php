<?
include('header.php');
?>
<Br><Br>
<center>
<form method='post' action='https://www.radio.warwick.ac.uk/dps/dps.php'>
<table width=450px height=300px border=0 background='logon.png' class=login>
<tr><td colspan=2>&nbsp</td></tr>
<tr><td colspan=2>&nbsp</td></tr>
<tr>
    <td align=right class=login><b>Username:</b></td><td class=login><input type=text name=username></td>
</tr>
<tr>
    <td align=right class=login><b>Password:</b></td><td class=login><input type=password name=password></td>
</tr>
<tr><td colspan=2 align=center class=login><input type=submit value="    Login    " ></td></tr>
<!--<tr><td colspan=2>Down for temperary Service</td></tr>-->
<tr><td colspan=2 align=center>&nbsp<font color='white'><b><?=$errorMSG ?></b></font></td></tr>
<tr><td colspan=2>&nbsp</td></tr>
<tr><td colspan=2>&nbsp</td></tr>
<tr><td colspan=2>&nbsp</td></tr>
</table>
</form>
</center>
<?
include('footer.php');
?>

