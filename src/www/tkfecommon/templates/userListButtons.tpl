[
{if $ingroup}
+ <a href="javascript:submitform('userRemove', {$groupid})">-</a> 
{else}
<a href="javascript:submitform('userAdd', {$groupid})">+</a> -
{/if}
]