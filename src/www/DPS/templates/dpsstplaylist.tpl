{include file="rfile:dpsstudiotopframe.tpl" title="Digiplay Manager" access_playlist='t' studio=$VIEWER.studioAccess}
    <div>Select Playlist:
        {foreach from=$VIEWER.playlists item="playlist"}
            | {templateLink id=$VIEWER.templateID text=$playlist.name
                _dpsPlaylistID=$playlist.id _dpsSortType=$VIEWER.sortType
                    _dpsSearchType=$VIEWER.searchType
                    _dpsSearchVal=$VIEWER.searchValue
                    _dpsResultType=$VIEWER.resultType}
        {/foreach}
        | ({templateLink id=71 text="Edit"})
    </div>
    <div>&nbsp;</div>
    <div class="bigTitle">{if $VIEWER.resultType == 'View' }View{else}Add to{/if} Playlist: {$VIEWER.playlist.name}</div>
    <br style="&7b;clear:both;&7c;" />
    <form name="dpsPlaylistSearchForm" method="post" action="{$CONFIG.general.siteRoot}" style="float:left">
        <input type="hidden" name="formName" value="dpsPlaylistSearchForm" />
        <input type="hidden" name="moduleName" value="DPS" />
        <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
        <input type="hidden" name="dpsPlaylistID" value="{$VIEWER.playlist.id}" />
        <input type="hidden" name="dpsResultType" value="Search" /> 
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
	<div style="float:left">&nbsp;or&nbsp;</div>
    <form name="dpsPlaylistViewForm" method="post" action="{$CONFIG.general.siteRoot}" style="float:left">
        <input type="hidden" name="formName" value="dpsPlaylistViewForm" />
        <input type="hidden" name="moduleName" value="DPS" />
        <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
        <input type="hidden" name="dpsPlaylistID" value="{$VIEWER.playlist.id}" />
        <input type="submit" name="dpsViewPlaylist" value="View {$VIEWER.playlist.name}"/>
        <input type="hidden" name="dpsResultType" value="View" /> 
    </form>
    <div style="clear:both" />
        {if $VIEWER.searchResult}
            <div class="sueplaylistInfo1">
                {if $VIEWER.sortType == "artist"}
                    Sort by artist
                {else}
                    {templateLink id=$VIEWER.templateID text="Sort by artist"
                        _dpsSortType="artist" _dpsSearchType=$VIEWER.searchType
                            _dpsSearchVal=$VIEWER.searchValue
                            _dpsResultType=$VIEWER.resultType}
                {/if}
                | 
                {if $VIEWER.sortType == "title"}
                    Sort by title
                {else}
                    {templateLink id=$VIEWER.templateID text="Sort by title"
                        _dpsSortType="title" _dpsSearchType=$VIEWER.searchType
                            _dpsSearchVal=$VIEWER.searchValue
                            _dpsResultType=$VIEWER.resultType}
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
                <input type="hidden" name="dpsResultType" value="{$VIEWER.resultType}" /> 
                {if $VIEWER.searchValue != ""}
                    <input type="hidden" name="dpsSearchVal" value="{$VIEWER.searchValue}" />
                    <input type="hidden" name="dpsSearchType" value="{$VIEWER.searchType}" />
                {/if}
                <input type="hidden" name="dpsPlaylistID" value="{$VIEWER.playlist.id}" />
                <table class="sueviewplaylist">
                    <tr>
                        {if Access_EditTrack}<th></th>{/if}
		                <th>Playlisted?</th>
                        <th>Artist</th><th>Title</th><th>Length</th><th>30s Preview</th>
                    </tr>
                    {foreach from=$VIEWER.searchResult item=track}
                        <tr>
                            {if Access_EditTrack}
                                <th>{templateLink id="37" text="<img class='musicSearchTableTh' src='DPS/images/blackExpand.gif'>" _trackID=$track.id}</th>
                            {/if}
                            <td>
                                {if $track.playlist == 't'}
                                    <input type="checkbox"
                                    name="checkbox_{$track.searchNumber}" checked>
                                    <input type="hidden"
                                    name="trackVal_{$track.searchNumber}" value="on">
                                {else}
                                    <input type="checkbox"
                                    name="checkbox_{$track.searchNumber}">
                                    <input type="hidden"
                                    name="trackVal_{$track.searchNumber}" value="off">
                                {/if}
                                <input type="hidden" name="trackID_{$track.searchNumber}" value="{$track.id}">
                            </td>
                            <td>{$track.artist}</td>
                            <td>{templateLink id="10" text=$track.title _trackID=$track.id}</td>
                            <td>{$track.length}</td>
                            <td>{templateLink id="18" text="Preview" _trackID=$track.id}</td>
                        </tr>
                    {/foreach}
                </table>
                <div class="sueplaylistpage">
                    {if $VIEWER.resultType == "View" or $VIEWER.searchValue != ""}
                        Page: 
                        {foreach from=$VIEWER.pages item=page}
                            | {templateLink id=$VIEWER.templateID text=$page
                                _dpsSearchPage=$page
                                    _dpsSearchVal=$VIEWER.searchValue
                                    _dpsSearchType=$VIEWER.searchType
                                    _dpsResultType=$VIEWER.resultType}
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
	</div>
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
