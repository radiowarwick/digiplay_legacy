<?php /* Smarty version 2.6.14, created on 2007-01-07 22:49:00
         compiled from rfile:realmTreeButtons.tpl */ ?>
<?php if ($this->_tpl_vars['type'] == 'edit'): ?>
 [ <a href="javascript:editrealm(<?php echo $this->_tpl_vars['realmid']; ?>
)">Edit</a> ] 
<?php elseif ($this->_tpl_vars['type'] == 'perm'): ?>
[
<a href="javascript:submitform('realmAllow', <?php echo $this->_tpl_vars['realmid']; ?>
)">a</a> 
<a href="javascript:submitform('realmDeny', <?php echo $this->_tpl_vars['realmid']; ?>
)">d</a> 
<a href="javascript:submitform('realmIgnore', <?php echo $this->_tpl_vars['realmid']; ?>
)">i</a>
]
<?php elseif ($this->_tpl_vars['type'] == 'setRealmParentID'): ?>
[
<a href="javascript:addRealmSubmitForm(<?php echo $this->_tpl_vars['realmid']; ?>
)">Select</a> 
]
<?php endif; ?>