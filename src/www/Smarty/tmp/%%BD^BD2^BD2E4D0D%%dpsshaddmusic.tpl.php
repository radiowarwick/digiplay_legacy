<?php /* Smarty version 2.6.14, created on 2007-01-05 14:25:55
         compiled from rfile:/var/www/DPS/templates/dpsshaddmusic.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:/var/www/DPS/templates/dpsshaddmusic.tpl', 53, false),)), $this); ?>
<html>
  <head>
    <title>Add Music</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
  </head>
  <body>
    <?php if ($this->_tpl_vars['VIEWER']['error'] != ''): ?>
      <?php echo $this->_tpl_vars['VIEWER']['error']; ?>

    <?php else: ?>
    <div class='alignleft'>
    <div class='bigTitle'>Select Track</div>
		<div class='subTitle'>Showplan: <?php echo $this->_tpl_vars['VIEWER']['show']['name']; ?>
, Item: <?php echo $this->_tpl_vars['VIEWER']['item']['position']; ?>
 
    <hr>
    <div class=''>
	    Search for tracks
	    <form name="dpsMusicSearchForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
	      <input type="hidden" name="formName" value="dpsMusicSearchForm" />
	      <input type="hidden" name="moduleName" value="DPS" />
	      <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
				<input type="hidden" name="itemID" value="<?php echo $this->_tpl_vars['VIEWER']['item']['id']; ?>
" />
	      <?php if ($this->_tpl_vars['ERRORS']['dpsSearchVal']): ?>
	      <div class="frame_musicboxerror"><?php echo $this->_tpl_vars['ERRORS']['dpsSearchVal']; ?>
</div>
	      <?php elseif ($this->_tpl_vars['ERRORS']['dpsSearchType']): ?>
	      <div class="frame_musicboxerror"><?php echo $this->_tpl_vars['ERRORS']['dpsSearchType']; ?>
</div>
	      <?php endif; ?>
	      <input type="text" name="dpsSearchVal" value="<?php echo $this->_tpl_vars['VIEWER']['searchValue']; ?>
">
	      <select name="dpsSearchType">
					<?php if ($this->_tpl_vars['VIEWER']['searchType'] == 'Both'): ?>
		  		<option value="Both" selected="selected">Both</option>
					<?php else: ?>
		  		<option value="Both">Both</option>
					<?php endif; ?>
					<?php if ($this->_tpl_vars['VIEWER']['searchType'] == 'Artist'): ?>
		  		<option value="Artist" selected="selected">Artist</option>
					<?php else: ?>
		  		<option value="Artist">Artist</option>
					<?php endif; ?>
					<?php if ($this->_tpl_vars['VIEWER']['searchType'] == 'Title'): ?>
		  		<option selected="selected" value="Title">Title</option>
					<?php else: ?>
		  		<option value="Title">Title</option>
					<?php endif; ?>
	      </select>
	      <input type="Submit" name="Search" value="Search">
			</form>
    </div>
		<hr>
		<div>
	    <div class="musicResultSorts">
	      <?php if ($this->_tpl_vars['VIEWER']['sortType'] == 'artist'): ?>
	      Sort by artist
	      <?php else: ?>
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Sort by artist','_dpsSortType' => 'artist','_dpsSearchType' => $this->_tpl_vars['VIEWER']['searchType'],'_dpsSearchVal' => $this->_tpl_vars['VIEWER']['searchValue'],'_itemID' => $this->_tpl_vars['VIEWER']['item']['id']), $this);?>

	      <?php endif; ?>
	      | 
	      <?php if ($this->_tpl_vars['VIEWER']['sortType'] == 'title'): ?>
	      Sort by title
	      <?php else: ?>
	      <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => 'Sort by title','_dpsSortType' => 'title','_dpsSearchType' => $this->_tpl_vars['VIEWER']['searchType'],'_dpsSearchVal' => $this->_tpl_vars['VIEWER']['searchValue'],'_itemID' => $this->_tpl_vars['VIEWER']['item']['id']), $this);?>

	      <?php endif; ?>
	    </div>
			<div class="musicSearchPages">
				<?php if ($this->_tpl_vars['VIEWER']['searchValue'] != ""): ?>
				Page: 
				<?php $_from = $this->_tpl_vars['VIEWER']['pages']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['page']):
?>
				| <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => $this->_tpl_vars['page'],'_dpsSearchPage' => $this->_tpl_vars['page'],'_dpsSearchVal' => $this->_tpl_vars['VIEWER']['searchValue'],'_dpsSearchType' => $this->_tpl_vars['VIEWER']['searchType'],'_itemID' => $this->_tpl_vars['VIEWER']['item']['id']), $this);?>

				<?php endforeach; endif; unset($_from); ?> 
				|
				<?php endif; ?>
			</div>
			<table class="musicSearchTable" cellspacing=0>
			 	<tr>
					<th>Artist</th><th>Title</th><th>Swearing?</th><th>Select</th>
				</tr>
				<?php $_from = $this->_tpl_vars['VIEWER']['searchResult']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['track']):
?>
				<tr>
		  		<td><?php echo $this->_tpl_vars['track']['artist']; ?>
</td>
		  		<td><?php echo $this->_tpl_vars['track']['title']; ?>
</td>
		  		<td>
		    		<?php if ($this->_tpl_vars['track']['censor'] == 't'): ?>
		    		<div class="musicCensoredLable">Censored</div>
		    		<?php elseif ($this->_tpl_vars['track']['flagged'] == 't'): ?>
		    		<div class="musicPossibleSwearLable">Possibly</div>
		    		<?php else: ?>
						No
						<?php endif; ?>
					</td>
					<td><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => 70,'text' => 'Select','_formName' => 'dpsUserAudioShow','_moduleName' => 'DPS','_audioID' => $this->_tpl_vars['track']['id'],'_itemID' => $this->_tpl_vars['VIEWER']['item']['id']), $this);?>
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
				| <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => $this->_tpl_vars['VIEWER']['templateID'],'text' => $this->_tpl_vars['page'],'_dpsSearchPage' => $this->_tpl_vars['page'],'_dpsSearchVal' => $this->_tpl_vars['VIEWER']['searchValue'],'_dpsSearchType' => $this->_tpl_vars['VIEWER']['searchType'],'_itemID' => $this->_tpl_vars['VIEWER']['item']['id']), $this);?>

				<?php endforeach; endif; unset($_from); ?> 
				|
				<?php endif; ?>
			</div>
		</div>
    <?php endif; ?>
  </body>
</html>