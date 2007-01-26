<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Auth Administration</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />

<link href="tkfecommonr.css/user.css" rel="stylesheet" type="text/css" />
<link href="tkfecommon/css/mktree.css" rel="stylesheet" type="text/css" />
<script language="JavaScript" type="text/JavaScript" src="tkfecommon/js/submitform.js"></script>
<script language="JavaScript" type="text/JavaScript" src="tkfecommon/js/mktree.js"></script>
</head>

<body onload="expandTree('realmTree')">
{include file="rfile:mainTableTop.tpl" title="User Administration"}
  
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
      {if $DATA.newUserID}
        The user has been added. Click
        {templateLink name="userModify.tpl" text="here" _userToEdit=$DATA.newUserID}
        if you wish to modify their permissions
      {else}
        <h2>New User Details:</h2>
        <form name="addUserDetailsForm" method="post" action="{$CONFIG.general.siteRoot}">
        <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
        <input type="hidden" name="formName" value="addUserDetailsForm" />
        <input type="hidden" name="moduleName" value="Auth" />
        <table width="400px" border="0" cellspacing="0" cellpadding="5">
        {if $VIEWER.customFields}
        {foreach from=$VIEWER.customFields item="fieldInfo"}
          <tr valign="top">
            <td>{$fieldInfo.niceName}: </td>
            <td>
              {if $VIEWER.formName == "detailsForm"}
              {assign var="name" value=$fieldInfo.fieldName}
              <input type="text" name="{$fieldInfo.fieldName}" value="{$DATA.$name}" />
              {else}
              <input type="text" name="{$fieldInfo.fieldName}" value="{$fieldInfo.value}" />
              {/if}
            </td>
          </tr>
        {/foreach}
        {/if}
          <tr valign="top"> 
            <td>Password: </td>
            <td>
              <input type="text" name="password" />
            </td>
          </tr>
          <tr valign="top">
            <td colspan="2" align="right">
              <input type="submit" name="detailSubmit" value="Add User" align="right" />
            </td>
          </tr>
        </table>
        </form>
      {/if}
        <hr />
      </td>
    </tr>
  </table>
{include file="rfile:mainTableBot.tpl"}
</body>
</html>
