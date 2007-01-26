<?php /* Smarty version 2.6.14, created on 2006-09-28 18:04:50
         compiled from rfile:/var/www/toolkit/DPS/templates/dpsmsearch.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/toolkit/DPS/templates/dpsmsearch.tpl', 15, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsmusictopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager','RequestTrack' => $this->_tpl_vars['VIEWER']['RequestTrack'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
	    <div class="musicResultInfo">
	      <?php if ($this->_tpl_vars['VIEWER']['searchValue'] != ""): ?>
	      <b>Found:</b><br>
	      <?php endif; ?>
	      <?php echo $this->_tpl_vars['VIEWER']['searchInfo']; ?>

	      <?php if ($this->_tpl_vars['VIEWER']['DeleteTrack']): ?>
		<div class="warning">Warning: Deleting a track removes it from the Sustainer automaticaly!</div>
	      <?php endif; ?>
	    </div>
	    <div class="musicResultSorts">
	      <?php if ($this->_tpl_vars['VIEWER']['sortType'] == 'artist'): ?>
	      Sort by artist
	      <?php else: ?>
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '48','text' => 'Sort by artist','_dpsSortType' => 'artist','_dpsSearchType' => $this->_tpl_vars['VIEWER']['searchType'],'_dpsSearchVal' => $this->_tpl_vars['VIEWER']['searchValue']), $this);?>

	      <?php endif; ?>
	      | 
	      <?php if ($this->_tpl_vars['VIEWER']['sortType'] == 'title'): ?>
	      Sort by title
	      <?php else: ?>
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '48','text' => 'Sort by title','_dpsSortType' => 'title','_dpsSearchType' => $this->_tpl_vars['VIEWER']['searchType'],'_dpsSearchVal' => $this->_tpl_vars['VIEWER']['searchValue']), $this);?>

	      <?php endif; ?>
	    </div>
	    <form name="dpsMusicSearchViewForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
	      <input type="hidden" name="formName" value="dpsMusicSearchViewForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <input type="hidden" name="templateID" value="55" />
	      <table class="musicSearchTable" cellspacing=0>
		<tr>
		  <?php if ($this->_tpl_vars['VIEWER']['EditTrack']): ?>
		  <th> </th>
		  <?php endif; ?>
		  <th>Artist</th><th>Title</th><th>30s Preview</th><th>Swearing?</th> 
		  <?php if ($this->_tpl_vars['VIEWER']['DeleteTrack']): ?>
		  <th>
		  Delete
		  </th>
		  <?php endif; ?>
		  <th>View</th>
		</tr>
		<?php $_from = $this->_tpl_vars['VIEWER']['searchResult']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['track']):
?>
		<tr>
		  <?php if ($this->_tpl_vars['VIEWER']['EditTrack']): ?>
		  <th><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '53','text' => "<img class='musicSearchTableTh' src='DPS/images/blackExpand.gif'>",'_trackID' => $this->_tpl_vars['track']['id']), $this);?>
</th>
		  <?php endif; ?>
		  <td><?php echo $this->_tpl_vars['track']['artist']; ?>
</td>
		  <td><?php echo $this->_tpl_vars['track']['title']; ?>
</td>
		  <td><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '57','text' => 'Preview','_trackID' => $this->_tpl_vars['track']['id']), $this);?>
</td>
		  <td>
		    <?php if ($this->_tpl_vars['track']['censor'] == 't'): ?>
		    <div class="musicCensoredLable">Censored</div>
		    <?php elseif ($this->_tpl_vars['track']['flagged'] == 't'): ?>
		    <div class="musicPossibleSwearLable">Possibly</div>
		    <?php else: ?>
		    <?php if ($this->_tpl_vars['VIEWER']['ReportTrack']): ?>
		    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Report','_formName' => 'dpsMusicReportForm','_moduleName' => 'DPS','_trackID' => $this->_tpl_vars['track']['id'],'_dpsSearchType' => $this->_tpl_vars['VIEWER']['searchType'],'_dpsSearchVal' => $this->_tpl_vars['VIEWER']['searchValue'],'_dpsSearchPage' => $this->_tpl_vars['VIEWER']['page']), $this);?>

		    <?php else: ?>
		    Clean
		    <?php endif; ?>
		    <?php endif; ?>
		  </td>
		  <?php if ($this->_tpl_vars['VIEWER']['DeleteTrack']): ?>
		  <td>
		  <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Delete','_formName' => 'dpsMusicDeleteForm','_moduleName' => 'DPS','_trackID' => $this->_tpl_vars['track']['id'],'_dpsSearchType' => $this->_tpl_vars['VIEWER']['searchType'],'_dpsSearchVal' => $this->_tpl_vars['VIEWER']['searchValue'],'_dpsSearchPage' => $this->_tpl_vars['VIEWER']['page']), $this);?>

		  </td>
		  <?php endif; ?>
		  <td>
		    <input type="checkbox" name="checkbox_<?php echo $this->_tpl_vars['track']['searchNumber']; ?>
">
		    <input type="hidden" name="trackID_<?php echo $this->_tpl_vars['track']['searchNumber']; ?>
" value="<?php echo $this->_tpl_vars['track']['id']; ?>
">
		  </td>
		</tr>
		<?php endforeach; endif; unset($_from); ?>
	      </table>
	      <div class="musicSearchPages">
		<?php if ($this->_tpl_vars['VIEWER']['searchValue'] != ""): ?>
		Page: 
		<?php $_from = $this->_tpl_vars['VIEWER']['pages']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['page']):
?>
		| <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => $this->_tpl_vars['page'],'_dpsSearchPage' => $this->_tpl_vars['page'],'_dpsSearchVal' => $this->_tpl_vars['VIEWER']['searchValue'],'_dpsSearchType' => $this->_tpl_vars['VIEWER']['searchType']), $this);?>

		<?php endforeach; endif; unset($_from); ?> 
		|
		<?php endif; ?>
	      </div>
	      <div class="musicSearchFormSubmit">
		<?php if ($this->_tpl_vars['VIEWER']['searchResult']): ?>
		<input type="Submit" value="View Selected Tracks">
		<?php endif; ?>
	      </div>
	      <br style="&7b;clear:both;&7c;" />
	    </form>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsmusicbottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>