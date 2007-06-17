{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager" studio="t" access_playlist=$VIEWER.access_playlist}
	<br>
	<br>
<div class='bigTitle'>Station Cartwall Profiles</div>

<div class='subTitle'>Currently there are following cartwalls available:</div>
	<table border=1 class='stationtable'>
{foreach from=$VIEWER.cartsets item=cartset}
		<tr>
			<th class="userTableName">
				{$cartset.name}
			</th>
			<td class="userTableOption">
				{templateLink id="30" _cartset=$cartset.id text="view"}
			</td>
			<td class="userTableOption">
				{if $cartset.permissions.1 == '1'}
				{templateLink id="28" _cartset=$cartset.id text="edit"}
				{/if}
			</td>
			<td class="userTableOption">
				{if $cartset.permissions.1 == '1'}
				{templateLink id=$VIEWER.templateID _cartset=$cartset.id text="delete" _cartset=$cartset.id _formName="dpsStationDelCartsetForm" _moduleName="DPS"}
				{/if}
			</td>
			<td class="userTableDetail">
				{if $cartset.active == 't'}
				<div class="userdefaultcartset">active cartset</div>
				{else}
				{templateLink id=$VIEWER.templateID _cartset=$cartset.id text="make active cartset" _cartset=$cartset.id _formName="dpsStationActCartsetForm" _moduleName="DPS"}
				{/if}
			</td>
		</tr>
{/foreach}
	</table>
<div class='statiosubtitle'>Create new cartwall</div>
<form name="dpsStationNewCartsetForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="formName" value="dpsStationNewCartsetForm" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
	{if $ERRORS.name}<div class='frame_musicboxerror'>{$ERRORS.name}</div>{/if}
	Name: <input type=text name='name' value=''><br>
	{if $ERRORS.desc}<div class='frame_musicboxerror'>{$ERRORS.desc}</div>{/if}
	Description: <input type=text name='desc' value=''><br>
	<input type=submit name='submit' value='Add new'>
</form>
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
