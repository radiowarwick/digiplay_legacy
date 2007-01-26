<?php /* Smarty version 2.6.14, created on 2007-01-05 14:25:34
         compiled from rfile:/var/www/DPS/templates/dpsshedititem.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpsshedititem.tpl', 18, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsshowtopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
	<div class="showPlanList">
		<div class="bigTitle">
			<?php if ($this->_tpl_vars['VIEWER']['done'] == 't'): ?>
			<img class="showImgTitle" src="DPS/images/showFinished.png" alt="Finished">
			<?php else: ?>
			<?php if ($this->_tpl_vars['VIEWER']['show']['completed'] == 't'): ?>
			<img src="DPS/images/showReady.png" alt="Ready">
			<?php else: ?>
			<img class="showImgTitle" src="DPS/images/showUnfinished.png" alt="Unfinished">
			<?php endif; ?>
			<?php endif; ?>
			<?php echo $this->_tpl_vars['VIEWER']['show']['name']; ?>

		</div>
	  <i><?php echo $this->_tpl_vars['VIEWER']['show']['niceAirDate']; ?>
 - <?php echo $this->_tpl_vars['VIEWER']['show']['niceAirTime']; ?>
</i>
	</div>
	<div class="rightLinks">
		<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '82','text' => "<< Back to full show plan",'_showID' => $this->_tpl_vars['VIEWER']['show']['id']), $this);?>
<br>
		<div class="showSmall">only if you don't want to save changes!</div>
	</div>
	<br style="&7b;clear:both;&7c;" />
	<form name="dpsUserEditShowItem" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
	<input type="hidden" name="formName" value="dpsUserEditShowItem" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
	<input type="hidden" name="itemID" value="<?php echo $this->_tpl_vars['VIEWER']['item']['id']; ?>
" />
	<table class="showItems" width=100%>
		<tr>
			<th>Time</th><th>Element</th><th>Nature</th><th>Length</th><th>Note</th>
		</tr>
		<tr>
			<td>
				<b><?php echo $this->_tpl_vars['VIEWER']['item']['niceTime']; ?>
</b>
			</td>
			<td>
				<b><?php echo $this->_tpl_vars['VIEWER']['item']['title']; ?>
</b>
				<?php if ($this->_tpl_vars['VIEWER']['item']['audioTitle'] != ''): ?>
				<br /><?php echo $this->_tpl_vars['VIEWER']['item']['audioTitle']; ?>

				<?php endif; ?>
			</td>
			<td>
        <?php if ($this->_tpl_vars['VIEWER']['item']['nature'] == 'music'): ?>
				Music
				<?php elseif ($this->_tpl_vars['VIEWER']['item']['nature'] == 'jingle'): ?>
				Jingle
				<?php elseif ($this->_tpl_vars['VIEWER']['item']['nature'] == 'advert'): ?>
				Advert
				<?php else: ?>
				Other
				<?php endif; ?>
				<?php if ($this->_tpl_vars['VIEWER']['item']['script'] != ''): ?>
				+</a><br /><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => "",'text' => 'Script'), $this);?>

				<?php endif; ?>
			</td>
			<td>
				<?php echo $this->_tpl_vars['VIEWER']['item']['niceLength']; ?>

			</td>
			<td>
				<?php echo $this->_tpl_vars['VIEWER']['item']['comment']; ?>

			</td>
		</tr>
	</table>
	<div class="bigTitle">Edit Element</div>
	<div class="subTitle">You MUST save changes by clicking "Submit"</div>

	<table class="showEdititem">
		<tr>
			<th>Element type</th>
			<td>
        <?php if ($this->_tpl_vars['VIEWER']['item']['nature'] == 'music'): ?>
				Music
				<?php elseif ($this->_tpl_vars['VIEWER']['item']['nature'] == 'jingle'): ?>
				Jingle
				<?php elseif ($this->_tpl_vars['VIEWER']['item']['nature'] == 'advert'): ?>
				Advert
				<?php else: ?>
				Other
				<?php endif; ?>
			</td>
		</tr>
		<tr>
			<th>Element name</th>
			<td>
				<input type="text" name="title" value="<?php echo $this->_tpl_vars['VIEWER']['item']['title']; ?>
">
			</td>
			<th>
			</th>
		</tr>
		<tr>
			<th>Element audio</th>
			<td>	
				<?php if ($this->_tpl_vars['VIEWER']['item']['audioTitle'] != ''): ?>
				<?php echo $this->_tpl_vars['VIEWER']['item']['audioTitle']; ?>
 - <?php echo $this->_tpl_vars['VIEWER']['item']['niceAudioLength']; ?>
 (<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Remove','_formName' => 'dpsUserDelAudioShow','_moduleName' => 'DPS','_itemID' => $this->_tpl_vars['VIEWER']['item']['id']), $this);?>
)
				<?php else: ?>
				None (Add: <a href="javascript:NewWindow('?templateID=92&itemID=<?php echo $this->_tpl_vars['VIEWER']['item']['id']; ?>
','DPS Music','640','580');">Music</a>,
				<a href="javascript:NewWindow('?templateID=90&itemID=<?php echo $this->_tpl_vars['VIEWER']['item']['id']; ?>
','DPS Jingle',640,580);">Jingle</a>,
				<a href="javascript:NewWindow('?templateID=91&itemID=<?php echo $this->_tpl_vars['VIEWER']['item']['id']; ?>
','DPS Advert','640','580');">Advert</a>)
				<?php endif; ?>
			</td>
		</tr>
		<tr>
			<th>Associated script</th>
			<td>
				<?php if ($this->_tpl_vars['VIEWER']['item']['script'] != ''): ?>
				<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => "",'text' => $this->_tpl_vars['VIEWER']['item']['scriptName']), $this);?>
 - <?php echo $this->_tpl_vars['VIEWER']['item']['niceScriptLength']; ?>
 (<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Remove','_formName' => 'dpsUserDelScriptShow','_moduleName' => 'DPS','_itemID' => $this->_tpl_vars['VIEWER']['item']['id']), $this);?>
)
				<?php else: ?>
				None (Add: <a href="javascript:NewWindow('?templateID=95&itemID=<?php echo $this->_tpl_vars['VIEWER']['item']['id']; ?>
','DPS - Script','640','580');">Script</a>)
				<?php endif; ?>
			</td>
		</tr>
		<tr>
			<th>Length (MM:SS)</th>
			<td>
				<?php if ($this->_tpl_vars['VIEWER']['short'] == 't'): ?>
				<div class='error'>Warning: Item shorter than contents!</div>
				<?php endif; ?>
				<input type=text name="mins" maxlength=2 size=2 value="<?php echo $this->_tpl_vars['VIEWER']['item']['m']; ?>
" />:<input type=text name="secs" maxlength=2 size=2 value="<?php echo $this->_tpl_vars['VIEWER']['item']['s']; ?>
" />
			</td>
		</tr>
		<tr>
			<th>Note</th>
			<td>
				<textarea name="notes"><?php echo $this->_tpl_vars['VIEWER']['item']['comment']; ?>
</textarea>
			</td>
		</tr>
		<tr>
			<th></th>
			<th><input type="Submit" value="Save Changes" name="Submit" /></th>
		</tr>
	</table>
	</form>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsshowbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>