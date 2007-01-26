<?php /* Smarty version 2.6.14, created on 2006-10-26 18:45:50
         compiled from rfile:/var/www/DPS/templates/dpsstviewcartwall.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpsstviewcartwall.tpl', 6, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsstudiotopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager','studio' => $this->_tpl_vars['VIEWER']['studioAccess'],'access_playlist' => $this->_tpl_vars['VIEWER']['access_playlist'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
  <br>
  <br>
  <div class='FloatL'><div class='bigTitle'>View Cartwall</div></div>
  <div class='cartwallinfoR'>
    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '66','text' => "<<< return to cartwall profiles"), $this);?>
 
    <?php if ($this->_tpl_vars['VIEWER']['editperm'] == 't'): ?>
    <br><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '68','text' => "<<< edit cartwall",'_cartset' => $this->_tpl_vars['VIEWER']['cartsetID'],'_page' => $this->_tpl_vars['VIEWER']['cartwall']['page']), $this);?>
 
    <?php endif; ?>
  </div>
  <br style='clear: both;'>
  <?php if ($this->_tpl_vars['VIEWER']['permError'] == 't'): ?>
    You do not have permission to view this cartwall.
  <?php else: ?>
  <div class='cartwallinfoL'>
    Name: <b><?php echo $this->_tpl_vars['VIEWER']['cartwall']['name']; ?>
</b>
  </div>
  <br style='clear: both;'>
  <div class='cartwallinfoL'>
    Desc: <b><?php echo $this->_tpl_vars['VIEWER']['cartwall']['description']; ?>
</b>
  </div>
  <div class='cartwallPage'>
    <img src='DPS/images/cartwallPageL.png' class='cartwallPageL'>
    <div class='cartwallpagenum'>
      Page: 
      <?php $_from = $this->_tpl_vars['VIEWER']['pagelink']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['pages']):
?>
	<?php if ($this->_tpl_vars['pages']['active'] == 't'): ?>
	  <b><?php echo $this->_tpl_vars['pages']['num']; ?>
</b> 
	<?php else: ?>
	  <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '67','text' => $this->_tpl_vars['pages']['num'],'_cartset' => $this->_tpl_vars['VIEWER']['cartsetID'],'_page' => $this->_tpl_vars['pages']['id']), $this);?>
 
	<?php endif; ?>
      <?php endforeach; endif; unset($_from); ?>
    </div>
    <img src='DPS/images/cartwallPageR.png' class='cartwallPageR'>
  </div>
  <br style='clear: both;'>
  <table class="cartwall">
    <tr>
      <td style='background: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart1']['BackColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart1']['BackColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart1']['BackColour']['b']; ?>
); color: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart1']['ForeColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart1']['ForeColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart1']['ForeColour']['b']; ?>
)'>
	<div class='cartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart1']['name']; ?>
</div>
	<div class='cartTime'><?php echo $this->_tpl_vars['VIEWER']['cart1']['length']; ?>
</div>
      </td>
      <td style='background: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart2']['BackColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart2']['BackColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart2']['BackColour']['b']; ?>
); color: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart2']['ForeColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart2']['ForeColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart2']['ForeColour']['b']; ?>
)'>
	<div class='cartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart2']['name']; ?>
</div>
	<div class='cartTime'><?php echo $this->_tpl_vars['VIEWER']['cart2']['length']; ?>
</div>
      </td>
      <td style='background: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart3']['BackColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart3']['BackColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart3']['BackColour']['b']; ?>
); color: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart3']['ForeColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart3']['ForeColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart3']['ForeColour']['b']; ?>
)'>
	<div class='cartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart3']['name']; ?>
</div>
	<div class='cartTime'><?php echo $this->_tpl_vars['VIEWER']['cart3']['length']; ?>
</div>
      </td>
    </tr>
    <tr>
      <td style='background: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart4']['BackColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart4']['BackColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart4']['BackColour']['b']; ?>
); color: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart4']['ForeColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart4']['ForeColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart4']['ForeColour']['b']; ?>
)'>
	<div class='cartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart4']['name']; ?>
</div>
	<div class='cartTime'><?php echo $this->_tpl_vars['VIEWER']['cart4']['length']; ?>
</div>
      </td>
      <td style='background: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart5']['BackColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart5']['BackColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart5']['BackColour']['b']; ?>
); color: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart5']['ForeColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart5']['ForeColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart5']['ForeColour']['b']; ?>
)'>
	<div class='cartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart5']['name']; ?>
</div>
	<div class='cartTime'><?php echo $this->_tpl_vars['VIEWER']['cart5']['length']; ?>
</div>
      </td>
      <td style='background: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart6']['BackColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart6']['BackColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart6']['BackColour']['b']; ?>
); color: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart6']['ForeColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart6']['ForeColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart6']['ForeColour']['b']; ?>
)'>
	<div class='cartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart6']['name']; ?>
</div>
	<div class='cartTime'><?php echo $this->_tpl_vars['VIEWER']['cart6']['length']; ?>
</div>
      </td>
    </tr>
    <tr>
      <td style='background: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart7']['BackColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart7']['BackColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart7']['BackColour']['b']; ?>
); color: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart7']['ForeColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart7']['ForeColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart7']['ForeColour']['b']; ?>
)'>
	<div class='cartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart7']['name']; ?>
</div>
	<div class='cartTime'><?php echo $this->_tpl_vars['VIEWER']['cart7']['length']; ?>
</div>
      </td>
      <td style='background: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart8']['BackColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart8']['BackColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart8']['BackColour']['b']; ?>
); color: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart8']['ForeColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart8']['ForeColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart8']['ForeColour']['b']; ?>
)'>
	<div class='cartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart8']['name']; ?>
</div>
	<div class='cartTime'><?php echo $this->_tpl_vars['VIEWER']['cart8']['length']; ?>
</div>
      </td>
      <td style='background: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart9']['BackColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart9']['BackColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart9']['BackColour']['b']; ?>
); color: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart9']['ForeColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart9']['ForeColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart9']['ForeColour']['b']; ?>
)'>
	<div class='cartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart9']['name']; ?>
</div>
	<div class='cartTime'><?php echo $this->_tpl_vars['VIEWER']['cart9']['length']; ?>
</div>
      </td>
    </tr>
    <tr>
      <td style='background: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart10']['BackColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart10']['BackColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart10']['BackColour']['b']; ?>
); color: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart10']['ForeColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart10']['ForeColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart10']['ForeColour']['b']; ?>
)'>
	<div class='cartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart10']['name']; ?>
</div>
	<div class='cartTime'><?php echo $this->_tpl_vars['VIEWER']['cart10']['length']; ?>
</div>
      </td>
      <td style='background: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart11']['BackColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart11']['BackColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart11']['BackColour']['b']; ?>
); color: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart11']['ForeColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart11']['ForeColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart11']['ForeColour']['b']; ?>
)'>
	<div class='cartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart11']['name']; ?>
</div>
	<div class='cartTime'><?php echo $this->_tpl_vars['VIEWER']['cart11']['length']; ?>
</div>
      </td>
      <td style='background: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart12']['BackColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart12']['BackColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart12']['BackColour']['b']; ?>
); color: rgb(<?php echo $this->_tpl_vars['VIEWER']['cart12']['ForeColour']['r']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart12']['ForeColour']['g']; ?>
,<?php echo $this->_tpl_vars['VIEWER']['cart12']['ForeColour']['b']; ?>
)'>
	<div class='cartTitle'><?php echo $this->_tpl_vars['VIEWER']['cart12']['name']; ?>
</div>
	<div class='cartTime'><?php echo $this->_tpl_vars['VIEWER']['cart12']['length']; ?>
</div>
      </td>
    </tr>
  </table>
  <?php endif;  $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsstudiobottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>