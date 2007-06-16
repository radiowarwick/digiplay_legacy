{include file="rfile:authtopframe.tpl" title="Configuration Management"}
<div class='bigTitle'>Configuration Management</div>
<div class='subTitle'>
	Warning: Changing these settings may seriously comprimise your system's stability and <u>should not</u> be done while the system is on air.
</div>
<hr />
<form name="addGroupForm" method="post" action="{$CONFIG.general.siteRoot}">
<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
<input type="hidden" name="formName" value="alterConfigurationForm" />
<input type="hidden" name="moduleName" value="Auth" />
	<table>
	<tr>
		<th>Paramerter</th><th>Value</th><th>Location</th>
	</tr>
	{foreach from=$VIEWER.configs item="config"}
	<tr>
		<td>{$config.parameter}</td>
		<td><input type='text' name='val{$config.id}' value='{$config.val}' /></td>
		<td>
			<select name='loc{$config.id}'}
			{foreach from=$VIEWER.locs item='loc'}
				{if $loc.location == $config.location}
				<option value='{$loc.location}' selected>{$loc.location}</option>
				{else}
				<option value='{$loc.location}'>{$loc.location}</option>
				{/if}
			{/foreach}
			</select>
		</td>
	</tr>
	{/foreach}
	</table>
	<input type='submit' value='Update' text='Update'>
</form>
{include file="rfile:authbottomframe.tpl"}
