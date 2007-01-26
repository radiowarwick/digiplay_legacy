<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Editing CMS Region</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>

{include file="rfile:mainTableTop.tpl" title="CMS Administration"}

{if $ERRORS.permission}
<p>
The following error occured while processing your request:
</p>
<ul>
  <li>
  {$ERRORS.permission}
  </li>
</ul>
{/if}

<form name="selectRegionForm" method="post" action="{$CONFIG.general.siteRoot}" />
<input type="hidden" name="formName" value="selectRegionForm" />
<input type="hidden" name="moduleName" value="CMS" />
<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
<select name="regionID">
{foreach from=$VIEWER.regions key="id" item="name"}
  <option value="{$id}">{$name}</option>
{/foreach}
</select>
<input type="submit" name="submit" value="Edit" />
</form>

{if $DATA.regionID}

<hr />

<form name="regionModifyForm" method="post" action="{$CONFIG.general.siteRoot}" />
<h2>Details</h2>
<table>
 <tr>
  <td>
   Region ID
  </td>
  <td>
   {$DATA.regionID}
  </td>
 </tr>
 <tr>
  <td>
   Name
  </td>
  <td>
   <input type="text" name="name" value="{$VIEWER.name}" />
  </td>
 </tr>
 <tr>
  <td>
   Realm required for viewing
  </td>
  <td>
   <select name="viewRealm">
    {foreach from=$VIEWER.realms item="realm" key="id"}
     {if $id == $VIEWER.viewRealm}
      <option value="{$id}" selected>{$realm}</option>
     {else}
      <option value="{$id}">{$realm}</option>
     {/if}
    {/foreach}
   </select>
  </td>
 </tr>
 <tr>
  <td>
   Realm required for editing
  </td>
  <td>
   <select name="editRealm">
    {foreach from=$VIEWER.realms item="realm" key="id"}
     {if $id == $VIEWER.editRealm}
      <option value="{$id}" selected>{$realm}</option>
     {else}
      <option value="{$id}">{$realm}</option>
     {/if}
    {/foreach}
   </select>
  </td>
 </tr>
 <tr>
  <td>
   Toolbar to be used for inline editing
  </td>
  <td>
   <select name="inlineToolbar">
    {foreach from=$CONFIG.CMS.availableToolbars item="tbName"}
     {if $tbName == $VIEWER.inlineToolbar}
      <option value="{$tbName}" selected>{$tbName}</option>
     {else}
      <option value="{$tbName}">{$tbName}</option>
     {/if}
    {/foreach}
   </select>
  </td>
 </tr>
 <tr>
  <td>
   Toolbar to be used for windowed editing
  </td>
  <td>
   <select name="windowToolbar">
    {foreach from=$CONFIG.CMS.availableToolbars item="tbName"}
     {if $tbName == $VIEWER.windowToolbar}
      <option value="{$tbName}" selected>{$tbName}</option>
     {else}
      <option value="{$tbName}">{$tbName}</option>
     {/if}
    {/foreach}
   </select>
  </td>
 </tr>
</table>

<hr />

<h2>Content<h2>

<input type="hidden" name="formName" value="regionModifyForm" />
<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
<input type="hidden" name="moduleName" value="CMS" />
<input type="hidden" name="regionID" value="{$DATA.regionID}" />
{$VIEWER.editorCode}
<input type="submit" name="submit" value="Save" />
</form>

{/if}
{include file="rfile:mainTableBot.tpl"}
</body>
</html>
