<?php /* Smarty version 2.6.14, created on 2007-01-21 17:08:16
         compiled from rfile:dpssuetopframe.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:dpssuetopframe.tpl', 11, false),)), $this); ?>
<html>
  <head>
    <title><?php echo $this->_tpl_vars['title']; ?>
</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
  </head>
  <body>
    <div class="centreContainer">
      <div class="frame_bottom">
	<div class="frame_suesidebar">
	  <img class="frame_sidebarlogo" src="DPS/images/homenavsue.png" alt="Sue Stamp">
	  <div class="frame_sidebarmusic"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '76','text' => 'Music Library'), $this);?>
</div>
	  <div class="frame_sidebarshow"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '79','text' => 'Show Planning'), $this);?>
</div>
	  <div class="frame_sidebarstudio"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '78','text' => 'Studio Cartwalls'), $this);?>
</div>
	  <div class="frame_suesidebarlinks">
	    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '77','text' => 'Information'), $this);?>
<br>
		<?php if (Access_ViewSue): ?>
	    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '61','text' => 'View Sue Playlist'), $this);?>
<br>
		<?php endif; ?>
	    <?php if (Access_EditSue): ?>
	    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '62','text' => 'Add to Sue Playlist'), $this);?>
<br>
	    <?php endif; ?>
		<?php if (Access_SueStats): ?>
	    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '60','text' => "Sue Stamp's Statistics"), $this);?>
<br>
		<?php endif; ?>
	  </div>
        </div>
        <div class="frame_rightside">
	  <div class="frame_suesearchbox">
	    <?php if ($this->_tpl_vars['suesearchid'] == 61): ?>
	    Search for tracks on Sue
	    <?php elseif ($this->_tpl_vars['suesearchid'] == 62): ?>
	    Search for tracks to add
	    <?php else: ?>
	    Search for tracks
	    <?php endif; ?>
	    <form name="dpsSueSearchForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
	      <input type="hidden" name="formName" value="dpsSueSearchForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <?php if ($this->_tpl_vars['suesearchid']): ?>
	      <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['suesearchid']; ?>
" />
	      <?php else: ?>
	      <input type="hidden" name="templateID" value="61">
	      <?php endif; ?>
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
	  <div class="frame_suenextbox">
	    <b>Coming up soon:</b><br>
	    <?php echo $this->_tpl_vars['nexttrack']['artist']; ?>
 - <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '55','text' => $this->_tpl_vars['nexttrack']['title'],'_trackID' => $this->_tpl_vars['nexttrack']['id']), $this);?>
<br>
          </div>

	  <div class="frame_content">