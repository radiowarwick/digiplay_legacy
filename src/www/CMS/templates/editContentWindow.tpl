<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Editing CMS Region</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>
{if $VIEWER.error}
	Error:<br>
	{$VIEWER.error}
{else}
	{if $VIEWER.perm == 'edit'}
		<form method='post' action=''>
		<input type='hidden' name='formName' value='inlineEdit' />
		<input type='hidden' name='moduleName' value='CMS' />
		{$VIEWER.editorCode}
		<input type="hidden" name="regionID" value="{$VIEWER.regionID}" />
		<p>
		Show In Line Editing <input type='checkbox' name='alwaysInLine' {$VIEWER.showInLineEditing} />
		<input type="submit" name="submit" value="Save" />
		</p>
		</form>
	{/if}
{/if}
</body>
</html>
