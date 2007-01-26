<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Permission Error</title>
<link href="tkfecommon/css/user.css" rel="stylesheet" type="text/css" />
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>
{include file="rfile:mainTableTop.tpl" title="Administration"}
<h1>Authentication Error</h1>
{if $ERRORS.permission}
<p>
The following error occurred while authorising your request:
</p>
<ul>
  <li>
  {$ERRORS.permission}
  </li>
</ul>
<p>If you need to access the logon page you may do so 
<a href="?templateID={$VIEWER.loginTplID}&fwdtid={$DATA.templateID}">here</a></p>


{else}
An unspecified error has occured
{/if}
{include file="rfile:mainTableBot.tpl"}
</body>
</html>
