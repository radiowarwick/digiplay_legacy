<html>
  <head>
    <title>Add Jingle</title>
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
				if ((String(id).substring(0,3)) != "dir") {
					document.getElementById('niceName').value = tree.getItemText(id);
					document.getElementById('audioID').value = (String(id).substring(3,(String(id).length)));
				}
			}
		</script>
		{/literal}
  </head>
  <body>
    {if $VIEWER.error != ''}
      {$VIEWER.error}
    {else}
    <div class='alignleft'>
    <div class='bigTitle'>Select Jingle</div>
		<div class='subTitle'>Showplan: {$VIEWER.show.name}, Item: {$VIEWER.item.position} 
    <hr>
    <div class=''>
      <form name="dpsUserAudioShow" method="post" action="{$CONFIG.general.siteRoot}">
      	<input type="hidden" name="formName" value="dpsUserAudioShow" />
      	<input type="hidden" name="moduleName" value="DPS" />
      	<input type="hidden" name="templateID" value="70" />
      	<input type="hidden" name="itemID" value="{$VIEWER.item.id}" />
				<input type="hidden" id="audioID" name="audioID" value="{$VIEWER.item.audio}" />
      	<input type="text" id="niceName" name="niceName" readonly value="{$VIEWER.item.audioTitle}" />
				<input type="Submit" name="Submit" value="Submit" />
      </form>
    </div>
		<hr>
		<div id="toc_tree" class="fileselect">
	  	<script>
				loadTree();
			</script>
			<noscript>
				A filebrowser will display here if you have javascript enabled
			</noscript>
		</div>
    {/if}
  </body>
</html>
