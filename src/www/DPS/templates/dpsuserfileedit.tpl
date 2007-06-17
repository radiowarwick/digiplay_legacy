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
				<input type="hidden" name="dirID" value="{$VIEWER.folder.id}" />
				Name: <input type="text" name="dirtext" value="{$VIEWER.folder.name}" /><br />
				{if $VIEWER.dirown == 't'}
				{if $VIEWER.dirpub == 't'}
				Permission: 
				<input type="option" name="dirperm" value="priv" />
				{if $VIEWER.dirr == 't'}
				<input type="option" name="dirperm" value="pubr" checked/>
				{else}
				<input type="option" name="dirperm" value="pubr" />
				{/if}
				{if $VIEWER.dirrw == 't'}
				<input type="option" name="dirperm" value="pubrw" checked/>
				{else}
				<input type="option" name="dirperm" value="pubrw" />
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
