{include file="rfile:dpsstudiotopframe.tpl" title="Digiplay Manager" studio="t" access_playlist=$VIEWER.access_playlist}

<div class='bigTitle'>Move Jingle into Package</div>
<form name="dpsStationMoveJingleForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="formName" value="dpsStationMoveJingleForm" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
	<input type="hidden" name="jingleID" value="{$VIEWER.jingleID}" />
	<input type="hidden" name="audioID" value="{$VIEWER.jingleID}" />
	<p>Jingle Name: {$VIEWER.jinglename}</p>
	<p>Current Package: {$VIEWER.currentpkg}</p>
	<p>Move to Existing Package: <select name="jinglepkgID"><option value="{$VIEWER.currentpkgid}"></option>
		{foreach from=$VIEWER.jinglepkgs item=jinglepkg}
			{if $jinglepkg.name != ''}			
				<option value="{$jinglepkg.id}">{$jinglepkg.name}</option>
			{else}
				<option value="{$jinglepkg.id}">Default Package</option>
			{/if}
		{/foreach}
		</select></p>
	<p>Move to New Package:<br />Name: <input type="text" name="newPackageName" /><br />Description: <input type="text" name="newPackageDesc" /></p>
<input type=submit name='submit' value='Submit Change'>
</form>

{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
