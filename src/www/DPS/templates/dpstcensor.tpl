{include file="rfile:dpsmusictopframe.tpl" title="RaW Digiplay Manager" RequestTrack=$VIEWER.RequestTrack}
	    <div class="bigTitle">Censored Tracks</div>
	    <div class="subTitle">
	      {$VIEWER.flagNum} tracks have been recommened for censorship<br>
	      {$VIEWER.censorNum} tracks have been censored
	    </div>
	    <hr \>
	    {if $VIEWER.flagNum}
	    <div class="musicCensorInfo1">Recommended for censorship</div>
	    <div class="musicCensorInstructions1">Select tick-box to censor</div>
			{if $VIEWER.CensorTrack == 't'}
	    <form name='dpsTrackAddCensorForm'method="post" action="{$CONFIG.general.siteRoot}">
	      <input type="hidden" name="formName" value="dpsTrackAddCensorForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
			{/if}
	    <div class="musicCensorRecommend">
	      <table class="musicCensorRecommend">
					{foreach from=$VIEWER.flaggedTracks item=ftrack}
					<tr>
		  			<td>{$ftrack.artist}</td>
		  			<td>{$ftrack.title}</td>
		  			<td>{templateLink id="18" text="Preview" _trackID=$ftrack.id}</td>
		  			{if $VIEWER.CensorTrack == 't'}
		  			<td>
		    			<input type="checkbox" name="checkbox_{$ftrack.searchNumber}">
		    			<input type="hidden" name="trackID_{$ftrack.searchNumber}" value="{$ftrack.id}">
		  			</td>
		  			{/if}
					</tr>
					{/foreach}
	      </table> 
	    </div>
	    <div>
	    	<div class="musicCensorInstructions2">
	      	Censored tracks cannot be played through Digiplay between <b>7am to 9pm</b>
	    	</div>
				{if $VIEWER.CensorTrack == 't'}
	    	<div class="musicCensorCMB1">
	      	<input type="submit" name="submit" value="Submit">
	      	<input type="reset" value="Reset"><br>
	      	<input type="submit" name="submit" value="Clear List">
	    	</div> 
	    	<input type="hidden" name="resultCount" value="{$VIEWER.flagNum}">
			{/if}
	    </div>
			{if $VIEWER.CensorTrack == 't'}
	    </form>
			{/if}
	    <br style="&7b;clear:both&7c;" \>
	    {/if}
	    {if $VIEWER.censorNum}
	    <div class="musicCensorInfo1">Censored tracks</div>
	    <div class="musicCensorInstructions1">Select tick-box to remove from list</div>
			{if $VIEWER.CensorTrack == 't'}
	    <form name='dpsTrackCensorForm' method="post" action="{$CONFIG.general.siteRoot}">
	      <input type="hidden" name="formName" value="dpsTrackCensorForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
			{/if}
	    <div class="musicCensored">
	      <table class="musicCensored">
					{foreach from=$VIEWER.censoredTracks item=ctrack}
					<tr>
		  			<td>{$ctrack.artist}</td>
		  			<td>{$ctrack.title}</td>
		  			<td>{templateLink id="18" text="Preview" _trackID=$ctrack.id}</td>
		  			{if $VIEWER.CensorTrack == 't'}
		  			<td>
		    			<input type="checkbox" name="checkbox_{$ctrack.searchNumber}">
		    			<input type="hidden" name="trackID_{$ctrack.searchNumber}" value="{$ctrack.id}">
		  			</td>
		  			{/if}
					</tr>
					{/foreach}
	      </table>
	      <input type="hidden" name="resultCount" value="{$VIEWER.censorNum}">
	    </div>
			{if $VIEWER.CensorTrack == 't'}
	    <div class="musicCensorCMB2">
	      <input type="submit" name="submit" value="Submit">
	      <input type="reset" value="Reset"><br>
	    </div>
	    </form>
			{/if}
	    {/if}
	  <br style="&7b;clear:both&7c;" \> 
{include file="rfile:dpsmusicbottomframe.tpl" Admin=$VIEWER.Admin}
