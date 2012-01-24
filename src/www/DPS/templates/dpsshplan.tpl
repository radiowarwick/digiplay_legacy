{include file="rfile:dpsshowtopframe.tpl" title="Digiplay Manager"}
		<div class="showPlanList">
				<div class="bigTitle">Current shows</div>
				<div class="showPlanButtons">
                {templateLink id=$VIEWER.templateID text="Create new show"
                    _formName="dpsUserAddShow" _moduleName="DPS"}
                </div>
				<div class="subTitle">You have {$VIEWER.pShowCount} show(s) in progress</div>
				{foreach from=$VIEWER.partShows item=show}
                <div class="showPlanItem">
				{if $show.completed == 't'}
				<img src="DPS/images/showReady.png" alt="Ready">
				{else}
				<img src="DPS/images/showUnfinished.png" alt="Unfinished">
				{/if}
				{templateLink id="55" text=$show.text _showID=$show.id}<br>
				<div class="showPlanInteract">
				{if $show.parentperm.1 == "1"}
                {if $VIEWER.deleteID == $show.id}
                    Delete Show - Are You Sure?
				    {templateLink id=$VIEWER.templateID text="Yes"
                        _formName="dpsUserDelShow" _moduleName="DPS" _showID=$show.id}
                    |
				    {templateLink id=$VIEWER.templateID text="No"}
                {else}
                    {templateLink id=$VIEWER.templateID text="Delete Show"
                        _deleteID=$show.id}
                {/if}
				{/if}
				</div>
                </div>
				{/foreach}
				<br>
				
				<div class="bigTitle">Previous shows</div>
				<div class="subTitle">You have {$VIEWER.dShowCount} old program(s)</div>
				{foreach from=$VIEWER.doneShows item=show}
                <div class="showPlanItem">
				<img src="DPS/images/showFinished.png" alt="Unfinished">
				{templateLink id="55" text=$show.text _showID=$show.id}<br>
				<div class="showPlanInteract">
				{if $show.parentperm.1 == "1"}
                {if $VIEWER.deleteID == $show.id}
                    Delete Show - Are You Sure?
				    {templateLink id=$VIEWER.templateID text="Yes"
                        _formName="dpsUserDelShow" _moduleName="DPS" _showID=$show.id}
                    |
				    {templateLink id=$VIEWER.templateID text="No"}
                {else}
                    {templateLink id=$VIEWER.templateID text="Delete Show"
                        _deleteID=$show.id}
                {/if}
				{/if}
				</div>
                </div>
				{/foreach}
			</div>
			<div class="showPlanHelp">
				<img src="DPS/images/showFinished.png" alt="Finished"> Already broadcast<br>
				<img src="DPS/images/showUnfinished.png" alt="Uninished"> Unfinished<br>
				<img src="DPS/images/showReady.png" alt="Ready"> Finished & ready<br>
			</div>
		<br style="&7b;clear:both;&7c;" />
{include file="rfile:dpsshowbottomframe.tpl" Admin=$VIEWER.Admin}
