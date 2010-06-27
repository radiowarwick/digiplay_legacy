<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Auth Administration</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />

<link href="tkfecommon/css/user.css" rel="stylesheet" type="text/css" />
<script language="JavaScript" type="text/JavaScript" src="tkfecommon/js/submitform.js"></script>
</head>

<body>
{include file="rfile:mainTableTop.tpl" title="Realm Administration"}
  <table width="100%" border="0" cellspacing="0" cellpadding="5">
    {if $ERRORS}
    <tr valign="top">
      <td colspan="2">
        {include file="rfile:errorsList.tpl" errors=$ERRORS}
      </td>
    </tr>
    {/if}
    <tr valign="top">
      <td width="35%">
        <span class="label">Select Realm:</span><br />
        <form name="mainForm" method="post" action="{$CONFIG.general.siteRoot}">
        <input type="hidden" name="parentID" value="" />
        <input type="hidden" name="templateID" value="{$DATA.templateID}" />
        <input type="hidden" name="formName" value="addRealmSelForm" />
        <input type="hidden" name="moduleName" value="Auth" />
        <p>Root {include file="rfile:realmTreeButtons.tpl" realmid="0" type="setRealmParentID"}
        {include file="rfile:realmTreeMaker.tpl" realms=$VIEWER.realminfo type="setRealmParentID"}
        </form>
      </td>
      <td width="65%">
      {if $DATA.parentID != '' && $VIEWER.customFields}
        <span class="label">Details:</span>
        <form name="addRealmDetailsForm" method="post" action="{$CONFIG.general.siteRoot}">
        <input type="hidden" name="parentID" value="{$DATA.parentID}" />
        <input type="hidden" name="templateID" value="{$DATA.templateID}" />
        <input type="hidden" name="formName" value="addRealmDetailsForm" />
        <input type="hidden" name="moduleName" value="Auth" />
        <table width="400px" border="0" cellspacing="0" cellpadding="5">
        {foreach from=$VIEWER.customFields item="fieldInfo"}
          <tr valign="top">
            <td>{$fieldInfo.niceName}: </td>
            <td>
              <input type="text" name="{$fieldInfo.fieldName}"/>
            </td>
          </tr>
        {/foreach}
          <tr valign="top">
            <td colspan="2" align="right">
              <input type="submit" name="detailSubmit" value="Add Realm" align="right" />
            </td>
          </tr>
        </table>
        </form>
      {/if}
      </td>
    </tr>
  </table>
</form>
{include file="rfile:mainTableBot.tpl"}
</body>
</html>
