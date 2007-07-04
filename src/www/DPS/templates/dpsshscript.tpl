{include file="rfile:dpsshowtopframe.tpl" title="RaW Digiplay Manager"}
		<div class="showPlanList">
				<div class="bigTitle">Current Scripts</div>
				<div class="subTitle">You have {$VIEWER.scriptCount} script(s)</div>
				{if $ERRORS.dpsUserDelScript.scriptID != ''}
				<div class="frame_musicboxerror">{$ERRORS.dpsUserDelScript.scriptID}</div>
				{/if}
				{foreach from=$VIEWER.scripts item=script}
				<img src="DPS/images/showScript.png" alt="Show Script">
				{templateLink id="45" text=$script.text _scriptID=$script.id}<br>
				{if $script.parentperm.1 == "1"}
				<div class="showPlanInteract">
					{templateLink id=$VIEWER.templateID text="Delete Script" _formName="dpsUserDelScript" _moduleName="DPS" _scriptID=$script.id}
				</div>
				{/if}
				{/foreach}
				<br>
			</div>
			<div class="showPlanNew">
				{templateLink id=$VIEWER.templateID text="Create new script" _formName="dpsUserAddScript" _moduleName="DPS"}</a>
			</div>
		<br style="&7b;clear:both;&7c;" />
{include file="rfile:dpsshowbottomframe.tpl" Admin=$VIEWER.Admin}
