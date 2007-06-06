{include file="rfile:dpsmusictopframe.tpl" title="RaW Digiplay Manager" RequestTrack=$VIEWER.RequestTrack}
	    <div class="bigTitle">Track Details</div>
	    <div class="rightLinks">{templateLink id=20 text="Go back to search screen"}</div>
	    {foreach from=$VIEWER.tracksDetails item=trackDetails}
	    <hr style=&7b;clear:both;&7c;>
	    <div class="musicTrackHolder">
	      <div class="musicTrackDetailsL">
		<table class="musicShowTrackInfo">
		  <tr><th>Artist(s)</th><td>
		    {foreach from=$trackDetails.artist item=artist}
		      {$artist}<br />
		    {/foreach}
		  </td></tr>
		  <tr><th>Title</th><td>{$trackDetails.title}</td></tr>
		  <tr><th>Album</th><td>{$trackDetails.album}</td></tr>
		  <tr><th>Year</th><td>{$trackDetails.music_released}</td></tr>
		  <tr><th>Length</th><td>{$trackDetails.length}</td></tr>
		  <tr><th>Keywords</th><td>
		    {foreach from=$trackDetails.keywords item=keyword}
		      {$keyword}<br />
		    {/foreach}
		  </td></tr>
		  <tr><th>Reclib</th><td>{$trackDetails.reclibid}</td></tr>
		  <tr><th>Origin</th><td>{$trackDetails.origin}</td></tr> 
		  <tr><th>Flagged</th><td>
		    {if $trackDetails.flagged == 't' }
		      Yes
		    {else}
		      No
		    {/if}
		  </td></tr>
		  <tr><th>Censored</th><td>
		    {if $trackDetails.censor == 't' }
		      Yes
		    {else}
		      No
		    {/if}
		  </td></tr>
		  <tr><th>Playlisted</th><td>
		    {if $trackDetails.sustainer == 't' }
		      Yes
		    {else}
		      No
		    {/if}
		  </td></tr>
		  <tr><th>Notes</th>
		    <td>
		      {foreach from=$trackDetails.comments item=comment}
		      {$comment.comment}
		      <div class="musicTrackCommentTools">
			Added by {$comment.username} 
			{if $comment.username == $AUTH.user}
			{if $VIEWER.Access_CommentTrack == 't'}
			{templateLink id=$VIEWER.templateID text="delete"
			_formName="dpsMusicDeleteCommentForm"
			_moduleName="DPS"
			_commentID=$comment.id
			_trackID=$DATA.trackID}
			{/if}
			{/if}
		      </div>
		      <hr>	
		      {/foreach}
		    </td>
		  </tr>
		</table>
	      </div>
	      <div class="musicTrackDetailsR">
		{if $VIEWER.Access_EditTrack}
		{templateLink id="37" text="Edit this track's details" _trackID=$trackDetails.id}<br>
		{/if}
		{if $VIEWER.Access_CommentTrack == 't'}
		<b>Write note about track</b>
		<form name="dpsMusicCommentForm" method="post" action="{$CONFIG.general.siteRoot}">
		  <input type="hidden" name="formName" value="dpsMusicCommentForm" />
		  <input type="hidden" name="moduleName" value="DPS" />
		  <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
		  <input type="hidden" name="audioID" value="{$trackDetails.id}" />
		  <input type="hidden" name="trackID" value="{$DATA.trackID}" />
		  <textarea name="comment" rows="5" cols="34"></textarea><br>
		  <input type="Submit" value="Submit">
		</form>
		{else}
		<b>You do not haver permission to add comments to tracks.</b>
		{/if}
	      </div>
	    </div>
	    {/foreach} 
	    <br style=&7b;clear:both;&7c;>
{include file="rfile:dpsmusicbottomframe.tpl" Admin=$VIEWER.Admin}
