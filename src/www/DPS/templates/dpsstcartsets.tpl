{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager"}
  <br>
  <br>
<div class='stationtitle'>Station Cartwall</div>

<div class='statioinfo1'>Available Cartsets for Station Cartwall</div>
<form name="dpsStationActCartsetForm" method="post" action="{$CONFIG.general.siteRoot}">
  <input type="hidden" name="formName" value="dpsStationActCartsetForm" />
  <input type="hidden" name="moduleName" value="DPS" />
  <input type="hidden" name="templateID" value="63" />
    <table border=1 class='statiotable'>
    <tr>
      <th width=120>
	Cartset
      </th>
      <th>
	Status
      </th>
      <th>
	Edit
      </th>
    </tr>
{foreach from=$VIEWER.cartsets item=cartset}
    <tr>
      <td>
	{$cartset.name}
      </td>
      <td>
      {if $cartset.active == 1}
	<input type='radio' checked="checked" value='{$cartset.id}' name='activeSCW'>
      {else}
	<input type='radio' value='{$cartset.id}' name='activeSCW'>
      {/if}
      </td>
      <td>
	{templateLink id="64" _cartsetID=$cartset.id text="Edit"}
      </td>
    </tr>
{/foreach}
  </table>
  <input type=submit value="Update" name=submit>
</form>
<div class='statiosubtitle'>New Cartset</div>
<form name="dpsNewStationCartsetForm" method="post" action="{$CONFIG.general.siteRoot}">
  <input type="hidden" name="formName" value="dpsNewStationCartsetForm" />
  <input type="hidden" name="moduleName" value="DPS" />
  <input type="hidden" name="templateID" value="63" />
  Name: <input type=text name='name' value=''><br>
  Description: <input type=text name='desc' value=''><br>
  <input type=submit name='submit' value='Add new'>
</form>
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
