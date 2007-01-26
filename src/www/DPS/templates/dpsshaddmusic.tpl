<html>
  <head>
    <title>Add Music</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
  </head>
  <body>
    {if $VIEWER.error != ''}
      {$VIEWER.error}
    {else}
    <div class='alignleft'>
    <div class='bigTitle'>Select Track</div>
		<div class='subTitle'>Showplan: {$VIEWER.show.name}, Item: {$VIEWER.item.position} 
    <hr>
    <div class=''>
	    Search for tracks
	    <form name="dpsMusicSearchForm" method="post" action="{$CONFIG.general.siteRoot}">
	      <input type="hidden" name="formName" value="dpsMusicSearchForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
				<input type="hidden" name="itemID" value="{$VIEWER.item.id}" />
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
    </div>
		<hr>
		<div>
	    <div class="musicResultSorts">
	      {if $VIEWER.sortType == "artist"}
	      Sort by artist
	      {else}
	      {templateLink id=$VIEWER.templateID text="Sort by artist" _dpsSortType="artist" _dpsSearchType=$VIEWER.searchType _dpsSearchVal=$VIEWER.searchValue _itemID=$VIEWER.item.id}
	      {/if}
	      | 
	      {if $VIEWER.sortType == "title"}
	      Sort by title
	      {else}
	      {templateLink id=$VIEWER.templateID text="Sort by title" _dpsSortType="title" _dpsSearchType=$VIEWER.searchType _dpsSearchVal=$VIEWER.searchValue _itemID=$VIEWER.item.id}
	      {/if}
	    </div>
			<div class="musicSearchPages">
				{if $VIEWER.searchValue != ""}
				Page: 
				{foreach from=$VIEWER.pages item=page}
				| {templateLink id=$VIEWER.templateID text=$page _dpsSearchPage=$page _dpsSearchVal=$VIEWER.searchValue _dpsSearchType=$VIEWER.searchType _itemID=$VIEWER.item.id}
				{/foreach} 
				|
				{/if}
			</div>
			<table class="musicSearchTable" cellspacing=0>
			 	<tr>
					<th>Artist</th><th>Title</th><th>Swearing?</th><th>Select</th>
				</tr>
				{foreach from=$VIEWER.searchResult item=track}
				<tr>
		  		<td>{$track.artist}</td>
		  		<td>{$track.title}</td>
		  		<td>
		    		{if $track.censor == 't'}
		    		<div class="musicCensoredLable">Censored</div>
		    		{elseif $track.flagged == 't'}
		    		<div class="musicPossibleSwearLable">Possibly</div>
		    		{else}
						No
						{/if}
					</td>
					<td>{templateLink id=70 text="Select" _formName="dpsUserAudioShow" _moduleName="DPS" _audioID=$track.id _itemID=$VIEWER.item.id}</td>
				</tr>
				{/foreach}
			</table>
			<div class="musicSearchPages">
				{if $VIEWER.searchValue != ""}
				Page: 
				{foreach from=$VIEWER.pages item=page}
				| {templateLink id=$VIEWER.templateID text=$page _dpsSearchPage=$page _dpsSearchVal=$VIEWER.searchValue _dpsSearchType=$VIEWER.searchType _itemID=$VIEWER.item.id}
				{/foreach} 
				|
				{/if}
			</div>
		</div>
    {/if}
  </body>
</html>
