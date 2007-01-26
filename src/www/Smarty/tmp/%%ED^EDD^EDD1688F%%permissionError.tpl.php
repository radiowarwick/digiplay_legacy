<?php /* Smarty version 2.6.14, created on 2006-07-04 19:52:36
         compiled from rfile:/var/www/toolkit/tkfecommon/templates/permissionError.tpl */ ?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Permission Error</title>
<link href="tkfecommon/css/user.css" rel="stylesheet" type="text/css" />
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:mainTableTop.tpl", 'smarty_include_vars' => array('title' => 'Administration')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
<h1>Authentication Error</h1>
<?php if ($this->_tpl_vars['ERRORS']['permission']): ?>
<p>
The following error occurred while authorising your request:
</p>
<ul>
  <li>
  <?php echo $this->_tpl_vars['ERRORS']['permission']; ?>

  </li>
</ul>
<p>If you need to access the logon page you may do so 
<a href="?templateID=<?php echo $this->_tpl_vars['VIEWER']['loginTplID']; ?>
&fwdtid=<?php echo $this->_tpl_vars['DATA']['templateID']; ?>
">here</a></p>


<?php else: ?>
An unspecified error has occured
<?php endif;  $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:mainTableBot.tpl", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
</body>
</html>