{include file="rfile:dpsfiletopframe.tpl" title="RaW Digiplay Manager" studio=$VIEWER.studioAccess access_playlist=$VIEWER.access_playlist}
	<div class="bigTitle">User File System {$DATA.rootDir}</div>
	<div class="subTitle">Please click on a file or folder for options</div>
	{if $ERRORS.rootdir}
	<div class="fileError">{$ERRORS.rootdir}</div>
	{elseif $ERRORS.dirtext}
	<div class="fileError">Please enter a directory Name</div>
	{/if}
	
	<div id="folderBar" class="folderBar">
		<div id="dircCreate" class="fileLink">
			<img src="DPS/images/dirNew.png" alt="Create Folder"> 
			<input size="10" onchange="javascript:dirChange()" type=text name=dirtext id=dirctext value="New Folder" onkeypress="javascript:handleKeyPress(event,'dirCreate')"> 
			<a id="dirCreate" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">Create New</a>
		</div>
		<div id="dircRename" class="fileLink">
			<img src="DPS/images/dirRename.png" alt="Rename Folder"> 
			<input size="10" onchange="javascript:dirChange()" type=text name=dirtext id=dirrtext value="" onkeypress="javascript:handleKeyPress(event,'dirRename')"> 
			<a id="dirRename" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">Rename</a>
		</div>
		<div id="dircDelete" class="fileLink">
			<a id="dirDelete" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">
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
		<div id="cartsetcView" class="fileLink">
			<a id="cartsetView" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">
				<img src="DPS/images/cartsetEdit.png" alt="View Carset"> View Cartset
			</a>
		</div>
		<div id="cartsetcEdit" class="fileLink">
			<a id="cartsetEdit" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">
				<img src="DPS/images/cartsetEdit.png" alt="Edit Carset"> Edit Cartset
			</a>
		</div>
		<div id="cartsetcMove" class="fileLink">
			<a id="cartsetMove" href="javascript:moveCartset();">
				<img src="DPS/images/cartsetMove.png" alt="Move Cartset"> Move Cartset
			</a>
		</div>
		<div id="cartsetcDelete" class="fileLink">
			<a id="cartsetDelete" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">
				<img src="DPS/images/cartsetDel.png" alt="Delete Cartset"> Delete Cartset
			</a>
		</div>
	</div>
	
	<div id="scriptBar" class="folderBar">
		<div id="scriptcEdit" class="fileLink">
			<a id="scriptEdit" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">
				<img src="DPS/images/scriptEdit.png" alt="Edit Script"> Edit Script
			</a>
		</div>
		<div id="scriptcMove" class="fileLink">
			<a id="scriptMove" href="javascript:moveScript();">
				<img src="DPS/images/scriptMove.png" alt="Move Script"> Move Script
			</a>
		</div>
		<div id="scriptcDelete" class="fileLink">
			<a id="scriptDelete" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">
				<img src="DPS/images/scriptDel.png" alt="Delete Script"> Delete Script
			</a>
		</div>
	</div>
	
	<div id="showBar" class="folderBar">
		<div id="showcEdit" class="fileLink">
			<a id="showEdit" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">
				<img src="DPS/images/scriptEdit.png" alt="Edit Script"> Edit Show
			</a>
		</div>
		<div id="showcMove" class="fileLink">
			<a id="showMove" href="javascript:moveShow();">
				<img src="DPS/images/scriptMove.png" alt="Move Script"> Move Show
			</a>
		</div>
		<div id="showcDelete" class="fileLink">
			<a id="showDelete" href="{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}">
				<img src="DPS/images/scriptDel.png" alt="Delete Show"> Delete Show
			</a>
		</div>
	</div>

	<div id="toc_tree" class="filebrowser">
		<script language="javascript" type="text/javascript">
			loadTree();
		</script>
		<noscript>
			A filebrowser will display here if you have javascript enabled
		</noscript>
	</div>
	</body>
</html>
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
