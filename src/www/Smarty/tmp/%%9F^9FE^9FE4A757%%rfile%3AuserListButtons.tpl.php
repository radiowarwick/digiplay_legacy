<?php /* Smarty version 2.6.14, created on 2007-01-07 22:49:00
         compiled from rfile:userListButtons.tpl */ ?>
[
<?php if ($this->_tpl_vars['ingroup']): ?>
+ <a href="javascript:submitform('userRemove', <?php echo $this->_tpl_vars['groupid']; ?>
)">-</a> 
<?php else: ?>
<a href="javascript:submitform('userAdd', <?php echo $this->_tpl_vars['groupid']; ?>
)">+</a> -
<?php endif; ?>
]