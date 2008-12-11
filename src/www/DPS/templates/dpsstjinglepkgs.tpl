{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager" studio="t" access_playlist=$VIEWER.access_playlist}
<div class='bigTitle'>Station Jingle Packages</div>
	{if $VIEWER.jinglepkgs}
	<div class='subTitle'>Currently there are following Jingle Packages available:</div>
	{/if}
	<table border=1 class='stationtable'>
	{foreach from=$VIEWER.jinglepkgs item=jinglepkg}
		<tr>
			<th class="userTableName" style="border-right:1px black solid;">
				{if $jinglepkg.name == ''}unnamed{else}{$jinglepkg.name}{/if}
			</th>
			<td class="userTableOption" rowspan="2">
				{templateLink id="72" _jinglepkg=$jinglepkg.id text="view"}
			</td>
			<td class="userTableOption" rowspan="2">
				{templateLink id="70" _jinglepkg=$jinglepkg.id text="edit"}
			</td>
			<td class="userTableDetail" rowspan="2">
				{if $jinglepkg.enabled == 't'}
				<div class="userdefaultawset">Enabled on Sue</div>
				{else}
				Not Enabled on Sue
				{/if}
			</td>
		</tr>
		<tr>
			<td class="userTableDetail" style="border-left:0px; border-right:1px black solid;">
				{$jinglepkg.description}				
			</td>
		</tr>
	{/foreach}
	</table>

{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
