<?php /* Smarty version 2.6.14, created on 2007-01-21 17:08:16
         compiled from rfile:/var/www/DPS/templates/dpssplaylist.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpssplaylist.tpl', 4, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpssuetopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager','nexttrack' => $this->_tpl_vars['VIEWER']['sueNextTrack'],'suesearchid' => $this->_tpl_vars['VIEWER']['templateID'],'Access_EditSue' => $this->_tpl_vars['VIEWER']['Access_EditSue'],'Access_SueStats' => $this->_tpl_vars['VIEWER']['Access_SueStats'],'Access_ViewSue' => $this->_tpl_vars['VIEWER']['Access_ViewSue'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
	    <div class="bigTitle">View Sue Playlist</div>
	    <div class="sueplaylistletters">
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => "#",'_dpsSearchLetter' => "*"), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'A','_dpsSearchLetter' => 'A'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'B','_dpsSearchLetter' => 'B'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'C','_dpsSearchLetter' => 'C'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'D','_dpsSearchLetter' => 'D'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'E','_dpsSearchLetter' => 'E'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'F','_dpsSearchLetter' => 'F'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'G','_dpsSearchLetter' => 'G'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'H','_dpsSearchLetter' => 'H'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'I','_dpsSearchLetter' => 'I'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'J','_dpsSearchLetter' => 'J'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'K','_dpsSearchLetter' => 'K'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'L','_dpsSearchLetter' => 'L'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'M','_dpsSearchLetter' => 'M'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'N','_dpsSearchLetter' => 'N'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'O','_dpsSearchLetter' => 'O'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'P','_dpsSearchLetter' => 'P'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Q','_dpsSearchLetter' => 'Q'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'R','_dpsSearchLetter' => 'R'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'S','_dpsSearchLetter' => 'S'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'T','_dpsSearchLetter' => 'T'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'U','_dpsSearchLetter' => 'U'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'V','_dpsSearchLetter' => 'V'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'W','_dpsSearchLetter' => 'W'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'X','_dpsSearchLetter' => 'X'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Y','_dpsSearchLetter' => 'Y'), $this);?>
 | 
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Z','_dpsSearchLetter' => 'Z'), $this);?>
 | 
	      <br />
	    </div>
	    
	    <?php if ($this->_tpl_vars['VIEWER']['searchResult']): ?>
	    <div class="sueplaylistInfo1">
	      <?php if ($this->_tpl_vars['VIEWER']['sortType'] == 'artist'): ?>
	      Sort by artist
	      <?php else: ?>
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '61','text' => 'Sort by artist','_dpsSearchLetter' => $this->_tpl_vars['VIEWER']['searchLetter'],'_dpsSortType' => 'artist','_dpsSearchType' => $this->_tpl_vars['VIEWER']['searchType'],'_dpsSearchVal' => $this->_tpl_vars['VIEWER']['searchValue']), $this);?>

	      <?php endif; ?>
	      | 
	      <?php if ($this->_tpl_vars['VIEWER']['sortType'] == 'title'): ?>
	      Sort by title
	      <?php else: ?>
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '61','text' => 'Sort by title','_dpsSearchLetter' => $this->_tpl_vars['VIEWER']['searchLetter'],'_dpsSortType' => 'title','_dpsSearchType' => $this->_tpl_vars['VIEWER']['searchType'],'_dpsSearchVal' => $this->_tpl_vars['VIEWER']['searchValue']), $this);?>

	      <?php endif; ?>
	    </div>
	    <div class="sueplaylistInfo2">
	      Click a track's title for more information
	    </div>

	    <?php if (Access_EditSue == 't'): ?>
	    <form name="dpsSuePlaylistForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
	      <input type="hidden" name="formName" value="dpsSuePlaylistForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
	      <input type="hidden" name="dpsSearchPage" value="<?php echo $this->_tpl_vars['VIEWER']['page']; ?>
" />
	      <?php if ($this->_tpl_vars['VIEWER']['searchValue'] != ""): ?>
	      <input type="hidden" name="dpsSearchVal" value="<?php echo $this->_tpl_vars['VIEWER']['searchValue']; ?>
" />
	      <input type="hidden" name="dpsSearchType" value="<?php echo $this->_tpl_vars['VIEWER']['searchType']; ?>
" />
	      <?php elseif ($this->_tpl_vars['VIEWER']['searchLetter'] != ""): ?>
	      <input type="hidden" name="dpsSearchLetter" value="<?php echo $this->_tpl_vars['VIEWER']['searchLetter']; ?>
" />
	      <?php endif; ?>
	    <?php endif; ?>
			<?php if ($this->_tpl_vars['VIEWER']['Access_Delete'] == 't'): ?>
			<br style="clear: both;">
			<div class="warning">Warning: Deleting a track removes it from the Sustainer automaticaly!</div>
			<?php endif; ?>
	      <table class="sueviewplaylist">
		<tr>
		  <?php if ($this->_tpl_vars['VIEWER']['Access_EditTrack'] == 't'): ?>
		  <th></th>
		  <?php endif; ?>
			<th>Artist</th><th>Title</th><th>Preview</th>
			<?php if ($this->_tpl_vars['VIEWER']['Access_Delete'] == 't'): ?>
			<th>Delete</th>
			<?php endif; ?>
			<th>Playlisted?</th>
		</tr>
		<?php $_from = $this->_tpl_vars['VIEWER']['searchResult']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['track']):
?>
		<tr>
		  <?php if ($this->_tpl_vars['VIEWER']['Access_EditTrack'] == 't'): ?>
		  <th rowspan="2"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '53','text' => "<img class='musicSearchTableTh' src='DPS/images/blackExpand.gif'>",'_trackID' => $this->_tpl_vars['track']['id']), $this);?>
</th>
		  <?php endif; ?>
		  <td rowspan="2"><?php echo $this->_tpl_vars['track']['artist']; ?>
</td>
		  <td rowspan="2"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '55','text' => $this->_tpl_vars['track']['title'],'_trackID' => $this->_tpl_vars['track']['id']), $this);?>
</td>
		  <td><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '57','text' => 'Preview','_trackID' => $this->_tpl_vars['track']['id']), $this);?>
</td>
			<?php if ($this->_tpl_vars['VIEWER']['Access_Delete'] == 't'): ?>
			<td>
				<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Delete','_formName' => 'dpsMusicDeleteForm','_moduleName' => 'DPS','_trackID' => $this->_tpl_vars['track']['id'],'_dpsSearchType' => $this->_tpl_vars['VIEWER']['searchType'],'_dpsSearchVal' => $this->_tpl_vars['VIEWER']['searchValue'],'_dpsSearchPage' => $this->_tpl_vars['VIEWER']['page']), $this);?>

			</td>
			<?php endif; ?>
		  <?php if ($this->_tpl_vars['VIEWER']['Access_EditSue'] == 't'): ?>
		  <td>
		    <input type="checkbox" name="checkbox_<?php echo $this->_tpl_vars['track']['searchNumber']; ?>
" checked>
		    <input type="hidden" name="trackID_<?php echo $this->_tpl_vars['track']['searchNumber']; ?>
" value="<?php echo $this->_tpl_vars['track']['id']; ?>
">
		  </td>
			<?php else: ?>
			<td>
				<input type="checkbox" name="checkbox_<?php echo $this->_tpl_vars['track']['searchNumber']; ?>
" checked disabled>
			</td>
		  <?php endif; ?>
		</tr>
		<tr>
			<?php if ($this->_tpl_vars['VIEWER']['Access_Delete'] == 't'): ?>
			<td colspan="2"><div class="music_mini">
			<?php else: ?>
			<td><div class="music_mini">
			<?php endif; ?>
				<?php echo $this->_tpl_vars['track']['origin']; ?>
 
				<?php if ($this->_tpl_vars['track']['reclibid'] != ''): ?>
				: <?php echo $this->_tpl_vars['track']['reclibid']; ?>

				<?php endif; ?>
			</div></td>
			<td><div class="music_mini"><?php echo $this->_tpl_vars['track']['length']; ?>
</div></td>
		</tr>
		<?php endforeach; endif; unset($_from); ?>
	      </table>
	      <div class="sueplaylistpage">
		<?php if ($this->_tpl_vars['VIEWER']['searchValue'] != ""): ?>
		Page: 
		<?php $_from = $this->_tpl_vars['VIEWER']['pages']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['page']):
?>
		| <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => $this->_tpl_vars['page'],'_dpsSearchPage' => $this->_tpl_vars['page'],'_dpsSearchVal' => $this->_tpl_vars['VIEWER']['searchValue'],'_dpsSearchType' => $this->_tpl_vars['VIEWER']['searchType']), $this);?>

		<?php endforeach; endif; unset($_from); ?> 
		|
		<?php elseif ($this->_tpl_vars['VIEWER']['searchLetter'] != ""): ?>
		Page: 
		<?php $_from = $this->_tpl_vars['VIEWER']['pages']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['page']):
?>
		| <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => $this->_tpl_vars['page'],'_dpsSearchPage' => $this->_tpl_vars['page'],'_dpsSearchLetter' => $this->_tpl_vars['VIEWER']['searchLetter']), $this);?>

		<?php endforeach; endif; unset($_from); ?> 
		|
		<?php endif; ?>

	      </div>
	      <?php if (Access_EditSue == 't'): ?>
	      <div class="sueplaylistupdate">
		<input type="submit" value="Submit">
	      </div>
	      </form>
	      <?php endif; ?>
	      <?php endif; ?>
	      <br style="&7b;clear:both;&7c;" />
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsmusicbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>