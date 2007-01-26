{if $type=="edit"}
 [ <a href="javascript:editrealm({$realmid})">Edit</a> ] 
{elseif $type=="perm"}
[
<a href="javascript:submitform('realmAllow', {$realmid})">a</a> 
<a href="javascript:submitform('realmDeny', {$realmid})">d</a> 
<a href="javascript:submitform('realmIgnore', {$realmid})">i</a>
]
{elseif $type=="setRealmParentID"}
[
<a href="javascript:addRealmSubmitForm({$realmid})">Select</a> 
]
{/if}