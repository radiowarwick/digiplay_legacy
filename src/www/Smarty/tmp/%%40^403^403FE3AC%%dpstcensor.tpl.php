<?php /* Smarty version 2.6.14, created on 2006-10-26 22:30:44
         compiled from rfile:/var/www/DPS/templates/dpstcensor.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpstcensor.tpl', 23, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsmusictopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager','RequestTrack' => $this->_tpl_vars['VIEWER']['RequestTrack'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
	    <div class="bigTitle">Censored Tracks</div>
	    <div class="subTitle">
	      <?php echo $this->_tpl_vars['VIEWER']['flagNum']; ?>
 tracks have been recommened for censorship<br>
	      <?php echo $this->_tpl_vars['VIEWER']['censorNum']; ?>
 tracks have been censored
	    </div>
	    <hr \>
	    <?php if ($this->_tpl_vars['VIEWER']['flagNum']): ?>
	    <div class="musicCensorInfo1">Recommended for censorship</div>
	    <div class="musicCensorInstructions1">Select tick-box to censor</div>
			<?php if ($this->_tpl_vars['VIEWER']['CensorTrack'] == 't'): ?>
	    <form name='dpsTrackAddCensorForm'method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
	      <input type="hidden" name="formName" value="dpsTrackAddCensorForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
			<?php endif; ?>
	    <div class="musicCensorRecommend">
	      <table class="musicCensorRecommend">
					<?php $_from = $this->_tpl_vars['VIEWER']['flaggedTracks']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['ftrack']):
?>
					<tr>
		  			<td><?php echo $this->_tpl_vars['ftrack']['artist']; ?>
</td>
		  			<td><?php echo $this->_tpl_vars['ftrack']['title']; ?>
</td>
		  			<td><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '57','text' => 'Preview','_trackID' => $this->_tpl_vars['ftrack']['id']), $this);?>
</td>
		  			<?php if ($this->_tpl_vars['VIEWER']['CensorTrack'] == 't'): ?>
		  			<td>
		    			<input type="checkbox" name="checkbox_<?php echo $this->_tpl_vars['ftrack']['searchNumber']; ?>
">
		    			<input type="hidden" name="trackID_<?php echo $this->_tpl_vars['ftrack']['searchNumber']; ?>
" value="<?php echo $this->_tpl_vars['ftrack']['id']; ?>
">
		  			</td>
		  			<?php endif; ?>
					</tr>
					<?php endforeach; endif; unset($_from); ?>
	      </table> 
	    </div>
	    <div>
	    	<div class="musicCensorInstructions2">
	      	Censored tracks cannot be played through Digiplay between <b>7am to 9pm</b>
	    	</div>
				<?php if ($this->_tpl_vars['VIEWER']['CensorTrack'] == 't'): ?>
	    	<div class="musicCensorCMB1">
	      	<input type="submit" name="submit" value="Submit">
	      	<input type="reset" value="Reset"><br>
	      	<input type="submit" name="submit" value="Clear List">
	    	</div> 
	    	<input type="hidden" name="resultCount" value="<?php echo $this->_tpl_vars['VIEWER']['flagNum']; ?>
">
			<?php endif; ?>
	    </div>
			<?php if ($this->_tpl_vars['VIEWER']['CensorTrack'] == 't'): ?>
	    </form>
			<?php endif; ?>
	    <br style="&7b;clear:both&7c;" \>
	    <?php endif; ?>
	    <?php if ($this->_tpl_vars['VIEWER']['censorNum']): ?>
	    <div class="musicCensorInfo1">Censored tracks</div>
	    <div class="musicCensorInstructions1">Select tick-box to remove from list</div>
			<?php if ($this->_tpl_vars['VIEWER']['CensorTrack'] == 't'): ?>
	    <form name='dpsTrackCensorForm' method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
	      <input type="hidden" name="formName" value="dpsTrackCensorForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
			<?php endif; ?>
	    <div class="musicCensored">
	      <table class="musicCensored">
					<?php $_from = $this->_tpl_vars['VIEWER']['censoredTracks']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['ctrack']):
?>
					<tr>
		  			<td><?php echo $this->_tpl_vars['ctrack']['artist']; ?>
</td>
		  			<td><?php echo $this->_tpl_vars['ctrack']['title']; ?>
</td>
		  			<td><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '57','text' => 'Preview','_trackID' => $this->_tpl_vars['ctrack']['id']), $this);?>
</td>
		  			<?php if ($this->_tpl_vars['VIEWER']['CensorTrack'] == 't'): ?>
		  			<td>
		    			<input type="checkbox" name="checkbox_<?php echo $this->_tpl_vars['ctrack']['searchNumber']; ?>
">
		    			<input type="hidden" name="trackID_<?php echo $this->_tpl_vars['ctrack']['searchNumber']; ?>
" value="<?php echo $this->_tpl_vars['ctrack']['id']; ?>
">
		  			</td>
		  			<?php endif; ?>
					</tr>
					<?php endforeach; endif; unset($_from); ?>
	      </table>
	      <input type="hidden" name="resultCount" value="<?php echo $this->_tpl_vars['VIEWER']['censorNum']; ?>
">
	    </div>
			<?php if ($this->_tpl_vars['VIEWER']['CensorTrack'] == 't'): ?>
	    <div class="musicCensorCMB2">
	      <input type="submit" name="submit" value="Submit">
	      <input type="reset" value="Reset"><br>
	    </div>
	    </form>
			<?php endif; ?>
	    <?php endif; ?>
	  <br style="&7b;clear:both&7c;" \> 
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsmusicbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>