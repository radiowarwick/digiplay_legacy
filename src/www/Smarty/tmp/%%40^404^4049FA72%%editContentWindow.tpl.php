<?php /* Smarty version 2.6.14, created on 2007-01-07 18:48:45
         compiled from rfile:/var/www/CMS/templates/editContentWindow.tpl */ ?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Editing CMS Region</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>
<?php if ($this->_tpl_vars['VIEWER']['error']): ?>
	Error:<br>
	<?php echo $this->_tpl_vars['VIEWER']['error']; ?>

<?php else: ?>
	<?php if ($this->_tpl_vars['VIEWER']['perm'] == 'edit'): ?>
		<form method='post' action=''>
		<input type='hidden' name='formName' value='inlineEdit' />
		<input type='hidden' name='moduleName' value='CMS' />
		<?php echo $this->_tpl_vars['VIEWER']['editorCode']; ?>

		<input type="hidden" name="regionID" value="<?php echo $this->_tpl_vars['VIEWER']['regionID']; ?>
" />
		<p>
		Show In Line Editing <input type='checkbox' name='alwaysInLine' <?php echo $this->_tpl_vars['VIEWER']['showInLineEditing']; ?>
 />
		<input type="submit" name="submit" value="Save" />
		</p>
		</form>
	<?php endif;  endif; ?>
</body>
</html>