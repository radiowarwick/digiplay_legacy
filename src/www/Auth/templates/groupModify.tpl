{include file="rfile:authtopframe.tpl" title="Group Administration"}
	<form name="groupSelForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="templateID" value="{$DATA.templateID}">
	<p align="center"><span class="label">Select Group:</span><br />
	<select name="groupToEdit" id="groupToEdit" size="1">
	{foreach from=$VIEWER.groups key="id" item="name"}
		{if $id == $DATA.groupToEdit}
		<option value="{$id}" selected>{$name}</option>
		{else}
		<option value="{$id}">{$name}</option>
		{/if}
	{/foreach}
	</select>
	<input type="submit" name="submit" value="Edit">
	<input type="hidden" name="formName" value="groupSelForm">
	<input type="hidden" name="moduleName" value="Auth">
	</form>
	</p>
	<hr />
	{if $DATA.groupToEdit}
	<table width="100%" border="0" cellspacing="0" cellpadding="5">
		{if $ERRORS}
		<tr valign="top">
			<td colspan="2">
				{include file="rfile:errorsList.tpl" errors=$ERRORS}
			</td>
		</tr>
		{/if}
		<tr valign="top">
			<td colspan="2">
			{if $VIEWER.customFields}
				<h2>Details:</h2>
				<form name="groupDetailsForm" method="post" action="{$CONFIG.general.siteRoot}">
				<input type="hidden" name="groupToEdit" value="{$DATA.groupToEdit}" />
				<input type="hidden" name="templateID" value="{$DATA.templateID}" />
				<input type="hidden" name="formName" value="groupDetailsForm" />
				<input type="hidden" name="moduleName" value="Auth">
				<table width="400px" border="0" cellspacing="0" cellpadding="5">
				{foreach from=$VIEWER.customFields item="fieldInfo"}
					<tr valign="top">
						<td>{$fieldInfo.niceName}: </td>
						<td>
							<input type="text" name="{$fieldInfo.fieldName}" value="{$fieldInfo.value}" />
						</td>
					</tr>
				{/foreach}
					<tr valign="top">
						<td colspan="2">
							<input type="submit" name="detailSubmit" value="Save Changes" />
						</td>
					</tr>
				</table>
				</form>
				<table width="400px" border="0" cellspacing="0" cellpadding="5">
					<tr>
						<td>
							<form name="groupDeleteForm" method="post" action="{$CONFIG.general.siteRoot}">
							<input type="hidden" name="groupToEdit" value="{$DATA.groupToEdit}" />
							<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
							<input type="hidden" name="formName" value="groupDeleteForm" />
							<input type="hidden" name="moduleName" value="Auth">
							<input type="submit" name="deleteGroup" value="  Delete Group  " />
							</form>
						</td>
					</tr>
				</table>
				<hr />
			{/if}
			</td>
		</tr>
		<tr valign="top"> 
			<td colspan="2">
				<table width="100%" border="0" cellspacing="0" cellpadding="5">
					<tr>
						<td width="70%" valign="top">
							<h3>Realms:</h3>
							<div id="toc_tree" >
								<script>
									loadTree();
								</script>
								<noscript>
									A filebrowser will display here if you have javascript enabled
								</noscript>
							</div>
						</td>
						<td width="30%" valign="top"><h3>Users:</h3>
							<ul>
								{foreach from=$VIEWER.userinfo key="userid" item="user"}
									{if $user.inGroup}
										<b>{$user.username}</b>
									{else}
										{$user.username}
									{/if}
									[
									{if $user.inGroup}
									+ {templateLink id=$VIEWER.templateID text="-" 
										_formName="groupRealmForm" 
										_moduleName="Auth" 
										_task="userRemove" 
										_groupToEdit=$DATA.groupToEdit 
										_rguid=$userid}
									{else}
									{templateLink id=$VIEWER.templateID text="+" 
										_formName="groupRealmForm" 
										_moduleName="Auth" 
										_task="userAdd" 
										_groupToEdit=$DATA.groupToEdit 
										_rguid=$userid} -
									{/if}
									]
									</li>
								{/foreach}
							</ul>
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
	</form>
{else}
	<table width="100%" border="0" cellspacing="0" cellpadding="5">
		{if $ERRORS}
		<tr valign="top">
			<td colspan="2">
				{include file="rfile:errorsList.tpl" errors=$ERRORS}
			</td>
		</tr>
		{/if}
		<tr valign="top">
			{if $DATA.newGroupID}
				The group has been added. Click
				{templateLink name="groupModify.tpl" text="here" _groupToEdit=$DATA.newGroupID}
				if you wish to modify their permissions
			{else}
			<td colspan="2">
				<h2>New Group Details:</h2>
				<form name="addGroupForm" method="post" action="{$CONFIG.general.siteRoot}">
				<input type="hidden" name="templateID" value="{$DATA.templateID}" />
				<input type="hidden" name="formName" value="addGroupForm" />
				<input type="hidden" name="moduleName" value="Auth" />
				<table width="400px" border="0" cellspacing="0" cellpadding="5">
				{foreach from=$VIEWER.customFields item="fieldInfo"}
					<tr valign="top">
						<td>{$fieldInfo.niceName}: </td>
						<td>
							<input type="text" name="{$fieldInfo.fieldName}" value="{$fieldInfo.value}" />
						</td>
					</tr>
				{/foreach}
					<tr valign="top">
						<td colspan="2" align="right">
							<input type="submit" name="detailSubmit" value="Add Group" align="right" />
						</td>
					</tr>
				</table>
				</form>
				{/if}
				<hr />
			</td>
		</tr>
	</table>
{/if}
{include file="rfile:authbottomframe.tpl"}