{include file="rfile:dpsstudiotopframe.tpl" title="RaW Digiplay Manager" studio="t" access_playlist=$VIEWER.access_playlist}

<div class='bigTitle'>Station Jingle Package</div>
<p>Package Name: {$VIEWER.jinglepkg.name}</p>
<p>Package Description: {$VIEWER.jinglepkg.description}</p>
<p>Package Enabled on Sue?: 
	{if $VIEWER.jinglepkg.enabled == 't'}
		Yes
	{else}
		No
	{/if}
</p>
</form>

<div class='subTitle'>Jingles in this package:</div><br />
	<table border=1 class='stationtable'>
	{foreach from=$VIEWER.jingles item=jingle}
		<tr>
			<th class="userTableName">
				{$jingle.title}
			</th>
			<td class="userTableOption">
				{templateLink id=18 _trackID=$jingle.id text="Preview"}
			</td>
		</tr>
	{/foreach}
	</table>
{include file="rfile:dpsstudiobottomframe.tpl" Admin=$VIEWER.Admin}
