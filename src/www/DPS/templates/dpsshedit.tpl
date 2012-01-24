{include file="rfile:dpsshowtopframe.tpl" title="Digiplay Manager"}
{if $VIEWER.error}
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
			{$VIEWER.show.name}
		</div>

	  <i>{$VIEWER.show.niceAirDate} - {$VIEWER.show.niceAirTime}</i>
		{if $VIEWER.show.permissions.1 == "1" &&
            $VIEWER.done != 't' &&
            $VIEWER.show.completed != 't'}
			- {templateLink id="57" text="Edit Name and Time" _showID=$VIEWER.show.id}
		{/if}
      <br>
		<b>Length: </b> {$VIEWER.show.niceLength}<br />
		<!--<b>Genre: </b> Pop/Speech<br />-->
		<b>Producer: </b> {$VIEWER.show.niceProducer}<br />
		<!--<b>Participants: </b> People, Many many people<br />
		<a href="">Edit details and participants</a>-->
	</div>
	<div class="showPlanHelp">
		<img src="DPS/images/showFinished.png" alt="Finished"> Already broadcast<br>
	  <img src="DPS/images/showUnfinished.png" alt="Uninished"> Unfinished<br>
	  <img src="DPS/images/showReady.png" alt="Ready"> Finished & ready<br>
	</div>
	<br style="&7b;clear:both;&7c;" />
	<hr>
	{if $VIEWER.write == "t" && $VIEWER.done != 't'}
	{if $VIEWER.show.completed == 't'}
	<div class="showLinks">{templateLink id=$VIEWER.templateID text="<img src='DPS/images/showUnfinished.png' alt='Finished'> Declare show not finished" _formName="dpsUserUnCompleteShow" _moduleName="DPS" _showID=$VIEWER.show.id}</div>
	{else}
	<div class="showLinks">{templateLink id=$VIEWER.templateID text="<img src='DPS/images/showUnfinished.png' alt='Add'> Add Element" _formName="dpsUserAddShowItem" _moduleName="DPS" _showID=$VIEWER.show.id}</div>
	<div class="showLinks">
		{templateLink id="56" text="<img src='DPS/images/showUnfinished.png' alt='Order'> Change Order" _showID=$VIEWER.show.id}
	</div>
	<div class="showLinks">{templateLink id=$VIEWER.templateID text="<img src='DPS/images/showReady.png' alt='Unfinish'> Declare show finished" _formName="dpsUserCompleteShow" _moduleName="DPS" _showID=$VIEWER.show.id}</div>
	{/if}
	{/if}
<!--	<div class="showWarning">Show has 01:40:35 unlabelled</div>-->
	<br style="&7b;clear:both;&7c;" />
	<table class="showItems" width=100%>
		<tr>
			<th>Time</th><th>Element</th><th>Nature</th><th>Length</th><th>Note</th>
			{if $VIEWER.write == "t" && $VIEWER.done != 't' && $VIEWER.show.completed != 't'}
			<th></th>
			{/if}
		</tr>
		{foreach from=$VIEWER.showItems item=item}
		<tr>
			<td>
				<b>{$item.niceTime}</b>
			</td>
			<td>
	    		<b>{templateLink id="58" text=$item.title _itemID=$item.id}</b>
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
			<td>
				{$item.niceLength}
			</td>
			<td>
				{$item.comment}
			</td>
			{if $VIEWER.write == "t" && $VIEWER.done != 't' && $VIEWER.show.completed != 't'}
			<td>
                {if $VIEWER.deleteID == $item.id}
                    Are You Sure?<br/>
                    {templateLink id=$VIEWER.templateID text="Yes"
                        _itemID=$item.id _formName="dpsUserDelShowItem" _moduleName="DPS" _showID=$VIEWER.show.id}
                    |
                    {templateLink id=$VIEWER.templateID text="No" _showID=$VIEWER.show.id}
                {else}
                    {templateLink id=$VIEWER.templateID text="Delete"
                        _showID=$VIEWER.show.id _deleteID=$item.id}
                {/if}
			</td>
			{/if}
		</tr>
		{/foreach}
        <tr>
            <td><b>{$VIEWER.endTime}</b></td>
            <td colspan="5" style="text-align:center;"><b>END</b></td>
        </tr>
	</table>

{/if}
{include file="rfile:dpsshowbottomframe.tpl" Admin=$VIEWER.Admin}
