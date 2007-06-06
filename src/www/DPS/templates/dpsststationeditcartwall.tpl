{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager" studio="t" access_playlist=$VIEWER.access_playlist}
  <br>
  <br>
  <div class='FloatL'><div class='bigTitle'>Edit Cartwall</div></div>
  <div class='cartwallinfoR'>
    {templateLink id="30" text="<<< return to cartwall profiles"}<br>
    {templateLink id="27" text="<<< preview cartwall" _cartset=$VIEWER.cartsetID _page=$VIEWER.cartwall.page}
  </div>
  <br style='clear: both;'>
  {if $VIEWER.permError == 't'}
    You do not have permission to edit this cartwall.
  {else}
  <form name="dpsStationCartwallEditForm" method="post" action="{$CONFIG.general.siteRoot}">
  <input type="hidden" name="formName" value="dpsStationCartwallEditForm" />
  <input type="hidden" name="moduleName" value="DPS" />
  <input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
  <input type="hidden" name="cartset" value="{$VIEWER.cartsetID}" />
  <input type="hidden" name="cartwallID" value="{$VIEWER.cartwall.id}" />
  <input type="hidden" name="page" value="{$VIEWER.cartwall.page}" />
  {if $ERRORS.name}<div class='frame_musicboxerror'>{$ERRORS.name}</div>{/if}
  <div class='cartwallinfoL'>Name: <input type=text name=name value="{$VIEWER.cartwall.name}"></div>
  <br style='clear: both;'>
  {if $ERRORS.desc}<div class='frame_musicboxerror'>{$ERRORS.desc}</div>{/if}
  <div class='cartwallinfoL'>Desc: <input type=text size=35 name=desc value="{$VIEWER.cartwall.description}"></div>
  <div class='cartwallPage'>
    <img src='DPS/images/cartwallPageL.png' class='cartwallPageL'>
    <div class='cartwallpagenum'>
      Page: 
      {foreach from=$VIEWER.pagelink item=pages}
	{if $pages.id == $VIEWER.cartwall.page}
	  <b>{$pages.num}</b> 
	{else}
	  {templateLink id=$VIEWER.templateID text=$pages.num _cartset=$VIEWER.cartsetID _page=$pages.id} 
	{/if}
      {/foreach}
      <a href='{$CONFIG.general.siteRoot}?templateID={$VIEWER.templateID}&cartwallID={$VIEWER.cartwall.id}&cartset={$VIEWER.cartsetID}&page={$VIEWER.cartwall.page}&moduleName=DPS&formName=dpsStationAddCartwallPageForm'>+</a>
    </div>
    <img src='DPS/images/cartwallPageR.png' class='cartwallPageR'>
  </div>
  <br style='clear: both;'>
  <table class="cartwall">
    <tr>
      <td>
	{if $VIEWER.cart1.audioid == "none"}
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=29&cartID=New&cartPos=0&cartwallID={$VIEWER.cartwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EcartText'>{$VIEWER.cart1.name}</div>
	<div class='EcartTitle'>{$VIEWER.cart1.title}</div>
	<div class='EcartTime'>{$VIEWER.cart1.length}</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=29&cartID={$VIEWER.cart1.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td >
	{if $VIEWER.cart2.audioid == "none"}
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=29&cartID=New&cartPos=1&cartwallID={$VIEWER.cartwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EcartText'>{$VIEWER.cart2.name}</div>
	<div class='EcartTitle'>{$VIEWER.cart2.title}</div>
	<div class='EcartTime'>{$VIEWER.cart2.length}</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=29&cartID={$VIEWER.cart2.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td >
	{if $VIEWER.cart3.audioid == "none"}
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=29&cartID=New&cartPos=2&cartwallID={$VIEWER.cartwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EcartText'>{$VIEWER.cart3.name}</div>
	<div class='EcartTitle'>{$VIEWER.cart3.title}</div>
	<div class='EcartTime'>{$VIEWER.cart3.length}</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=29&cartID={$VIEWER.cart3.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
    </tr>
    <tr>
      <td>
	{if $VIEWER.cart4.audioid == "none"}
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=29&cartID=New&cartPos=3&cartwallID={$VIEWER.cartwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EcartText'>{$VIEWER.cart4.name}</div>
	<div class='EcartTitle'>{$VIEWER.cart4.title}</div>
	<div class='EcartTime'>{$VIEWER.cart4.length}</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=29&cartID={$VIEWER.cart4.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td>
	{if $VIEWER.cart5.audioid == "none"}
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=29&cartID=New&cartPos=4&cartwallID={$VIEWER.cartwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EcartText'>{$VIEWER.cart5.name}</div>
	<div class='EcartTitle'>{$VIEWER.cart5.title}</div>
	<div class='EcartTime'>{$VIEWER.cart5.length}</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=29&cartID={$VIEWER.cart5.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td>
	{if $VIEWER.cart6.audioid == "none"}
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=29&cartID=New&cartPos=5&cartwallID={$VIEWER.cartwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EcartText'>{$VIEWER.cart6.name}</div>
	<div class='EcartTitle'>{$VIEWER.cart6.title}</div>
	<div class='EcartTime'>{$VIEWER.cart6.length}</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=29&cartID={$VIEWER.cart6.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
    </tr>
    <tr>
      <td>
	{if $VIEWER.cart7.audioid == "none"}
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=29&cartID=New&cartPos=6&cartwallID={$VIEWER.cartwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EcartText'>{$VIEWER.cart7.name}</div>
	<div class='EcartTitle'>{$VIEWER.cart7.title}</div>
	<div class='EcartTime'>{$VIEWER.cart7.length}</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=29&cartID={$VIEWER.cart7.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td>
	{if $VIEWER.cart8.audioid == "none"}
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=29&cartID=New&cartPos=7&cartwallID={$VIEWER.cartwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EcartText'>{$VIEWER.cart8.name}</div>
	<div class='EcartTitle'>{$VIEWER.cart8.title}</div>
	<div class='EcartTime'>{$VIEWER.cart8.length}</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=29&cartID={$VIEWER.cart8.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td>
	{if $VIEWER.cart9.audioid == "none"}
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=29&cartID=New&cartPos=8&cartwallID={$VIEWER.cartwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EcartText'>{$VIEWER.cart9.name}</div>
	<div class='EcartTitle'>{$VIEWER.cart9.title}</div>
	<div class='EcartTime'>{$VIEWER.cart9.length}</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=29&cartID={$VIEWER.cart9.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
    </tr>
    <tr>
      <td>
	{if $VIEWER.cart10.audioid == "none"}
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=29&cartID=New&cartPos=9&cartwallID={$VIEWER.cartwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EcartText'>{$VIEWER.cart10.name}</div>
	<div class='EcartTitle'>{$VIEWER.cart10.title}</div>
	<div class='EcartTime'>{$VIEWER.cart10.length}</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=29&cartID={$VIEWER.cart10.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td>
	{if $VIEWER.cart11.audioid == "none"}
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=29&cartID=New&cartPos=10&cartwallID={$VIEWER.cartwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EcartText'>{$VIEWER.cart11.name}</div>
	<div class='EcartTitle'>{$VIEWER.cart11.title}</div>
	<div class='EcartTime'>{$VIEWER.cart11.length}</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=29&cartID={$VIEWER.cart11.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
      <td>
	{if $VIEWER.cart12.audioid == "none"}
	<div class='EcartBlank'>[BLANK]</div>
	<div class='EcartAdd'><a href="javascript:NewWindow('?templateID=29&cartID=New&cartPos=11&cartwallID={$VIEWER.cartwall.id}','acepopup','640','480');">Add</a></div>
	{else}
	<div class='EcartText'>{$VIEWER.cart12.name}</div>
	<div class='EcartTitle'>{$VIEWER.cart12.title}</div>
	<div class='EcartTime'>{$VIEWER.cart12.length}</div>
	<div class='EcartChange'><a href="javascript:NewWindow('?templateID=29&cartID={$VIEWER.cart12.id}','acepopup','640','480');">Change</a></div>
	{/if}
      </td>
    </tr>
  </table>
  <div class='EcartwallPerms'>
    {if $VIEWER.owner == 't'}
    {if $VIEWER.groupread}
    <input type="checkbox" name="readAll" value="on" checked>Allow others to use this cartset<br>
    {else}
    <input type="checkbox" name="readAll" value="on">Allow others to use this cartset<br>
    {/if}
    {if $VIEWER.groupwrite}
    <input type="checkbox" name="writeAll" value="on" checked>Allow others to edit this cartset<br>
    {else}
    <input type="checkbox" name="writeAll" value="on">Allow others to edit this cartset<br>
    {/if}
    {/if}
    <b>don't forget to save your changes!</b>
  </div>
  <div class='EcartwallSubmit'>
    <input type="Submit" name="Submit" value="Save Changes"><br>
    <input type="Submit" name="Submit" value="Remove Page">
  </div>
  </form>
  <br style='clear: both;'>
  <div class="warning">{$ERRORS.model}</div>
  {/if}
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
