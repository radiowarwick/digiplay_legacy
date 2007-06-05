<html>
  <head>
    <title>{$title}</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
  </head>
  <body>
    <div class="centreContainer">
      <div class="frame_bottom">
	<div class="frame_suesidebar">
	  <img class="frame_sidebarlogo" src="DPS/images/homenavsue.png" alt="Sue Stamp">
	  <div class="frame_sidebarmusic">{templateLink id="31" text="Music Library"}</div>
	  <div class="frame_sidebarshow">{templateLink id="34" text="Show Planning"}</div>
	  <div class="frame_sidebarstudio">{templateLink id="33" text="Studio Cartwalls"}</div>
	  <div class="frame_suesidebarlinks">
	    {templateLink id="32" text="Information"}<br>
		{if Access_ViewSue}
	    {templateLink id="40" text="View Sue Playlist"}<br>
		{/if}
	    {if Access_EditSue}
	    {templateLink id="35" text="Add to Sue Playlist"}<br>
	    {/if}
		{if Access_SueStats}
	    {templateLink id="36" text="Sue Stamp's Statistics"}<br>
		{/if}
	  </div>
        </div>
        <div class="frame_rightside">
	  <div class="frame_suesearchbox">
	    {if $suesearchid == 40}
	    Search for tracks on Sue
	    {elseif $suesearchid == 35}
	    Search for tracks to add
	    {else}
	    Search for tracks
	    {/if}
	    <form name="dpsSueSearchForm" method="post" action="{$CONFIG.general.siteRoot}">
	      <input type="hidden" name="formName" value="dpsSueSearchForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      {if $suesearchid}
	      <input type="hidden" name="templateID" value="{$suesearchid}" />
	      {else}
	      <input type="hidden" name="templateID" value="40">
	      {/if}
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
		{if $VIEWER.searchType == "Album"}
		  <option value="Album" selected="selected">Album</option>
		{else}
		  <option value="Album">Album</option>
		{/if}
	      </select>
	      <input type="Submit" name="Search" value="Search">
	    </form>
          </div>
	  <div class="frame_suenextbox">
	    <b>Coming up soon:</b><br>
	    {$nexttrack.artist} - {templateLink id="10" text=$nexttrack.title _trackID=$nexttrack.id}<br>
          </div>

	  <div class="frame_content">
