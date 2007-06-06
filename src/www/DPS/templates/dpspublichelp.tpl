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
    <div class="home_titleMid">
    </div>
    <div class="home_titleR">
			{if $VIEWER.Guest == 't'}
      {templateLink id="60" text="<img src='DPS/images/hometitleExit.gif' alt='Exit'>"}
      {templateLink id="59" text="<img src='DPS/images/hometitleHelp.gif' alt='Help'>"}
			{else}
      {templateLink id="60" text="<img src='DPS/images/hometitleExit.gif' alt='Exit'>"}
      {templateLink id="21" text="<img src='DPS/images/hometitleHelp.gif' alt='Help'>"}
			{/if}
      {if $VIEWER.Admin}
      {templateLink id="1" text="<img src='DPS/images/hometitleAdmin.gif' alt='Admin'>"}
      {/if}
    </div>
  </div>
	{use func="CMS::showRegion" regionID=6}
  <div class="copyright">Copyright &#169 RaW 1251AM, 2006</div>
  </div>
  </body>
</html>
