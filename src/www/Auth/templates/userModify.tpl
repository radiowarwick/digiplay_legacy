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
{include file="rfile:mainTableTop.tpl" title="User Administration"}
  <form name="userSelForm" method="post" action="{$CONFIG.general.siteRoot}">
  <input type="hidden" name="templateID" value="{$VIEWER.templateID}">
  <p align="center">
  <div align="center">
  <span class="label">Select User:</span><br />
    <select name="userToEdit" id="userToEdit" size="1">
      {foreach from=$VIEWER.users key="id" item="name"}
        {if $id == $DATA.userToEdit}
          <option value="{$id}" selected>{$name}</option>
        {else}
          <option value="{$id}">{$name}</option>
        {/if}
      {/foreach}
    </select>
    <input type="submit" name="submit" value="Edit">
    <input type="hidden" name="formName" value="userSelForm"><br />
    <input type="hidden" name="moduleName" value="Auth" />
  </form>
  </div>
  </p>
  {if $DATA.userToEdit}
  
  <hr />

  <table width="100%">
    {if $ERRORS}
    <tr valign="top">
      <td colspan="2">
        {include file="rfile:errorsList.tpl" errors=$ERRORS}
      </td>
    </tr>
    {/if}
    <tr valign="top">
      <td colspan="2">
        <h2>Details:</h2>
        <form name="modifyUserDetailsForm" method="post" action="{$CONFIG.general.siteRoot}">
        <input type="hidden" name="userToEdit" value="{$DATA.userToEdit}" />
        <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
        <input type="hidden" name="formName" value="modifyUserDetailsForm" />
        <input type="hidden" name="moduleName" value="Auth">
        <table width="400px" border="0" cellspacing="0" cellpadding="5">
        {if $VIEWER.customFields}
        {foreach from=$VIEWER.customFields item="fieldInfo"}
          <tr valign="top">
            <td>{$fieldInfo.niceName}: </td>
            <td>
              <input type="text" name="{$fieldInfo.fieldName}" value="{$fieldInfo.value}" />
            </td>
          </tr>
        {/foreach}
        {/if}
          <tr valign="top"> 
            <td>Password: </td>
            <td>
              <input type="checkbox" name="changePassword" />Change password<br />
              <input type="text" name="password" />
            </td>
          </tr>
          <tr valign="top">
            <td colspan="2">
              <input type="submit" name="detailSubmit" value="Save Changes" />
            </td>
          </tr>
        </table>
        </form>
        <table width="400px" border="0" cellspacing="0" cellpadding="5">
        <tr><td>
        <form name="userDeleteForm" method="post" action="{$CONFIG.general.siteRoot}">
        <input type="hidden" name="userToEdit" value="{$DATA.userToEdit}" />
        <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
        <input type="hidden" name="formName" value="userDeleteForm" />
        <input type="submit" name="deleteUser" value="   Delete User   " />
        <input type="hidden" name="moduleName" value="Auth" />
        </form>
        </tr></td>
        </table>
        <hr />
      </td>
    </tr>
    <tr valign="top"> 
      <td colspan="2">
      <form name="mainForm" method="post" action="{$CONFIG.general.siteRoot}">
      <table width="100%" border="0" cellspacing="0" cellpadding="5">
      <tr>
      <td width="50%" valign="top"><h3>Realms:</h3>
        <input type="hidden" name="userToEdit" value="{$DATA.userToEdit}" />
        <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
        <input type="hidden" name="task" value="" />
        <input type="hidden" name="rguid" value="" />
        <input type="hidden" name="formName" value="userPermissionForm" />
        <input type="hidden" name="moduleName" value="Auth" />
        {include file="rfile:realmTreeMaker.tpl" realms=$VIEWER.realminfo type="perm"}
      </td>
      <td width="50%" valign="top"><h3>Groups:</h3>
        {include file="rfile:groupList.tpl" groups=$VIEWER.groupinfo}
      </td>
      </tr>
      </table>
      </form>
      </td>
    </tr>
  </table>
</form>
{/if}
{include file="rfile:mainTableBot.tpl"}
</body>
</html>
