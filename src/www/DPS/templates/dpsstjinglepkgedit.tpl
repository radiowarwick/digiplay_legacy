{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager" studio="t" access_playlist=$VIEWER.access_playlist}

<div class='bigTitle'>Station Jingle Package</div>
<form name="dpsStationUpdateJinglePkgForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="formName" value="dpsStationUpdateJinglePkgForm" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
	<input type="hidden" name="jinglepkgID" value="{$VIEWER.jinglepkg.id}" />
<p>{if $ERRORS.name}<div class='frame_musicboxerror'>{$ERRORS.name}</div>{/if}Package Name: {if $VIEWER.jinglepkg.name != ''}<input type=text name='name' value='{$VIEWER.jinglepkg.name}'>{else}Default Package{/if}</p>
<p>{if $ERRORS.desc}<div class='frame_musicboxerror'>{$ERRORS.description}</div>{/if}Package Description: {if $VIEWER.jinglepkg.name != ''}<input type=text name='description' value='{$VIEWER.jinglepkg.description}'>{else}Default Jingle Package for newly uploaded jingles{/if}</p>
{if $VIEWER.access_sue == 1}
<p>Package Enabled on Sue?:
	{if $VIEWER.jinglepkg.enabled == 't'}
		<input type="checkbox" name=enabled checked>
	{else}
		<input type="checkbox" name="enabled">
	{/if}
</p>
{/if}

<input type=submit name='submit' value='Submit Changes'>
</form>

<div class='subTitle'>Jingles in this package:</div><br />
	<table border=1 class='stationtable'>
	{foreach from=$VIEWER.jingles item=jingle}
		<tr>
			<th class="userTableName">
				{$jingle.title}
			</th>
			<td class="userTableOption">
				{templateLink id=18 _trackID=$jingle.id text="Preview"}
			</td>
			{if $VIEWER.jinglepkg.name != ''}
			<td class="userTableOption">
				{templateLink id=$VIEWER.templateID text="Remove from package" _formName="dpsStationRemJingleFromPkgForm" _moduleName="DPS" _jingleID=$jingle.id _jinglepkgID=$VIEWER.jinglepkg.id}
			</td>
			{/if}
			<td class="userTableOption">
				{templateLink id=73 text="Change package" _audioID=$jingle.id}
			</td>
		</tr>
	{/foreach}
	</table>
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
