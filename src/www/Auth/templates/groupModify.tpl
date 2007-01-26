<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Auth Administration</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />

<link href="tkfecommon/css/user.css" rel="stylesheet" type="text/css" />
<link href="tkfecommon/css/mktree.css" rel="stylesheet" type="text/css" />
<script language="JavaScript" type="text/JavaScript" src="tkfecommon/js/submitform.js"></script>
<script language="JavaScript" type="text/JavaScript" src="tkfecommon/js/mktree.js"></script>
</head>

<body onload="expandTree('realmTree')">
{include file="rfile:mainTableTop.tpl" title="Group Administration"}
  <form name="groupSelForm" method="post" action="{$CONFIG.general.siteRoot}">
  <input type="hidden" name="templateID" value="{$DATA.templateID}">
  <p align="center"><span class="label">Select Group:</span><br />
    <select name="groupToEdit" id="groupToEdit" size="1">
      {foreach from=$VIEWER.groups key="id" item="name"}
        {if $id == $DATA.groupToEdit}
          <option value="{$id}" selected>{$name}</option>
        {else}
          <option value="{$id}">{$name}</option>
        {/if}
      {/foreach}
    </select>
    <input type="submit" name="submit" value="Edit">
    <input type="hidden" name="formName" value="groupSelForm">
    <input type="hidden" name="moduleName" value="Auth">
  </form>
  </p>
  {if $DATA.groupToEdit}
  
  <hr />

  <table width="100%" border="0" cellspacing="0" cellpadding="5">
    {if $ERRORS}
    <tr valign="top">
      <td colspan="2">
        {include file="rfile:errorsList.tpl" errors=$ERRORS}
      </td>
    </tr>
    {/if}
    <tr valign="top">
      <td colspan="2">
      {if $VIEWER.customFields}
        <h2>Details:</h2>
        <form name="groupDetailsForm" method="post" action="{$CONFIG.general.siteRoot}">
        <input type="hidden" name="groupToEdit" value="{$DATA.groupToEdit}" />
        <input type="hidden" name="templateID" value="{$DATA.templateID}" />
        <input type="hidden" name="formName" value="groupDetailsForm" />
        <input type="hidden" name="moduleName" value="Auth">
        <table width="400px" border="0" cellspacing="0" cellpadding="5">
        {foreach from=$VIEWER.customFields item="fieldInfo"}
          <tr valign="top">
            <td>{$fieldInfo.niceName}: </td>
            <td>
              <input type="text" name="{$fieldInfo.fieldName}" value="{$fieldInfo.value}" />
            </td>
          </tr>
        {/foreach}
          <tr valign="top">
            <td colspan="2">
              <input type="submit" name="detailSubmit" value="Save Changes" />
            </td>
          </tr>
        </table>
        </form>
		<table width="400px" border="0" cellspacing="0" cellpadding="5">
		<tr><td>
		<form name="groupDeleteForm" method="post" action="{$CONFIG.general.siteRoot}">
		<input type="hidden" name="groupToEdit" value="{$DATA.groupToEdit}" />
		<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
		<input type="hidden" name="formName" value="groupDeleteForm" />
		<input type="hidden" name="moduleName" value="Auth">
		<input type="submit" name="deleteGroup" value="  Delete Group  " />
		</form>
		</tr></td>
		</table>
        <hr />
      {/if}
      </td>
    </tr>
    <tr valign="top"> 
      <td colspan="2">
      <form name="mainForm" method="post" action="{$CONFIG.general.siteRoot}">
      <table width="100%" border="0" cellspacing="0" cellpadding="5">
      <tr>
      <td width="50%" valign="top"><h3>Realms:</h3>
        <input type="hidden" name="groupToEdit" value="{$DATA.groupToEdit}" />
        <input type="hidden" name="templateID" value="{$DATA.templateID}" />
        <input type="hidden" name="task" value="" />
        <input type="hidden" name="rguid" value="" />
        <input type="hidden" name="formName" value="groupRealmForm" />
        <input type="hidden" name="moduleName" value="Auth">
        {include file="rfile:realmTreeMaker.tpl" realms=$VIEWER.realminfo type="perm"}
      </td>
      <td width="50%" valign="top"><h3>Users:</h3>
        {include file="rfile:userList.tpl" users=$VIEWER.userinfo}
      </td>
      </tr>
      </table>
      </form>
      </td>
    </tr>
  </table>
</form>
{include file="rfile:mainTableBot.tpl"}
{/if}
</body>
</html>
