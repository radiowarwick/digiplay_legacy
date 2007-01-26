<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Permission Error</title>
<link href="tkfecommon/css/user.css" rel="stylesheet" type="text/css" />
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>
{include file="rfile:mainTableTop.tpl" title="Administration"}

{if $ERRORS}
 {include file="rfile:errorsList.tpl"}
{/if}
<form method="POST" action="{$smarty.server.PHP_SELF}">
<table>
<tr>
<td>
File Name:
</td>
<td>
<select name="fileName">
{foreach from=$VIEWER.unusedTemplates item=filename}
  <option value="{$filename}">{$filename}</option>
{/foreach}
</select>
</td>
</tr>
<tr>
<td>
Model Class Name:
</td>
<td>
<select name="modelName">
{foreach from=$VIEWER.models item=name}
  <option value="{$name}">{$name}</option>
{/foreach}
</select>
</td>
</tr>
<tr>
<td>
Viewer Class Name:
</td>
<td>
<select name="viewerName">
{foreach from=$VIEWER.viewers item=name}
  <option value="{$name}">{$name}</option>
{/foreach}
</select>
</td>
</tr>
</table>
<input type="hidden" name="templateID" value="{getTemplateID name='addTemplate.tpl'}">
<input type="hidden" name="process" value="1">
<input type="hidden" name="formName" value="addTemplateForm">
<input type="submit" name="submit" value="Add">
</ >

{include file="rfile:mainTableBot.tpl"}
</body>
</html>