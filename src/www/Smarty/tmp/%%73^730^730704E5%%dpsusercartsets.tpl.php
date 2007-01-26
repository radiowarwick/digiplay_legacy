<?php /* Smarty version 2.6.14, created on 2006-09-20 15:36:31
         compiled from rfile:/var/www/toolkit/DPS/templates/dpsusercartsets.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/toolkit/DPS/templates/dpsusercartsets.tpl', 13, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsstudiotopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
  <br>
  <br>
<div class='stationtitle'>Cartwall Profiles</div>

<div class='statioinfo1'>You currently have the following cartwalls available:</div>
  <table border=1 class='stationtable'>
    <tr>
      <th class="stationTableName">
	<?php echo $this->_tpl_vars['VIEWER']['stationcartset']['name']; ?>

      </th>
      <td class="stationTableOption">
	<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '67','_cartset' => $this->_tpl_vars['VIEWER']['stationcartset']['id'],'text' => 'view'), $this);?>

      </td>
      <td class="stationTableOption">
      </td>
      <td class="stationTableOption">
      </td>
      <td class="stationTableDetail">
	<div class="userdefaultcartset">preloaded</div>
      </td>
    </tr>
<?php $_from = $this->_tpl_vars['VIEWER']['cartsets']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['cartset']):
?>
    <tr>
      <th class="userTableName">
	<?php echo $this->_tpl_vars['cartset']['name']; ?>

      </th>
      <td class="userTableOption">
	<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '67','_cartset' => $this->_tpl_vars['cartset']['id'],'text' => 'view'), $this);?>

      </td>
      <td class="userTableOption">
	<?php if ($this->_tpl_vars['cartset']['permissions'] == 'o ' | $this->_tpl_vars['cartset']['permissions'] == 'w ' | $this->_tpl_vars['cartset']['permissions'] == 'rw'): ?>
	<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '68','_cartset' => $this->_tpl_vars['cartset']['id'],'text' => 'edit'), $this);?>

	<?php endif; ?>
      </td>
      <td class="userTableOption">
	<?php if ($this->_tpl_vars['cartset']['permissions'] == 'o '): ?>
	<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'_cartset' => $this->_tpl_vars['cartset']['id'],'text' => 'delete','_formName' => 'dpsDelUserCartsetForm','_moduleName' => 'DPS'), $this);?>

	<?php endif; ?>
      </td>
      <td class="userTableDetail">
	<?php if ($this->_tpl_vars['cartset']['active'] == 't'): ?>
	<div class="userdefaultcartset">default cartset</div>
	<?php else: ?>
	<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'_cartset' => $this->_tpl_vars['cartset']['id'],'text' => 'use in your digiplay profile','_formName' => 'dpsActUserCartsetForm','_moduleName' => 'DPS'), $this);?>

	<?php endif; ?>
      </td>
    </tr>
<?php endforeach; endif; unset($_from); ?>
  </table>
<div class='statiosubtitle'>Create new cartwall</div>
<form name="dpsNewUserCartsetForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
  <input type="hidden" name="formName" value="dpsNewUserCartsetForm" />
  <input type="hidden" name="moduleName" value="DPS" />
  <input type="hidden" name="templateID" value="66" />
  Name: <input type=text name='name' value=''><br>
  Description: <input type=text name='desc' value=''><br>
  <input type=submit name='submit' value='Add new'>
</form>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsstudiobottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>