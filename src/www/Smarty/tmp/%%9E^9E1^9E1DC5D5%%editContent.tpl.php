<?php /* Smarty version 2.6.14, created on 2007-01-05 16:48:47
         compiled from rfile:/var/www/CMS/templates/editContent.tpl */ ?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Editing CMS Region</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>

<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:mainTableTop.tpl", 'smarty_include_vars' => array('title' => 'CMS Administration')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>

<?php if ($this->_tpl_vars['ERRORS']['permission']): ?>
<p>
The following error occured while processing your request:
</p>
<ul>
  <li>
  <?php echo $this->_tpl_vars['ERRORS']['permission']; ?>

  </li>
</ul>
<?php endif; ?>

<form name="selectRegionForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
" />
<input type="hidden" name="formName" value="selectRegionForm" />
<input type="hidden" name="moduleName" value="CMS" />
<input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
<select name="regionID">
<?php $_from = $this->_tpl_vars['VIEWER']['regions']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['id'] => $this->_tpl_vars['name']):
?>
  <option value="<?php echo $this->_tpl_vars['id']; ?>
"><?php echo $this->_tpl_vars['name']; ?>
</option>
<?php endforeach; endif; unset($_from); ?>
</select>
<input type="submit" name="submit" value="Edit" />
</form>

<?php if ($this->_tpl_vars['DATA']['regionID']): ?>

<hr />

<form name="regionModifyForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
" />
<h2>Details</h2>
<table>
 <tr>
  <td>
   Region ID
  </td>
  <td>
   <?php echo $this->_tpl_vars['DATA']['regionID']; ?>

  </td>
 </tr>
 <tr>
  <td>
   Name
  </td>
  <td>
   <input type="text" name="name" value="<?php echo $this->_tpl_vars['VIEWER']['name']; ?>
" />
  </td>
 </tr>
 <tr>
  <td>
   Realm required for viewing
  </td>
  <td>
   <select name="viewRealm">
    <?php $_from = $this->_tpl_vars['VIEWER']['realms']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['id'] => $this->_tpl_vars['realm']):
?>
     <?php if ($this->_tpl_vars['id'] == $this->_tpl_vars['VIEWER']['viewRealm']): ?>
      <option value="<?php echo $this->_tpl_vars['id']; ?>
" selected><?php echo $this->_tpl_vars['realm']; ?>
</option>
     <?php else: ?>
      <option value="<?php echo $this->_tpl_vars['id']; ?>
"><?php echo $this->_tpl_vars['realm']; ?>
</option>
     <?php endif; ?>
    <?php endforeach; endif; unset($_from); ?>
   </select>
  </td>
 </tr>
 <tr>
  <td>
   Realm required for editing
  </td>
  <td>
   <select name="editRealm">
    <?php $_from = $this->_tpl_vars['VIEWER']['realms']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['id'] => $this->_tpl_vars['realm']):
?>
     <?php if ($this->_tpl_vars['id'] == $this->_tpl_vars['VIEWER']['editRealm']): ?>
      <option value="<?php echo $this->_tpl_vars['id']; ?>
" selected><?php echo $this->_tpl_vars['realm']; ?>
</option>
     <?php else: ?>
      <option value="<?php echo $this->_tpl_vars['id']; ?>
"><?php echo $this->_tpl_vars['realm']; ?>
</option>
     <?php endif; ?>
    <?php endforeach; endif; unset($_from); ?>
   </select>
  </td>
 </tr>
 <tr>
  <td>
   Toolbar to be used for inline editing
  </td>
  <td>
   <select name="inlineToolbar">
    <?php $_from = $this->_tpl_vars['CONFIG']['CMS']['availableToolbars']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['tbName']):
?>
     <?php if ($this->_tpl_vars['tbName'] == $this->_tpl_vars['VIEWER']['inlineToolbar']): ?>
      <option value="<?php echo $this->_tpl_vars['tbName']; ?>
" selected><?php echo $this->_tpl_vars['tbName']; ?>
</option>
     <?php else: ?>
      <option value="<?php echo $this->_tpl_vars['tbName']; ?>
"><?php echo $this->_tpl_vars['tbName']; ?>
</option>
     <?php endif; ?>
    <?php endforeach; endif; unset($_from); ?>
   </select>
  </td>
 </tr>
 <tr>
  <td>
   Toolbar to be used for windowed editing
  </td>
  <td>
   <select name="windowToolbar">
    <?php $_from = $this->_tpl_vars['CONFIG']['CMS']['availableToolbars']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['tbName']):
?>
     <?php if ($this->_tpl_vars['tbName'] == $this->_tpl_vars['VIEWER']['windowToolbar']): ?>
      <option value="<?php echo $this->_tpl_vars['tbName']; ?>
" selected><?php echo $this->_tpl_vars['tbName']; ?>
</option>
     <?php else: ?>
      <option value="<?php echo $this->_tpl_vars['tbName']; ?>
"><?php echo $this->_tpl_vars['tbName']; ?>
</option>
     <?php endif; ?>
    <?php endforeach; endif; unset($_from); ?>
   </select>
  </td>
 </tr>
</table>

<hr />

<h2>Content<h2>

<input type="hidden" name="formName" value="regionModifyForm" />
<input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
<input type="hidden" name="moduleName" value="CMS" />
<input type="hidden" name="regionID" value="<?php echo $this->_tpl_vars['DATA']['regionID']; ?>
" />
<?php echo $this->_tpl_vars['VIEWER']['editorCode']; ?>

<input type="submit" name="submit" value="Save" />
</form>

<?php endif;  $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:mainTableBot.tpl", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
</body>
</html>