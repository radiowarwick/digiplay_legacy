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

  <table width="100%" border="0" cellspacing="0" cellpadding="5">
    {if $ERRORS}
    <tr valign="top">
      <td colspan="2">
        {include file="rfile:errorsList.tpl" errors=$ERRORS}
      </td>
    </tr>
    {/if}
    <tr valign="top">
      {if $DATA.newGroupID}
        The group has been added. Click
        {templateLink name="groupModify.tpl" text="here" _groupToEdit=$DATA.newGroupID}
        if you wish to modify their permissions
      {else}
      <td colspan="2">
        <h2>New Group Details:</h2>
        <form name="addGroupForm" method="post" action="{$CONFIG.general.siteRoot}">
        <input type="hidden" name="templateID" value="{$DATA.templateID}" />
        <input type="hidden" name="formName" value="addGroupForm" />
        <input type="hidden" name="moduleName" value="Auth" />
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
            <td colspan="2" align="right">
              <input type="submit" name="detailSubmit" value="Add Group" align="right" />
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
