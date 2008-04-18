<html>
	<head>
		<title>{$title}</title>
		<link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
	</head>
	<body>
		<div class="centreContainer">
			<div class="frame_bottom">
	<div class="frame_musicsidebar">
		<img class="frame_sidebarlogo" src="DPS/images/homenavmusic.png" alt="Music Library">
		<div class="frame_sidebarshow">{templateLink id="34" text="Show Planning"}</div>
		<div class="frame_sidebarsue">{templateLink id="32" text="Sue Stamp"}</div>
		<div class="frame_sidebarstudio">{templateLink id="33" text="Studio Audiowalls"}</div>
		<div class="frame_musicsidebarlinks">
			{templateLink id="31" text="Information"}<br>
			{templateLink id="20" text="Search tracks"}<br>
			{if $RequestTrack}
			{templateLink id="19" text="View requested tracks"}<br>
			{/if}
			{templateLink id="38" text="View censored tracks"}<br>
		</div>
				</div>
				<div class="frame_rightside">
		<div class="frame_musicsearchbox">
			Search for tracks
			<form name="dpsMusicSearchForm" method="post" action="{$CONFIG.general.siteRoot}">
				<input type="hidden" name="formName" value="dpsMusicSearchForm" />
				<input type="hidden" name="moduleName" value="DPS" />
				<input type="hidden" name="templateID" value="20" />
				{if $ERRORS.dpsSearchVal}
				<div class="frame_musicboxerror">{$ERRORS.dpsSearchVal}</div>
				{elseif $ERRORS.dpsSearchType}
				<div class="frame_musicboxerror">{$ERRORS.dpsSearchType}</div>
				{/if}
				<input type="text" name="dpsSearchVal" value="{$VIEWER.searchValue}">
				<select name="dpsSearchType">
				{if $VIEWER.searchType == "Both"}
					<option value="Both" selected="selected">All</option>
				{else}
					<option value="Both">All</option>
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
					<option selected="selected" value="Album">Album</option>
				{else}
					<option value="Album">Album</option>
				{/if}
				</select>
				<input type="Submit" name="Search" value="Search">
			</form>
		</div>

		<div class="frame_musicrequestbox">
			{if $RequestTrack}
			Can't find the track you're after?<br>
			<b>Request it</b>
			{if $ERRORS.artist}
			<div class="frame_musicboxerror">{$ERRORS.artist}</div>
			{elseif $ERRORS.title}
			<div class="frame_musicboxerror">{$ERRORS.title}</div>
			{/if}
			<form name="dpsMusicRequestForm" method="post" action="{$CONFIG.general.siteRoot}">
				<input type="hidden" name="formName" value="dpsMusicRequestForm" />
				<input type="hidden" name="moduleName" value="DPS" />
				<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
				<input type="text" name="artist" size=17 maxlength=50 value="Artist"> 
				<input type="text" name="title" size=17 maxlength=50 value="Title"><br>
				<input class="frame_musicrequestcmd" type="submit" value="Request"><br>
				{templateLink id="19" text="View requested tracks"}
			</form>
			{else}
				You do not have permission to request tracks.
			{/if}
					</div>
					<div class="frame_content">
