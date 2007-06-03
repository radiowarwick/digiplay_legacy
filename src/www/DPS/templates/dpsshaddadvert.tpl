<html>
  <head>
    <title>Add Advert</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
		<link rel="STYLESHEET" type="text/css" href="DPS/scripts/dhtmlxTree/css/dhtmlXTree.css">
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXCommon.js"></script>
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXTree.js"></script>
		{literal}
		<script language="javascript" type="text/javascript">
			var tree;

			function loadTree(){
				tree=new dhtmlXTreeObject(document.getElementById('toc_tree'),"100%","100%",0);
				tree.setXMLAutoLoading("{/literal}{$CONFIG.general.toolkitRootURL}{literal}?templateID=65&treeType={/literal}{$VIEWER.treeType}{literal}");
				tree.setImagePath("DPS/scripts/dhtmlxTree/imgs/");
				tree.setOnClickHandler(doOnClick);
				tree.enableTreeLines(false);
				tree.loadXML("{/literal}{$CONFIG.general.toolkitRootURL}{literal}?templateID=65&treeType={/literal}{$VIEWER.treeType}{literal}&id=dir1");
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
			{if $VIEWER.write == 't'}
    	<div class='bigTitle'>Select Advert</div>
			<div class='subTitle'>Showplan: {$VIEWER.show.name}, Item: {$VIEWER.item.position}</div>
    	<hr>
    	<div class=''>
      	<form name="dpsUserAudioShow" method="post" action="{$CONFIG.general.siteRoot}">
      		<input type="hidden" name="formName" value="dpsUserAudioShow" />
      		<input type="hidden" name="moduleName" value="DPS" />
      		<input type="hidden" name="templateID" value="22" />
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
			{else}
			<div class='bigTitle'>Select Advert</div>
			<div class='subTitle'>Showplan: {$VIEWER.show.name}, Item: {$VIEWER.item.position}</div>
			<hr>
			<b>{$VIEWER.item.audioTitle}</b>
			{/if}
		</div>
    {/if}
  </body>
</html>
