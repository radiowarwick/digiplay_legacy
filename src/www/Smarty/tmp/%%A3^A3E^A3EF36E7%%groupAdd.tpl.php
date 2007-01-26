<?php /* Smarty version 2.6.14, created on 2006-10-12 18:44:00
         compiled from rfile:/var/www/Auth/templates/groupAdd.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/Auth/templates/groupAdd.tpl', 27, false),)), $this); ?>
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
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:mainTableTop.tpl", 'smarty_include_vars' => array('title' => 'Group Administration')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>

  <table width="100%" border="0" cellspacing="0" cellpadding="5">
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
      <?php if ($this->_tpl_vars['DATA']['newGroupID']): ?>
        The group has been added. Click
        <?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "groupModify.tpl",'text' => 'here','_groupToEdit' => $this->_tpl_vars['DATA']['newGroupID']), $this);?>

        if you wish to modify their permissions
      <?php else: ?>
      <td colspan="2">
        <h2>New Group Details:</h2>
        <form name="addGroupForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
        <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['DATA']['templateID']; ?>
" />
        <input type="hidden" name="formName" value="addGroupForm" />
        <input type="hidden" name="moduleName" value="Auth" />
        <table width="400px" border="0" cellspacing="0" cellpadding="5">
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
          <tr valign="top">
            <td colspan="2" align="right">
              <input type="submit" name="detailSubmit" value="Add Group" align="right" />
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