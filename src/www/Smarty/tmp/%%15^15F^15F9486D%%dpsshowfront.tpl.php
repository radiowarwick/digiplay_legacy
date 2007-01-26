<?php /* Smarty version 2.6.14, created on 2007-01-08 17:02:20
         compiled from rfile:/var/www/DPS/templates/dpsshowfront.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'use', 'rfile:/var/www/DPS/templates/dpsshowfront.tpl', 3, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsshowtopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
<br><br>
<?php echo $this->_plugins['function']['use'][0][0]->SMARTY_use(array('func' => "CMS::showRegion",'regionID' => 5), $this);?>

<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsshowbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>