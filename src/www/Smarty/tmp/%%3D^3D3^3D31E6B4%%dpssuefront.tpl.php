<?php /* Smarty version 2.6.14, created on 2006-09-28 18:03:58
         compiled from rfile:/var/www/toolkit/DPS/templates/dpssuefront.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'use', 'rfile:/var/www/toolkit/DPS/templates/dpssuefront.tpl', 2, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpssuetopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager','nexttrack' => $this->_tpl_vars['VIEWER']['sueNextTrack'],'Access_EditSue' => $this->_tpl_vars['VIEWER']['Access_EditSue'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
  echo $this->_plugins['function']['use'][0][0]->SMARTY_use(array('func' => "CMS::showRegion",'regionID' => 3), $this);?>

<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsmusicbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>