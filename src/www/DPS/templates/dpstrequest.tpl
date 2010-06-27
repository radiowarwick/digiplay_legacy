{include file="rfile:dpsmusictopframe.tpl" title="RaW Digiplay Manager" RequestTrack=$VIEWER.RequestTrack}
	    <div class="bigTitle">Requested Tracks</div>
	    <div class="subTitle">
	      {$VIEWER.requestedNum} track(s) have been requested
	    </div>
	    <hr \>
	    {if $VIEWER.requestedTracks}
	    {if $VIEWER.RemoveRequestTrack}
	    <form name="dpsMusicRemoveRequestForm" method="post" action="{$CONFIG.general.siteRoot}">
	      <input type="hidden" name="formName" value="dpsMusicRemoveRequestForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
	    {/if}
	      <div class="musicRequested">
		<table class="musicRequested">
		  <tr>
		    <th>Artist</th>
		    <th>Title</th>
		    <th>Date Requested</th>
		    <th>User</th>
		    {if $VIEWER.RemoveRequestTrack}
		    <th>Remove</th>
		    {/if}
		  </tr>
		  {foreach from=$VIEWER.requestedTracks item=rtrack}
		  <tr>
		    <td>{$rtrack.artistname}</td>
		    <td>{$rtrack.name}</td>
		    <td>{$rtrack.rtime}</td>
		    <td>{$rtrack.user}</td>
		    {if $VIEWER.RemoveRequestTrack}
		    <td>
		      <input type="checkbox" name="track{$rtrack.number}" value="on">
		      <input type="hidden" name="track{$rtrack.number}id" value="{$rtrack.id}">
		    </td>
		    {/if}
		  </tr>
		  {/foreach}
		</table> 
	      </div>
	    {if  $VIEWER.RemoveRequestTrack}
	      <input type="hidden" name="tracknum" value="{$VIEWER.requestedNum}">
	      <input type="submit" name="submit" value="Remove Selected">
	    </form>
	    {/if}
	    {/if}
{include file="rfile:dpsmusicbottomframe.tpl" Admin=$VIEWER.Admin}
