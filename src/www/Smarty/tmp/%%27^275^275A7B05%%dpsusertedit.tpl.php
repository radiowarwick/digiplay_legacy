<?php /* Smarty version 2.6.14, created on 2006-12-22 17:09:03
         compiled from rfile:/var/www/DPS/templates/dpsusertedit.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpsusertedit.tpl', 2, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsstudiotopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager','studio' => $this->_tpl_vars['VIEWER']['studioAccess'],'access_playlist' => $this->_tpl_vars['VIEWER']['access_playlist'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
			<div class="rightLinks"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => 86,'text' => "<<< Go back to your files"), $this);?>
</div>
	    <div class=FloatL"><div class="bigTitle">Edit Track Details</div></div>
			<?php if ($this->_tpl_vars['VIEWER']['authError'] == 't'): ?>
			<div class="subTitle">You do not have permission to Edit that track</div>
			<?php else: ?>
	    <div class="musicTrackHolder">
	      <form name="dpsUserEditTrackForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
	      <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
	      <input type="hidden" name="trackID" value="<?php echo $this->_tpl_vars['VIEWER']['trackID']; ?>
" />
	      <input type="hidden" name="formName" value="dpsUserEditTrackForm" />
	      <input type="hidden" name="moduleName" value="DPS" />

	      <div class="musicTrackDetailsL">
		<table class="musicShowTrackInfo">
		  <tr>
		    <th>Artist</th>
		    <td>
		      <?php if ($this->_tpl_vars['VIEWER']['trackDetails']['artist']): ?>
		      Artists:<br />
		      <?php endif; ?>
		      <?php $_from = $this->_tpl_vars['VIEWER']['trackDetails']['artist']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['artist']):
?>
		      <input type="text" name="artist<?php echo $this->_tpl_vars['artist']['number']; ?>
" value="<?php echo $this->_tpl_vars['artist']['name']; ?>
">
		      <input type="hidden" name="artist<?php echo $this->_tpl_vars['artist']['number']; ?>
id" value="<?php echo $this->_tpl_vars['artist']['id']; ?>
"><br />
		      <?php endforeach; endif; unset($_from); ?>
		      New Artist :<br /><input type="text" name="artist<?php echo $this->_tpl_vars['VIEWER']['artistNum']; ?>
" value="">
		      <input type="hidden" name="artistnum" value="<?php echo $this->_tpl_vars['VIEWER']['artistNum']; ?>
">
		    </td>
		  </tr>
		  <tr><th>Title</th><td><?php if ($this->_tpl_vars['ERRORS']['title']): ?><div class='frame_musicboxerror'><?php echo $this->_tpl_vars['ERRORS']['title']; ?>
</div><?php endif; ?><input type="text" name="title" value="<?php echo $this->_tpl_vars['VIEWER']['trackDetails']['title']; ?>
"></td></tr>
		  <tr><th>Year</th><td><input type="text" name="released" value="<?php echo $this->_tpl_vars['VIEWER']['trackDetails']['music_released']; ?>
"></td></tr>
		  <tr><th>Length</th><td><?php echo $this->_tpl_vars['VIEWER']['trackDetails']['length']; ?>
</td></tr>
		  <tr>
		    <th>Keywords</th>
		    <td>
		      <?php if ($this->_tpl_vars['VIEWER']['trackDetails']['keywords']): ?>
		      Keywords:<br />
		      <?php endif; ?>
		      <?php $_from = $this->_tpl_vars['VIEWER']['trackDetails']['keywords']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['keyword']):
?>
		      <input type="text" name="keyword<?php echo $this->_tpl_vars['keyword']['number']; ?>
" value="<?php echo $this->_tpl_vars['keyword']['name']; ?>
">
		      <input type="hidden" name="keyword<?php echo $this->_tpl_vars['keyword']['number']; ?>
id" value="<?php echo $this->_tpl_vars['keyword']['id']; ?>
"><br />
		      <?php endforeach; endif; unset($_from); ?>
		      New Keyword :<br /><input type="text" name="keyword<?php echo $this->_tpl_vars['VIEWER']['keywordNum']; ?>
" value="">
		      <input type="hidden" name="keywordnum" value="<?php echo $this->_tpl_vars['VIEWER']['keywordNum']; ?>
">
		    </td>
		  </tr>
		  <tr><th>Reclib</th><td><input type="text" name="reclib" value="<?php echo $this->_tpl_vars['VIEWER']['trackDetails']['reclibid']; ?>
"></td></tr>
		  <tr><th>Origin</th><td><?php if ($this->_tpl_vars['ERRORS']['origin']): ?><div class='frame_musicboxerror'><?php echo $this->_tpl_vars['ERRORS']['origin']; ?>
</div><?php endif; ?><input type="text" name="origin" value="<?php echo $this->_tpl_vars['VIEWER']['trackDetails']['origin']; ?>
"></td></tr>
		  <tr><th>Censored</th><td>
		    <?php if ($this->_tpl_vars['VIEWER']['trackDetails']['censor'] == 't'): ?>
		      Censored
		    <?php elseif ($this->_tpl_vars['VIEWER']['trackDetails']['flagged'] == 't'): ?>
		      Flagged
		    <?php else: ?>
		      No
		    <?php endif; ?>
		  </td></tr>
		  <tr><th>Notes</th>
		    <td>
		      <?php $_from = $this->_tpl_vars['VIEWER']['trackDetails']['comments']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
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
		<b>Write note about track</b>
		<textarea name="comment" rows="5" cols="34"></textarea><br>
		<input type="Submit" value="Submit">
	      </div>
	      </form>
	    </div>
			<?php endif; ?>
	    <br style=&7b;clear:both;&7c;>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsstudiobottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>