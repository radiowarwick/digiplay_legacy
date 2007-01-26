<?php /* Smarty version 2.6.14, created on 2006-09-25 12:34:00
         compiled from rfile:/var/www/toolkit/DPS/templates/dpstrequest.tpl */ ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsmusictopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager','RequestTrack' => $this->_tpl_vars['VIEWER']['RequestTrack'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
	    <div class="musicTitle">Requested Tracks</div>
	    <div class="musicSubTitle">
	      <?php echo $this->_tpl_vars['VIEWER']['requestedNum']; ?>
 track(s) have been requested
	    </div>
	    <hr \>
	    <?php if ($this->_tpl_vars['VIEWER']['requestedTracks']): ?>
	    <?php if ($this->_tpl_vars['VIEWER']['RemoveRequestTrack']): ?>
	    <form name="dpsMusicRemoveRequestForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
	      <input type="hidden" name="formName" value="dpsMusicRemoveRequestForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
	    <?php endif; ?>
	      <div class="musicRequested">
		<table class="musicRequested">
		  <tr>
		    <th>Artist</th>
		    <th>Title</th>
		    <th>Date Requested</th>
		    <th>User</th>
		    <?php if ($this->_tpl_vars['VIEWER']['RemoveRequestTrack']): ?>
		    <th>Remove</th>
		    <?php endif; ?>
		  </tr>
		  <?php $_from = $this->_tpl_vars['VIEWER']['requestedTracks']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['rtrack']):
?>
		  <tr>
		    <td><?php echo $this->_tpl_vars['rtrack']['artistname']; ?>
</td>
		    <td><?php echo $this->_tpl_vars['rtrack']['name']; ?>
</td>
		    <td><?php echo $this->_tpl_vars['rtrack']['rtime']; ?>
</td>
		    <td><?php echo $this->_tpl_vars['rtrack']['user']; ?>
</td>
		    <?php if ($this->_tpl_vars['VIEWER']['RemoveRequestTrack']): ?>
		    <td>
		      <input type="checkbox" name="track<?php echo $this->_tpl_vars['rtrack']['number']; ?>
" value="on">
		      <input type="hidden" name="track<?php echo $this->_tpl_vars['rtrack']['number']; ?>
id" value="<?php echo $this->_tpl_vars['rtrack']['id']; ?>
">
		    </td>
		    <?php endif; ?>
		  </tr>
		  <?php endforeach; endif; unset($_from); ?>
		</table> 
	      </div>
	    <?php if ($this->_tpl_vars['VIEWER']['RemoveRequestTrack']): ?>
	      <input type="hidden" name="tracknum" value="<?php echo $this->_tpl_vars['VIEWER']['requestedNum']; ?>
">
	      <input type="submit" name="submit" value="Remove Selected">
	    </form>
	    <?php endif; ?>
	    <?php endif;  $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsmusicbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>