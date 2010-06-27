{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager"}
	<br>
	<br>
<h1>{$VIEWER.setName} Audiowall Set</h1>
		<hr>
		{templateLink id="23" text="Station Audiowalls"} -> {$VIEWER.setName}
		<hr>
<form name="dpsEStationAwSetForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="formName" value="dpsEStationAwSetForm" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value={$VIEWER.templateID} />
	<input type="hidden" name="awsetID" value="{$VIEWER.setID}" />
	Name: <input type=text name='name' value='{$VIEWER.setName}'><br>
	Description: <input type=text name='desc' size=30 value='{$VIEWER.setDescription}'><br>
	<input type=submit name='submit' value='Update'>
</form>
<form name="dpsDStationAwSetForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="formName" value="dpsDStationAwSetForm" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value="23" />
	<input type="hidden" name="awsetID" value="{$VIEWER.setID}" />
	<input type=submit name='submit' value='Delete Audiowall Set'>
</form>
		<table border=1>
			<tr>
				<th>
		Page
				</th>

				<th>
					Audiowall Items
				</th>
			</tr>
			{foreach from=$VIEWER.awwalls item=wall}
			<tr>
	<td valign=top>
		{$wall.name}
	</td>
				<td>
		{templateLink id=25 _awwallID=$wall.id text="Edit"}
				</td>
			</tr>
			{/foreach}
		</table>

		<b>New Audiowall</b><br>
<form name="dpsAStationAwWallForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="formName" value="dpsAStationAwWallForm" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value={$VIEWER.templateID} />
	<input type="hidden" name="awsetID" value="{$VIEWER.setID}" />
	Name: <input type=text name='name' value=''><br>
	Description: <input type=text name='desc' value=''><br>
	<input type=submit name='submit' value='Add new'>
</form>
{include file="rfile:dpsstudiobottomframe.tpl"  Admin=$VIEWER.Admin}
