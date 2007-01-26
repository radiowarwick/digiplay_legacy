<?php /* Smarty version 2.6.14, created on 2007-01-08 17:02:23
         compiled from rfile:/var/www/DPS/templates/dpsuserfile.tpl */ ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsfiletopframe.tpl", 'smarty_include_vars' => array('title' => 'RaW Digiplay Manager','studio' => $this->_tpl_vars['VIEWER']['studioAccess'],'access_playlist' => $this->_tpl_vars['VIEWER']['access_playlist'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
	<div class="bigTitle">User File System <?php echo $this->_tpl_vars['DATA']['rootDir']; ?>
</div>
	<div class="subTitle">Please click on a file or folder for options</div>
	<?php if ($this->_tpl_vars['ERRORS']['rootdir']): ?>
	<div class="fileError"><?php echo $this->_tpl_vars['ERRORS']['rootdir']; ?>
</div>
	<?php elseif ($this->_tpl_vars['ERRORS']['dirtext']): ?>
	<div class="fileError">Please enter a directory Name</div>
	<?php endif; ?>
	
	<div id="folderBar" class="folderBar">
		<div class="fileLink">
			<img src="DPS/images/dirNew.png" alt="Create Folder"> 
			<input size="10" onchange="javascript:dirChange()" type=text name=dirtext id=dirctext value="New Folder" onkeypress="javascript:handleKeyPress(event,'dirCreate')"> 
			<a id="dirCreate" href="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
?templateID=<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
">Create New</a>
		</div>
		<div class="fileLink">
			<img src="DPS/images/dirRename.png" alt="Rename Folder"> 
			<input size="10" onchange="javascript:dirChange()" type=text name=dirtext id=dirrtext value="" onkeypress="javascript:handleKeyPress(event,'dirRename')"> 
			<a id="dirRename" href="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
?templateID=<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
">Rename</a>
		</div>
		<div class="fileLink">
			<a id="dirDel" href="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
?templateID=<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
">
				<img src="DPS/images/dirDel.png" alt="Delete Folder">
				 Delete
			</a>
		</div>
		<div class="fileLink">
			<a href="javascript:moveDir();">
				<img src="DPS/images/dirMove.png" alt="Move">
				 Move
			</a>
		</div>
		<div class="fileLink">
			<a href="javascript:uploadDir();">
				<img src="DPS/images/dirUpload.png" alt="Upload">
				 Upload File
			</a>
		</div>
	</div>
	
	<div id="jingleBar" class="folderBar">
		<div class="fileLink">
			<a id="jingleEdit" href="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
?templateID=<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
">
				<img src="DPS/images/jingleEdit.png" alt="Edit Jingle"> Edit Jingle
			</a>
		</div>
		<div class="fileLink">
			<a id="jingleMove" href="javascript:moveAudio();">
				<img src="DPS/images/jingleMove.png" alt="Move Jingle"> Move Jingles
			</a>
		</div>
		<div class="fileLink">
			<a id="jingleDelete" href="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
?templateID=<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
">
				<img src="DPS/images/jingleDel.png" alt="Delete Jingle"> Delete Jingle
			</a>
		</div>
	</div>
	
	<div id="cartsetBar" class="folderBar">
		<div class="fileLink">
			<a id="cartsetEdit" href="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
?templateID=<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
">
				<img src="DPS/images/cartsetEdit.png" alt="Edit Carset"> Edit Cartset
			</a>
		</div>
		<div class="fileLink">
			<a id="cartsetMove" href="javascript:moveCartset();">
				<img src="DPS/images/cartsetMove.png" alt="Move Cartset"> Move Cartset
			</a>
		</div>
		<div class="fileLink">
			<a id="cartsetDel" href="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
?templateID=<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
">
				<img src="DPS/images/cartsetDel.png" alt="Delete Cartset"> Delete Cartset
			</a>
		</div>
	</div>
	
	<div id="scriptBar" class="folderBar">
		<div class="fileLink">
			<a id="scriptEdit" href="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
?templateID=<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
">
				<img src="DPS/images/scriptEdit.png" alt="Edit Script"> Edit Script
			</a>
		</div>
		<div class="fileLink">
			<a id="scriptMove" href="javascript:moveScript();">
				<img src="DPS/images/scriptMove.png" alt="Move Script"> Move Script
			</a>
		</div>
		<div class="fileLink">
			<a id="scriptDel" href="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
?templateID=<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
">
				<img src="DPS/images/scriptDel.png" alt="Delete Script"> Delete Script
			</a>
		</div>
	</div>

	<div id="toc_tree" class="filebrowser">
		<script>
			loadTree();		
		</script>
		<noscript>
			A filebrowser will display here if you have javascript enabled
		</noscript>
	</div>
  </body>
</html>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "rfile:dpsstudiobottomframe.tpl", 'smarty_include_vars' => array('Admin' => $this->_tpl_vars['VIEWER']['Admin'])));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>