<?php /* Smarty version 2.6.14, created on 2007-01-22 10:18:12
         compiled from rfile:dpsmusicbottomframe.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:dpsmusicbottomframe.tpl', 7, false),)), $this); ?>
	  </div>
        </div>
        <div class="copyright">Copyright &#169 RaW 1251AM, 2006</div>
      </div>    
      <div class="frame_halfTitleBar">
	<div class="frame_halfTitleL">
	  <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '47','text' => "<img class='home_title' src='DPS/images/hometitle.gif' alt='Raw Digiplay Manager'>"), $this);?>

	  <img class="home_titleOverlap" src="DPS/images/hometitlebgMid.png">
	</div>
	<div class="home_titleMid"></div>
	<div class="frame_titleR">
	  <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '71','text' => "<img src='DPS/images/titleExit.gif' alt='Exit'>"), $this);?>

	  <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '58','text' => "<img src='DPS/images/titleHelp.gif' alt='Help'>"), $this);?>

	  <?php if ($this->_tpl_vars['Admin']): ?>
	  <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '2','text' => "<img src='DPS/images/titleAdmin.gif' alt='Admin'>"), $this);?>

	  <?php endif; ?>
	</div>
      </div>
    </div>
  </body>
</html>