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
			<th>No.</th><th>Time</th><th>Element</th><th colspan="2">Move</th><th>Options</th>
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
				{if $item.audioTitle != ''}
				<br />
				{$item.audioTitle}
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
			<td>
				{templateLink id="58" text="Edit" _itemID=$item.id}<br>{templateLink id=$VIEWER.templateID text="Erase" _itemID=$item.id _formName="dpsUserDelShowItem" _moduleName="DPS" _showID=$VIEWER.show.id}
			</td>
		</tr>
		{/foreach}
	</table>
{/if}
{include file="rfile:dpsshowbottomframe.tpl" Admin=$VIEWER.Admin}
