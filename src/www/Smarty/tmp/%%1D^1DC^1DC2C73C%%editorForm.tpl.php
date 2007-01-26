<?php /* Smarty version 2.6.14, created on 2006-09-29 13:52:27
         compiled from rfile:/var/www/toolkit/CMS/templates/editorForm.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/toolkit/CMS/templates/editorForm.tpl', 22, false),)), $this); ?>
<?php if ($this->_tpl_vars['VIEWER']['error']): ?>
	Error:<br>
	<?php echo $this->_tpl_vars['VIEWER']['error']; ?>

<?php else: ?>
	<?php if ($this->_tpl_vars['VIEWER']['perm'] == 'view'): ?>
		<?php echo $this->_tpl_vars['VIEWER']['code']; ?>

	<?php elseif ($this->_tpl_vars['VIEWER']['perm'] == 'edit'): ?>
		<?php if ($this->_tpl_vars['VIEWER']['showInLineEditing'] == 'CHECKED'): ?>
			<form method='post' action=''>
			<input type='hidden' name='formName' value='inlineEdit' />
			<input type='hidden' name='moduleName' value='CMS' />
			<input type='hidden' name='templateID' value='<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
' />
			<?php echo $this->_tpl_vars['VIEWER']['code']; ?>

			<input type="hidden" name="regionID" value="<?php echo $this->_tpl_vars['VIEWER']['regionID']; ?>
" />
			<p>
			Show InLine Editing <input type='checkbox' name='alwaysInLine' <?php echo $this->_tpl_vars['VIEWER']['showInLineEditing']; ?>
 value = "on"/>
			<input type="submit" name="submit" value="Save" />
			</p>
			</form>
		<?php else: ?>
			<?php echo $this->_tpl_vars['VIEWER']['code']; ?>
<br>
			<p><?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "editContentWindow.tpl",'text' => 'Window Edit','target' => '_blank','_regionID' => $this->_tpl_vars['VIEWER']['regionID']), $this);?>
</p>
		<?php endif; ?>
	<?php endif;  endif; ?>