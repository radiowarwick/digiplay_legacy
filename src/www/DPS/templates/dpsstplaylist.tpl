{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager" access_playlist='t' studio=$VIEWER.studioAccess}
	    <div class="bigTitle">Add to Playlist: {$VIEWER.playlist.name}</div>
		<div class="studioPlaylists">Edit Playlist:
		{foreach from=$VIEWER.playlists item="playlist"}
		{templateLink id="80" text=$playlist.name _dpsPlaylistID=$playlist.id _dpsSearchLetter=$VIEWER.searchLetter _dpsSortType=$VIEWER.sortType _dpsSearchType=$VIEWER.searchType _dpsSearchVal=$VIEWER.searchValue} 
		{/foreach}
		</div>
		<br style="&7b;clear:both;&7c;" />

		<form name="dpsPlaylistSearchForm" method="post" action="{$CONFIG.general.siteRoot}">
          <input type="hidden" name="formName" value="dpsPlaylistSearchForm" />
          <input type="hidden" name="moduleName" value="DPS" />
          <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
		  <input type="hidden" name="dpsPlaylistID" value="{$VIEWER.playlist.id}" /> 
		  {if $ERRORS.dpsSearchVal}
          <div class="frame_musicboxerror">{$ERRORS.dpsSearchVal}</div>
          {elseif $ERRORS.dpsSearchType}
          <div class="frame_musicboxerror">{$ERRORS.dpsSearchType}</div>
          {/if}
          <input type="text" name="dpsSearchVal" value="{$VIEWER.searchValue}">
          <select name="dpsSearchType">
        {if $VIEWER.searchType == "Both"}
          <option value="Both" selected="selected">Both</option>
        {else}
          <option value="Both">Both</option>
        {/if}
        {if $VIEWER.searchType == "Artist"}
          <option value="Artist" selected="selected">Artist</option>
        {else}
          <option value="Artist">Artist</option>
        {/if}
        {if $VIEWER.searchType == "Title"}
          <option selected="selected" value="Title">Title</option>
        {else}
          <option value="Title">Title</option>
        {/if}
          </select>
          <input type="Submit" name="Search" value="Search">
        </form>
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
	      {templateLink id="80" text="Sort by artist" _dpsSearchLetter=$VIEWER.searchLetter _dpsSortType="artist" _dpsSearchType=$VIEWER.searchType _dpsSearchVal=$VIEWER.searchValue}
	      {/if}
	      | 
	      {if $VIEWER.sortType == "title"}
	      Sort by title
	      {else}
	      {templateLink id="80" text="Sort by title" _dpsSearchLetter=$VIEWER.searchLetter _dpsSortType="title" _dpsSearchType=$VIEWER.searchType _dpsSearchVal=$VIEWER.searchValue}
	      {/if}
	    </div>
	    <div class="sueplaylistInfo2">
	      Click a track's title for more information
	    </div>
	    <form name="dpsStAddPlaylistForm" method="post" action="{$CONFIG.general.siteRoot}">
	      <input type="hidden" name="formName" value="dpsStAddPlaylistForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
	      <input type="hidden" name="dpsSearchPage" value="{$VIEWER.page}" />
	      {if $VIEWER.searchValue != ""}
	      <input type="hidden" name="dpsSearchVal" value="{$VIEWER.searchValue}" />
	      <input type="hidden" name="dpsSearchType" value="{$VIEWER.searchType}" />
	      {elseif $VIEWER.searchLetter != ""}
	      <input type="hidden" name="dpsSearchLetter" value="{$VIEWER.searchLetter}" />
	      {/if}
		  <input type="hidden" name="dpsPlaylistID" value="{$VIEWER.playlist.id}" />
	    <table class="sueviewplaylist">
	      <tr>
		{if Access_EditTrack}
	        <th></th>
		{/if}
		<th>Playlisted?</th><th>Artist</th><th>Title</th><th>Length</th><th>30s Preview</th>
	      </tr>
	      {foreach from=$VIEWER.searchResult item=track}
	      <tr>
		{if Access_EditTrack}
		<th>{templateLink id="53" text="<img class='musicSearchTableTh' src='DPS/images/blackExpand.gif'>" _trackID=$track.id}</th>
		{/if}
		<td>
		  {if $track.playlist == 't'}
		  <input type="checkbox" name="checkbox_{$track.searchNumber}" checked>
		  <input type="hidden" name="trackVal_{$track.searchNumber}" value="on">
		  {else}
		  <input type="checkbox" name="checkbox_{$track.searchNumber}">
		  <input type="hidden" name="trackVal_{$track.searchNumber}" value="off">
		  {/if}
		  <input type="hidden" name="trackID_{$track.searchNumber}" value="{$track.id}">
		</td>
		<td>{$track.artist}</td>
		<td>{templateLink id="55" text=$track.title _trackID=$track.id}</td>
		<td>{$track.length}</td>
		<td>{templateLink id="57" text="Preview" _trackID=$track.id}</td>
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
	      <div class="sueplaylistupdate">
		<input type="submit" value="Submit">
	      </div>
	      </form>
	      {/if}
	      <br style="&7b;clear:both;&7c;" />
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
