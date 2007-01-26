<?php /* Smarty version 2.6.14, created on 2006-09-14 01:45:20
         compiled from rfile:/var/www/toolkit/Auth/templates/logout.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/toolkit/Auth/templates/logout.tpl', 12, false),)), $this); ?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Logout Successful</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>
<h1>You have now been logged out</h1>
<p>
If you wish to return to the home page you may do so 
<?php echo SmartyFunctions::SMARTY_templateLink(array('text' => 'here','name' => $this->_tpl_vars['CONFIG']['smarty']['defaultTemplate']), $this);?>
. Alternatively, if you wish to 
login again, you may do so <?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "login.tpl",'text' => 'here'), $this);?>
</p>
</p>



</body>
</html>