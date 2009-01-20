{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager" studio="t" access_playlist=$VIEWER.access_playlist}
<div class='bigTitle'>Station Audiowall Sets</div>
	{if $VIEWER.awsets}
	<div class='subTitle'>Currently there are following audiowall sets available:</div>
	{/if}
	<table border=1 class='stationtable'>
	{foreach from=$VIEWER.awsets item=awset}
		<tr>
			<th class="userTableName">
				{$awset.name}
			</th>
            <td class="userTableAuthor">({$awset.userid})</td>
			<td class="userTableOption">
				{templateLink id="30" _awset=$awset.id text="view"}
			</td>
			<td class="userTableOption">
				{if $awset.permissions.1 == '1'}
				{templateLink id="28" _awset=$awset.id text="edit"}
				{/if}
			</td>
			<td class="userTableOption">
				{if $awset.parentperm.1 == '1'}
				{templateLink id=$VIEWER.templateID _awset=$awset.id text="delete" _awset=$awset.id _formName="dpsStationDelAwSetForm" _moduleName="DPS"}
				{/if}
			</td>
			<td class="userTableDetail">
				{if $awset.active == 't'}
				<div class="userdefaultawset">active audiowall set</div>
				{else}
				{templateLink id=$VIEWER.templateID _awset=$awset.id text="make active audiowall set" _awset=$awset.id _formName="dpsStationActAwSetForm" _moduleName="DPS"}
				{/if}
			</td>
		</tr>
	{/foreach}
	</table>
	<br />
<div class='subTitle'>Create new audiowall</div>
<form name="dpsStationNewAwSetForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="formName" value="dpsStationNewAwSetForm" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
	{if $ERRORS.name}<div class='frame_musicboxerror'>{$ERRORS.name}</div>{/if}
	Name: <input type=text name='name' value=''><br>
	{if $ERRORS.desc}<div class='frame_musicboxerror'>{$ERRORS.desc}</div>{/if}
	Description: <input type=text name='desc' value=''><br>
	<input type=submit name='submit' value='Add new'>
</form>
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
