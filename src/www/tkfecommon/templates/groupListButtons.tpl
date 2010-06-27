[
{if $ingroup}
+ <a href="javascript:submitform('groupRemove', {$groupid})">-</a> 
{else}
<a href="javascript:submitform('groupAdd', {$groupid})">+</a> -
{/if}
]