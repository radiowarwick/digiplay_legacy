<?php /* Smarty version 2.6.14, created on 2006-09-22 18:54:49
         compiled from rfile:/var/www/toolkit/DPS/templates/dpstview.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/toolkit/DPS/templates/dpstview.tpl', 3, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsmusictopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager','RequestTrack' => $this->_tpl_vars['VIEWER']['RequestTrack'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
	    <div class="musicTitle">Track Details</div>
	    <div class="musicTrackDetailsLinks"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => 48,'text' => 'Go back to search screen'), $this);?>
</div>
	    <?php $_from = $this->_tpl_vars['VIEWER']['tracksDetails']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['trackDetails']):
?>
	    <hr style=&7b;clear:both;&7c;>
	    <div class="musicTrackHolder">
	      <div class="musicTrackDetailsL">
		<table class="musicShowTrackInfo">
		  <tr><th>Artist(s)</th><td>
		    <?php $_from = $this->_tpl_vars['trackDetails']['artist']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['artist']):
?>
		      <?php echo $this->_tpl_vars['artist']; ?>
<br />
		    <?php endforeach; endif; unset($_from); ?>
		  </td></tr>
		  <tr><th>Title</th><td><?php echo $this->_tpl_vars['trackDetails']['title']; ?>
</td></tr>
		  <tr><th>Album</th><td><?php echo $this->_tpl_vars['trackDetails']['album']; ?>
</td></tr>
		  <tr><th>Year</th><td><?php echo $this->_tpl_vars['trackDetails']['music_released']; ?>
</td></tr>
		  <tr><th>Length</th><td><?php echo $this->_tpl_vars['trackDetails']['length']; ?>
</td></tr>
		  <tr><th>Keywords</th><td>
		    <?php $_from = $this->_tpl_vars['trackDetails']['keywords']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['keyword']):
?>
		      <?php echo $this->_tpl_vars['keyword']; ?>
<br />
		    <?php endforeach; endif; unset($_from); ?>
		  </td></tr>
		  <tr><th>Reclib</th><td><?php echo $this->_tpl_vars['trackDetails']['reclibid']; ?>
</td></tr>
		  <tr><th>Origin</th><td><?php echo $this->_tpl_vars['trackDetails']['origin']; ?>
</td></tr> 
		  <tr><th>Flagged</th><td>
		    <?php if ($this->_tpl_vars['trackDetails']['flagged'] == 't'): ?>
		      Yes
		    <?php else: ?>
		      No
		    <?php endif; ?>
		  </td></tr>
		  <tr><th>Censored</th><td>
		    <?php if ($this->_tpl_vars['trackDetails']['censor'] == 't'): ?>
		      Yes
		    <?php else: ?>
		      No
		    <?php endif; ?>
		  </td></tr>
		  <tr><th>Playlisted</th><td>
		    <?php if ($this->_tpl_vars['trackDetails']['sustainer'] == 't'): ?>
		      Yes
		    <?php else: ?>
		      No
		    <?php endif; ?>
		  </td></tr>
		  <tr><th>Notes</th>
		    <td>
		      <?php $_from = $this->_tpl_vars['trackDetails']['comments']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['comment']):
?>
		      <?php echo $this->_tpl_vars['comment']['comment']; ?>

		      <div class="musicTrackCommentTools">
			Added by <?php echo $this->_tpl_vars['comment']['username']; ?>
 
			<?php if ($this->_tpl_vars['comment']['username'] == $this->_tpl_vars['AUTH']['user']): ?>
			<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'delete','_formName' => 'dpsMusicDeleteCommentForm','_moduleName' => 'DPS','_commentID' => $this->_tpl_vars['comment']['id'],'_trackID' => $this->_tpl_vars['DATA']['trackID']), $this);?>

			<?php endif; ?>
		      </div>
		      <hr>	
		      <?php endforeach; endif; unset($_from); ?>
		    </td>
		  </tr>
		</table>
	      </div>
	      <div class="musicTrackDetailsR">
		<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '53','text' => "Edit this track's details",'_trackID' => $this->_tpl_vars['trackDetails']['id']), $this);?>
<br>
		<b>Write note about track</b>
		<form name="dpsMusicCommentForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
		  <input type="hidden" name="formName" value="dpsMusicCommentForm" />
		  <input type="hidden" name="moduleName" value="DPS" />
		  <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
		  <input type="hidden" name="audioID" value="<?php echo $this->_tpl_vars['trackDetails']['id']; ?>
" />
		  <input type="hidden" name="trackID" value="<?php echo $this->_tpl_vars['DATA']['trackID']; ?>
" />
		  <textarea name="comment" rows="5" cols="34"></textarea><br>
		  <input type="Submit" value="Submit">
		</form>
	      </div>
	    </div>
	    <?php endforeach; endif; unset($_from); ?> 
	    <br style=&7b;clear:both;&7c;>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsmusicbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>