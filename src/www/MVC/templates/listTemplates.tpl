<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Permission Error</title>
<link href="tkfecommon/css/user.css" rel="stylesheet" type="text/css" />
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>
{include file="rfile:mainTableTop.tpl" title="Administration"}
<table>
{foreach from=$VIEWER.templateList item=template}
  <tr>
  {foreach from=$template item=field}
    <td>{$field}</td>
  {/foreach}
  </tr>
{/foreach}
</table>
{include file="rfile:mainTableBot.tpl"}
</body>
</html>