{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager" studio=$VIEWER.studioAccess access_playlist=$VIEWER.access_playlist}
<br><br>
<div class='bigTitle'>Audiowall Profiles</div>

<div class='subTitle'>You currently have the following audiowall sets available:</div>
	<table border=1 class='stationtable'>
	{if $VIEWER.stationawset != "None" && $VIEWER.stationawset.id != ""}
		<tr>
			<th class="stationTableName">
				{$VIEWER.stationawset.name}
			</th>
			<td class="stationTableOption">
				{templateLink id="26" _awset=$VIEWER.stationawset.id text="view"}
			</td>
			<td class="stationTableOption">
			</td>
			<td class="stationTableOption">
			</td>
			<td class="stationTableDetail">
	<div class="userdefaultawset">preloaded</div>
			</td>
		</tr>
	{else}
		<tr>
			<th colspan=5 class="stationTableName">
				no station audiowall set selected
			</th>
		</tr>
	{/if}
{foreach from=$VIEWER.awsets item=awset}
		<tr>
			<th class="userTableName">
				{$awset.name}
			</th>
			<td class="userTableOption">
				{if $awset.permissions.0 == '1'}
				{templateLink id="26" _awset=$awset.id text="view"}
				{/if}
			</td>
			<td class="userTableOption">
				{if $awset.permissions.1 == '1'}
				{templateLink id="25" _awset=$awset.id text="edit"}
				{/if}
			</td>
			<td class="userTableOption">
				{if $awset.parentperm.1 == '1'}
				{templateLink id=$VIEWER.templateID _awset=$awset.id text="delete" _awset=$awset.id _formName="dpsUserDelAwSetForm" _moduleName="DPS"}
				{/if}
			</td>
			<td class="userTableDetail">
				{if $awset.active == 't'}
				<div class="userdefaultawset">default awset</div>
				{else}
					{if $awset.permissions.0 == '1'}
				{templateLink id=$VIEWER.templateID _awset=$awset.id text="use in your digiplay profile" _awset=$awset.id _formName="dpsUserActAwSetForm" _moduleName="DPS"}
					{/if}
				{/if}
			</td>
		</tr>
{/foreach}
{if !$VIEWER.awsets}
		<tr>
			<th colspan=5 class="stationTableName">
				no user audiowall sets exist
			</th>
		</tr>
{/if}
	</table>
<div class='statiosubtitle'>Create new audiowall</div>
<form name="dpsUserNewAwSetForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="formName" value="dpsUserNewAwSetForm" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value={$VIEWER.templateID} />
	{if $ERRORS.name}<div class='frame_musicboxerror'>{$ERRORS.name}</div>{/if}
	Name: <input type=text name='name' value=''><br>
	{if $ERRORS.desc}<div class='frame_musicboxerror'>{$ERRORS.desc}</div>{/if}
	Description: <input type=text name='desc' value=''><br>
	<input type=submit name='submit' value='Add new'>
</form>
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
