<?php /* Smarty version 2.6.14, created on 2007-01-05 14:21:35
         compiled from rfile:/var/www/DPS/templates/dpsshscript.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpsshscript.tpl', 10, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsshowtopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
		<div class="showPlanList">
	      <div class="bigTitle">Current Scripts</div>
	      <div class="subTitle">You have <?php echo $this->_tpl_vars['VIEWER']['scriptCount']; ?>
 script(s)</div>
				<?php if ($this->_tpl_vars['ERRORS']['dpsUserDelScript']['scriptID'] != ''): ?>
				<div class="frame_musicboxerror"><?php echo $this->_tpl_vars['ERRORS']['dpsUserDelScript']['scriptID']; ?>
</div>
				<?php endif; ?>
				<?php $_from = $this->_tpl_vars['VIEWER']['scripts']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['script']):
?>
	      <img src="DPS/images/showScript.png" alt="Show Script">
				<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '94','text' => $this->_tpl_vars['script']['text'],'_scriptID' => $this->_tpl_vars['script']['id']), $this);?>
<br>
	      <div class="showPlanInteract"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Delete Script','_formName' => 'dpsUserDelScript','_moduleName' => 'DPS','_scriptID' => $this->_tpl_vars['script']['id']), $this);?>
</div>
				<?php endforeach; endif; unset($_from); ?>
	     	<br>
			</div>
	    <div class="showPlanNew">
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Create new script','_formName' => 'dpsUserAddScript','_moduleName' => 'DPS'), $this);?>
</a>
	    </div>
		<br style="&7b;clear:both;&7c;" />
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsshowbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>