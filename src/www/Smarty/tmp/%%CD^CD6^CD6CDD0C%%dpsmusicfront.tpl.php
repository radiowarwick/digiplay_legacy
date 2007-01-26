<?php /* Smarty version 2.6.14, created on 2007-01-22 10:18:05
         compiled from rfile:/var/www/DPS/templates/dpsmusicfront.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'use', 'rfile:/var/www/DPS/templates/dpsmusicfront.tpl', 2, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsmusictopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager','RequestTrack' => $this->_tpl_vars['VIEWER']['RequestTrack'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
  echo $this->_plugins['function']['use'][0][0]->SMARTY_use(array('func' => "CMS::showRegion",'regionID' => 2), $this);?>

<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsmusicbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>