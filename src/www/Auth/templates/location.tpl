{include file="rfile:authtopframe.tpl" title="Configuration Management"}
<div class='bigTitle'>Location Management</div>
<div class='subTitle'>
	Warning: Changing these settings may seriously comprimise your system's stability and <u>should not</u> be done while the system is on air.
</div>
<hr />
<div class='subTitle'>
	New Location Details:
</div>
<form name="addLocationForm" method="post" action="{$CONFIG.general.siteRoot}">
<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
<input type="hidden" name="formName" value="addLocationForm" />
<input type="hidden" name="moduleName" value="Auth" />
channel_1: <input type="text" name="channel_1" value="/dev/null" /><br />
channel_2: <input type="text" name="channel_2" value="/dev/null" /><br />
channel_3: <input type="text" name="channel_3" value="/dev/null" /><br />
channel_4: <input type="text" name="channel_4" value="/dev/null" /><br />
<input type="submit" name="Submit" value="Submit" />
</form>
<hr />
<div class='subTitle'>
	Current Locations:
</div>
<table>
	<tr>
		<th>Location Name</th><th>Action</th>
	</tr>
	{foreach from=$VIEWER.locs item="loc"}
	<tr>
		<td>{$loc.locname}</td>
		<td>{templateLink id=$VIEWER.templateID text="Remove" _formName="removeLocationForm" _moduleName="Auth" _locationID=$loc.locid}</td>
	</tr>
	{/foreach}
	</table>
{include file="rfile:authbottomframe.tpl"}