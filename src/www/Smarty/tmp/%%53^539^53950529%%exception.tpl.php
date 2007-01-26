<?php /* Smarty version 2.6.14, created on 2006-06-05 19:25:59
         compiled from file:/var/www/toolkit/tkfecommon/templates/exception.tpl */ ?>
<HTML>
<HEAD>
<TITLE>OH NO! There has been a problem!</TITLE>
</HEAD>
<BODY>
<H1>Whoops!</H1><BR>
There seems to have been a problem<BR>
<?php if ($this->_tpl_vars['showExceptionInfo']): ?>
	<?php $_from = $this->_tpl_vars['exceptionData']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['k'] => $this->_tpl_vars['v']):
?>
		<?php echo $this->_tpl_vars['k']; ?>
 : <?php echo $this->_tpl_vars['v']; ?>
<BR>
	<?php endforeach; endif; unset($_from); ?>
<?php endif; ?>
</FORM>
</BODY>
</HTML>