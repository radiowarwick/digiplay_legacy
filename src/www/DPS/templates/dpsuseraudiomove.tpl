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
		<div class='subTitle'>You do not have permission to move that item</div>
	{else}
		<div class='alignleft'>
			<div class='bigTitle'>Advanced Properties: {$VIEWER.audio.title}</div>
			<form name="dpsUserMoveAudioForm" method="post" action="{$CONFIG.general.siteRoot}">
    	  <input type="hidden" name="formName" value="dpsUserMoveAudioForm" />
				<input type="hidden" name="moduleName" value="DPS" />
				<input type="hidden" name="templateID" value="70" />
				<input type="hidden" name="audioID" value="{$VIEWER.audio.id}" />
				<input type="hidden" id="newparent" name="newParent" value="{$VIEWER.folder.parent}" />
				{if $VIEWER.own == 't'}
<!--				<div class='subTitle'>Select the items permissions from the options below</div>
				Private : <input type="radio" name="perm" value="private" checked/>
				Public read : <input type="radio" name="perm" value="aread" />
				Public write : <input type="radio" name="perm" value="awrite" />
-->
				{/if}
				<div class='subTitle'>If you want to move this item please select a new subfolder</div>
				<input type="submit" value="Save" />
				{if $DATA.error == 'perm'}
				<div class='error'>You do not have permission to move the item to the selected location</div>
				{/if}
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
