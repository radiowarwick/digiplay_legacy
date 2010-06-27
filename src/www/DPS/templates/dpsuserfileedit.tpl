<html>
	<head>
		<title>Edit Directory Information</title>
		<link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
	</head>
	<body>
	{if $VIEWER.permError}
		<div class='bigTitle'>Permission Error</div>
		<div class='subTitle'>You do not have permission to edit to that folder</div>
	{else}
		<div class='alignleft'>
			<div class='bigTitle'>Edit Directory: {$VIEWER.folder.name}</div>
			<hr />
			<div class='subTitle'>Directory Name</div>
			<form name="dpsdirrename" method="post" action="{$CONFIG.general.siteRoot}">
				<input type="hidden" name="formName" value="dpsdirrename" />
				<input type="hidden" name="moduleName" value="DPS" />
				<input type="hidden" name="templateID" value="22" />
				<input type="hidden" name="rootdir" value="{$VIEWER.folder.id}" />
				Name: <input type="text" name="dirtext" value="{$VIEWER.folder.name}" /><br />
				{if $VIEWER.dirown == 't'}
				{if $VIEWER.dirpub == 't'}
				Permission:<br />
				{if $VIEWER.priv == 't'}
				<input type="radio" name="dirperm" value="priv" checked/> Private<br />
				{else}
				<input type="radio" name="dirperm" value="priv" /> Private<br />
				{/if}
				{if $VIEWER.dirr == 't'}
				<input type="radio" name="dirperm" value="pubr" checked/> Everyone Read only<br />
				{else}
				<input type="radio" name="dirperm" value="pubr" /> Everyone Read only<br />
				{/if}
				{if $VIEWER.dirrw == 't'}
				<input type="radio" name="dirperm" value="pubrw" checked/> Everyone Read/Write<br />
				{else}
				<input type="radio" name="dirperm" value="pubrw" /> Everyone Read/Write<br />
				{/if}
				<br />
				{else}
				Permission: All higher level folders must be public read<br />
				{/if}
				{/if}
				<input type="submit" value="Save" />
			</form>
		</div>
		{/if}
	</body>
</html>
