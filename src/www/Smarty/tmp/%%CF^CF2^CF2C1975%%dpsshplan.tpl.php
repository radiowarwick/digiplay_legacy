<?php /* Smarty version 2.6.14, created on 2007-01-05 14:25:28
         compiled from rfile:/var/www/DPS/templates/dpsshplan.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpsshplan.tpl', 11, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsshowtopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
		<div class="showPlanList">
	      <div class="bigTitle">Current shows</div>
	      <div class="subTitle">You have <?php echo $this->_tpl_vars['VIEWER']['pShowCount']; ?>
 show(s) in progress</div>
				<?php $_from = $this->_tpl_vars['VIEWER']['partShows']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['show']):
?>
				<?php if ($this->_tpl_vars['show']['completed'] == 't'): ?>
				<img src="DPS/images/showReady.png" alt="Ready">
				<?php else: ?>
	      <img src="DPS/images/showUnfinished.png" alt="Unfinished">
				<?php endif; ?>
				<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '82','text' => $this->_tpl_vars['show']['text'],'_showID' => $this->_tpl_vars['show']['id']), $this);?>
<br>
	      <div class="showPlanInteract"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Delete Show','_formName' => 'dpsUserDelShow','_moduleName' => 'DPS','_showID' => $this->_tpl_vars['show']['id']), $this);?>
&nbsp;&nbsp; <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '89','text' => 'Edit Name and Time','_showID' => $this->_tpl_vars['show']['id']), $this);?>
</div>
				<?php endforeach; endif; unset($_from); ?>
	     	<br>
	      
	      <div class="bigTitle">Previous shows</div>
	      <div class="subTitle">You have <?php echo $this->_tpl_vars['VIEWER']['dShowCount']; ?>
 old program(s)</div>
				<?php $_from = $this->_tpl_vars['VIEWER']['doneShows']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['show']):
?>
	      <img src="DPS/images/showFinished.png" alt="Unfinished">
				<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '82','text' => $this->_tpl_vars['show']['text'],'_showID' => $this->_tpl_vars['show']['id']), $this);?>
<br>
	      <div class="showPlanInteract"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Delete Show','_formName' => 'dpsUserDelShow','_moduleName' => 'DPS','_showID' => $this->_tpl_vars['show']['id']), $this);?>
&nbsp;&nbsp; <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '89','text' => 'Edit Name and Time','_showID' => $this->_tpl_vars['show']['id']), $this);?>
</div>
				<?php endforeach; endif; unset($_from); ?>
	    </div>
	    <div class="showPlanHelp">
	      <img src="DPS/images/showFinished.png" alt="Finished"> Already broadcast<br>
	      <img src="DPS/images/showUnfinished.png" alt="Uninished"> Unfinished<br>
	      <img src="DPS/images/showReady.png" alt="Ready"> Finished & ready<br>
	    </div>
	    <div class="showPlanNew">
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Create new show','_formName' => 'dpsUserAddShow','_moduleName' => 'DPS'), $this);?>
</a>
	    </div>
		<br style="&7b;clear:both;&7c;" />
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsshowbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>