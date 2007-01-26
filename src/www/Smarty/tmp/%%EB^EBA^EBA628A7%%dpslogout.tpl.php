<?php /* Smarty version 2.6.14, created on 2006-09-28 17:57:35
         compiled from rfile:/var/www/toolkit/DPS/templates/dpslogout.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/toolkit/DPS/templates/dpslogout.tpl', 13, false),)), $this); ?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Logout Successful</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>
<h1>You have now been logged out</h1>
<p>
If you wish to return to the RaW homepage you may do so 
<a href="http://www.radio.warwick.ac.uk">here</a>. Alternatively, if you wish to 
login again, you may do so <?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "dpslogin.tpl",'text' => 'here'), $this);?>
</p>
</p>



</body>
</html>