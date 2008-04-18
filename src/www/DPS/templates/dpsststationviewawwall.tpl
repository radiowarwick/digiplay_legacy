{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager" studio="t" access_playlist=$VIEWER.access_playlist}
  <br>
  <br>
  <div class='FloatL'><div class='bigTitle'>View Audiowall</div></div>
  <div class='awwallinfoR'>
    {templateLink id="27" text="<<< return to audiowall set profiles"} 
    {if $VIEWER.editperm == 't'}
    <br>{templateLink id="28" text="<<< edit audiowall set" _awset=$VIEWER.awsetID _page=$VIEWER.awwall.page} 
    {/if}
  </div>
  <br class='ClearLR'>
  {if $VIEWER.permError == 't'}
    You do not have permission to view this audiowall.
  {else}
  <div class='awwallinfoL'>
    Name: <b>{$VIEWER.awwall.name}</b>
  </div>
  <br style='clear: both;'>
  <div class='awwallinfoL'>
    Desc: <b>{$VIEWER.awwall.description}</b>
  </div>
  <div class='awwallPage'>
    <img src='DPS/images/awwallPageL.png' class='awwallPageL'>
    <div class='awwallpagenum'>
      Page: 
      {foreach from=$VIEWER.pagelink item=pages}
	{if $pages.active == 't'}
	  <b>{$pages.num}</b> 
	{else}
	  {templateLink id=$VIEWER.templateID text=$pages.num _awset=$VIEWER.awsetID _page=$pages.id} 
	{/if}
      {/foreach}
    </div>
    <img src='DPS/images/awwallPageR.png' class='awwallPageR'>
  </div>
  <br style='clear: both;'>
  <table class="awwall">
    <tr>
      <td style='background: rgb({$VIEWER.awitem1.BackColour.r},{$VIEWER.awitem1.BackColour.g},{$VIEWER.awitem1.BackColour.b}); color: rgb({$VIEWER.awitem1.ForeColour.r},{$VIEWER.awitem1.ForeColour.g},{$VIEWER.awitem1.ForeColour.b})'>
	<div class='awitemTitle'>{$VIEWER.awitem1.name}</div>
	<div class='awitemTime'>{$VIEWER.awitem1.length}</div>
      </td>
      <td style='background: rgb({$VIEWER.awitem2.BackColour.r},{$VIEWER.awitem2.BackColour.g},{$VIEWER.awitem2.BackColour.b}); color: rgb({$VIEWER.awitem2.ForeColour.r},{$VIEWER.awitem2.ForeColour.g},{$VIEWER.awitem2.ForeColour.b})'>
	<div class='awitemTitle'>{$VIEWER.awitem2.name}</div>
	<div class='awitemTime'>{$VIEWER.awitem2.length}</div>
      </td>
      <td style='background: rgb({$VIEWER.awitem3.BackColour.r},{$VIEWER.awitem3.BackColour.g},{$VIEWER.awitem3.BackColour.b}); color: rgb({$VIEWER.awitem3.ForeColour.r},{$VIEWER.awitem3.ForeColour.g},{$VIEWER.awitem3.ForeColour.b})'>
	<div class='awitemTitle'>{$VIEWER.awitem3.name}</div>
	<div class='awitemTime'>{$VIEWER.awitem3.length}</div>
      </td>
    </tr>
    <tr>
      <td style='background: rgb({$VIEWER.awitem4.BackColour.r},{$VIEWER.awitem4.BackColour.g},{$VIEWER.awitem4.BackColour.b}); color: rgb({$VIEWER.awitem4.ForeColour.r},{$VIEWER.awitem4.ForeColour.g},{$VIEWER.awitem4.ForeColour.b})'>
	<div class='awitemTitle'>{$VIEWER.awitem4.name}</div>
	<div class='awitemTime'>{$VIEWER.awitem4.length}</div>
      </td>
      <td style='background: rgb({$VIEWER.awitem5.BackColour.r},{$VIEWER.awitem5.BackColour.g},{$VIEWER.awitem5.BackColour.b}); color: rgb({$VIEWER.awitem5.ForeColour.r},{$VIEWER.awitem5.ForeColour.g},{$VIEWER.awitem5.ForeColour.b})'>
	<div class='awitemTitle'>{$VIEWER.awitem5.name}</div>
	<div class='awitemTime'>{$VIEWER.awitem5.length}</div>
      </td>
      <td style='background: rgb({$VIEWER.awitem6.BackColour.r},{$VIEWER.awitem6.BackColour.g},{$VIEWER.awitem6.BackColour.b}); color: rgb({$VIEWER.awitem6.ForeColour.r},{$VIEWER.awitem6.ForeColour.g},{$VIEWER.awitem6.ForeColour.b})'>
	<div class='awitemTitle'>{$VIEWER.awitem6.name}</div>
	<div class='awitemTime'>{$VIEWER.awitem6.length}</div>
      </td>
    </tr>
    <tr>
      <td style='background: rgb({$VIEWER.awitem7.BackColour.r},{$VIEWER.awitem7.BackColour.g},{$VIEWER.awitem7.BackColour.b}); color: rgb({$VIEWER.awitem7.ForeColour.r},{$VIEWER.awitem7.ForeColour.g},{$VIEWER.awitem7.ForeColour.b})'>
	<div class='awitemTitle'>{$VIEWER.awitem7.name}</div>
	<div class='awitemTime'>{$VIEWER.awitem7.length}</div>
      </td>
      <td style='background: rgb({$VIEWER.awitem8.BackColour.r},{$VIEWER.awitem8.BackColour.g},{$VIEWER.awitem8.BackColour.b}); color: rgb({$VIEWER.awitem8.ForeColour.r},{$VIEWER.awitem8.ForeColour.g},{$VIEWER.awitem8.ForeColour.b})'>
	<div class='awitemTitle'>{$VIEWER.awitem8.name}</div>
	<div class='awitemTime'>{$VIEWER.awitem8.length}</div>
      </td>
      <td style='background: rgb({$VIEWER.awitem9.BackColour.r},{$VIEWER.awitem9.BackColour.g},{$VIEWER.awitem9.BackColour.b}); color: rgb({$VIEWER.awitem9.ForeColour.r},{$VIEWER.awitem9.ForeColour.g},{$VIEWER.awitem9.ForeColour.b})'>
	<div class='awitemTitle'>{$VIEWER.awitem9.name}</div>
	<div class='awitemTime'>{$VIEWER.awitem9.length}</div>
      </td>
    </tr>
    <tr>
      <td style='background: rgb({$VIEWER.awitem10.BackColour.r},{$VIEWER.awitem10.BackColour.g},{$VIEWER.awitem10.BackColour.b}); color: rgb({$VIEWER.awitem10.ForeColour.r},{$VIEWER.awitem10.ForeColour.g},{$VIEWER.awitem10.ForeColour.b})'>
	<div class='awitemTitle'>{$VIEWER.awitem10.name}</div>
	<div class='awitemTime'>{$VIEWER.awitem10.length}</div>
      </td>
      <td style='background: rgb({$VIEWER.awitem11.BackColour.r},{$VIEWER.awitem11.BackColour.g},{$VIEWER.awitem11.BackColour.b}); color: rgb({$VIEWER.awitem11.ForeColour.r},{$VIEWER.awitem11.ForeColour.g},{$VIEWER.awitem11.ForeColour.b})'>
	<div class='awitemTitle'>{$VIEWER.awitem11.name}</div>
	<div class='awitemTime'>{$VIEWER.awitem11.length}</div>
      </td>
      <td style='background: rgb({$VIEWER.awitem12.BackColour.r},{$VIEWER.awitem12.BackColour.g},{$VIEWER.awitem12.BackColour.b}); color: rgb({$VIEWER.awitem12.ForeColour.r},{$VIEWER.awitem12.ForeColour.g},{$VIEWER.awitem12.ForeColour.b})'>
	<div class='awitemTitle'>{$VIEWER.awitem12.name}</div>
	<div class='awitemTime'>{$VIEWER.awitem12.length}</div>
      </td>
    </tr>
  </table>
  {/if}
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
