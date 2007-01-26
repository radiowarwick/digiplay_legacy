        <ul>
          {foreach from=$groups key="groupid" item="group"}
            {if $group.inGroup}
              <li class="inGroup">
            {else}
              <li>
            {/if}
            {$group.groupname}
            {include file="rfile:groupListButtons.tpl" groupid=$groupid ingroup=$group.inGroup}
            </li>
          {/foreach}
        </ul>
