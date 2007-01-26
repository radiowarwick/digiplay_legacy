<?php /* Smarty version 2.6.14, created on 2007-01-05 14:54:33
         compiled from rfile:/var/www/DPS/templates/dpssteditcartwall.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpssteditcartwall.tpl', 6, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsstudiotopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager','studio' => $this->_tpl_vars['VIEWER']['studioAccess'],'access_playlist' => $this->_tpl_vars['VIEWER']['access_playlist'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
  <br>
  <br>
  <div class='FloatL'><div class='bigTitle'>Edit Cartwall</div></div>
  <div class='cartwallinfoR'>
    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '66','text' => "<<< return to cartwall profiles"), $this);?>
<br>
    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '67','text' => "<<< preview cartwall",'_cartset' => $this->_tpl_vars['VIEWER']['cartsetID'],'_page' => $this->_tpl_vars['VIEWER']['cartwall']['page']), $this);?>

  </div>
  <br style='clear: both;'>
  <?php if ($this->_tpl_vars['VIEWER']['permError'] == 't'): ?>
    You do not have permission to view this cartwall.
  <?php else: ?>
  <form name="dpsUserCartwallEditForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
  <input type="hidden" name="formName" value="dpsUserCartwallEditForm" />
  <input type="hidden" name="moduleName" value="DPS" />
  <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
  <input type="hidden" name="cartset" value="<?php echo $this->_tpl_vars['VIEWER']['cartsetID']; ?>
" />
  <input type="hidden" name="cartwallID" value="<?php echo $this->_tpl_vars['VIEWER']['cartwall']['id']; ?>
" />
  <input type="hidden" name="page" value="<?php echo $this->_tpl_vars['VIEWER']['cartwall']['page']; ?>
" />
  <?php if ($this->_tpl_vars['ERRORS']['name']): ?><div class='frame_musicboxerror'><?php echo $this->_tpl_vars['ERRORS']['name']; ?>
</div><?php endif; ?>
  <div class='cartwallinfoL'>Name: <input type=text name=name value="<?php echo $this->_tpl_vars['VIEWER']['cartwall']['name']; ?>
"></div>
  <br style='clear: both;'>
  <?php if ($this->_tpl_vars['ERRORS']['desc']): ?><div class='frame_musicboxerror'><?php echo $this->_tpl_vars['ERRORS']['desc']; ?>
</div><?php endif; ?>
  <div class='cartwallinfoL'>Desc: <input type=text size=35 name=desc value="<?php echo $this->_tpl_vars['VIEWER']['cartwall']['description']; ?>
"></div>
  <div class='cartwallPage'>
    <img src='DPS/images/cartwallPageL.png' class='cartwallPageL'>
    <div class='cartwallpagenum'>
      Page: 
      <?php $_from = $this->_tpl_vars['VIEWER']['pagelink']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['pages']):
?>
	<?php if ($this->_tpl_vars['pages']['id'] == $this->_tpl_vars['VIEWER']['cartwall']['page']): ?>
	  <b><?php echo $this->_tpl_vars['pages']['num']; ?>
</b> 
	<?php else: ?>
	  <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => $this->_tpl_vars['pages']['num'],'_cartset' => $this->_tpl_vars['VIEWER']['cartsetID'],'_page' => $this->_tpl_vars['pages']['id']), $this);?>
 
	<?php endif; ?>
      <?php endforeach; endif; unset($_from); ?>
      <a href='<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
?templateID=<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
&cartwallID=<?php echo $this->_tpl_vars['VIEWER']['cartwall']['id']; ?>
&cartset=<?php echo $this->_tpl_vars['VIEWER']['cartsetID']; ?>
&page=<?php echo $this->_tpl_vars['VIEWER']['cartwall']['page']; ?>
&moduleName=DPS&formName=dpsUserAddCartwallPageForm'>+</a>
    </div>
    <img src='DPS/images/cartwallPageR.png' class='cartwallPageR'>
  </div>
  <br style='clear: both;'>
  <table class="cartwall">
    <tr>
      <td>
	<?php if ($this->_tpl_vars['VIEWER']['cart1']['audioid'] == 'none'): ?>
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=69&cartID=New&cartPos=0&cartwallID=<?php echo $this->_tpl_vars['VIEWER']['cartwall']['id']; ?>
','acepopup','640','480');">Add</a></div>
	<?php else: ?>
	<div class='EcartText'><?php echo $this->_tpl_vars['VIEWER']['cart1']['name']; ?>
</div>
	<div class='EcartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart1']['title']; ?>
</div>
	<div class='EcartTime'><?php echo $this->_tpl_vars['VIEWER']['cart1']['length']; ?>
</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=69&cartID=<?php echo $this->_tpl_vars['VIEWER']['cart1']['id']; ?>
','acepopup','640','480');">Change</a></div>
	<?php endif; ?>
      </td>
      <td >
	<?php if ($this->_tpl_vars['VIEWER']['cart2']['audioid'] == 'none'): ?>
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=69&cartID=New&cartPos=1&cartwallID=<?php echo $this->_tpl_vars['VIEWER']['cartwall']['id']; ?>
','acepopup','640','480');">Add</a></div>
	<?php else: ?>
	<div class='EcartText'><?php echo $this->_tpl_vars['VIEWER']['cart2']['name']; ?>
</div>
	<div class='EcartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart2']['title']; ?>
</div>
	<div class='EcartTime'><?php echo $this->_tpl_vars['VIEWER']['cart2']['length']; ?>
</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=69&cartID=<?php echo $this->_tpl_vars['VIEWER']['cart2']['id']; ?>
','acepopup','640','480');">Change</a></div>
	<?php endif; ?>
      </td>
      <td >
	<?php if ($this->_tpl_vars['VIEWER']['cart3']['audioid'] == 'none'): ?>
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=69&cartID=New&cartPos=2&cartwallID=<?php echo $this->_tpl_vars['VIEWER']['cartwall']['id']; ?>
','acepopup','640','480');">Add</a></div>
	<?php else: ?>
	<div class='EcartText'><?php echo $this->_tpl_vars['VIEWER']['cart3']['name']; ?>
</div>
	<div class='EcartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart3']['title']; ?>
</div>
	<div class='EcartTime'><?php echo $this->_tpl_vars['VIEWER']['cart3']['length']; ?>
</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=69&cartID=<?php echo $this->_tpl_vars['VIEWER']['cart3']['id']; ?>
','acepopup','640','480');">Change</a></div>
	<?php endif; ?>
      </td>
    </tr>
    <tr>
      <td>
	<?php if ($this->_tpl_vars['VIEWER']['cart4']['audioid'] == 'none'): ?>
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=69&cartID=New&cartPos=3&cartwallID=<?php echo $this->_tpl_vars['VIEWER']['cartwall']['id']; ?>
','acepopup','640','480');">Add</a></div>
	<?php else: ?>
	<div class='EcartText'><?php echo $this->_tpl_vars['VIEWER']['cart4']['name']; ?>
</div>
	<div class='EcartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart4']['title']; ?>
</div>
	<div class='EcartTime'><?php echo $this->_tpl_vars['VIEWER']['cart4']['length']; ?>
</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=69&cartID=<?php echo $this->_tpl_vars['VIEWER']['cart4']['id']; ?>
','acepopup','640','480');">Change</a></div>
	<?php endif; ?>
      </td>
      <td>
	<?php if ($this->_tpl_vars['VIEWER']['cart5']['audioid'] == 'none'): ?>
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=69&cartID=New&cartPos=4&cartwallID=<?php echo $this->_tpl_vars['VIEWER']['cartwall']['id']; ?>
','acepopup','640','480');">Add</a></div>
	<?php else: ?>
	<div class='EcartText'><?php echo $this->_tpl_vars['VIEWER']['cart5']['name']; ?>
</div>
	<div class='EcartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart5']['title']; ?>
</div>
	<div class='EcartTime'><?php echo $this->_tpl_vars['VIEWER']['cart5']['length']; ?>
</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=69&cartID=<?php echo $this->_tpl_vars['VIEWER']['cart5']['id']; ?>
','acepopup','640','480');">Change</a></div>
	<?php endif; ?>
      </td>
      <td>
	<?php if ($this->_tpl_vars['VIEWER']['cart6']['audioid'] == 'none'): ?>
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=69&cartID=New&cartPos=5&cartwallID=<?php echo $this->_tpl_vars['VIEWER']['cartwall']['id']; ?>
','acepopup','640','480');">Add</a></div>
	<?php else: ?>
	<div class='EcartText'><?php echo $this->_tpl_vars['VIEWER']['cart6']['name']; ?>
</div>
	<div class='EcartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart6']['title']; ?>
</div>
	<div class='EcartTime'><?php echo $this->_tpl_vars['VIEWER']['cart6']['length']; ?>
</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=69&cartID=<?php echo $this->_tpl_vars['VIEWER']['cart6']['id']; ?>
','acepopup','640','480');">Change</a></div>
	<?php endif; ?>
      </td>
    </tr>
    <tr>
      <td>
	<?php if ($this->_tpl_vars['VIEWER']['cart7']['audioid'] == 'none'): ?>
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=69&cartID=New&cartPos=6&cartwallID=<?php echo $this->_tpl_vars['VIEWER']['cartwall']['id']; ?>
','acepopup','640','480');">Add</a></div>
	<?php else: ?>
	<div class='EcartText'><?php echo $this->_tpl_vars['VIEWER']['cart7']['name']; ?>
</div>
	<div class='EcartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart7']['title']; ?>
</div>
	<div class='EcartTime'><?php echo $this->_tpl_vars['VIEWER']['cart7']['length']; ?>
</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=69&cartID=<?php echo $this->_tpl_vars['VIEWER']['cart7']['id']; ?>
','acepopup','640','480');">Change</a></div>
	<?php endif; ?>
      </td>
      <td>
	<?php if ($this->_tpl_vars['VIEWER']['cart8']['audioid'] == 'none'): ?>
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=69&cartID=New&cartPos=7&cartwallID=<?php echo $this->_tpl_vars['VIEWER']['cartwall']['id']; ?>
','acepopup','640','480');">Add</a></div>
	<?php else: ?>
	<div class='EcartText'><?php echo $this->_tpl_vars['VIEWER']['cart8']['name']; ?>
</div>
	<div class='EcartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart8']['title']; ?>
</div>
	<div class='EcartTime'><?php echo $this->_tpl_vars['VIEWER']['cart8']['length']; ?>
</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=69&cartID=<?php echo $this->_tpl_vars['VIEWER']['cart8']['id']; ?>
','acepopup','640','480');">Change</a></div>
	<?php endif; ?>
      </td>
      <td>
	<?php if ($this->_tpl_vars['VIEWER']['cart9']['audioid'] == 'none'): ?>
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=69&cartID=New&cartPos=8&cartwallID=<?php echo $this->_tpl_vars['VIEWER']['cartwall']['id']; ?>
','acepopup','640','480');">Add</a></div>
	<?php else: ?>
	<div class='EcartText'><?php echo $this->_tpl_vars['VIEWER']['cart9']['name']; ?>
</div>
	<div class='EcartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart9']['title']; ?>
</div>
	<div class='EcartTime'><?php echo $this->_tpl_vars['VIEWER']['cart9']['length']; ?>
</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=69&cartID=<?php echo $this->_tpl_vars['VIEWER']['cart9']['id']; ?>
','acepopup','640','480');">Change</a></div>
	<?php endif; ?>
      </td>
    </tr>
    <tr>
      <td>
	<?php if ($this->_tpl_vars['VIEWER']['cart10']['audioid'] == 'none'): ?>
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=69&cartID=New&cartPos=9&cartwallID=<?php echo $this->_tpl_vars['VIEWER']['cartwall']['id']; ?>
','acepopup','640','480');">Add</a></div>
	<?php else: ?>
	<div class='EcartText'><?php echo $this->_tpl_vars['VIEWER']['cart10']['name']; ?>
</div>
	<div class='EcartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart10']['title']; ?>
</div>
	<div class='EcartTime'><?php echo $this->_tpl_vars['VIEWER']['cart10']['length']; ?>
</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=69&cartID=<?php echo $this->_tpl_vars['VIEWER']['cart10']['id']; ?>
','acepopup','640','480');">Change</a></div>
	<?php endif; ?>
      </td>
      <td>
	<?php if ($this->_tpl_vars['VIEWER']['cart11']['audioid'] == 'none'): ?>
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=69&cartID=New&cartPos=10&cartwallID=<?php echo $this->_tpl_vars['VIEWER']['cartwall']['id']; ?>
','acepopup','640','480');">Add</a></div>
	<?php else: ?>
	<div class='EcartText'><?php echo $this->_tpl_vars['VIEWER']['cart11']['name']; ?>
</div>
	<div class='EcartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart11']['title']; ?>
</div>
	<div class='EcartTime'><?php echo $this->_tpl_vars['VIEWER']['cart11']['length']; ?>
</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=69&cartID=<?php echo $this->_tpl_vars['VIEWER']['cart11']['id']; ?>
','acepopup','640','480');">Change</a></div>
	<?php endif; ?>
      </td>
      <td>
	<?php if ($this->_tpl_vars['VIEWER']['cart12']['audioid'] == 'none'): ?>
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=69&cartID=New&cartPos=11&cartwallID=<?php echo $this->_tpl_vars['VIEWER']['cartwall']['id']; ?>
','acepopup','640','480');">Add</a></div>
	<?php else: ?>
	<div class='EcartText'><?php echo $this->_tpl_vars['VIEWER']['cart12']['name']; ?>
</div>
	<div class='EcartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart12']['title']; ?>
</div>
	<div class='EcartTime'><?php echo $this->_tpl_vars['VIEWER']['cart12']['length']; ?>
</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=69&cartID=<?php echo $this->_tpl_vars['VIEWER']['cart12']['id']; ?>
','acepopup','640','480');">Change</a></div>
	<?php endif; ?>
      </td>
    </tr>
  </table>
  <div class='EcartwallPerms'>
    <?php if ($this->_tpl_vars['VIEWER']['owner'] == 't'): ?>
    <?php if ($this->_tpl_vars['VIEWER']['groupread']): ?>
    <input type="checkbox" name="readAll" value="on" checked>Allow others to use this cartset<br>
    <?php else: ?>
    <input type="checkbox" name="readAll" value="on">Allow others to use this cartset<br>
    <?php endif; ?>
    <?php if ($this->_tpl_vars['VIEWER']['groupwrite']): ?>
    <input type="checkbox" name="writeAll" value="on" checked>Allow others to edit this cartset<br>
    <?php else: ?>
    <input type="checkbox" name="writeAll" value="on">Allow others to edit this cartset<br>
    <?php endif; ?>
    <?php endif; ?>
    <b>don't forget to save your changes!</b>
  </div>
  <div class='EcartwallSubmit'>
    <input type="Submit" name="Submit" value="Save Changes"><br>
    <input type="Submit" name="Submit" value="Remove Page">
  </div>
  </form>
  <br style='clear: both;'>
  <div class="warning"><?php echo $this->_tpl_vars['ERRORS']['model']; ?>
</div>
  <?php endif;  $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsstudiobottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>