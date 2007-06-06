	{if $ERRORS.rootdir}
	<div class="fileError">{$ERRORS.rootdir}</div>
	{elseif $ERRORS.dirtext}
	<div class="fileError">Please enter a directory Name</div>
	{/if}
	{if $bar == 't'}
	<div id="folderBar" class="folderBar">
		<div id="dircCreate" class="fileLink">
			<img src="DPS/images/dirNew.png" alt="Create Folder"> 
			<input size="10" onchange="javascript:dirChange()" type=text name=dirtext id=dirctext value="New Folder" onkeypress="javascript:handleKeyPress(event,'dirCreate')"> 
			<a id="dirCreate" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">Create New</a>
		</div>
		<div d="dircRename"class="fileLink">
			<img src="DPS/images/dirRename.png" alt="Rename Folder"> 
			<input size="10" onchange="javascript:dirChange()" type=text name=dirtext id=dirrtext value="" onkeypress="javascript:handleKeyPress(event,'dirRename')"> 
			<a id="dirRename" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">Rename</a>
		</div>
		<div id="dircDel" class="fileLink">
			<a id="dirDel" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">
				<img src="DPS/images/dirDel.png" alt="Delete Folder">
					Delete
			</a>
		</div>
		<div id="dircMove" class="fileLink">
			<a href="javascript:moveDir();">
				<img src="DPS/images/dirMove.png" alt="Move">
					Move
			</a>
		</div>
		<div id="dircUpload" class="fileLink">
			<a href="javascript:uploadDir();">
				<img src="DPS/images/dirUpload.png" alt="Upload">
					Upload File
			</a>
		</div>
	</div>
	
	<div id="jingleBar" class="folderBar">
		<div id="jinglecEdit" class="fileLink">
			<a id="jingleEdit" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">
				<img src="DPS/images/jingleEdit.png" alt="Edit Jingle"> Edit Jingle
			</a>
		</div>
		<div id="jinglecMove" class="fileLink">
			<a id="jingleMove" href="javascript:moveAudio();">
				<img src="DPS/images/jingleMove.png" alt="Move Jingle"> Move Jingles
			</a>
		</div>
		<div id="jinglecDelete" class="fileLink">
			<a id="jingleDelete" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">
				<img src="DPS/images/jingleDel.png" alt="Delete Jingle"> Delete Jingle
			</a>
		</div>
	</div>
	
	<div id="cartsetBar" class="folderBar">
		<div class="fileLink">
			<a id="cartsetEdit" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">
				<img src="DPS/images/cartsetEdit.png" alt="Edit Carset"> Edit Cartset
			</a>
		</div>
		<div class="fileLink">
			<a id="cartsetMove" href="javascript:moveCartset();">
				<img src="DPS/images/cartsetMove.png" alt="Move Cartset"> Move Cartset
			</a>
		</div>
		<div class="fileLink">
			<a id="cartsetDel" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">
				<img src="DPS/images/cartsetDel.png" alt="Delete Cartset"> Delete Cartset
			</a>
		</div>
	</div>
	
	<div id="scriptBar" class="folderBar">
		<div class="fileLink">
			<a id="scriptEdit" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">
				<img src="DPS/images/scriptEdit.png" alt="Edit Script"> Edit Script
			</a>
		</div>
		<div class="fileLink">
			<a id="scriptMove" href="javascript:moveScript();">
				<img src="DPS/images/scriptMove.png" alt="Move Script"> Move Script
			</a>
		</div>
		<div class="fileLink">
			<a id="scriptDel" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">
				<img src="DPS/images/scriptDel.png" alt="Delete Script"> Delete Script
			</a>
		</div>
	</div>
	{/if}
	<div id="toc_tree" class="filebrowser">
		<script>
			loadTree();		
		</script>
		<noscript>
			A filebrowser will display here if you have javascript enabled
		</noscript>
	</div>
