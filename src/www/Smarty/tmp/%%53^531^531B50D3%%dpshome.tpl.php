<?php /* Smarty version 2.6.14, created on 2007-01-22 10:18:02
         compiled from rfile:/var/www/DPS/templates/dpshome.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpshome.tpl', 10, false),array('function', 'use', 'rfile:/var/www/DPS/templates/dpshome.tpl', 94, false),)), $this); ?>
<html>
  <head>
    <title>RaW Digiplay Manager</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
  </head>
  <body>
  <div class="centreContainer">
  <div class="home_titleBar">
    <div class="home_titleL">
      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '47','text' => "<img class='home_title' src='DPS/images/hometitle.gif' alt='Raw Digiplay Manager'>"), $this);?>

      <img class="home_titleOverlap" src="DPS/images/hometitlebgMid.png">
    </div> 
    <div class="home_titleMid">
    </div>
    <div class="home_titleR">
      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '71','text' => "<img src='DPS/images/hometitleExit.gif' alt='Exit'>"), $this);?>

      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '58','text' => "<img src='DPS/images/hometitleHelp.gif' alt='Help'>"), $this);?>

      <?php if ($this->_tpl_vars['VIEWER']['Admin']): ?>
      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '2','text' => "<img src='DPS/images/hometitleAdmin.gif' alt='Admin'>"), $this);?>

      <?php endif; ?>
    </div>
  </div>  
  <div class="home_navigateBar">
    <div class="home_musicNav">
      <div class="home_musicNavTitle">
	<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '76','text' => "<img src='DPS/images/homenavmusic.png' alt='Music Library'>"), $this);?>

      </div>
      <div class="home_musicNavDesc">
	<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '76','text' => 'Search for and edit music'), $this);?>

      </div>
    </div>
    <div class="home_showNav">
      <div class="home_showNavTitle">
	<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '79','text' => "<img src='DPS/images/homenavshow.png' alt='Show Planning'>"), $this);?>

      </div>
      <div class="home_showNavDesc">
	<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '79','text' => 'Plan and schedule your show'), $this);?>

      </div>
    </div>
    <div class="home_sueNav">
      <div class="home_sueNavTitle">
	<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '77','text' => "<img src='DPS/images/homenavsue.png' alt='Sue Stamp'>"), $this);?>

      </div>
      <div class="home_sueNavDesc">
	<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '77','text' => 'view and edit Sue playlist'), $this);?>

      </div>
    </div>
    <div class="home_studioNav">
      <div class="home_studioNavTitle">
	<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '78','text' => "<img src='DPS/images/homenavstudio.png' alt='Studio Cartwalls'>"), $this);?>

      </div>
      <div class="home_studioNavDesc">
	<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '78','text' => 'Edit your jingles'), $this);?>

      </div>
    </div>
  </div>
  <div class="home_content">
    <div class="home_contentL">
      <div class="home_userBox">
	<b>Logged in as</b> <?php echo $this->_tpl_vars['AUTH']['user']; ?>
<br>
        <!--<a href="/">Change user settings</a>--><br>
        last logged in: <?php echo $this->_tpl_vars['VIEWER']['userLastLogin']; ?>

      </div>    
      <div class="home_statsBox">
        <img src="DPS/images/homelivestats.gif" alt="Live Statistics"><br>
	<table class="home_stats">
	  <tr><th>Tracks stored:</th><td><?php echo $this->_tpl_vars['VIEWER']['storedTracks']; ?>
</td></tr>
	  <tr><th>Length of tracks:</th><td><?php echo $this->_tpl_vars['VIEWER']['lengthOfTracks']; ?>
</td></tr>
	  <tr><th>Sue playlist:</th><td><?php echo $this->_tpl_vars['VIEWER']['suePlaylistTracks']; ?>
</td></tr>
	  <tr><th>Length of playlist:</th><td><?php echo $this->_tpl_vars['VIEWER']['suePlaylistLength']; ?>
</td></tr>
	</table>
      </div>
    </div>
    <div class="home_contentMid">
      <div class="home_sueBox">
        <img src="DPS/images/homesueplaylist.gif" alt="Sue Playlist"><br>
	<table class="home_playlist">
	  <tr><th>Last track:</th><td><?php echo $this->_tpl_vars['VIEWER']['sueLastTrack']['artist']; ?>
 - <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '55','text' => $this->_tpl_vars['VIEWER']['sueLastTrack']['title'],'_trackID' => $this->_tpl_vars['VIEWER']['sueLastTrack']['id']), $this);?>
</td></tr>
	  <tr><th>Next track:</th><td><?php echo $this->_tpl_vars['VIEWER']['sueNextTrack']['artist']; ?>
 - <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '55','text' => $this->_tpl_vars['VIEWER']['sueNextTrack']['title'],'_trackID' => $this->_tpl_vars['VIEWER']['sueNextTrack']['id']), $this);?>
</td></tr>
	</table>
	<!--<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '47','text' => 'Further playlist'), $this);?>
--><br>
      </div>
      <div class="home_scheduleBox">
        <img src="DPS/images/homerawschedule.gif" alt="RaW Schedule"><br>
	<table class="home_schedule">
	  <tr><th>Current Show:</th><td><?php echo $this->_tpl_vars['VIEWER']['scheduleCurrent']['name']; ?>
</td></tr>
	  <tr><th>Last Show:</th><td><?php echo $this->_tpl_vars['VIEWER']['scheduleLast']['name']; ?>
</td></tr>
	  <tr><th>Next Show:</th><td><?php echo $this->_tpl_vars['VIEWER']['scheduleNext']['name']; ?>
</td></tr>
	</table>
	<!--<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '47','text' => 'Full schedule'), $this);?>
-->
      </div>
    </div>
    <div class="home_featuresBox">
		<?php echo $this->_plugins['function']['use'][0][0]->SMARTY_use(array('func' => "CMS::showRegion",'regionID' => 8), $this);?>

    <!--  <b>Other Features</b><br>
      <a href="https://www.radio.warwick.ac.uk/digilog">Audio Archive</a><br>
      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '59','text' => 'Requested Tracks'), $this);?>
<br>
      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '52','text' => 'Censored Tracks'), $this);?>
<br>
    </div>-->
  </div>
  <div class="copyright">Copyright &#169 RaW 1251AM, 2006</div>
  </div>
  </body>
</html>