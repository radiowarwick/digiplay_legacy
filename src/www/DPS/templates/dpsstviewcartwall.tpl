{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager" studio=$VIEWER.studioAccess access_playlist=$VIEWER.access_playlist}
	<br>
	<br>
	<div class='FloatL'><div class='bigTitle'>View Cartwall</div></div>
	<div class='cartwallinfoR'>
		{templateLink id="23" text="<<< return to cartwall profiles"} 
		{if $VIEWER.editperm == 't'}
		<br>{templateLink id="25" text="<<< edit cartwall" _cartset=$VIEWER.cartsetID _page=$VIEWER.cartwall.page} 
		{/if}
	</div>
	<br style='clear: both;'>
	{if $VIEWER.permError == 't'}
		You do not have permission to view this cartwall.
	{else}
	<div class='cartwallinfoL'>
		Name: <b>{$VIEWER.cartwall.name}</b>
	</div>
	<br style='clear: both;'>
	<div class='cartwallinfoL'>
		Desc: <b>{$VIEWER.cartwall.description}</b>
	</div>
	<div class='cartwallPage'>
		<img src='DPS/images/cartwallPageL.png' class='cartwallPageL'>
		<div class='cartwallpagenum'>
			Page: 
			{foreach from=$VIEWER.pagelink item=pages}
				{if $pages.active == 't'}
					<b>{$pages.num}</b>
				{else}
					{templateLink id="67" text=$pages.num _cartset=$VIEWER.cartsetID _page=$pages.id} 
				{/if}
			{/foreach}
		</div>
		<img src='DPS/images/cartwallPageR.png' class='cartwallPageR'>
	</div>
	<br style='clear: both;'>
	<table class="cartwall">
		<tr>
			<td style='background: rgb({$VIEWER.cart1.BackColour.r},{$VIEWER.cart1.BackColour.g},{$VIEWER.cart1.BackColour.b}); color: rgb({$VIEWER.cart1.ForeColour.r},{$VIEWER.cart1.ForeColour.g},{$VIEWER.cart1.ForeColour.b})'>
	<div class='cartTitle'>{$VIEWER.cart1.name}</div>
	<div class='cartTime'>{$VIEWER.cart1.length}</div>
			</td>
			<td style='background: rgb({$VIEWER.cart2.BackColour.r},{$VIEWER.cart2.BackColour.g},{$VIEWER.cart2.BackColour.b}); color: rgb({$VIEWER.cart2.ForeColour.r},{$VIEWER.cart2.ForeColour.g},{$VIEWER.cart2.ForeColour.b})'>
	<div class='cartTitle'>{$VIEWER.cart2.name}</div>
	<div class='cartTime'>{$VIEWER.cart2.length}</div>
			</td>
			<td style='background: rgb({$VIEWER.cart3.BackColour.r},{$VIEWER.cart3.BackColour.g},{$VIEWER.cart3.BackColour.b}); color: rgb({$VIEWER.cart3.ForeColour.r},{$VIEWER.cart3.ForeColour.g},{$VIEWER.cart3.ForeColour.b})'>
	<div class='cartTitle'>{$VIEWER.cart3.name}</div>
	<div class='cartTime'>{$VIEWER.cart3.length}</div>
			</td>
		</tr>
		<tr>
			<td style='background: rgb({$VIEWER.cart4.BackColour.r},{$VIEWER.cart4.BackColour.g},{$VIEWER.cart4.BackColour.b}); color: rgb({$VIEWER.cart4.ForeColour.r},{$VIEWER.cart4.ForeColour.g},{$VIEWER.cart4.ForeColour.b})'>
	<div class='cartTitle'>{$VIEWER.cart4.name}</div>
	<div class='cartTime'>{$VIEWER.cart4.length}</div>
			</td>
			<td style='background: rgb({$VIEWER.cart5.BackColour.r},{$VIEWER.cart5.BackColour.g},{$VIEWER.cart5.BackColour.b}); color: rgb({$VIEWER.cart5.ForeColour.r},{$VIEWER.cart5.ForeColour.g},{$VIEWER.cart5.ForeColour.b})'>
	<div class='cartTitle'>{$VIEWER.cart5.name}</div>
	<div class='cartTime'>{$VIEWER.cart5.length}</div>
			</td>
			<td style='background: rgb({$VIEWER.cart6.BackColour.r},{$VIEWER.cart6.BackColour.g},{$VIEWER.cart6.BackColour.b}); color: rgb({$VIEWER.cart6.ForeColour.r},{$VIEWER.cart6.ForeColour.g},{$VIEWER.cart6.ForeColour.b})'>
	<div class='cartTitle'>{$VIEWER.cart6.name}</div>
	<div class='cartTime'>{$VIEWER.cart6.length}</div>
			</td>
		</tr>
		<tr>
			<td style='background: rgb({$VIEWER.cart7.BackColour.r},{$VIEWER.cart7.BackColour.g},{$VIEWER.cart7.BackColour.b}); color: rgb({$VIEWER.cart7.ForeColour.r},{$VIEWER.cart7.ForeColour.g},{$VIEWER.cart7.ForeColour.b})'>
	<div class='cartTitle'>{$VIEWER.cart7.name}</div>
	<div class='cartTime'>{$VIEWER.cart7.length}</div>
			</td>
			<td style='background: rgb({$VIEWER.cart8.BackColour.r},{$VIEWER.cart8.BackColour.g},{$VIEWER.cart8.BackColour.b}); color: rgb({$VIEWER.cart8.ForeColour.r},{$VIEWER.cart8.ForeColour.g},{$VIEWER.cart8.ForeColour.b})'>
	<div class='cartTitle'>{$VIEWER.cart8.name}</div>
	<div class='cartTime'>{$VIEWER.cart8.length}</div>
			</td>
			<td style='background: rgb({$VIEWER.cart9.BackColour.r},{$VIEWER.cart9.BackColour.g},{$VIEWER.cart9.BackColour.b}); color: rgb({$VIEWER.cart9.ForeColour.r},{$VIEWER.cart9.ForeColour.g},{$VIEWER.cart9.ForeColour.b})'>
	<div class='cartTitle'>{$VIEWER.cart9.name}</div>
	<div class='cartTime'>{$VIEWER.cart9.length}</div>
			</td>
		</tr>
		<tr>
			<td style='background: rgb({$VIEWER.cart10.BackColour.r},{$VIEWER.cart10.BackColour.g},{$VIEWER.cart10.BackColour.b}); color: rgb({$VIEWER.cart10.ForeColour.r},{$VIEWER.cart10.ForeColour.g},{$VIEWER.cart10.ForeColour.b})'>
	<div class='cartTitle'>{$VIEWER.cart10.name}</div>
	<div class='cartTime'>{$VIEWER.cart10.length}</div>
			</td>
			<td style='background: rgb({$VIEWER.cart11.BackColour.r},{$VIEWER.cart11.BackColour.g},{$VIEWER.cart11.BackColour.b}); color: rgb({$VIEWER.cart11.ForeColour.r},{$VIEWER.cart11.ForeColour.g},{$VIEWER.cart11.ForeColour.b})'>
	<div class='cartTitle'>{$VIEWER.cart11.name}</div>
	<div class='cartTime'>{$VIEWER.cart11.length}</div>
			</td>
			<td style='background: rgb({$VIEWER.cart12.BackColour.r},{$VIEWER.cart12.BackColour.g},{$VIEWER.cart12.BackColour.b}); color: rgb({$VIEWER.cart12.ForeColour.r},{$VIEWER.cart12.ForeColour.g},{$VIEWER.cart12.ForeColour.b})'>
	<div class='cartTitle'>{$VIEWER.cart12.name}</div>
	<div class='cartTime'>{$VIEWER.cart12.length}</div>
			</td>
		</tr>
	</table>
	{/if}
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
