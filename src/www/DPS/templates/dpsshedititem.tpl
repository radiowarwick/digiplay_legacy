{include file="rfile:dpsshowtopframe.tpl" title="RaW Digiplay Manager"}
	<div class="showPlanList">
		<div class="bigTitle">
			{if $VIEWER.done == 't'}
			<img class="showImgTitle" src="DPS/images/showFinished.png" alt="Finished">
			{else}
			{if $VIEWER.show.completed == 't'}
			<img src="DPS/images/showReady.png" alt="Ready">
			{else}
			<img class="showImgTitle" src="DPS/images/showUnfinished.png" alt="Unfinished">
			{/if}
			{/if}
			{$VIEWER.show.name}
		</div>
	  <i>{$VIEWER.show.niceAirDate} - {$VIEWER.show.niceAirTime}</i>
	</div>
	<div class="rightLinks">
		{templateLink id="55" text="<< Back to full show plan" _showID=$VIEWER.show.id}<br>
		<div class="showSmall">only if you don't want to save changes!</div>
	</div>
	<br style="&7b;clear:both;&7c;" />
	<table class="showItems" width=100%>
		<tr>
			<th>Time</th><th>Element</th><th>Nature</th><th>Length</th><th>Note</th>
		</tr>
		<tr>
			<td>
				<b>{$VIEWER.item.niceTime}</b>
			</td>
			<td>
				<b>{$VIEWER.item.title}</b>
				{if $VIEWER.item.audioTitle != ''}
				<br />{$VIEWER.item.audioTitle}
				{/if}
			</td>
			<td>
        {if $VIEWER.item.nature == 'music'}
				Music
				{elseif $VIEWER.item.nature == 'jingle'}
				Jingle
				{elseif $VIEWER.item.nature == 'advert'}
				Advert
				{else}
				Other
				{/if}
				{if $VIEWER.item.scriptid != ''}
				+<br />{templateLink id="45" _scriptID=$VIEWER.item.scriptid text=$VIEWER.item.scriptName}
				{/if}
			</td>
			<td>
				{$VIEWER.item.niceLength}
			</td>
			<td>
				{$VIEWER.item.comment}
			</td>
		</tr>
	</table>

	{if $VIEWER.write == "t"}
	<form name="dpsUserEditShowItem" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="formName" value="dpsUserEditShowItem" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
	<input type="hidden" name="itemID" value="{$VIEWER.item.id}" />
	<div class="bigTitle">Edit Element</div>
	<div class="subTitle">You MUST save changes by clicking "Submit"</div>

	<table class="showEdititem">
		<tr>
			<th>Element type</th>
			<td>
        {if $VIEWER.item.nature == 'music'}
				Music
				{elseif $VIEWER.item.nature == 'jingle'}
				Jingle
				{elseif $VIEWER.item.nature == 'advert'}
				Advert
				{else}
				Other
				{/if}
			</td>
		</tr>
		<tr>
			<th>Element name</th>
			<td>
				<input type="text" name="title" value="{$VIEWER.item.title}">
			</td>
			<th>
			</th>
		</tr>
		<tr>
			<th>Element audio</th>
			<td>	
				{if $VIEWER.item.audioTitle != ''}
				{$VIEWER.item.audioTitle} - {$VIEWER.item.niceAudioLength} ({templateLink id=$VIEWER.templateID text="Remove" _formName="dpsUserDelAudioShow" _moduleName="DPS" _itemID=$VIEWER.item.id})
				{else}
				None (Add: <a href="javascript:NewWindow('?templateID=43&itemID={$VIEWER.item.id}','DPS Music','640','580');">Music</a>,
				<a href="javascript:NewWindow('?templateID=41&itemID={$VIEWER.item.id}','DPS Jingle',640,580);">Jingle</a>,
				<a href="javascript:NewWindow('?templateID=42&itemID={$VIEWER.item.id}','DPS Advert','640','580');">Advert</a>)
				{/if}
			</td>
		</tr>
		<tr>
			<th>Associated script</th>
			<td>
				{if $VIEWER.item.scriptid != ''}
				{templateLink id="94" _scriptID=$VIEWER.item.scriptid text=$VIEWER.item.scriptName} - {$VIEWER.item.niceScriptLength} ({templateLink id=$VIEWER.templateID text="Remove" _formName="dpsUserDelScriptShow" _moduleName="DPS" _itemID=$VIEWER.item.id})
				{else}
				None (Add: <a href="javascript:NewWindow('?templateID=46&itemID={$VIEWER.item.id}','DPS - Script','640','580');">Script</a>)
				{/if}
			</td>
		</tr>
		<tr>
			<th>Length (MM:SS)</th>
			<td>
				{if $VIEWER.short == 't'}
				<div class='error'>Warning: Item shorter than contents!</div>
				{/if}
				<input type=text name="mins" maxlength=2 size=2 value="{$VIEWER.item.m}" />:<input type=text name="secs" maxlength=2 size=2 value="{$VIEWER.item.s}" />
			</td>
		</tr>
		<tr>
			<th>Note</th>
			<td>
				<textarea name="notes">{$VIEWER.item.comment}</textarea>
			</td>
		</tr>
		<tr>
			<th></th>
			<th><input type="Submit" value="Save Changes" name="Submit" /></th>
		</tr>
	</table>
	</form>
	{/if}
{include file="rfile:dpsshowbottomframe.tpl" Admin=$VIEWER.Admin}
