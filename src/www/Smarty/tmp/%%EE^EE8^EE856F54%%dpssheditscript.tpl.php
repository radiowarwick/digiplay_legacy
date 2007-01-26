<?php /* Smarty version 2.6.14, created on 2006-12-19 19:12:19
         compiled from rfile:/var/www/DPS/templates/dpssheditscript.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpssheditscript.tpl', 6, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsshowtopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
  if ($this->_tpl_vars['VIEWER']['error']): ?>
	<?php echo $this->_tpl_vars['VIEWER']['error']; ?>

<?php else: ?>
	<div class="showPlanList">
	<div class="rightLinks"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '93','text' => "<< Back to your scripts"), $this);?>
</div>
		<div class="bigTitle">
			<?php echo $this->_tpl_vars['VIEWER']['script']['name']; ?>

		</div>
		<b>New Details</b><br />
		<form name="dpsUserEditScript" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
		<input type="hidden" name="formName" value="dpsUserEditScript" />
		<input type="hidden" name="moduleName" value="DPS" />
		<input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
		<input type="hidden" name="scriptID" value="<?php echo $this->_tpl_vars['VIEWER']['script']['id']; ?>
" />
		<?php if ($this->_tpl_vars['ERRORS']['dpsUserEditScript']['scriptID'] != ''): ?>
			<?php echo $this->_tpl_vars['ERRORS']['dpsUserEditScript']['scriptID']; ?>
<br />
		<?php endif; ?>
		<?php if ($this->_tpl_vars['ERRORS']['dpsUserEditScript']['name'] != ''): ?>
			<?php echo $this->_tpl_vars['ERRORS']['dpsUserEditScript']['name']; ?>
<br />
		<?php endif; ?>
		Name: <input type="text" name="name" value="<?php echo $this->_tpl_vars['VIEWER']['script']['name']; ?>
"/><br />
		<?php if ($this->_tpl_vars['ERRORS']['dpsUserEditScript']['mins'] != ''): ?>
			<?php echo $this->_tpl_vars['ERRORS']['dpsUserEditScript']['mins']; ?>
<br />
		<?php elseif ($this->_tpl_vars['ERRORS']['dpsUserEditScript']['secs'] != ''): ?>
			<?php echo $this->_tpl_vars['ERRORS']['dpsUserEditScript']['secs']; ?>
<br />
		<?php endif; ?>
		Length (mm:ss): <input type=text name="mins" maxlength=2 size=2 value="<?php echo $this->_tpl_vars['VIEWER']['script']['m']; ?>
" />:<input type=text name="secs" maxlength=2 size=2 value="<?php echo $this->_tpl_vars['VIEWER']['script']['s']; ?>
" /><br />
		<b>Producer: </b> <?php echo $this->_tpl_vars['VIEWER']['script']['niceProducer']; ?>
<br />
		<hr>
		<textarea name="content" cols=70 rows=20><?php echo $this->_tpl_vars['VIEWER']['script']['contents']; ?>
</textarea><br />
		<input type="Submit" name="Submit" value="Submit" />
	</div>
	<br style="&7b;clear:both;&7c;" />
<?php endif;  $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsshowbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>