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
			<div class='bigTitle'>File Upload: {$VIEWER.folder.name}</div>
			<div class='subTitle'>Only upload *.wav files (44100Hz, 16-bit, Stereo). Size limit: 20MB</div>
			{if $DATA.error == 'form'}
			<div class='subTitle'>{$DATA.Emessage}</div>
			{elseif $DATA.error == 'perm'}
			<div class='subTitle'>You do not have permission to upload to the selected location</div>
			{/if}
			<form name="dpsUserUploadFileForm" enctype="multipart/form-data" method="post" action="{$CONFIG.general.siteRoot}">
				<input type="hidden" name="formName" value="dpsUserUploadFileForm" />
				<input type="hidden" name="moduleName" value="DPS" />
				<input type="hidden" name="templateID" value="22" />
				<input type="hidden" name="dirID" value="{$VIEWER.folder.id}" />
				Name: <input type="text" name="name" value="" /><br />
				Package: <input type="text" name="package" value="" /><br />
				Type: <select name="type">
					<option value="jingle">Jingle</option>
					<option value="advert">Advert</option>
					<!--<option value="pre-rec">Pre-rec</option>-->
				</select><br />
				File: <input type="file" name="ufile" /><br />
				<input type="submit" value="Save" />
			</form>
			<div class#'subTitle'>After clicking submit, please be patient while your file is uploaded and added to the playout system.</div>
		</div>
		{/if}
	</body>
</html>
