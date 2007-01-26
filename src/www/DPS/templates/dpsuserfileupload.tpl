<html>
  <head>
    <title>{$title}</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
		<link rel="STYLESHEET" type="text/css" href="DPS/scripts/dhtmlxTree/css/dhtmlXTree.css">
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXCommon.js"></script>
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXTree.js"></script>	
  </head>
  <body>
	{if $VIEWER.permError}
		<div class='bigTitle'>Permission Error</div>
		<div class='subTitle'>You do not have permission to write to that folder</div>
	{else}
		<div class='alignleft'>
			<div class='bigTitle'>Advanced Properties: {$VIEWER.folder.name}</div>
			<form name="dpsUserUploadFileForm" enctype="multipart/form-data" method="post" action="{$CONFIG.general.siteRoot}">
    	  <input type="hidden" name="formName" value="dpsUserUploadFileForm" />
				<input type="hidden" name="moduleName" value="DPS" />
				<input type="hidden" name="templateID" value="70" />
				<input type="hidden" name="dirID" value="{$VIEWER.folder.id}" />
				Name: <input type="text" name="name" value="" /><br />
				Type: <select name="type"><option value="jingle">Jingle</option><option value="advert">Advert</option><option value="pre-rec">Pre-rec</option></select><br />
				File: <input type="file" name="ufile" /><br />
				<input type="submit" value="Save" />
			</form>
		</div>
		{/if}
	</body>
</html>
