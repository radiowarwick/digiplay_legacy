{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager" studio=$VIEWER.studioAccess access_playlist=$VIEWER.access_playlist}
<br><br>
<div class='bigTitle'>Cartwall Profiles</div>

<div class='subTitle'>You currently have the following cartwalls available:</div>
	<table border=1 class='stationtable'>
	{if $VIEWER.stationcartset != "None" && $VIEWER.stationcartset.id != ""}
		<tr>
			<th class="stationTableName">
				{$VIEWER.stationcartset.name}
			</th>
			<td class="stationTableOption">
				{templateLink id="26" _cartset=$VIEWER.stationcartset.id text="view"}
			</td>
			<td class="stationTableOption">
			</td>
			<td class="stationTableOption">
			</td>
			<td class="stationTableDetail">
	<div class="userdefaultcartset">preloaded</div>
			</td>
		</tr>
	{else}
		<tr>
			<th colspan=5 class="stationTableName">
				no station cartset selected
			</th>
		</tr>
	{/if}
{foreach from=$VIEWER.cartsets item=cartset}
		<tr>
			<th class="userTableName">
				{$cartset.name}
			</th>
			<td class="userTableOption">
				{if $cartset.permissions.0 == '1'}
				{templateLink id="26" _cartset=$cartset.id text="view"}
				{/if}
			</td>
			<td class="userTableOption">
				{if $cartset.permissions.1 == '1'}
				{templateLink id="25" _cartset=$cartset.id text="edit"}
				{/if}
			</td>
			<td class="userTableOption">
				{if $cartset.parentperm.1 == '1'}
				{templateLink id=$VIEWER.templateID _cartset=$cartset.id text="delete" _cartset=$cartset.id _formName="dpsUserDelCartsetForm" _moduleName="DPS"}
				{/if}
			</td>
			<td class="userTableDetail">
				{if $cartset.active == 't'}
				<div class="userdefaultcartset">default cartset</div>
				{else}
					{if $cartset.permissions.0 == '1'}
				{templateLink id=$VIEWER.templateID _cartset=$cartset.id text="use in your digiplay profile" _cartset=$cartset.id _formName="dpsUserActCartsetForm" _moduleName="DPS"}
					{/if}
				{/if}
			</td>
		</tr>
{/foreach}
{if !$VIEWER.cartsets}
		<tr>
			<th colspan=5 class="stationTableName">
				no user cartsets exist
			</th>
		</tr>
{/if}
	</table>
<div class='statiosubtitle'>Create new cartwall</div>
<form name="dpsUserNewCartsetForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="formName" value="dpsUserNewCartsetForm" />
	<input type="hidden" name="moduleName" value="DPS" />
	<input type="hidden" name="templateID" value={$VIEWER.templateID} />
	{if $ERRORS.name}<div class='frame_musicboxerror'>{$ERRORS.name}</div>{/if}
	Name: <input type=text name='name' value=''><br>
	{if $ERRORS.desc}<div class='frame_musicboxerror'>{$ERRORS.desc}</div>{/if}
	Description: <input type=text name='desc' value=''><br>
	<input type=submit name='submit' value='Add new'>
</form>
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}