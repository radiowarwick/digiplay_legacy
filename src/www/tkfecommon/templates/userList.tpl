        <ul>
          {foreach from=$users key="userid" item="user"}
            {if $user.inGroup}
              <li class="inGroup">
            {else}
              <li>
            {/if}
            {$user.username}
            {include file="rfile:userListButtons.tpl" groupid=$userid ingroup=$user.inGroup}
            </li>
          {/foreach}
        </ul>