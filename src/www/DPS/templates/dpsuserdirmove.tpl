<html>
  <head>
    <title>{$title}</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
		<link rel="STYLESHEET" type="text/css" href="DPS/scripts/dhtmlxTree/css/dhtmlXTree.css">
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXCommon.js"></script>
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXTree.js"></script>	
		{literal}
		<script language="javascript" type="text/javascript">
			var tree;
			var xml1="{/literal}{$VIEWER.treeData}{literal}";
			var browserType;

			if (document.layers) {browserType = "nn4"}
			if (document.all) {browserType = "ie"}
			if (window.navigator.userAgent.toLowerCase().match("gecko")) {browserType= "gecko"}

			function loadTree(){
				tree=new dhtmlXTreeObject(document.getElementById('toc_tree'),"100%","100%",0);
				tree.setImagePath("DPS/scripts/dhtmlxTree/imgs/");
				tree.setOnClickHandler(doOnClick);
				tree.enableTreeLines(false);
				tree.loadXMLString(xml1);
			}

			function doOnClick(id){
				if ((String(id).substring(0,3)) == "dir") {
					document.getElementById('newparent').value = (String(id).substring(3,(String(id).length)));
				}
			}
		</script>
		{/literal}
  </head>
  <body>
	{if $VIEWER.permError}
		<div class='bigTitle'>Permission Error</div>
		<div class='subTitle'>You do not have permission to move that folder</div>
	{else}
		{if $DATA.error == 'form'}
			<div class='subTitle'>You can not move a folder to its self or one of its sub-folders</div>
		{elseif $DATA.error == 'perm'}
			<div class='subTitle'>You do not have permission to move the folder to the selected location</div>
		{/if}
		<div class='alignleft'>
			<div class='bigTitle'>Advanced Properties: {$VIEWER.folder.name}</div>
			<form name="dpsUserMoveDirForm" method="post" action="{$CONFIG.general.siteRoot}">
    	  <input type="hidden" name="formName" value="dpsUserMoveDirForm" />
				<input type="hidden" name="moduleName" value="DPS" />
				<input type="hidden" name="templateID" value="70" />
				<input type="hidden" name="dirID" value="{$VIEWER.folder.id}" />
				<input type="hidden" id="newparent" name="newParent" value="{$VIEWER.folder.parent}" />
<!--				<div class='subTitle'>Select the folder permissions from the options below</div>
				Private : <input type="radio" name="perm" value="private" checked/>
				Public read : <input type="radio" name="perm" value="aread" />
				Public write : <input type="radio" name="perm" value="awrite" />
-->
				<div class='subTitle'>If you want to move this folder please select a new subfolder</div>
				<input type="submit" value="Save" />
	  		<div id="toc_tree" class="filebrowser">
					<script>
						loadTree();
					</script>
					<noscript>
						A filebrowser will display here if you have javascript enabled
					</noscript>
				</div>
			</form>
		</div>
		{/if}
	</body>
</html>
