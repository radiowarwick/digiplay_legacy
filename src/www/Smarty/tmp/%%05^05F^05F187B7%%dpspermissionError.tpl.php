<?php /* Smarty version 2.6.14, created on 2007-01-05 17:16:51
         compiled from rfile:/var/www/DPS/templates/dpspermissionError.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpspermissionError.tpl', 21, false),)), $this); ?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Permission Error</title>
<link href="tkfecommon/css/user.css" rel="stylesheet" type="text/css" />
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>
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
<?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "dpslogin.tpl",'text' => 'here','_fwdtid' => $this->_tpl_vars['VIEWER']['templateID']), $this);?>
</p>
<?php else: ?>
An unspecified error has occured. Please contact the RaW webmaster.
<?php endif; ?>
</body>
</html>