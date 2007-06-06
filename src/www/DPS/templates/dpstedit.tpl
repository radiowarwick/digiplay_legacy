{include file="rfile:dpsmusictopframe.tpl" title="RaW Digiplay Manager"  RequestTrack=$VIEWER.RequestTrack}
	    <div class="musicTitle">Edit Track Details</div>
	    {if $VIEWER.searchValue}
	    <div class="musicTrackDetailsLinks">{templateLink id=20 text="Go back to the search screen" _dpsSearchVal=$VIEWER.searchValue _dpsSearchType=$VIEWER.searchType _dpsSearchPage=$VIEWER.page}</div>
	    {/if}
	    <div class="musicTrackHolder">
	      <form name="dpsEditTrackForm" method="post" action="{$CONFIG.general.siteRoot}">
	      <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
	      <input type="hidden" name="trackID" value="{$VIEWER.trackID}" />
	      <input type="hidden" name="formName" value="dpsEditTrackForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <div class="musicTrackDetailsL">
		<table class="musicShowTrackInfo">
		  <tr>
		    <th>Artist</th>
		    <td>
		      {if $VIEWER.trackDetails.artist}
		      Artists:<br />
		      {/if}
		      {foreach from=$VIEWER.trackDetails.artist item=artist}
		      <input type="text" name="artist{$artist.number}" value="{$artist.name}">
		      <input type="hidden" name="artist{$artist.number}id" value="{$artist.id}"><br />
		      {/foreach}
		      New Artist :<br /><input type="text" name="artist{$VIEWER.artistNum}" value="">
		      <input type="hidden" name="artistnum" value="{$VIEWER.artistNum}">
		    </td>
		  </tr>
		  <tr><th>Title</th><td>{if $ERRORS.title}<div class='frame_musicboxerror'>{$ERRORS.title}</div>{/if}<input type="text" name="title" value="{$VIEWER.trackDetails.title}"></td></tr>
		  <tr><th>Album</th><td><input type="text" name="album" value="{$VIEWER.trackDetails.album}"></td></tr>
		  <tr><th>Year</th><td><input type="text" name="released" value="{$VIEWER.trackDetails.music_released}"></td></tr>
		  <tr><th>Length</th><td>{$VIEWER.trackDetails.length}</td></tr>
		  <tr>
		    <th>Keywords</th>
		    <td>
		      {if $VIEWER.trackDetails.keywords}
		      Keywords:<br />
		      {/if}
		      {foreach from=$VIEWER.trackDetails.keywords item=keyword}
		      <input type="text" name="keyword{$keyword.number}" value="{$keyword.name}">
		      <input type="hidden" name="keyword{$keyword.number}id" value="{$keyword.id}"><br />
		      {/foreach}
		      New Keyword :<br /><input type="text" name="keyword{$VIEWER.keywordNum}" value="">
		      <input type="hidden" name="keywordnum" value="{$VIEWER.keywordNum}">
		    </td>
		  </tr>
		  <tr><th>Reclib</th><td><input type="text" name="reclib" value="{$VIEWER.trackDetails.reclibid}"></td></tr>
		  <tr><th>Origin</th><td>{if $ERRORS.origin}<div class='frame_musicboxerror'>{$ERRORS.origin}</div>{/if}<input type="text" name="origin" value="{$VIEWER.trackDetails.origin}"></td></tr>
		  <tr><th>Censored</th><td>
		    {if $VIEWER.trackDetails.censor == 't'}
		      Censored
		    {elseif $VIEWER.trackDetails.flagged == 't'}
		      Flagged
		    {else}
		      No
		    {/if}
		  </td></tr>
		  {if $VIEWER.SueEdit}
		  <tr><th>Playlisted</th><td>
		    {if $VIEWER.trackDetails.sustainer == 't'}
		    <input type="checkbox" name=playlist checked>
		    {else}
		    <input type="checkbox" name="playlist">
		    {/if}
		  </td></tr>
		  {/if}
		  <tr><th>Notes</th>
		    <td>
		      {foreach from=$VIEWER.trackDetails.comments item=comment}
		      {$comment.comment}
		      <div class="musicTrackCommentTools">
			Added by {$comment.username} 
			{if $comment.username == $AUTH.user}
			{templateLink id=$VIEWER.templateID text="delete"
			_formName="dpsMusicDeleteCommentForm"
			_moduleName="DPS"
			_commentID=$comment.id
			_trackID=$DATA.trackID}
			{/if}
		      </div>
		      <hr>	
		      {/foreach}
		    </td>
		  </tr>
		</table>
	      </div>
	      <div class="musicTrackDetailsR">

		<b>Write note about track</b>
		<textarea name="comment" rows="5" cols="34"></textarea><br>
		<input type="Submit" value="Submit">
	      </div>
	      </form>
	    </div>
	    <br style=&7b;clear:both;&7c;>
{include file="rfile:dpsmusicbottomframe.tpl" Admin=$VIEWER.Admin}
