{include file="rfile:dpsshowtopframe.tpl" title="RaW Digiplay Manager"}
{if $VIEWER.error != ''}
	{$VIEWER.error}
{else}
	<div class="showPlanList">
		<div class="bigTitle">
			{if $VIEWER.done == 't'}
			<img src="DPS/images/showFinished.png" alt="Finished">
			{else}
			{if $VIEWER.show.completed == 't'}
			<img src="DPS/images/showReady.png" alt="Ready">
			{else}
			<img src="DPS/images/showUnfinished.png" alt="Unfinished">
			{/if}
			{/if}
			{$VIEWER.show.name}</div>
	  <i>{$VIEWER.show.niceAirDate} - {$VIEWER.show.niceAirTime}</i><br>
	</div>
	<div class="rightLinks">{templateLink id="55" text="<< Back to full show plan" _showID=$VIEWER.show.id}</div>
	<br style="&7b;clear:both;&7c;" />
	<hr>
	<div class="bigTitle">Show Order</div>
	<div class="subTitle">Click the arrows to move the items</div>
	<table class="showItems" width=100%>
		<tr>
			<th>No.</th><th>Time</th><th>Element</th><th>Nature</th><th colspan="2">Move</th>
		</tr>
		{foreach from=$VIEWER.showItems item=item}
		<tr>
			<td>
				<b>{$item.position}</b>
			</td>
			<td>
				<b>{$item.niceTime}</b>
			</td>
			<td>
				<b>{$item.title}</b>
			</td>
			<td>
                {if $item.nature != 'unknown'}
				    {$item.nature}:
                    {templateLink id=18 _trackID=$item.audioid text=$item.audioTitle}
                {/if}
                {if $item.nature != 'unknown' && $item.scriptid != ''}
                    <br/>
                {/if}
				{if $item.scriptid != ''}
				    Script: {templateLink id="45" _scriptID=$item.scriptid text=$item.scriptName}
				{/if}
			</td>
			<td width=40px class="upDown">	
			{if $item.position == 1}
			    <img src='DPS/images/moveupdisabled18.png' alt='Up'>
            {else}
				{templateLink id=$VIEWER.templateID text="<img src='DPS/images/moveup18.png' alt='Up'>" _itemID=$item.id
                    _formName="dpsUserShowItemUp" _moduleName="DPS" _showID=$VIEWER.show.id}
            {/if}
			</td>
			<td width=40px class="upDown">
			{if $item.position == $VIEWER.itemCount}
			    <img src='DPS/images/movedowndisabled18.png' alt='Down'>
            {else}
				{templateLink id=$VIEWER.templateID text="<img src='DPS/images/movedown18.png' alt='Down'>" _itemID=$item.id
                    _formName="dpsUserShowItemDown" _moduleName="DPS" _showID=$VIEWER.show.id}
            {/if}
			</td>
		</tr>
		{/foreach}
        <tr>
            <td></td>
            <td><b>{$VIEWER.endTime}</b></td>
            <td colspan="4" style="text-align:center;"><b>END</b></td>
        </tr>
	</table>
    <form method="GET" action="">
        <input type="hidden" name="templateID" value="55" />
        <input type="hidden" name="showID" value="{$VIEWER.show.id}" />
        <input type="submit" value="Done" />
    </form>
{/if}
{include file="rfile:dpsshowbottomframe.tpl" Admin=$VIEWER.Admin}
