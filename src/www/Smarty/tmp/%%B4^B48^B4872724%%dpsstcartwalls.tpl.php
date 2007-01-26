<?php /* Smarty version 2.6.14, created on 2006-09-20 15:14:54
         compiled from rfile:/var/www/toolkit/DPS/templates/dpsstcartwalls.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/toolkit/DPS/templates/dpsstcartwalls.tpl', 7, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsstudiotopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
  <br>
  <br>
<h1><?php echo $this->_tpl_vars['VIEWER']['setName']; ?>
 Cartset</h1>

    <hr>
    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '63','text' => 'Station Cartwalls'), $this);?>
 -> <?php echo $this->_tpl_vars['VIEWER']['setName']; ?>

    <hr>
<form name="dpsEStationCartsetForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
  <input type="hidden" name="formName" value="dpsEStationCartsetForm" />
  <input type="hidden" name="moduleName" value="DPS" />
  <input type="hidden" name="templateID" value="64" />
  <input type="hidden" name="cartsetID" value="<?php echo $this->_tpl_vars['VIEWER']['setID']; ?>
" />
  Name: <input type=text name='name' value='<?php echo $this->_tpl_vars['VIEWER']['setName']; ?>
'><br>
  Description: <input type=text name='desc' size=30 value='<?php echo $this->_tpl_vars['VIEWER']['setDescription']; ?>
'><br>
  <input type=submit name='submit' value='Update'>
</form>
<form name="dpsDStationCartsetForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
  <input type="hidden" name="formName" value="dpsDStationCartsetForm" />
  <input type="hidden" name="moduleName" value="DPS" />
  <input type="hidden" name="templateID" value="63" />
  <input type="hidden" name="cartsetID" value="<?php echo $this->_tpl_vars['VIEWER']['setID']; ?>
" />
  <input type=submit name='submit' value='Delete Cartset'>
</form>
    <table border=1>
      <tr>
        <th>
	  Page
        </th>

        <th>
          Carts
        </th>
       </tr>
      <?php $_from = $this->_tpl_vars['VIEWER']['cartwalls']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['wall']):
?>
      <tr>
	<td valign=top>
	  <?php echo $this->_tpl_vars['wall']['name']; ?>

	</td>
        <td>
	  <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => 65,'_cartwallID' => $this->_tpl_vars['wall']['id'],'text' => 'Edit'), $this);?>

        </td>
      </tr>
      <?php endforeach; endif; unset($_from); ?>
    </table>

    <b>New Cartwall</b><br>
<form name="dpsAStationCartwallForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
  <input type="hidden" name="formName" value="dpsAStationCartwallForm" />
  <input type="hidden" name="moduleName" value="DPS" />
  <input type="hidden" name="templateID" value="64" />
  <input type="hidden" name="cartsetID" value="<?php echo $this->_tpl_vars['VIEWER']['setID']; ?>
" />
  Name: <input type=text name='name' value=''><br>
  Description: <input type=text name='desc' value=''><br>
  <input type=submit name='submit' value='Add new'>
</form>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsstudiobottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>