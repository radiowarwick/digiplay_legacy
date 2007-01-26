<?php /* Smarty version 2.6.14, created on 2006-11-20 11:20:46
         compiled from rfile:/var/www/DPS/templates/dpsshreorder.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpsshreorder.tpl', 19, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsshowtopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
  if ($this->_tpl_vars['VIEWER']['error'] != ''): ?>
	<?php echo $this->_tpl_vars['VIEWER']['error']; ?>

<?php else: ?>
	<div class="showPlanList">
		<div class="bigTitle">
			<?php if ($this->_tpl_vars['VIEWER']['done'] == 't'): ?>
			<img src="DPS/images/showFinished.png" alt="Finished">
			<?php else: ?>
			<?php if ($this->_tpl_vars['VIEWER']['show']['completed'] == 't'): ?>
			<img src="DPS/images/showReady.png" alt="Ready">
			<?php else: ?>
			<img src="DPS/images/showUnfinished.png" alt="Unfinished">
			<?php endif; ?>
			<?php endif; ?>
			<?php echo $this->_tpl_vars['VIEWER']['show']['name']; ?>
</div>
	  <i><?php echo $this->_tpl_vars['VIEWER']['show']['niceAirDate']; ?>
 - <?php echo $this->_tpl_vars['VIEWER']['show']['niceAirTime']; ?>
</i><br>
	</div>
	<div class="rightLinks"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '82','text' => "<< Back to full show plan",'_showID' => $this->_tpl_vars['VIEWER']['show']['id']), $this);?>
</div>
	<br style="&7b;clear:both;&7c;" />
	<hr>
	<div class="bigTitle">Show Order</div>
	<div class="subTitle">Click the arrows to move the items</div>
	<table class="showItems" width=100%>
		<tr>
			<th>No.</th><th>Time</th><th>Element</th><th colspan="2">Move</th><th>Options</th>
		</tr>
		<?php $_from = $this->_tpl_vars['VIEWER']['showItems']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['item']):
?>
		<tr>
			<td>
				<b><?php echo $this->_tpl_vars['item']['position']; ?>
</b>
			</td>
			<td>
				<b><?php echo $this->_tpl_vars['item']['niceTime']; ?>
</b>
			</td>
			<td>
				<b><?php echo $this->_tpl_vars['item']['title']; ?>
</b>
				<?php if ($this->_tpl_vars['item']['audioTitle'] != ''): ?>
				<br />
				<?php echo $this->_tpl_vars['item']['audioTitle']; ?>

				<?php endif; ?>
			</td>
			<?php if ($this->_tpl_vars['item']['position'] == 1): ?>
			<td width=40px>	
			</td>
			<td width=40px>
				<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => "<img scr='DPS/images/showUnfinished.png' alt='Down'>",'_itemID' => $this->_tpl_vars['item']['id'],'_formName' => 'dpsUserShowItemDown','_moduleName' => 'DPS','_showID' => $this->_tpl_vars['VIEWER']['show']['id']), $this);?>

			</td>
			<?php elseif ($this->_tpl_vars['item']['position'] == $this->_tpl_vars['VIEWER']['itemCount']): ?>
			<td>	
				<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => "<img scr='DPS/images/showUnfinished.png' alt='Up'>",'_itemID' => $this->_tpl_vars['item']['id'],'_formName' => 'dpsUserShowItemUp','_moduleName' => 'DPS','_showID' => $this->_tpl_vars['VIEWER']['show']['id']), $this);?>

			</td>
			<td>
			</td>
			<?php else: ?>
			<td>	
				<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => "<img scr='DPS/images/showUnfinished.png' alt='Up'>",'_itemID' => $this->_tpl_vars['item']['id'],'_formName' => 'dpsUserShowItemUp','_moduleName' => 'DPS','_showID' => $this->_tpl_vars['VIEWER']['show']['id']), $this);?>

			</td>
			<td>
				<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => "<img scr='DPS/images/showUnfinished.png' alt='Down'>",'_itemID' => $this->_tpl_vars['item']['id'],'_formName' => 'dpsUserShowItemDown','_moduleName' => 'DPS','_showID' => $this->_tpl_vars['VIEWER']['show']['id']), $this);?>

			</td>
			<?php endif; ?>
			<td>
				<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '85','text' => 'Edit','_itemID' => $this->_tpl_vars['item']['id']), $this);?>
<br><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Erase','_itemID' => $this->_tpl_vars['item']['id'],'_formName' => 'dpsUserDelShowItem','_moduleName' => 'DPS','_showID' => $this->_tpl_vars['VIEWER']['show']['id']), $this);?>

			</td>
		</tr>
		<?php endforeach; endif; unset($_from); ?>
	</table>
<?php endif;  $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsshowbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>