<?php /* Smarty version 2.6.14, created on 2006-09-25 13:32:45
         compiled from rfile:/var/www/toolkit/DPS/templates/dpshelp.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/toolkit/DPS/templates/dpshelp.tpl', 11, false),array('function', 'use', 'rfile:/var/www/toolkit/DPS/templates/dpshelp.tpl', 21, false),)), $this); ?>
<html>
  <head>
    <title>RaW Digiplay Manager</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
  </head>
  <body>
    <div class="centreContainer">
      <div class="frame_bottom">
	<div class="frame_musicsidebar">
	  <img class="frame_sidebarlogo" src="DPS/images/homenavadmin.png" alt="Admin">
	  <div class="frame_sidebarmusic"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '48','text' => 'Music Library'), $this);?>
</div>
	  <div class="frame_sidebarshow"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '47','text' => 'Show Planning'), $this);?>
</div>
	  <div class="frame_sidebarsue"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '61','text' => 'Sue Stamp'), $this);?>
</div>
	  <div class="frame_sidebarstudio"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '66','text' => 'Studio Cartwalls'), $this);?>
</div>
	  <div class="frame_musicsidebarlinks">
	  </div>
        </div>
        <div class="frame_rightside">
          <div class="frame_content">
	  <br><br>
	    <?php echo $this->_plugins['function']['use'][0][0]->SMARTY_use(array('func' => "CMS::showRegion",'regionID' => 1), $this);?>

	  </div>
        </div>
        <div class="copyright">Copyright &#169 RaW 1251AM, 2006</div>
      </div>    
      <div class="frame_fullTitleBar">
	<div class="frame_fullTitleL">
	  <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '47','text' => "<img class='home_title' src='DPS/images/hometitle.gif' alt='Raw Digiplay Manager'>"), $this);?>

	  <img class="home_titleOverlap" src="DPS/images/hometitlebgMid.png">
	</div>
	<div class="home_titleMid"></div>
	<div class="frame_titleR">
	  <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '71','text' => "<img src='DPS/images/titleExit.gif' alt='Exit'>"), $this);?>

	  <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '58','text' => "<img src='DPS/images/titleHelp.gif' alt='Help'>"), $this);?>

	  <?php if ($this->_tpl_vars['VIEWER']['Admin'] == 't'): ?>
	  <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '2','text' => "<img src='DPS/images/titleAdmin.gif' alt='Admin'>"), $this);?>

	  <?php endif; ?>
	</div>
      </div>
    </div>
  </body>
</html>