<?php /* Smarty version 2.6.14, created on 2007-01-22 10:18:11
         compiled from rfile:dpsmusictopframe.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:dpsmusictopframe.tpl', 11, false),)), $this); ?>
<html>
  <head>
    <title><?php echo $this->_tpl_vars['title']; ?>
</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
  </head>
  <body>
    <div class="centreContainer">
      <div class="frame_bottom">
	<div class="frame_musicsidebar">
	  <img class="frame_sidebarlogo" src="DPS/images/homenavmusic.png" alt="Music Library">
	  <div class="frame_sidebarshow"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '79','text' => 'Show Planning'), $this);?>
</div>
	  <div class="frame_sidebarsue"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '77','text' => 'Sue Stamp'), $this);?>
</div>
	  <div class="frame_sidebarstudio"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '78','text' => 'Studio Cartwalls'), $this);?>
</div>
	  <div class="frame_musicsidebarlinks">
	    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '76','text' => 'Information'), $this);?>
<br>
	    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '48','text' => 'Search tracks'), $this);?>
<br>
	    <?php if ($this->_tpl_vars['RequestTrack']): ?>
	    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '59','text' => 'View requested tracks'), $this);?>
<br>
	    <?php endif; ?>
	    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '52','text' => 'View censored tracks'), $this);?>
<br>
	  </div>
        </div>
        <div class="frame_rightside">
	  <div class="frame_musicsearchbox">
	    Search for tracks
	    <form name="dpsMusicSearchForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
	      <input type="hidden" name="formName" value="dpsMusicSearchForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <input type="hidden" name="templateID" value="48" />
	      <?php if ($this->_tpl_vars['ERRORS']['dpsSearchVal']): ?>
	      <div class="frame_musicboxerror"><?php echo $this->_tpl_vars['ERRORS']['dpsSearchVal']; ?>
</div>
	      <?php elseif ($this->_tpl_vars['ERRORS']['dpsSearchType']): ?>
	      <div class="frame_musicboxerror"><?php echo $this->_tpl_vars['ERRORS']['dpsSearchType']; ?>
</div>
	      <?php endif; ?>
	      <input type="text" name="dpsSearchVal" value="<?php echo $this->_tpl_vars['VIEWER']['searchValue']; ?>
">
	      <select name="dpsSearchType">
		<?php if ($this->_tpl_vars['VIEWER']['searchType'] == 'Both'): ?>
		  <option value="Both" selected="selected">Both</option>
		<?php else: ?>
		  <option value="Both">Both</option>
		<?php endif; ?>
		<?php if ($this->_tpl_vars['VIEWER']['searchType'] == 'Artist'): ?>
		  <option value="Artist" selected="selected">Artist</option>
		<?php else: ?>
		  <option value="Artist">Artist</option>
		<?php endif; ?>
		<?php if ($this->_tpl_vars['VIEWER']['searchType'] == 'Title'): ?>
		  <option selected="selected" value="Title">Title</option>
		<?php else: ?>
		  <option value="Title">Title</option>
		<?php endif; ?>
	      </select>
	      <input type="Submit" name="Search" value="Search">
	    </form>
	  </div>

	  <div class="frame_musicrequestbox">
	    <?php if ($this->_tpl_vars['RequestTrack']): ?>
	    Can't find the track you're after?<br>
	    <b>Request it</b>
	    <?php if ($this->_tpl_vars['ERRORS']['artist']): ?>
	    <div class="frame_musicboxerror"><?php echo $this->_tpl_vars['ERRORS']['artist']; ?>
</div>
	    <?php elseif ($this->_tpl_vars['ERRORS']['title']): ?>
	    <div class="frame_musicboxerror"><?php echo $this->_tpl_vars['ERRORS']['title']; ?>
</div>
	    <?php endif; ?>
	    <form name="dpsMusicRequestForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
	      <input type="hidden" name="formName" value="dpsMusicRequestForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
	      <input type="text" name="artist" size=17 maxlength=50 value="Artist"> 
	      <input type="text" name="title" size=17 maxlength=50 value="Title"><br>
	      <input class="frame_musicrequestcmd" type="submit" value="Request"><br>
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '59','text' => 'View requested tracks'), $this);?>

	    </form>
	    <?php else: ?>
	      You do not have permission to request tracks.
	    <?php endif; ?>
          </div>
          <div class="frame_content">