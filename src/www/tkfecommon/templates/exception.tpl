<HTML>
<HEAD>
<TITLE>OH NO! There has been a problem!</TITLE>
</HEAD>
<BODY>
<H1>Whoops!</H1><BR>
There seems to have been a problem<BR>
{if $showExceptionInfo}
	{foreach from=$exceptionData item=v key=k }
		{$k} : {$v}<BR>
	{/foreach}
{/if}
</FORM>
</BODY>
</HTML>