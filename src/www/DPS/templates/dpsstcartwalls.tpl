{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager"}
	<br>
	<br>
<h1>{$VIEWER.setName} Cartset</h1>
		<hr>
		{templateLink id="23" text="Station Cartwalls"} -> {$VIEWER.setName}
		<hr>
<form name="dpsEStationCartsetForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="formName" value="dpsEStationCartsetForm" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value={$VIEWER.templateID} />
	<input type="hidden" name="cartsetID" value="{$VIEWER.setID}" />
	Name: <input type=text name='name' value='{$VIEWER.setName}'><br>
	Description: <input type=text name='desc' size=30 value='{$VIEWER.setDescription}'><br>
	<input type=submit name='submit' value='Update'>
</form>
<form name="dpsDStationCartsetForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="formName" value="dpsDStationCartsetForm" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value="23" />
	<input type="hidden" name="cartsetID" value="{$VIEWER.setID}" />
	<input type=submit name='submit' value='Delete Cartset'>
</form>
		<table border=1>
			<tr>
				<th>
		Page
				</th>

				<th>
					Carts
				</th>
			</tr>
			{foreach from=$VIEWER.cartwalls item=wall}
			<tr>
	<td valign=top>
		{$wall.name}
	</td>
				<td>
		{templateLink id=25 _cartwallID=$wall.id text="Edit"}
				</td>
			</tr>
			{/foreach}
		</table>

		<b>New Cartwall</b><br>
<form name="dpsAStationCartwallForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="formName" value="dpsAStationCartwallForm" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value={$VIEWER.templateID} />
	<input type="hidden" name="cartsetID" value="{$VIEWER.setID}" />
	Name: <input type=text name='name' value=''><br>
	Description: <input type=text name='desc' value=''><br>
	<input type=submit name='submit' value='Add new'>
</form>
{include file="rfile:dpsstudiobottomframe.tpl"  Admin=$VIEWER.Admin}
