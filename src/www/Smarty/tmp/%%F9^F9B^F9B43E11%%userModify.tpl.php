<?php /* Smarty version 2.6.14, created on 2007-01-07 22:44:40
         compiled from rfile:/var/www/Auth/templates/userModify.tpl */ ?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Auth Administration</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />

<link href="tkfecommon/css/user.css" rel="stylesheet" type="text/css" />
<link href="tkfecommon/css/mktree.css" rel="stylesheet" type="text/css" />
<script language="JavaScript" type="text/JavaScript" src="tkfecommon/js/submitform.js"></script>
<script language="JavaScript" type="text/JavaScript" src="tkfecommon/js/mktree.js"></script>
</head>

<body onload="expandTree('realmTree')">
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:mainTableTop.tpl", 'smarty_include_vars' => array('title' => 'User Administration')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
  <form name="userSelForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
  <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
">
  <p align="center">
  <div align="center">
  <span class="label">Select User:</span><br />
    <select name="userToEdit" id="userToEdit" size="1">
      <?php $_from = $this->_tpl_vars['VIEWER']['users']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['id'] => $this->_tpl_vars['name']):
?>
        <?php if ($this->_tpl_vars['id'] == $this->_tpl_vars['DATA']['userToEdit']): ?>
          <option value="<?php echo $this->_tpl_vars['id']; ?>
" selected><?php echo $this->_tpl_vars['name']; ?>
</option>
        <?php else: ?>
          <option value="<?php echo $this->_tpl_vars['id']; ?>
"><?php echo $this->_tpl_vars['name']; ?>
</option>
        <?php endif; ?>
      <?php endforeach; endif; unset($_from); ?>
    </select>
    <input type="submit" name="submit" value="Edit">
    <input type="hidden" name="formName" value="userSelForm"><br />
    <input type="hidden" name="moduleName" value="Auth" />
  </form>
  </div>
  </p>
  <?php if ($this->_tpl_vars['DATA']['userToEdit']): ?>
  
  <hr />

  <table width="100%">
    <?php if ($this->_tpl_vars['ERRORS']): ?>
    <tr valign="top">
      <td colspan="2">
        <?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:errorsList.tpl", 'smarty_include_vars' => array('errors' => $this->_tpl_vars['ERRORS'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
      </td>
    </tr>
    <?php endif; ?>
    <tr valign="top">
      <td colspan="2">
        <h2>Details:</h2>
        <form name="modifyUserDetailsForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
        <input type="hidden" name="userToEdit" value="<?php echo $this->_tpl_vars['DATA']['userToEdit']; ?>
" />
        <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
        <input type="hidden" name="formName" value="modifyUserDetailsForm" />
        <input type="hidden" name="moduleName" value="Auth">
        <table width="400px" border="0" cellspacing="0" cellpadding="5">
        <?php if ($this->_tpl_vars['VIEWER']['customFields']): ?>
        <?php $_from = $this->_tpl_vars['VIEWER']['customFields']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['fieldInfo']):
?>
          <tr valign="top">
            <td><?php echo $this->_tpl_vars['fieldInfo']['niceName']; ?>
: </td>
            <td>
              <input type="text" name="<?php echo $this->_tpl_vars['fieldInfo']['fieldName']; ?>
" value="<?php echo $this->_tpl_vars['fieldInfo']['value']; ?>
" />
            </td>
          </tr>
        <?php endforeach; endif; unset($_from); ?>
        <?php endif; ?>
          <tr valign="top"> 
            <td>Password: </td>
            <td>
              <input type="checkbox" name="changePassword" />Change password<br />
              <input type="text" name="password" />
            </td>
          </tr>
          <tr valign="top">
            <td colspan="2">
              <input type="submit" name="detailSubmit" value="Save Changes" />
            </td>
          </tr>
        </table>
        </form>
        <table width="400px" border="0" cellspacing="0" cellpadding="5">
        <tr><td>
        <form name="userDeleteForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
        <input type="hidden" name="userToEdit" value="<?php echo $this->_tpl_vars['DATA']['userToEdit']; ?>
" />
        <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
        <input type="hidden" name="formName" value="userDeleteForm" />
        <input type="submit" name="deleteUser" value="   Delete User   " />
        <input type="hidden" name="moduleName" value="Auth" />
        </form>
        </tr></td>
        </table>
        <hr />
      </td>
    </tr>
    <tr valign="top"> 
      <td colspan="2">
      <form name="mainForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
      <table width="100%" border="0" cellspacing="0" cellpadding="5">
      <tr>
      <td width="50%" valign="top"><h3>Realms:</h3>
        <input type="hidden" name="userToEdit" value="<?php echo $this->_tpl_vars['DATA']['userToEdit']; ?>
" />
        <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
        <input type="hidden" name="task" value="" />
        <input type="hidden" name="rguid" value="" />
        <input type="hidden" name="formName" value="userPermissionForm" />
        <input type="hidden" name="moduleName" value="Auth" />
        <?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:realmTreeMaker.tpl", 'smarty_include_vars' => array('realms' => $this->_tpl_vars['VIEWER']['realminfo'],'type' => 'perm')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
      </td>
      <td width="50%" valign="top"><h3>Groups:</h3>
        <?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:groupList.tpl", 'smarty_include_vars' => array('groups' => $this->_tpl_vars['VIEWER']['groupinfo'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
      </td>
      </tr>
      </table>
      </form>
      </td>
    </tr>
  </table>
</form>
<?php endif; ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:mainTableBot.tpl", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
</body>
</html>