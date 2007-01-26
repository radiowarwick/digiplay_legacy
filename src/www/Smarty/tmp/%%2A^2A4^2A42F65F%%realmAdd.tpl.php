<?php /* Smarty version 2.6.14, created on 2006-07-23 20:27:55
         compiled from rfile:/var/www/toolkit/Auth/templates/realmAdd.tpl */ ?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Auth Administration</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />

<link href="tkfecommon/css/user.css" rel="stylesheet" type="text/css" />
<script language="JavaScript" type="text/JavaScript" src="tkfecommon/js/submitform.js"></script>
</head>

<body>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:mainTableTop.tpl", 'smarty_include_vars' => array('title' => 'Realm Administration')));
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
      <td width="35%">
        <span class="label">Select Realm:</span><br />
        <form name="mainForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
        <input type="hidden" name="parentID" value="" />
        <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['DATA']['templateID']; ?>
" />
        <input type="hidden" name="formName" value="addRealmSelForm" />
        <input type="hidden" name="moduleName" value="Auth" />
        <p>Root <?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:realmTreeButtons.tpl", 'smarty_include_vars' => array('realmid' => '0','type' => 'setRealmParentID')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
        <?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:realmTreeMaker.tpl", 'smarty_include_vars' => array('realms' => $this->_tpl_vars['VIEWER']['realminfo'],'type' => 'setRealmParentID')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
        </form>
      </td>
      <td width="65%">
      <?php if ($this->_tpl_vars['DATA']['parentID'] != '' && $this->_tpl_vars['VIEWER']['customFields']): ?>
        <span class="label">Details:</span>
        <form name="addRealmDetailsForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
        <input type="hidden" name="parentID" value="<?php echo $this->_tpl_vars['DATA']['parentID']; ?>
" />
        <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['DATA']['templateID']; ?>
" />
        <input type="hidden" name="formName" value="addRealmDetailsForm" />
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
"/>
            </td>
          </tr>
        <?php endforeach; endif; unset($_from); ?>
          <tr valign="top">
            <td colspan="2" align="right">
              <input type="submit" name="detailSubmit" value="Add Realm" align="right" />
            </td>
          </tr>
        </table>
        </form>
      <?php endif; ?>
      </td>
    </tr>
  </table>
</form>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:mainTableBot.tpl", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
</body>
</html>