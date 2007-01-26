<?php /* Smarty version 2.6.14, created on 2006-12-17 18:15:04
         compiled from rfile:/var/www/DPS/templates/dpssheditdetails.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpssheditdetails.tpl', 54, false),)), $this); ?>
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
		<b>New Details</b><br />
		<form name="dpsUserEditShow" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
		<input type="hidden" name="formName" value="dpsUserEditShow" />
		<input type="hidden" name="moduleName" value="DPS" />
		<input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
		<input type="hidden" name="showID" value="<?php echo $this->_tpl_vars['VIEWER']['show']['id']; ?>
" />
		Name: <input type="text" name="name" value="<?php echo $this->_tpl_vars['VIEWER']['show']['name']; ?>
"/><br />
		<?php if ($this->_tpl_vars['ERRORS']['dpsUserEditShow']['form'] != ''): ?>
			<?php echo $this->_tpl_vars['ERRORS']['dpsUserEditShow']['form']; ?>
<br />
		<?php endif; ?>
		Airing Date:
		<select name="day" text="<?php echo $this->_tpl_vars['VIEWER']['show']['D']; ?>
">
			<?php echo $this->_tpl_vars['VIEWER']['formOpts']['date']; ?>

		</select>
		<select name="month" value="<?php echo $this->_tpl_vars['VIEWER']['show']['M']; ?>
">
			<?php echo $this->_tpl_vars['VIEWER']['formOpts']['month']; ?>

		</select>
		<select name="year" text="<?php echo $this->_tpl_vars['VIEWER']['show']['Y']; ?>
">
			<?php echo $this->_tpl_vars['VIEWER']['formOpts']['year']; ?>

		</select><br />
		<?php if ($this->_tpl_vars['ERRORS']['dpsUserEditShow']['hours'] != ''): ?>
			<?php echo $this->_tpl_vars['ERRORS']['dpsUserEditShow']['hours']; ?>
<br />
		<?php elseif ($this->_tpl_vars['ERRORS']['dpsUserEditShow']['mins'] != ''): ?>
			<?php echo $this->_tpl_vars['ERRORS']['dpsUserEditShow']['mins']; ?>
<br />
		<?php endif; ?>
		Airing Time(24h): <input type=text name="hours" maxlength=2 size=2 value="<?php echo $this->_tpl_vars['VIEWER']['show']['h']; ?>
" />:<input type=text name="mins" maxlength=2 size=2 value="<?php echo $this->_tpl_vars['VIEWER']['show']['m']; ?>
" /><br />
		<b>Producer: </b> <?php echo $this->_tpl_vars['VIEWER']['show']['niceProducer']; ?>
<br />
		<!--<b>Participants: </b> People, Many many people<br />
		<a href="">Edit details and participants</a>-->
		<input type="Submit" name="Submit" value="Submit" />
	</div>
	<div class="showPlanHelp">
		<img src="DPS/images/showFinished.png" alt="Finished"> Already broadcast<br>
	  <img src="DPS/images/showUnfinished.png" alt="Uninished"> Unfinished<br>
	  <img src="DPS/images/showReady.png" alt="Ready"> Finished & ready<br>
	</div>
	<div class="rightLinks"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '81','text' => "<< Back to your shows"), $this);?>
</div>
	<br style="&7b;clear:both;&7c;" />
<?php endif;  $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsshowbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>