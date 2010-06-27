{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager"}
	<br>
	<br>
<div class='stationtitle'>Station Audiowall</div>
<div class='statioinfo1'>Available Audiowall sets for Station Audiowall</div>
<form name="dpsStationActAwSetForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="formName" value="dpsStationActAwSetForm" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value={$VIEWER.templateID} />
		<table border=1 class='statiotable'>
		<tr>
			<th width=120>
				Audiowall Set
			</th>
			<th>
				Status
			</th>
			<th>
				Edit
			</th>
		</tr>
{foreach from=$VIEWER.awsets item=awset}
		<tr>
			<td>
				{$awset.name}
			</td>
			<td>
				{if $awset.active == 1}
				<input type='radio' checked="checked" value='{$awset.id}' name='activeSCW'>
				{else}
				<input type='radio' value='{$awset.id}' name='activeSCW'>
				{/if}
			</td>
			<td>
				{templateLink id="64" _awsetID=$awset.id text="Edit"}
			</td>
		</tr>
{/foreach}
	</table>
	<input type=submit value="Update" name=submit>
</form>
<div class='statiosubtitle'>New Audiowall Set</div>
<form name="dpsNewStationAwSetForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="formName" value="dpsNewStationAwSetForm" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value={$VIEWER.templateID} />
	Name: <input type=text name='name' value=''><br>
	Description: <input type=text name='desc' value=''><br>
	<input type=submit name='submit' value='Add new'>
</form>
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
