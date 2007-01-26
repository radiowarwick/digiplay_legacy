<?php /* Smarty version 2.6.14, created on 2007-01-05 14:03:25
         compiled from rfile:/var/www/DPS/templates/dpssstats.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpssstats.tpl', 14, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpssuetopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager','nexttrack' => $this->_tpl_vars['VIEWER']['sueNextTrack'],'Access_EditSue' => $this->_tpl_vars['VIEWER']['Access_EditSue'],'Access_ViewSue' => 't')));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
	    <div class="bigTitle">Sue Stamp's Stats</div>
	    <table class="suestats">
	      <tr><th>Tracks currently on Sue Playlist</th><td><?php echo $this->_tpl_vars['VIEWER']['suePlaylistTracks']; ?>
</td></tr>
	      <tr><th>Time currently on Sue Playlist</th><td><?php echo $this->_tpl_vars['VIEWER']['suePlaylistLength']; ?>
</td></tr>
	      <tr><th>Total tracks currently on system</th><td><?php echo $this->_tpl_vars['VIEWER']['storedTracks']; ?>
</td></tr>
	      <tr><th>Total time currently on system</th><td><?php echo $this->_tpl_vars['VIEWER']['lengthOfTracks']; ?>
</td></tr>
	    </table>
	    <br />
	    <div class="bigTitle">Coming up on Sue</div>
	    <table class="suestats">
	      <tr><th>Title</th><th>Artist</th></tr>
	      <?php $_from = $this->_tpl_vars['VIEWER']['suePlaylist']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['track']):
?>
	      		<tr><td><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '55','text' => $this->_tpl_vars['track']['title'],'_trackID' => $this->_tpl_vars['track']['id']), $this);?>
</td><td><?php echo $this->_tpl_vars['track']['artist']; ?>
</td></tr>
	      <?php endforeach; endif; unset($_from); ?>
	    </table>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsmusicbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>