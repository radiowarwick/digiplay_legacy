{include file="rfile:dpsmusictopframe.tpl" title="RaW Digiplay Manager" RequestTrack=$VIEWER.RequestTrack}
			<div class="musicResultInfo">
				{if $VIEWER.searchValue != ""}
				<b>Found:</b><br>
				{/if}
				{$VIEWER.searchInfo}
				{if $VIEWER.DeleteTrack}
				<div class="warning">Warning: Deleting a track removes it from the Sustainer automaticaly!</div>
				{/if}
			</div>
			<div class="musicResultSorts">
				{if $VIEWER.sortType == "artist"}
				Sort by artist
				{else}
				{templateLink id=$VIEWER.templateID text="Sort by artist" _dpsSortType="artist" _dpsSearchType=$VIEWER.searchType _dpsSearchVal=$VIEWER.searchValue}
				{/if}
				| 
				{if $VIEWER.sortType == "title"}
				Sort by title
				{else}
				{templateLink id=$VIEWER.templateID text="Sort by title" _dpsSortType="title" _dpsSearchType=$VIEWER.searchType _dpsSearchVal=$VIEWER.searchValue}
				{/if}
			</div>
			<form name="dpsMusicSearchViewForm" method="post" action="{$CONFIG.general.siteRoot}">
				<input type="hidden" name="formName" value="dpsMusicSearchViewForm" />
				<input type="hidden" name="moduleName" value="DPS" />
				<input type="hidden" name="templateID" value="10" />
				<table class="musicSearchTable" cellspacing=0>
		<tr>
			{if $VIEWER.EditTrack == 't'}
			<th> </th>
			{/if}
			<th>Artist</th><th>Title</th><th>Preview</th>
			{if $VIEWER.DeleteTrack == 't'}
			<th>Swearing?</th> 
			<th>
			Delete
			</th>
			{else}
			<th colspan="2">Swearing?</th>
			{/if}
			<th>View</th>
		</tr>
		{foreach from=$VIEWER.searchResult item=track}
		<tr>
			{if $VIEWER.EditTrack}
			<th rowspan="2">{templateLink id="37" text="<img class='musicSearchTableTh' src='DPS/images/blackExpand.gif'>" _trackID=$track.id}</th>
			{/if}
			<td rowspan="2">{$track.artist}</td>
			<td>{$track.title}</td>
			<td>{templateLink id="18" text="Preview" _trackID=$track.id}</td>
			{if $VIEWER.DeleteTrack == 't'}
			<td>
			{else}
			<td colspan=2>
			{/if}
				{if $track.censor == 't'}
				<div class="musicCensoredLable">Censored</div>
				{elseif $track.flagged == 't'}
				<div class="musicPossibleSwearLable">Possibly</div>
				{else}
				{if $VIEWER.ReportTrack == 't'}
				{templateLink id=$VIEWER.templateID text="Report" _formName="dpsMusicReportForm" _moduleName="DPS" _trackID=$track.id _dpsSearchType=$VIEWER.searchType _dpsSearchVal=$VIEWER.searchValue _dpsSearchPage=$VIEWER.page}
				{else}
				Clean
				{/if}
				{/if}
			</td>
			{if $VIEWER.DeleteTrack == 't'}
			<td>
			{templateLink id=$VIEWER.templateID text="Delete" _formName="dpsMusicDeleteForm" _moduleName="DPS" _trackID=$track.id _dpsSearchType=$VIEWER.searchType _dpsSearchVal=$VIEWER.searchValue _dpsSearchPage=$VIEWER.page}
			</td>
			{/if}
			<td>
				<input type="checkbox" name="checkbox_{$track.searchNumber}">
				<input type="hidden" name="trackID_{$track.searchNumber}" value="{$track.id}">
			</td>
		</tr>
		<tr>
			<td><div class="music_mini">{$track.album}</div></td>
			<td colspan="2"><div class="music_mini">
				{$track.origin} 
				{if $track.reclibid != ''}
				: {$track.reclibid}
				{/if}
			</div></td>
			<td colspan="2"><div class="music_mini">{$track.length}</div></td>
		</tr>
		{/foreach}
				</table>
				<div class="musicSearchPages">
		{if $VIEWER.searchValue != ""}
		Page: 
		{foreach from=$VIEWER.pages item=page}
		| {templateLink id=$VIEWER.templateID text=$page _dpsSearchPage=$page _dpsSearchVal=$VIEWER.searchValue _dpsSearchType=$VIEWER.searchType}
		{/foreach} 
		|
		{/if}
				</div>
				<div class="musicSearchFormSubmit">
		{if $VIEWER.searchResult}
		<input type="Submit" value="View Selected Tracks">
		{/if}
				</div>
				<br style="&7b;clear:both;&7c;" />
			</form>
{include file="rfile:dpsmusicbottomframe.tpl" Admin=$VIEWER.Admin}