<?php /* Smarty version 2.6.14, created on 2007-01-05 15:46:16
         compiled from rfile:/var/www/DPS/templates/dpspublichelp.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpspublichelp.tpl', 10, false),array('function', 'use', 'rfile:/var/www/DPS/templates/dpspublichelp.tpl', 28, false),)), $this); ?>
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
			<?php if ($this->_tpl_vars['VIEWER']['Guest'] == 't'): ?>
      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '47','text' => "<img src='DPS/images/hometitleExit.gif' alt='Exit'>"), $this);?>

      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '100','text' => "<img src='DPS/images/hometitleHelp.gif' alt='Help'>"), $this);?>

			<?php else: ?>
      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '71','text' => "<img src='DPS/images/hometitleExit.gif' alt='Exit'>"), $this);?>

      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '58','text' => "<img src='DPS/images/hometitleHelp.gif' alt='Help'>"), $this);?>

			<?php endif; ?>
      <?php if ($this->_tpl_vars['VIEWER']['Admin']): ?>
      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '2','text' => "<img src='DPS/images/hometitleAdmin.gif' alt='Admin'>"), $this);?>

      <?php endif; ?>
    </div>
  </div>
	<?php echo $this->_plugins['function']['use'][0][0]->SMARTY_use(array('func' => "CMS::showRegion",'regionID' => 6), $this);?>

  <div class="copyright">Copyright &#169 RaW 1251AM, 2006</div>
  </div>
  </body>
</html>