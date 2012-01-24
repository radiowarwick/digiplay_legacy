{include file="rfile:dpssuetopframe.tpl" title="Digiplay Manager" nexttrack=$VIEWER.sueNextTrack Access_EditSue=$VIEWER.Access_EditSue Access_ViewSue=$VIEWER.Access_ViewSue Access_ViewSue='t'}
	    <div class="bigTitle">Sue Stamp's Stats</div>
	    <table class="suestats">
	      <tr><th>Tracks currently on Sue Playlist</th><td>{$VIEWER.suePlaylistTracks}</td></tr>
	      <tr><th>Time currently on Sue Playlist</th><td>{$VIEWER.suePlaylistLength}</td></tr>
	      <tr><th>Total tracks currently on system</th><td>{$VIEWER.storedTracks}</td></tr>
	      <tr><th>Total time currently on system</th><td>{$VIEWER.lengthOfTracks}</td></tr>
	    </table>
	    <br />
	    <div class="bigTitle">Coming up on Sue</div>
	    <table class="suestats">
	      <tr><th>Title</th><th>Artist</th></tr>
	      {foreach from=$VIEWER.suePlaylist item=track}
	      		<tr><td>{templateLink id="10" text=$track.title _trackID=$track.id}</td><td>{$track.artist}</td></tr>
	      {/foreach}
	    </table>
{include file="rfile:dpsmusicbottomframe.tpl" Admin=$VIEWER.Admin}
