<?php /* Smarty version 2.6.14, created on 2007-01-07 22:48:59
         compiled from rfile:mainTableTop.tpl */ ?>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> 
    <td colspan="2"><div class="pageTitle"><?php echo $this->_tpl_vars['title']; ?>
</div></td>
  </tr>
  <tr valign="top"> 
    <td width="150"><p>Contents</p>
        <?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:contents.tpl", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
        <p />
        Logged in as: <?php echo $this->_tpl_vars['AUTH']['user']; ?>

      </td>
    <td>