<?php /* Smarty version 2.6.14, created on 2006-06-06 19:51:49
         compiled from rfile:/var/www/toolkit/Auth/templates/userAdd.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/toolkit/Auth/templates/userAdd.tpl', 30, false),)), $this); ?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Auth Administration</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />

<link href="tkfecommonr.css/user.css" rel="stylesheet" type="text/css" />
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
      <?php if ($this->_tpl_vars['DATA']['newUserID']): ?>
        The user has been added. Click
        <?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "userModify.tpl",'text' => 'here','_userToEdit' => $this->_tpl_vars['DATA']['newUserID']), $this);?>

        if you wish to modify their permissions
      <?php else: ?>
        <h2>New User Details:</h2>
        <form name="addUserDetailsForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>
">
        <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
        <input type="hidden" name="formName" value="addUserDetailsForm" />
        <input type="hidden" name="moduleName" value="Auth" />
        <table width="400px" border="0" cellspacing="0" cellpadding="5">
        <?php if ($this->_tpl_vars['VIEWER']['customFields']): ?>
        <?php $_from = $this->_tpl_vars['VIEWER']['customFields']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['fieldInfo']):
?>
          <tr valign="top">
            <td><?php echo $this->_tpl_vars['fieldInfo']['niceName']; ?>
: </td>
            <td>
              <?php if ($this->_tpl_vars['VIEWER']['formName'] == 'detailsForm'): ?>
              <?php $this->assign('name', $this->_tpl_vars['fieldInfo']['fieldName']); ?>
              <input type="text" name="<?php echo $this->_tpl_vars['fieldInfo']['fieldName']; ?>
" value="<?php echo $this->_tpl_vars['DATA'][$this->_tpl_vars['name']]; ?>
" />
              <?php else: ?>
              <input type="text" name="<?php echo $this->_tpl_vars['fieldInfo']['fieldName']; ?>
" value="<?php echo $this->_tpl_vars['fieldInfo']['value']; ?>
" />
              <?php endif; ?>
            </td>
          </tr>
        <?php endforeach; endif; unset($_from); ?>
        <?php endif; ?>
          <tr valign="top"> 
            <td>Password: </td>
            <td>
              <input type="text" name="password" />
            </td>
          </tr>
          <tr valign="top">
            <td colspan="2" align="right">
              <input type="submit" name="detailSubmit" value="Add User" align="right" />
            </td>
          </tr>
        </table>
        </form>
      <?php endif; ?>
        <hr />
      </td>
    </tr>
  </table>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:mainTableBot.tpl", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
</body>
</html>