{if $VIEWER.error}
	Error:<br>
	{$VIEWER.error}
{else}
	{if $VIEWER.perm == 'view'}
		{$VIEWER.code}
	{elseif $VIEWER.perm == 'edit'}
		{if $VIEWER.showInLineEditing == "CHECKED"}
			<form method='post' action='{$CONFIG.general.siteRoot}'>
			<input type='hidden' name='formName' value='inlineEdit' />
			<input type='hidden' name='moduleName' value='CMS' />
			<input type='hidden' name='templateID' value='{$VIEWER.parentID}' />
			{$VIEWER.code}
			<input type="hidden" name="regionID" value="{$VIEWER.regionID}" />
			<p>
			Show InLine Editing <input type='checkbox' name='alwaysInLine' {$VIEWER.showInLineEditing} value = "on"/>
			<input type="submit" name="submit" value="Save" />
			</p>
			</form>
		{else}
			{$VIEWER.code}<br>
			<p>{templateLink name="editContentWindow.tpl" text="Window Edit" target="_blank" _regionID=$VIEWER.regionID}</p>
		{/if}
	{/if}
{/if}
