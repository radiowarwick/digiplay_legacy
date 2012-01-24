{include file="rfile:dpsshowtopframe.tpl" title="Digiplay Manager"}
		<div class="showPlanList">
				<div class="bigTitle">Current Scripts</div>
                <div class="showPlanButtons">
				{templateLink id=$VIEWER.templateID text="Create new script"
                    _formName="dpsUserAddScript" _moduleName="DPS"}
                </div>
				<div class="subTitle">You have {$VIEWER.scriptCount} script(s)</div>
				{if $ERRORS.dpsUserDelScript.scriptID != ''}
				<div class="frame_musicboxerror">{$ERRORS.dpsUserDelScript.scriptID}</div>
				{/if}
				{foreach from=$VIEWER.scripts item=script}<br>
				{templateLink id="45" text=$script.text _scriptID=$script.id}<br>
				{if $script.parentperm.1 == "1"}
				<div class="showPlanInteract">

                    {if $script.id == $VIEWER.deleteID}
                        Delete Script - Are You Sure?
    					{templateLink id=$VIEWER.templateID text="Yes"
                            _formName="dpsUserDelScript" _moduleName="DPS" _scriptID=$script.id}
                        |
                        {templateLink id=$VIEWER.templateID text="No"}
                    {else} 
					    {templateLink id=$VIEWER.templateID text="Delete Script"
                            _deleteID=$script.id}
                    {/if}
				</div>
				{/if}
				{/foreach}
				<br>
			</div>
		<br style="&7b;clear:both;&7c;" />
{include file="rfile:dpsshowbottomframe.tpl" Admin=$VIEWER.Admin}
