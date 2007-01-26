<?php /* Smarty version 2.6.14, created on 2006-10-24 15:04:57
         compiled from rfile:groupList.tpl */ ?>
        <ul>
          <?php $_from = $this->_tpl_vars['groups']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['groupid'] => $this->_tpl_vars['group']):
?>
            <?php if ($this->_tpl_vars['group']['inGroup']): ?>
              <li class="inGroup">
            <?php else: ?>
              <li>
            <?php endif; ?>
            <?php echo $this->_tpl_vars['group']['groupname']; ?>

            <?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:groupListButtons.tpl", 'smarty_include_vars' => array('groupid' => $this->_tpl_vars['groupid'],'ingroup' => $this->_tpl_vars['group']['inGroup'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
            </li>
          <?php endforeach; endif; unset($_from); ?>
        </ul>