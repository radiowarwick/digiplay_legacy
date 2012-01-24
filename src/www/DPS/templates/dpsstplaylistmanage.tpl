{include file="rfile:dpsstudiotopframe.tpl" title="Digiplay Manager" access_playlist='t' studio=$VIEWER.studioAccess}
        {if $VIEWER.Action == "Add"}
            <div class="bigTitle">Create Playlist</div>
            <div style="clear:both">&nbsp;</div>
            <div style="text-align:center">
                <form name="dpsPlaylistManageAddForm" method="post" action="{$CONFIG.general.siteRoot}">
                    <input type="hidden" name="formName" value="dpsPlaylistManageAddForm" />
                    <input type="hidden" name="moduleName" value="DPS" />
                    <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
                    <input type="hidden" name="dpsAction" value="View" />
                    
                    Playlist Name:
                    <input type="text" name="playlistName" value="" />
                    <br/><br/>
                    <input type="submit" name="add" value="Add">
                    &nbsp;&nbsp;
                    <input type="reset" name="reset" value="Reset" />
                    &nbsp;&nbsp;
                    <input type="submit" name="cancel" value="Cancel">
                </form>
            </div>
        {elseif $VIEWER.Action == "Rename"}
            <div class="bigTitle">Rename Playlist</div>
            <div style="clear:both">&nbsp;</div>
            <div style="text-align:center">
                <form name="dpsPlaylistManageRenameForm" method="post" action="{$CONFIG.general.siteRoot}">
                    <input type="hidden" name="formName" value="dpsPlaylistManageRenameForm" />
                    <input type="hidden" name="moduleName" value="DPS" />
                    <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
                    <input type="hidden" name="dpsAction" value="View" />
                    
                    Playlist Name:
                    <input type="text" name="playlistName" value="{$VIEWER.playlist.name}" />
                    <input type="hidden" name="playlistID" value="{$VIEWER.playlist.id}" />
                    <br/><br/>
                    <input type="submit" name="rename" value="Rename">
                    &nbsp;&nbsp;
                    <input type="reset" name="reset" value="Reset" />
                    &nbsp;&nbsp;
                    <input type="submit" name="cancel" value="Cancel">
                </form>
            </div>
        {elseif $VIEWER.Action == "Delete"}
            <div class="bigTitle">Delete Playlist</div>
            <div style="clear:both">&nbsp;</div>
            <div style="text-align:center">
                Are you sure you want to delete "{$VIEWER.playlist.name}"?
                <br/><br/>
                <form name="dpsPlaylistManageDeleteForm" method="post" action="{$CONFIG.general.siteRoot}">
                    <input type="hidden" name="formName" value="dpsPlaylistManageDeleteForm" />
                    <input type="hidden" name="moduleName" value="DPS" />
                    <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
                    <input type="hidden" name="dpsAction" value="View" />

                    <input type="hidden" name="playlistID" value="{$VIEWER.playlist.id}" />
                    <input type="submit" name="yes" value="Yes">
                    &nbsp;&nbsp;
                    <input type="submit" name="no" value="No">
                </form>
            </div>
        {else}
            <div class="bigTitle">Edit Playlists</div>
            <div style="text-align:right;padding-right:10px;padding-bottom:5px;">
                {templateLink id=$VIEWER.templateID text="Add A New Playlist" _dpsAction="Add" _dpsPlaylistID=$playlist.id}
            </div>
            <div style="text-align:center"/>
            <table class="sueviewplaylist" style="width:auto;min-width:60%;margin-left:auto;margin-right:auto;">
               <tr>
                    <th>Playlist</th><th>Tracks</th>
                    <th>Rename</th><th>Delete</th>
                </tr>
                {foreach from=$VIEWER.playlists item=playlist}
                    <tr>
                        <td>{$playlist.name}</td>
                        <td>{$playlist.count}</td>
                        <td>{templateLink id=$VIEWER.templateID text="Rename" _dpsAction="Rename" _dpsPlaylistID=$playlist.id}</td>
                        <td>{templateLink id=$VIEWER.templateID text="Delete" _dpsAction="Delete" _dpsPlaylistID=$playlist.id}</td>
                    </tr>
                {/foreach}
            </table>
            </div>
        {/if}
        <br style="&7b;clear:both;&7c;" />
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
