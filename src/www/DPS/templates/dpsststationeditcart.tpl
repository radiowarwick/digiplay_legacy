<html>
  <head>
    <title>Edit a Cart</title>
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
	    <div class='bigTitle'>Editing cart {$VIEWER.cartPos}</div>
  	  <hr>
    	{if $VIEWER.permError == 't'}
      You do not have permission to edit this cart.
    	{else}
    	<div class='EditCartDetails'>
      	{if $VIEWER.new != 't'}
	      <form name="dpsStationCartEditForm" method="post" action="{$CONFIG.general.siteRoot}">
	  	    <input type="hidden" name="formName" value="dpsStationCartEditForm" />
  	  	  <input type="hidden" name="moduleName" value="DPS" />
    	  	<input type="hidden" name="templateID" value="22" />
		      <input type="hidden" name="cartID" value="{$VIEWER.cartInfo.id}" />
	      {else}
	      <form name="dpsStationCartAddForm" method="post" action="{$CONFIG.general.siteRoot}">
		      <input type="hidden" name="formName" value="dpsStationCartAddForm" />
		      <input type="hidden" name="moduleName" value="DPS" />
  		    <input type="hidden" name="templateID" value="22" />
    		  <input type="hidden" name="cartPos" value="{$VIEWER.cartPos}" />
      		<input type="hidden" name="cartwallID" value="{$VIEWER.cartwallID}" />
	      {/if}
		      <div class='EditCartDetail'>Text:</div>
		      {if $DATA.error == 'text'}<div class='frame_musicboxerror'>Invalid field entry</div>{/if}
		      <div class='EditCartValue'><textarea name="text">{$VIEWER.cartInfo.text}</textarea></div>
		      <input type="hidden" name="audioID" id="audioID" value="{$VIEWER.cartInfo.audioid}" />
	      	<div class='EditCartDetail'>Style:</div>
	    	  {if $ERRORS.style}<div class='frame_musicboxerror'>{$ERRORS.style}</div>{/if}
  		    {if $DATA.error == 'style'}<div class='frame_musicboxerror'>Invalid style selected</div>{/if}
	  	    <div class='EditCartValue'>
						<select name=style>
							{foreach from=$VIEWER.styles item=style}
						  {if $style.id == $VIEWER.cartInfo.styleid}
					  	<option value={$style.id} selected>{$style.name}</option>
						  {else}
						  <option value={$style.id}>{$style.name}</option>
						  {/if}
							{/foreach}
						</select>
	    	  </div>
  		    <div class='EditCartDetailSub'><input type="Submit" name="Submit" value="Submit"></div>
	      </form>
    	  <div class='EditCartDetailSub'>
  	    	{if $VIEWER.new != 't'}
	      	<form name="dpsStationCartDelForm" method="post" action="{$CONFIG.general.siteRoot}">
      			<input type="hidden" name="formName" value="dpsStationCartDelForm" />
      			<input type="hidden" name="moduleName" value="DPS" />
    	  		<input type="hidden" name="templateID" value="22" />
  	    		<input type="hidden" name="cartID" value="{$VIEWER.cartInfo.id}" />
	      		<input type="Submit" name="Submit" value="Clear">
      		</form>
      		{/if}
      	</div>
    	</div>
    	<div class='EditCartFile'>
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
