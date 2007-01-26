{if $notRoot}
<ul>
{else}
<ul class="mktree" id="realmTree">
{/if}
  {foreach from=$realms key="name" item="subrealms"}
    {if $name != '_DETAILS_'}
    <li>
    {if $subrealms._DETAILS_.userallow == 'n' || $subrealms._DETAILS_.groupallow == 'n' || $subrealms._DETAILS_.groupallow == '!'}
      <span class="deny">
      {elseif $subrealms._DETAILS_.userallow == 'y' || $subrealms._DETAILS_.groupallow == 'y'}
      <span class="allow">
    {/if}
    {$name}</span> 
    
    {if     $subrealms._DETAILS_.userallow == 'y'}u:allow
    {elseif $subrealms._DETAILS_.userallow == 'n'}u:deny
    {elseif $subrealms._DETAILS_.userallow == '!'}u:deny!{/if}
    
    {if     $subrealms._DETAILS_.groupallow == 'y'}g:allow
    {elseif $subrealms._DETAILS_.groupallow == 'n'}g:deny
    {elseif $subrealms._DETAILS_.groupallow == '!'}g:deny!{/if}
    
    {include file="rfile:realmTreeButtons.tpl" realmid=$subrealms._DETAILS_.realmid type=$type}
    
    {if $subrealms|@count > 1}
      {include file="rfile:realmTreeMaker.tpl" realms=$subrealms notRoot=1}
    {/if}
    </li>
    {/if}
  {/foreach}
</ul>