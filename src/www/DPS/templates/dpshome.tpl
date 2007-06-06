<html>
	<head>
		<title>RaW Digiplay Manager</title>
		<link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
	</head>
	<body>
		<div class="centreContainer">
			<div class="home_titleBar">
				<div class="home_titleL">
					{templateLink id="12" text="<img class='home_title' src='DPS/images/hometitle.gif' alt='Raw Digiplay Manager'>"}
					<img class="home_titleOverlap" src="DPS/images/hometitlebgMid.png">
				</div> 
				<div class="home_titleMid"></div>
				<div class="home_titleR">
					{templateLink id="60" text="<img src='DPS/images/hometitleExit.gif' alt='Exit'>"}
					{templateLink id="21" text="<img src='DPS/images/hometitleHelp.gif' alt='Help'>"}
					{if $VIEWER.Admin}
					{templateLink id="1" text="<img src='DPS/images/hometitleAdmin.gif' alt='Admin'>"}
					{/if}
				</div>
			</div>
			<div class="home_navigateBar">
				<div class="home_musicNav">
					<div class="home_musicNavTitle">
			{templateLink id="31" text="<img src='DPS/images/homenavmusic.png' alt='Music Library'>"}
					</div>
					<div class="home_musicNavDesc">
			{templateLink id="31" text="Search for and edit music"}
					</div>
				</div>
				<div class="home_showNav">
					<div class="home_showNavTitle">
			{templateLink id="34" text="<img src='DPS/images/homenavshow.png' alt='Show Planning'>"}
					</div>
					<div class="home_showNavDesc">
			{templateLink id="34" text="Plan and schedule your show"}
					</div>
				</div>
				<div class="home_sueNav">
					<div class="home_sueNavTitle">
			{templateLink id="32" text="<img src='DPS/images/homenavsue.png' alt='Sue Stamp'>"}
					</div>
					<div class="home_sueNavDesc">
			{templateLink id="32" text="view and edit Sue playlist"}
					</div>
				</div>
				<div class="home_studioNav">
					<div class="home_studioNavTitle">
			{templateLink id="33" text="<img src='DPS/images/homenavstudio.png' alt='Studio Cartwalls'>"}
					</div>
					<div class="home_studioNavDesc">
			{templateLink id="33" text="Edit your jingles"}
					</div>
				</div>
			</div>
			<div class="home_content">
				<div class="home_contentL">
					<div class="home_userBox">
						<b>Logged in as</b> {$AUTH.user}<br>
						<!--<a href="/">Change user settings</a>--><br>
						last logged in: {$VIEWER.userLastLogin}
					</div>
					<div class="home_statsBox">
						<img src="DPS/images/homelivestats.gif" alt="Live Statistics"><br>
						<table class="home_stats">
							<tr><th>Tracks stored:</th><td>{$VIEWER.storedTracks}</td></tr>
							<tr><th>Length of tracks:</th><td>{$VIEWER.lengthOfTracks}</td></tr>
							<tr><th>Sue playlist:</th><td>{$VIEWER.suePlaylistTracks}</td></tr>
							<tr><th>Length of playlist:</th><td>{$VIEWER.suePlaylistLength}</td></tr>
						</table>
					</div>
				</div>
				<div class="home_contentMid">
					<div class="home_sueBox">
						<img src="DPS/images/homesueplaylist.gif" alt="Sue Playlist"><br>
						<table class="home_playlist">
							<tr><th>Last track:</th><td>{$VIEWER.sueLastTrack.artist} - {templateLink id="10" text=$VIEWER.sueLastTrack.title _trackID=$VIEWER.sueLastTrack.id}</td></tr>
							<tr><th>Next track:</th><td>{$VIEWER.sueNextTrack.artist} - {templateLink id="10" text=$VIEWER.sueNextTrack.title _trackID=$VIEWER.sueNextTrack.id}</td></tr>
						</table>
						<!--{templateLink id="47" text="Further playlist"}--><br>
					</div>
					<div class="home_scheduleBox">
						<img src="DPS/images/homerawschedule.gif" alt="RaW Schedule"><br>
						<table class="home_schedule">
							<tr><th>Current Show:</th><td>{$VIEWER.scheduleCurrent.name}</td></tr>
							<tr><th>Last Show:</th><td>{$VIEWER.scheduleLast.name}</td></tr>
							<tr><th>Next Show:</th><td>{$VIEWER.scheduleNext.name}</td></tr>
						</table>
						<!--{templateLink id="47" text="Full schedule"}-->
					</div>
				</div>
				<div class="home_featuresBox">
					{use func="CMS::showRegion" regionID=8}
					<!--  <b>Other Features</b><br>
						<a href="https://www.radio.warwick.ac.uk/digilog">Audio Archive</a><br>
						{templateLink id="59" text="Requested Tracks"}<br>
						{templateLink id="52" text="Censored Tracks"}<br>
					</div>-->
			</div>
			<div class="copyright">Copyright &#169 RaW 1251AM, 2006</div>
		</div>
	</body>
</html>
