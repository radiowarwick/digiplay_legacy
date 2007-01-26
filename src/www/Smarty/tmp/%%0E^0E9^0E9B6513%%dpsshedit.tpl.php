<?php /* Smarty version 2.6.14, created on 2007-01-05 14:25:30
         compiled from rfile:/var/www/DPS/templates/dpsshedit.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpsshedit.tpl', 31, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsshowtopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
  if ($this->_tpl_vars['VIEWER']['error']): ?>
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
		<b>Length: </b> <?php echo $this->_tpl_vars['VIEWER']['show']['niceLength']; ?>
<br />
		<!--<b>Genre: </b> Pop/Speech<br />-->
		<b>Producer: </b> <?php echo $this->_tpl_vars['VIEWER']['show']['niceProducer']; ?>
<br />
		<!--<b>Participants: </b> People, Many many people<br />
		<a href="">Edit details and participants</a>-->
	</div>
	<div class="showPlanHelp">
		<img src="DPS/images/showFinished.png" alt="Finished"> Already broadcast<br>
	  <img src="DPS/images/showUnfinished.png" alt="Uninished"> Unfinished<br>
	  <img src="DPS/images/showReady.png" alt="Ready"> Finished & ready<br>
	</div>
	<div class="rightLinks"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '81','text' => "<< Back to your shows"), $this);?>
</div>
	<br style="&7b;clear:both;&7c;" />
	<hr>
	<?php if ($this->_tpl_vars['VIEWER']['show']['completed'] == 't'): ?>
	<div class="showLinks"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => "<img src='DPS/images/showUnfinished.png' alt='Finished'>Declare show not finished",'_formName' => 'dpsUserUnCompleteShow','_moduleName' => 'DPS','_showID' => $this->_tpl_vars['VIEWER']['show']['id']), $this);?>
</div>
	<?php else: ?>
	<div class="showLinks"><img src="DPS/images/showUnfinished.png" alt="Add"> <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Add Element','_formName' => 'dpsUserAddShowItem','_moduleName' => 'DPS','_showID' => $this->_tpl_vars['VIEWER']['show']['id']), $this);?>
</div>
	<div class="showLinks">
		<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '83','text' => "<img src='DPS/images/showUnfinished.png' alt='Order'> Change Order",'_showID' => $this->_tpl_vars['VIEWER']['show']['id']), $this);?>

	</div>
	<div class="showLinks"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => "<img src='DPS/images/showUnfinished.png' alt='Unfinish'>Declare show finished",'_formName' => 'dpsUserCompleteShow','_moduleName' => 'DPS','_showID' => $this->_tpl_vars['VIEWER']['show']['id']), $this);?>
</div>
	<?php endif; ?>
<!--	<div class="showWarning">Show has 01:40:35 unlabelled</div>-->
	<br style="&7b;clear:both;&7c;" />
	<table class="showItems" width=100%>
		<tr>
			<th>Time</th><th>Element</th><th>Nature</th><th>Length</th><th>Note</th>
			<?php if ($this->_tpl_vars['VIEWER']['done'] != 't' && $this->_tpl_vars['VIEWER']['show']['completed'] != 't'): ?>
			<th></th>
			<?php endif; ?>
		</tr>
		<?php $_from = $this->_tpl_vars['VIEWER']['showItems']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['item']):
?>
		<tr>
			<td>
				<b><?php echo $this->_tpl_vars['item']['niceTime']; ?>
</b>
			</td>
			<td>
				<b><?php echo $this->_tpl_vars['item']['title']; ?>
</b><br>
				<?php echo $this->_tpl_vars['item']['audioTitle']; ?>

			</td>
			<td>
				<?php if ($this->_tpl_vars['item']['nature'] == 'music'): ?>
				Music
				<?php elseif ($this->_tpl_vars['item']['nature'] == 'jingle'): ?>
				Jingle
				<?php elseif ($this->_tpl_vars['item']['nature'] == 'advert'): ?>
				Advert
				<?php else: ?>
				Other
				<?php endif; ?>
				<?php if ($this->_tpl_vars['item']['script'] != ''): ?>
				+<br /><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => "",'text' => 'Script'), $this);?>

				<?php endif; ?>
			</td>
			<td>
				<?php echo $this->_tpl_vars['item']['niceLength']; ?>

			</td>
			<td>
				<?php echo $this->_tpl_vars['item']['comment']; ?>

			</td>
			<?php if ($this->_tpl_vars['VIEWER']['done'] != 't' && $this->_tpl_vars['VIEWER']['show']['completed'] != 't'): ?>
			<td>
				<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '85','text' => 'Edit','_itemID' => $this->_tpl_vars['item']['id']), $this);?>
<br><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Erase','_itemID' => $this->_tpl_vars['item']['id'],'_formName' => 'dpsUserDelShowItem','_moduleName' => 'DPS','_showID' => $this->_tpl_vars['VIEWER']['show']['id']), $this);?>

			</td>
			<?php endif; ?>
		</tr>
		<?php endforeach; endif; unset($_from); ?>
	</table>
<?php endif;  $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsshowbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>