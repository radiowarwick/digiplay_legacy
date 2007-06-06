<html>
	<head>
		<title>RaW Digiplay Manager</title>
		<link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
	</head>
	<body>
		<div class="centreContainer">
			<div class="frame_bottom">
				<div class="frame_musicsidebar">
					<!--<img class="frame_sidebarlogo" src="DPS/images/homenavadmin.png" alt="Admin">--><br>
					<div class="frame_sidebarmusic">{templateLink id="31" text="Music Library"}</div>
					<div class="frame_sidebarshow">{templateLink id="34" text="Show Planning"}</div>
					<div class="frame_sidebarsue">{templateLink id="32" text="Sue Stamp"}</div>
					<div class="frame_sidebarstudio">{templateLink id="33" text="Studio Cartwalls"}</div>
					<div class="frame_musicsidebarlinks"></div>
				</div>
				<div class="frame_rightside">
					<div class="frame_content">
					<br><br>
						{use func="CMS::showRegion" regionID=1}
					</div>
				</div>
				<div class="copyright">Copyright &#169 RaW 1251AM, 2006</div>
			</div>    
			<div class="frame_fullTitleBar">
				<div class="frame_fullTitleL">
					{templateLink id="12" text="<img class='home_title' src='DPS/images/hometitle.gif' alt='Raw Digiplay Manager'>"}
					<img class="home_titleOverlap" src="DPS/images/hometitlebgMid.png">
				</div>
				<div class="home_titleMid"></div>
				<div class="frame_titleR">
					{templateLink id="60" text="<img src='DPS/images/titleExit.gif' alt='Exit'>"}
					{templateLink id="21" text="<img src='DPS/images/titleHelp.gif' alt='Help'>"}
					{if $VIEWER.Admin == 't'}
					{templateLink id="1" text="<img src='DPS/images/titleAdmin.gif' alt='Admin'>"}
					{/if}
				</div>
			</div>
		</div>
	</body>
</html>
