<?php /* Smarty version 2.6.14, created on 2006-10-24 15:04:58
         compiled from rfile:groupListButtons.tpl */ ?>
[
<?php if ($this->_tpl_vars['ingroup']): ?>
+ <a href="javascript:submitform('groupRemove', <?php echo $this->_tpl_vars['groupid']; ?>
)">-</a> 
<?php else: ?>
<a href="javascript:submitform('groupAdd', <?php echo $this->_tpl_vars['groupid']; ?>
)">+</a> -
<?php endif; ?>
]