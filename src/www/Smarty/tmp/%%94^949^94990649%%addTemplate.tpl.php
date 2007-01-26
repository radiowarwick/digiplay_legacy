<?php /* Smarty version 2.6.14, created on 2006-09-30 17:54:38
         compiled from rfile:/var/www/MVC/templates/addTemplate.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'getTemplateID', 'rfile:/var/www/MVC/templates/addTemplate.tpl', 54, false),)), $this); ?>
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

<?php if ($this->_tpl_vars['ERRORS']): ?>
 <?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:errorsList.tpl", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
  endif; ?>
<form method="POST" action="<?php echo $_SERVER['PHP_SELF']; ?>
">
<table>
<tr>
<td>
File Name:
</td>
<td>
<select name="fileName">
<?php $_from = $this->_tpl_vars['VIEWER']['unusedTemplates']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['filename']):
?>
  <option value="<?php echo $this->_tpl_vars['filename']; ?>
"><?php echo $this->_tpl_vars['filename']; ?>
</option>
<?php endforeach; endif; unset($_from); ?>
</select>
</td>
</tr>
<tr>
<td>
Model Class Name:
</td>
<td>
<select name="modelName">
<?php $_from = $this->_tpl_vars['VIEWER']['models']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['name']):
?>
  <option value="<?php echo $this->_tpl_vars['name']; ?>
"><?php echo $this->_tpl_vars['name']; ?>
</option>
<?php endforeach; endif; unset($_from); ?>
</select>
</td>
</tr>
<tr>
<td>
Viewer Class Name:
</td>
<td>
<select name="viewerName">
<?php $_from = $this->_tpl_vars['VIEWER']['viewers']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['name']):
?>
  <option value="<?php echo $this->_tpl_vars['name']; ?>
"><?php echo $this->_tpl_vars['name']; ?>
</option>
<?php endforeach; endif; unset($_from); ?>
</select>
</td>
</tr>
</table>
<input type="hidden" name="templateID" value="<?php echo SmartyFunctions::SMARTY_getTemplateID(array('name' => 'addTemplate.tpl'), $this);?>
">
<input type="hidden" name="process" value="1">
<input type="hidden" name="formName" value="addTemplateForm">
<input type="submit" name="submit" value="Add">
</ >

<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:mainTableBot.tpl", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
</body>
</html>