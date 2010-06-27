<html>
  <head>
    <title>Edit an Audiowall Item</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXCommon.js"></script>
		<link rel="STYLESHEET" type="text/css" href="DPS/scripts/dhtmlxTree/css/dhtmlXTree.css">
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXTree.js"></script>
		{literal}
   	<script language="javascript">
			var tree;
			var siteRoot="{/literal}{$CONFIG.general.siteRoot}{literal}";
			var treeType="{/literal}{$VIEWER.treeType}{literal}";
			var browserType;

			if (document.layers) {browserType = "nn4"}
			if (document.all) {browserType = "ie"}
			if (window.navigator.userAgent.toLowerCase().match("gecko")) {browserType= "gecko"}

			function loadTree(){
				var hrefstr = siteRoot + "?" +
					"templateID=65&treeType=" + treeType;
				tree=new dhtmlXTreeObject(document.getElementById('toc_tree'),"100%","100%",0);
				tree.setXMLAutoLoading(hrefstr);
				tree.setImagePath("DPS/scripts/dhtmlxTree/imgs/");
				tree.setOnClickHandler(doOnClick);
				tree.enableTreeLines(false);
				tree.loadXML(hrefstr + "&id=dir1");
			}

			function doOnClick(id){
				if ((String(id).substring(0,3)) != "dir") {
					//document.getElementById('niceName').value = tree.getItemText(id);
					document.getElementById('audioID').value = (String(id).substring(3,(String(id).length)));
				}
			}
    </script>
    {/literal}  
  </head>
  <body>
    <div class='alignleft'>
	    <div class='bigTitle'>Editing audiowall item {$VIEWER.awitemPos}</div>
  	  <hr>
    	{if $VIEWER.permError == 't'}
      You do not have permission to edit this audiowall item.
    	{else}
    	<div class='EditAwItemDetails'>
      	{if $VIEWER.new != 't'}
	      <form name="dpsStationAwItemEditForm" method="post" action="{$CONFIG.general.siteRoot}">
	  	    <input type="hidden" name="formName" value="dpsStationAwItemEditForm" />
  	  	  <input type="hidden" name="moduleName" value="DPS" />
    	  	<input type="hidden" name="templateID" value="22" />
		      <input type="hidden" name="awitemID" value="{$VIEWER.awitemInfo.id}" />
	      {else}
	      <form name="dpsStationAwItemAddForm" method="post" action="{$CONFIG.general.siteRoot}">
		      <input type="hidden" name="formName" value="dpsStationAwItemAddForm" />
		      <input type="hidden" name="moduleName" value="DPS" />
  		    <input type="hidden" name="templateID" value="22" />
    		  <input type="hidden" name="awitemPos" value="{$VIEWER.awitemPos}" />
      		<input type="hidden" name="awwallID" value="{$VIEWER.awwallID}" />
	      {/if}
		      <div class='EditAwItemDetail'>Text:</div>
		      {if $DATA.error == 'text'}<div class='frame_musicboxerror'>Invalid field entry</div>{/if}
		      <div class='EditAwItemValue'><textarea name="text">{$VIEWER.awitemInfo.text}</textarea></div>
		      <input type="hidden" name="audioID" id="audioID" value="{$VIEWER.awitemInfo.audioid}" />
	      	<div class='EditAwItemDetail'>Style:</div>
	    	  {if $ERRORS.style}<div class='frame_musicboxerror'>{$ERRORS.style}</div>{/if}
  		    {if $DATA.error == 'style'}<div class='frame_musicboxerror'>Invalid style selected</div>{/if}
	  	    <div class='EditAwItemValue'>
						<select name=style>
							{foreach from=$VIEWER.styles item=style}
						  {if $style.id == $VIEWER.awitemInfo.styleid}
					  	<option value={$style.id} selected>{$style.name}</option>
						  {else}
						  <option value={$style.id}>{$style.name}</option>
						  {/if}
							{/foreach}
						</select>
	    	  </div>
  		    <div class='EditAwItemDetailSub'><input type="Submit" name="Submit" value="Submit"></div>
	      </form>
    	  <div class='EditAwItemDetailSub'>
  	    	{if $VIEWER.new != 't'}
	      	<form name="dpsStationAwItemDelForm" method="post" action="{$CONFIG.general.siteRoot}">
      			<input type="hidden" name="formName" value="dpsStationAwItemDelForm" />
      			<input type="hidden" name="moduleName" value="DPS" />
    	  		<input type="hidden" name="templateID" value="22" />
  	    		<input type="hidden" name="awitemID" value="{$VIEWER.awitemInfo.id}" />
	      		<input type="Submit" name="Submit" value="Clear">
      		</form>
      		{/if}
      	</div>
    	</div>
    	<div class='EditAwItemFile'>
    		{if $DATA.error == 'audioID'}<div class='frame_musicboxerror'>Please select a jingle or advert</div>{/if}
				<div id="toc_tree" class="fileselect">
	  			<script>
						loadTree();
					</script>
					<noscript>
						A filebrowser will display here if you have javascript enabled
					</noscript>
				</div>
			</div>
    	<br style="clear: both;">
			{/if}
    </div>
  </body>
</html>
