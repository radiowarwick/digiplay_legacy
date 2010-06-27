<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Please Login</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>
<form name="loginForm" method="post" action="{$CONFIG.general.siteRoot}">
<!--<form name="loginForm" method="post" action="{$smarty.server.PHP_SELF}">-->
{if $ERRORS.permission && $AUTH.user != $CONFIG.Auth.anonuser}
<p>
The following error occured while processing your request:
</p>
<ul>
  <li>
  {$ERRORS.permission}
  </li>
</ul>
If you need to access the logon page you may do so <a href="?templateid=5&fwdtid={$fieldData.templateID}">here</a>
{else}
  {if $DATA.fwdtid}
  <input type="hidden" name="templateID" value="{$DATA.fwdtid}" />
  {/if}
  
  {if $ERRORS.permission && $AUTH.user == $CONFIG.Auth.anonuser}
    You do not seem to have permission to access that page. Logging in may 
    resolve this problem:
  {/if}
  
  <input type="hidden" name="formName" value="loginForm" />
  <input type="hidden" name="moduleName" value="Auth" />
  <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
  <table width="300" border="0" align="center" cellpadding="5" cellspacing="0">
    <tr> 
      <td colspan="2"><div align="center">Login:</div></td>
    </tr>
    <tr> 
      <td>Username:</td>
      <td><input name="authUser" type="text" id="authUser" value="{$DATA.authUser}"></td>
    </tr>
    <tr> 
      <td>Password: {$ERRORS.authPassword}</td>
      <td><input name="authPassword" type="password" id="authPassword"></td>
    </tr>
    <tr>
      <td colspan="2"><div align="right">
          <input type="submit" name="Submit" value="Login">
        </div></td>
    </tr>
  </table>
{/if}
</form>
</body>
</html>
