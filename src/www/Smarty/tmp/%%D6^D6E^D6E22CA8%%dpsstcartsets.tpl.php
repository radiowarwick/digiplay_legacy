<?php /* Smarty version 2.6.14, created on 2006-09-20 15:14:49
         compiled from rfile:/var/www/toolkit/DPS/templates/dpsstcartsets.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/toolkit/DPS/templates/dpsstcartsets.tpl', 36, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsstudiotopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
  <br>
  <br>
<div class='stationtitle'>Station Cartwall</div>

<div class='statioinfo1'>Available Cartsets for Station Cartwall</div>
<form name="dpsStationActCartsetForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
  <input type="hidden" name="formName" value="dpsStationActCartsetForm" />
  <input type="hidden" name="moduleName" value="DPS" />
  <input type="hidden" name="templateID" value="63" />
    <table border=1 class='statiotable'>
    <tr>
      <th width=120>
	Cartset
      </th>
      <th>
	Status
      </th>
      <th>
	Edit
      </th>
    </tr>
<?php $_from = $this->_tpl_vars['VIEWER']['cartsets']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['cartset']):
?>
    <tr>
      <td>
	<?php echo $this->_tpl_vars['cartset']['name']; ?>

      </td>
      <td>
      <?php if ($this->_tpl_vars['cartset']['active'] == 1): ?>
	<input type='radio' checked="checked" value='<?php echo $this->_tpl_vars['cartset']['id']; ?>
' name='activeSCW'>
      <?php else: ?>
	<input type='radio' value='<?php echo $this->_tpl_vars['cartset']['id']; ?>
' name='activeSCW'>
      <?php endif; ?>
      </td>
      <td>
	<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '64','_cartsetID' => $this->_tpl_vars['cartset']['id'],'text' => 'Edit'), $this);?>

      </td>
    </tr>
<?php endforeach; endif; unset($_from); ?>
  </table>
  <input type=submit value="Update" name=submit>
</form>
<div class='statiosubtitle'>New Cartset</div>
<form name="dpsNewStationCartsetForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
  <input type="hidden" name="formName" value="dpsNewStationCartsetForm" />
  <input type="hidden" name="moduleName" value="DPS" />
  <input type="hidden" name="templateID" value="63" />
  Name: <input type=text name='name' value=''><br>
  Description: <input type=text name='desc' value=''><br>
  <input type=submit name='submit' value='Add new'>
</form>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsstudiobottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>