{include file="rfile:dpsshowtopframe.tpl" title="Digiplay Manager"}
{if $VIEWER.error}
	{$VIEWER.error}
{else}
	<div class="showPlanList">
		<div class="bigTitle">
			{$VIEWER.script.name}
		</div>
		{if $VIEWER.write == 't'}
		<b>New Details</b><br />
		<form name="dpsUserEditScript" method="post" action="{$CONFIG.general.siteRoot}">
		<input type="hidden" name="formName" value="dpsUserEditScript" />
		<input type="hidden" name="moduleName" value="DPS" />
		<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
		<input type="hidden" name="scriptID" value="{$VIEWER.script.id}" />
		{if $ERRORS.dpsUserEditScript.scriptID != ''}
			{$ERRORS.dpsUserEditScript.scriptID}<br />
		{/if}
		{if $ERRORS.dpsUserEditScript.name != ''}
			{$ERRORS.dpsUserEditScript.name}<br />
		{/if}
		Name: <input type="text" name="name" value="{$VIEWER.script.name}"/><br />
		{if $ERRORS.dpsUserEditScript.mins != ''}
			{$ERRORS.dpsUserEditScript.mins}<br />
		{elseif $ERRORS.dpsUserEditScript.secs != ''}
			{$ERRORS.dpsUserEditScript.secs}<br />
		{/if}
		Length (mm:ss): <input type=text name="mins" maxlength=2 size=2 value="{$VIEWER.script.m}" />:<input type=text name="secs" maxlength=2 size=2 value="{$VIEWER.script.s}" /><br />
		<hr>
		<textarea name="content" cols=70 rows=20>{$VIEWER.script.contents}</textarea><br />
		<input type="Submit" name="Save" value="Save" />
		<input type="Submit" name="Submit" value="Save &amp; Return" />
	    {templateLink id="44" text=" Cancel"}
		{else}
		<b>Name:</b> {$VIEWER.script.name}<br />
		<b>Length (mm:ss):</b> {$VIEWER.script.m}:{$VIEWER.script.s}<br />
		<hr />
		<div>{$VIEWER.script.contents}</div>
		{/if}
	</div>
	<br style="&7b;clear:both;&7c;" />
{/if}
{include file="rfile:dpsshowbottomframe.tpl" Admin=$VIEWER.Admin}
