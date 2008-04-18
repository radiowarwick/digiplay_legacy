{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager" studio=$VIEWER.studioAccess access_playlist=$VIEWER.access_playlist}
  <br>
  <br>
  <div class='FloatL'><div class='bigTitle'>Edit Audiowall</div></div>
  <div class='awwallinfoR'>
    {templateLink id="23" text="<<< return to audiowall profiles"}<br>
    {templateLink id="26" text="<<< preview audiowall" _awset=$VIEWER.awsetID _page=$VIEWER.awwall.page}
  </div>
  <br style='clear: both;'>
  {if $VIEWER.permError == 't'}
    You do not have permission to view this audiowall.
  {else}
  <form name="dpsUserAwWallEditForm" method="post" action="{$CONFIG.general.siteRoot}">
  <input type="hidden" name="formName" value="dpsUserAwWallEditForm" />
  <input type="hidden" name="moduleName" value="DPS" />
  <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
  <input type="hidden" name="awset" value="{$VIEWER.awsetID}" />
  <input type="hidden" name="awwallID" value="{$VIEWER.awwall.id}" />
  <input type="hidden" name="page" value="{$VIEWER.awwall.page}" />
  {if $ERRORS.name}<div class='frame_musicboxerror'>{$ERRORS.name}</div>{/if}
  <div class='awwallinfoL'>Name: <input type=text name=name value="{$VIEWER.awwall.name}"></div>
  <br style='clear: both;'>
  {if $ERRORS.desc}<div class='frame_musicboxerror'>{$ERRORS.desc}</div>{/if}
  <div class='awwallinfoL'>Desc: <input type=text size=35 name=desc value="{$VIEWER.awwall.description}"></div>
  <div class='awwallPage'>
    <img src='DPS/images/awwallPageL.png' class='awwallPageL'>
    <div class='awwallpagenum'>
      Page: 
      {foreach from=$VIEWER.pagelink item=pages}
	{if $pages.id == $VIEWER.awwall.page}
	  <b>{$pages.num}</b> 
{else}
	  {templateLink id=$VIEWER.templateID text=$pages.num _awset=$VIEWER.awsetID _page=$pages.id} 
	{/if}
      {/foreach}
      <a href='{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}&awwallID={$VIEWER.awwall.id}&awset={$VIEWER.awsetID}&page={$VIEWER.awwall.page}&moduleName=DPS&formName=dpsUserAddAwWallPageForm'>+</a>
    </div>
    <img src='DPS/images/awwallPageR.png' class='awwallPageR'>
  </div>
  <br style='clear: both;'>
  <table class="awwall">
    <tr>
      <td>
	{if $VIEWER.awwall1.audioid == "none"}
	<div class='EawitemBlank'>[BLANK]</div>
	<div class='EawitemAdd'><a href="javascript:NewWindow('?templateID=24&awitemID=New&awitemPos=0&awwallID={$VIEWER.awwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EawitemText'>{$VIEWER.awitem1.name}</div>
	<div class='EawitemTitle'>{$VIEWER.awitem1.title}</div>
	<div class='EawitemTime'>{$VIEWER.awitem1.length}</div>
	<div class='EawitemChange'><a href="javascript:NewWindow('?templateID=24&awitemID={$VIEWER.awitem1.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td >
	{if $VIEWER.awitem2.audioid == "none"}
	<div class='EawitemBlank'>[BLANK]</div>
	<div class='EawitemAdd'><a href="javascript:NewWindow('?templateID=24&awitemID=New&awitemPos=1&awwallID={$VIEWER.awwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EawitemText'>{$VIEWER.awitem2.name}</div>
	<div class='EawitemTitle'>{$VIEWER.awitem2.title}</div>
	<div class='EawitemTime'>{$VIEWER.awitem2.length}</div>
	<div class='EawitemChange'><a href="javascript:NewWindow('?templateID=24&awitemID={$VIEWER.awitem2.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td >
	{if $VIEWER.awitem3.audioid == "none"}
	<div class='EawitemBlank'>[BLANK]</div>
	<div class='EawitemAdd'><a href="javascript:NewWindow('?templateID=24&awitemID=New&awitemPos=2&awwallID={$VIEWER.awwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EawitemText'>{$VIEWER.awitem3.name}</div>
	<div class='EawitemTitle'>{$VIEWER.awitem3.title}</div>
	<div class='EawitemTime'>{$VIEWER.awitem3.length}</div>
	<div class='EawitemChange'><a href="javascript:NewWindow('?templateID=24&awitemID={$VIEWER.awitem3.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
    </tr>
    <tr>
      <td>
	{if $VIEWER.awitem4.audioid == "none"}
	<div class='EawitemBlank'>[BLANK]</div>
	<div class='EawitemAdd'><a href="javascript:NewWindow('?templateID=24&awitemID=New&awitemPos=3&awwallID={$VIEWER.awwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EawitemText'>{$VIEWER.awitem4.name}</div>
	<div class='EawitemTitle'>{$VIEWER.awitem4.title}</div>
	<div class='EawitemTime'>{$VIEWER.awitem4.length}</div>
	<div class='EawitemChange'><a href="javascript:NewWindow('?templateID=24&awitemID={$VIEWER.awitem4.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td>
	{if $VIEWER.awitem5.audioid == "none"}
	<div class='EawitemBlank'>[BLANK]</div>
	<div class='EawitemAdd'><a href="javascript:NewWindow('?templateID=24&awitemID=New&awitemPos=4&awwallID={$VIEWER.awwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EawitemText'>{$VIEWER.awitem5.name}</div>
	<div class='EawitemTitle'>{$VIEWER.awitem5.title}</div>
	<div class='EawitemTime'>{$VIEWER.awitem5.length}</div>
	<div class='EawitemChange'><a href="javascript:NewWindow('?templateID=24&awitemID={$VIEWER.awitem5.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td>
	{if $VIEWER.awitem6.audioid == "none"}
	<div class='EawitemBlank'>[BLANK]</div>
	<div class='EawitemAdd'><a href="javascript:NewWindow('?templateID=24&awitemID=New&awitemPos=5&awwallID={$VIEWER.awwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EawitemText'>{$VIEWER.awitem6.name}</div>
	<div class='EawitemTitle'>{$VIEWER.awitem6.title}</div>
	<div class='EawitemTime'>{$VIEWER.awitem6.length}</div>
	<div class='EawitemChange'><a href="javascript:NewWindow('?templateID=24&awitemID={$VIEWER.awitem6.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
    </tr>
    <tr>
      <td>
	{if $VIEWER.awitem7.audioid == "none"}
	<div class='EawitemBlank'>[BLANK]</div>
	<div class='EawitemAdd'><a href="javascript:NewWindow('?templateID=24&awitemID=New&awitemPos=6&awwallID={$VIEWER.awwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EawitemText'>{$VIEWER.awitem7.name}</div>
	<div class='EawitemTitle'>{$VIEWER.awitem7.title}</div>
	<div class='EawitemTime'>{$VIEWER.awitem7.length}</div>
	<div class='EawitemChange'><a href="javascript:NewWindow('?templateID=24&awitemID={$VIEWER.awitem7.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td>
	{if $VIEWER.awitem8.audioid == "none"}
	<div class='EawitemBlank'>[BLANK]</div>
	<div class='EawitemAdd'><a href="javascript:NewWindow('?templateID=24&awitemID=New&awitemPos=7&awwallID={$VIEWER.awwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EawitemText'>{$VIEWER.awitem8.name}</div>
	<div class='EawitemTitle'>{$VIEWER.awitem8.title}</div>
	<div class='EawitemTime'>{$VIEWER.awitem8.length}</div>
	<div class='EawitemChange'><a href="javascript:NewWindow('?templateID=24&awitemID={$VIEWER.awitem8.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td>
	{if $VIEWER.awitem9.audioid == "none"}
	<div class='EawitemBlank'>[BLANK]</div>
	<div class='EawitemAdd'><a href="javascript:NewWindow('?templateID=24&awitemID=New&awitemPos=8&awwallID={$VIEWER.awwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EawitemText'>{$VIEWER.awitem9.name}</div>
	<div class='EawitemTitle'>{$VIEWER.awitem9.title}</div>
	<div class='EawitemTime'>{$VIEWER.awitem9.length}</div>
	<div class='EawitemChange'><a href="javascript:NewWindow('?templateID=24&awitemID={$VIEWER.awitem9.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
    </tr>
    <tr>
      <td>
	{if $VIEWER.awitem10.audioid == "none"}
	<div class='EawitemBlank'>[BLANK]</div>
	<div class='EawitemAdd'><a href="javascript:NewWindow('?templateID=24&awitemID=New&awitemPos=9&awwallID={$VIEWER.awwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EawitemText'>{$VIEWER.awitem10.name}</div>
	<div class='EawitemTitle'>{$VIEWER.awitem10.title}</div>
	<div class='EawitemTime'>{$VIEWER.awitem10.length}</div>
	<div class='EawitemChange'><a href="javascript:NewWindow('?templateID=24&awitemID={$VIEWER.awitem10.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td>
	{if $VIEWER.awitem11.audioid == "none"}
	<div class='EawitemBlank'>[BLANK]</div>
	<div class='EawitemAdd'><a href="javascript:NewWindow('?templateID=24&awitemID=New&awitemPos=10&awwallID={$VIEWER.awwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EawitemText'>{$VIEWER.awitem11.name}</div>
	<div class='EawitemTitle'>{$VIEWER.awitem11.title}</div>
	<div class='EawitemTime'>{$VIEWER.awitem11.length}</div>
	<div class='EawitemChange'><a href="javascript:NewWindow('?templateID=24&awitemID={$VIEWER.awitem11.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td>
	{if $VIEWER.awitem12.audioid == "none"}
	<div class='EawitemBlank'>[BLANK]</div>
	<div class='EawitemAdd'><a href="javascript:NewWindow('?templateID=24&awitemID=New&awitemPos=11&awwallID={$VIEWER.awwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EawitemText'>{$VIEWER.awitem12.name}</div>
	<div class='EawitemTitle'>{$VIEWER.awitem12.title}</div>
	<div class='EawitemTime'>{$VIEWER.awitem12.length}</div>
	<div class='EawitemChange'><a href="javascript:NewWindow('?templateID=24&awitemID={$VIEWER.awitem12.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
    </tr>
  </table>
  <div class='EawitemwallPerms'>
    {if $VIEWER.owner == 't'}
    {if $VIEWER.groupread}
    <input type="checkbox" name="readAll" value="on" checked>Allow others to use this audiowall set<br>
    {else}
    <input type="checkbox" name="readAll" value="on">Allow others to use this audiowall set<br>
    {/if}
    {if $VIEWER.groupwrite}
    <input type="checkbox" name="writeAll" value="on" checked>Allow others to edit this audiowall set<br>
    {else}
    <input type="checkbox" name="writeAll" value="on">Allow others to edit this audiowall set<br>
    {/if}
    {/if}
    <b>don't forget to save your changes!</b>
  </div>
  <div class='EawwallSubmit'>
    <input type="Submit" name="Submit" value="Save Changes"><br>
    <input type="Submit" name="Submit" value="Remove Page">
  </div>
  </form>
  <br style='clear: both;'>
  <div class="warning">{$ERRORS.model}</div>
  {/if}
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
