<?php /* Smarty version 2.6.14, created on 2007-01-07 22:49:00
         compiled from rfile:userList.tpl */ ?>
        <ul>
          <?php $_from = $this->_tpl_vars['users']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['userid'] => $this->_tpl_vars['user']):
?>
            <?php if ($this->_tpl_vars['user']['inGroup']): ?>
              <li class="inGroup">
            <?php else: ?>
              <li>
            <?php endif; ?>
            <?php echo $this->_tpl_vars['user']['username']; ?>

            <?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:userListButtons.tpl", 'smarty_include_vars' => array('groupid' => $this->_tpl_vars['userid'],'ingroup' => $this->_tpl_vars['user']['inGroup'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
            </li>
          <?php endforeach; endif; unset($_from); ?>
        </ul>