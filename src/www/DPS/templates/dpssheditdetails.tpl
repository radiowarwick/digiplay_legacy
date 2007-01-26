{include file="rfile:dpsshowtopframe.tpl" title="RaW Digiplay Manager"}
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
		<b>New Details</b><br />
		<form name="dpsUserEditShow" method="post" action="{$CONFIG.general.siteRoot}">
		<input type="hidden" name="formName" value="dpsUserEditShow" />
		<input type="hidden" name="moduleName" value="DPS" />
		<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
		<input type="hidden" name="showID" value="{$VIEWER.show.id}" />
		Name: <input type="text" name="name" value="{$VIEWER.show.name}"/><br />
		{if $ERRORS.dpsUserEditShow.form != ''}
			{$ERRORS.dpsUserEditShow.form}<br />
		{/if}
		Airing Date:
		<select name="day" text="{$VIEWER.show.D}">
			{$VIEWER.formOpts.date}
		</select>
		<select name="month" value="{$VIEWER.show.M}">
			{$VIEWER.formOpts.month}
		</select>
		<select name="year" text="{$VIEWER.show.Y}">
			{$VIEWER.formOpts.year}
		</select><br />
		{if $ERRORS.dpsUserEditShow.hours != ''}
			{$ERRORS.dpsUserEditShow.hours}<br />
		{elseif $ERRORS.dpsUserEditShow.mins != ''}
			{$ERRORS.dpsUserEditShow.mins}<br />
		{/if}
		Airing Time(24h): <input type=text name="hours" maxlength=2 size=2 value="{$VIEWER.show.h}" />:<input type=text name="mins" maxlength=2 size=2 value="{$VIEWER.show.m}" /><br />
		<b>Producer: </b> {$VIEWER.show.niceProducer}<br />
		<!--<b>Participants: </b> People, Many many people<br />
		<a href="">Edit details and participants</a>-->
		<input type="Submit" name="Submit" value="Submit" />
	</div>
	<div class="showPlanHelp">
		<img src="DPS/images/showFinished.png" alt="Finished"> Already broadcast<br>
	  <img src="DPS/images/showUnfinished.png" alt="Uninished"> Unfinished<br>
	  <img src="DPS/images/showReady.png" alt="Ready"> Finished & ready<br>
	</div>
	<div class="rightLinks">{templateLink id="81" text="<< Back to your shows"}</div>
	<br style="&7b;clear:both;&7c;" />
{/if}
{include file="rfile:dpsshowbottomframe.tpl" Admin=$VIEWER.Admin}
