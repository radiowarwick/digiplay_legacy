</p>
<H1>Whoops!</H1><BR>
There seems to have been a problem<BR>
{if $showExceptionInfo}
	{foreach from=$exceptionData item=v key=k }
		{$k} : {$v}<BR>
	{/foreach}
{/if}
</p>
