{include file="rfile:dpsshowtopframe.tpl" title="RaW Digiplay Manager"}
		<div class="showPlanList">
				<div class="bigTitle">Current shows</div>
				<div class="subTitle">You have {$VIEWER.pShowCount} show(s) in progress</div>
				{foreach from=$VIEWER.partShows item=show}
				{if $show.completed == 't'}
				<img src="DPS/images/showReady.png" alt="Ready">
				{else}
				<img src="DPS/images/showUnfinished.png" alt="Unfinished">
				{/if}
				{templateLink id="55" text=$show.text _showID=$show.id}<br>
				<div class="showPlanInteract">
				{if $show.parentperm.1 == "1"}
				{templateLink id=$VIEWER.templateID text="Delete Show" _formName="dpsUserDelShow" _moduleName="DPS" _showID=$show.id}
				{/if}
				&nbsp;&nbsp;
				{if $show.permissions.1 == "1"}
				{templateLink id="57" text="Edit Name and Time" _showID=$show.id}
				{/if}
				</div>
				{/foreach}
				<br>
				
				<div class="bigTitle">Previous shows</div>
				<div class="subTitle">You have {$VIEWER.dShowCount} old program(s)</div>
				{foreach from=$VIEWER.doneShows item=show}
				<img src="DPS/images/showFinished.png" alt="Unfinished">
				{templateLink id="55" text=$show.text _showID=$show.id}<br>
				<div class="showPlanInteract">
				{if $show.parentperm.1 == "1"}
				{templateLink id=$VIEWER.templateID text="Delete Show" _formName="dpsUserDelShow" _moduleName="DPS" _showID=$show.id}
				{/if}
				&nbsp;&nbsp;
				{if $show.permissions.1 == "1"}
				{templateLink id="57" text="Edit Name and Time" _showID=$show.id}
				{/if}
				</div>
				{/foreach}
			</div>
			<div class="showPlanHelp">
				<img src="DPS/images/showFinished.png" alt="Finished"> Already broadcast<br>
				<img src="DPS/images/showUnfinished.png" alt="Uninished"> Unfinished<br>
				<img src="DPS/images/showReady.png" alt="Ready"> Finished & ready<br>
			</div>
			<div class="showPlanNew">
				{templateLink id=$VIEWER.templateID text="Create new show" _formName="dpsUserAddShow" _moduleName="DPS"}</a>
			</div>
		<br style="&7b;clear:both;&7c;" />
{include file="rfile:dpsshowbottomframe.tpl" Admin=$VIEWER.Admin}
