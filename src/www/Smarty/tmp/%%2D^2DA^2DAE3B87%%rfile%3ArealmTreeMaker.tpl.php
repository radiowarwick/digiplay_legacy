<?php /* Smarty version 2.6.14, created on 2007-01-07 22:49:00
         compiled from rfile:realmTreeMaker.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('modifier', 'count', 'rfile:realmTreeMaker.tpl', 26, false),)), $this); ?>
<?php if ($this->_tpl_vars['notRoot']): ?>
<ul>
<?php else: ?>
<ul class="mktree" id="realmTree">
<?php endif; ?>
  <?php $_from = $this->_tpl_vars['realms']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['name'] => $this->_tpl_vars['subrealms']):
?>
    <?php if ($this->_tpl_vars['name'] != '_DETAILS_'): ?>
    <li>
    <?php if ($this->_tpl_vars['subrealms']['_DETAILS_']['userallow'] == 'n' || $this->_tpl_vars['subrealms']['_DETAILS_']['groupallow'] == 'n' || $this->_tpl_vars['subrealms']['_DETAILS_']['groupallow'] == '!'): ?>
      <span class="deny">
      <?php elseif ($this->_tpl_vars['subrealms']['_DETAILS_']['userallow'] == 'y' || $this->_tpl_vars['subrealms']['_DETAILS_']['groupallow'] == 'y'): ?>
      <span class="allow">
    <?php endif; ?>
    <?php echo $this->_tpl_vars['name']; ?>
</span> 
    
    <?php if ($this->_tpl_vars['subrealms']['_DETAILS_']['userallow'] == 'y'): ?>u:allow
    <?php elseif ($this->_tpl_vars['subrealms']['_DETAILS_']['userallow'] == 'n'): ?>u:deny
    <?php elseif ($this->_tpl_vars['subrealms']['_DETAILS_']['userallow'] == '!'): ?>u:deny!<?php endif; ?>
    
    <?php if ($this->_tpl_vars['subrealms']['_DETAILS_']['groupallow'] == 'y'): ?>g:allow
    <?php elseif ($this->_tpl_vars['subrealms']['_DETAILS_']['groupallow'] == 'n'): ?>g:deny
    <?php elseif ($this->_tpl_vars['subrealms']['_DETAILS_']['groupallow'] == '!'): ?>g:deny!<?php endif; ?>
    
    <?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:realmTreeButtons.tpl", 'smarty_include_vars' => array('realmid' => $this->_tpl_vars['subrealms']['_DETAILS_']['realmid'],'type' => $this->_tpl_vars['type'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
    
    <?php if (count($this->_tpl_vars['subrealms']) > 1): ?>
      <?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:realmTreeMaker.tpl", 'smarty_include_vars' => array('realms' => $this->_tpl_vars['subrealms'],'notRoot' => 1)));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
    <?php endif; ?>
    </li>
    <?php endif; ?>
  <?php endforeach; endif; unset($_from); ?>
</ul>