{include file="rfile:dpssuetopframe.tpl" title="Digiplay Manager" nexttrack=$VIEWER.sueNextTrack suesearchid=$VIEWER.templateID Access_EditSue=$VIEWER.Access_EditSue Access_SueStats=$VIEWER.Access_SueStats Access_ViewSue=$VIEWER.Access_ViewSue}
	    <div class="bigTitle">View Sue Playlist</div>
	    <div class="sueplaylistletters">
	      {templateLink id=$VIEWER.templateID text="#" _dpsSearchLetter="*"} | 
	      {templateLink id=$VIEWER.templateID text="A" _dpsSearchLetter="A"} | 
	      {templateLink id=$VIEWER.templateID text="B" _dpsSearchLetter="B"} | 
	      {templateLink id=$VIEWER.templateID text="C" _dpsSearchLetter="C"} | 
	      {templateLink id=$VIEWER.templateID text="D" _dpsSearchLetter="D"} | 
	      {templateLink id=$VIEWER.templateID text="E" _dpsSearchLetter="E"} | 
	      {templateLink id=$VIEWER.templateID text="F" _dpsSearchLetter="F"} | 
	      {templateLink id=$VIEWER.templateID text="G" _dpsSearchLetter="G"} | 
	      {templateLink id=$VIEWER.templateID text="H" _dpsSearchLetter="H"} | 
	      {templateLink id=$VIEWER.templateID text="I" _dpsSearchLetter="I"} | 
	      {templateLink id=$VIEWER.templateID text="J" _dpsSearchLetter="J"} | 
	      {templateLink id=$VIEWER.templateID text="K" _dpsSearchLetter="K"} | 
	      {templateLink id=$VIEWER.templateID text="L" _dpsSearchLetter="L"} | 
	      {templateLink id=$VIEWER.templateID text="M" _dpsSearchLetter="M"} | 
	      {templateLink id=$VIEWER.templateID text="N" _dpsSearchLetter="N"} | 
	      {templateLink id=$VIEWER.templateID text="O" _dpsSearchLetter="O"} | 
	      {templateLink id=$VIEWER.templateID text="P" _dpsSearchLetter="P"} | 
	      {templateLink id=$VIEWER.templateID text="Q" _dpsSearchLetter="Q"} | 
	      {templateLink id=$VIEWER.templateID text="R" _dpsSearchLetter="R"} | 
	      {templateLink id=$VIEWER.templateID text="S" _dpsSearchLetter="S"} | 
	      {templateLink id=$VIEWER.templateID text="T" _dpsSearchLetter="T"} | 
	      {templateLink id=$VIEWER.templateID text="U" _dpsSearchLetter="U"} | 
	      {templateLink id=$VIEWER.templateID text="V" _dpsSearchLetter="V"} | 
	      {templateLink id=$VIEWER.templateID text="W" _dpsSearchLetter="W"} | 
	      {templateLink id=$VIEWER.templateID text="X" _dpsSearchLetter="X"} | 
	      {templateLink id=$VIEWER.templateID text="Y" _dpsSearchLetter="Y"} | 
	      {templateLink id=$VIEWER.templateID text="Z" _dpsSearchLetter="Z"} | 
	      <br />
	    </div>
	    
	    {if $VIEWER.searchResult}
	    <div class="sueplaylistInfo1">
	      {if $VIEWER.sortType == "artist"}
	      Sort by artist
	      {else}
	      {templateLink id=$VIEWER.templateID text="Sort by artist" _dpsSearchLetter=$VIEWER.searchLetter _dpsSortType="artist" _dpsSearchType=$VIEWER.searchType _dpsSearchVal=$VIEWER.searchValue}
	      {/if}
	      | 
	      {if $VIEWER.sortType == "title"}
	      Sort by title
	      {else}
	      {templateLink id=$VIEWER.templateID text="Sort by title" _dpsSearchLetter=$VIEWER.searchLetter _dpsSortType="title" _dpsSearchType=$VIEWER.searchType _dpsSearchVal=$VIEWER.searchValue}
	      {/if}
	    </div>
	    <div class="sueplaylistInfo2">
	      Click a track's title for more information
	    </div>

	    {if $VIEWER.Access_EditSue == 't'}
	    <form name="dpsSuePlaylistForm" method="post" action="{$CONFIG.general.siteRoot}">
	      <input type="hidden" name="formName" value="dpsSuePlaylistForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
	      <input type="hidden" name="dpsSearchPage" value="{$VIEWER.page}" />
	      {if $VIEWER.searchValue != ""}
	      <input type="hidden" name="dpsSearchVal" value="{$VIEWER.searchValue}" />
	      <input type="hidden" name="dpsSearchType" value="{$VIEWER.searchType}" />
	      {elseif $VIEWER.searchLetter != ""}
	      <input type="hidden" name="dpsSearchLetter" value="{$VIEWER.searchLetter}" />
	      {/if}
	    {/if}
			{if $VIEWER.Access_Delete == 't'}
			<br style="clear: both;">
			<div class="warning">Warning: Deleting a track removes it from the Sustainer automaticaly!</div>
			{/if}
	      <table class="sueviewplaylist">
		<tr>
		  {if $VIEWER.Access_EditTrack == 't'}
		  <th></th>
		  {/if}
			<th>Artist</th><th>Title</th><th>Preview</th>
			{if $VIEWER.Access_Delete == 't'}
			<th>Delete</th>
			{/if}
			<th>Playlisted?</th>
		</tr>
		{foreach from=$VIEWER.searchResult item=track}
		<tr>
		  {if $VIEWER.Access_EditTrack == 't'}
		  <th rowspan="2">{templateLink id="37" text="<img class='musicSearchTableTh' src='DPS/images/blackExpand.gif'>" _trackID=$track.id}</th>
		  {/if}
		  <td rowspan="2">{$track.artist}</td>
		  <td>{templateLink id="10" text=$track.title _trackID=$track.id}</td>
		  <td>{templateLink id="18" text="Preview" _trackID=$track.id}</td>
			{if $VIEWER.Access_Delete == 't'}
			<td>
				{templateLink id=$VIEWER.templateID text="Delete" _formName="dpsMusicDeleteForm" _moduleName="DPS" _trackID=$track.id _dpsSearchType=$VIEWER.searchType _dpsSearchVal=$VIEWER.searchValue _dpsSearchPage=$VIEWER.page}
			</td>
			{/if}
		  {if $VIEWER.Access_EditSue == 't'}
		  <td>
		    <input type="checkbox" name="checkbox_{$track.searchNumber}" checked>
		    <input type="hidden" name="trackID_{$track.searchNumber}" value="{$track.id}">
		  </td>
			{else}
			<td>
				<input type="checkbox" name="checkbox_{$track.searchNumber}" checked disabled>
			</td>
		  {/if}
		</tr>
		<tr>
			<td><div class="music_mini">{$track.album}</div></td>
			{if $VIEWER.Access_Delete == 't'}
			<td colspan="2"><div class="music_mini">
			{else}
			<td><div class="music_mini">
			{/if}
				{$track.origin} 
				{if $track.reclibid != ''}
				: {$track.reclibid}
				{/if}
			</div></td>
			<td><div class="music_mini">{$track.length}</div></td>
		</tr>
		{/foreach}
	      </table>
	      <div class="sueplaylistpage">
		{if $VIEWER.searchValue != ""}
		Page: 
		{foreach from=$VIEWER.pages item=page}
		| {templateLink id=$VIEWER.templateID text=$page _dpsSearchPage=$page _dpsSearchVal=$VIEWER.searchValue _dpsSearchType=$VIEWER.searchType}
		{/foreach} 
		|
		{elseif $VIEWER.searchLetter != ""}
		Page: 
		{foreach from=$VIEWER.pages item=page}
		| {templateLink id=$VIEWER.templateID text=$page _dpsSearchPage=$page _dpsSearchLetter=$VIEWER.searchLetter}
		{/foreach} 
		|
		{/if}

	      </div>
	      {if $VIEWER.Access_EditSue == 't'}
	      <div class="sueplaylistupdate">
		<input type="submit" value="Submit">
	      </div>
	      </form>
	      {/if}
	      {/if}
	      <br style="&7b;clear:both;&7c;" />
{include file="rfile:dpsmusicbottomframe.tpl" Admin=$VIEWER.Admin}
