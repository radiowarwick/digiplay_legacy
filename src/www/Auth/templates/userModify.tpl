{include file="rfile:authtopframe.tpl" title="User Administration" type="user"}
<div class="bigTitle">User Management</div>
<hr />
	<form name="userSelForm" method="post" action="{$CONFIG.general.siteRoot}">
	<input type="hidden" name="templateID" value="{$VIEWER.templateID}">
	<div class="subTitle">Select User:</div>
	<p align="center">
	<div align="center">
		<select name="userToEdit" id="userToEdit" size="1">
			{foreach from=$VIEWER.users key="id" item="name"}
				{if $id == $DATA.userToEdit}
					<option value="{$id}" selected>{$name}</option>
				{else}
					<option value="{$id}">{$name}</option>
				{/if}
			{/foreach}
		</select>
		<input type="submit" name="submit" value="Edit">
		<input type="hidden" name="formName" value="userSelForm"><br />
		<input type="hidden" name="moduleName" value="Auth" />
	</form>
	</div>
	</p>
	<hr />
	{if $DATA.userToEdit}
	<div class='subTitle'>Details:</div>
	<table width="100%">
		{if $ERRORS}
		<tr valign="top">
			<td colspan="2">
				{include file="rfile:errorsList.tpl" errors=$ERRORS}
			</td>
		</tr>
		{/if}
		<tr valign="top">
			<td colspan="2">
				<table width="400px" border="0" cellspacing="0" cellpadding="5">
				{if $VIEWER.customFields}
				{foreach from=$VIEWER.customFields item="fieldInfo"}
					<tr valign="top">
						<td>{$fieldInfo.niceName}: </td>
						<td>
							<input type="text" name="{$fieldInfo.fieldName}" value="{$fieldInfo.value}" />
						</td>
					</tr>
				{/foreach}
				{/if}
					<tr valign="top"> 
						<td>Password: </td>
						<td>
							<input type="checkbox" name="changePassword" />Change password<br />
							<input type="text" name="password" />
						</td>
					</tr>
					<tr valign="top">
						<td colspan="2">
							<input type="submit" name="detailSubmit" value="Save Changes" />
						</td>
					</tr>
				</table>
				<table width="400px" border="0" cellspacing="0" cellpadding="5">
					<tr>
						<td>
						<form name="userDeleteForm" method="post" action="{$CONFIG.general.siteRoot}">
						<input type="hidden" name="userToEdit" value="{$DATA.userToEdit}" />
						<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
						<input type="hidden" name="formName" value="userDeleteForm" />
						<input type="submit" name="deleteUser" value="   Delete User   " />
						<input type="hidden" name="moduleName" value="Auth" />
						</form>
						</td>
					</tr>
				</table>
				<hr />
			</td>
		</tr>
		<tr valign="top"> 
			<td colspan="2">
			<table width="100%" border="0" cellspacing="0" cellpadding="5">
				<tr>
					<td width="60%" valign="top">
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
					<td width="40%" valign="top"><h3>Groups:</h3>
						<ul>
							{foreach from=$VIEWER.groupinfo key="groupid" item="group"}
								<li>
								{if $group.inGroup}
									<b>{$group.groupname}</b>
								{else}
									{$group.groupname}
								{/if}
									[
									{if $group.inGroup}
									+ {templateLink id=$VIEWER.templateID text="-" 
												_formName="userPermissionForm" 
												_moduleName="Auth" 
												_task="groupRemove" 
												_userToEdit=$DATA.userToEdit 
												_rguid=$groupid} 
									{else}
											{templateLink id=$VIEWER.templateID text="+" 
												_formName="userPermissionForm" 
												_moduleName="Auth" 
												_task="groupAdd" 
												_userToEdit=$DATA.userToEdit 
												_rguid=$groupid} -
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
	<div class='subTitle'>New User Details:</div>
	<table width="100%">
		{if $ERRORS}
		<tr valign="top">
			<td colspan="2">
				{include file="rfile:errorsList.tpl" errors=$ERRORS}
			</td>
		</tr>
		{/if}
		<tr valign="top">
			<td colspan="2">
			{if $DATA.newUserID}
				The user has been added. Click
				{templateLink name="userModify.tpl" text="here" _userToEdit=$DATA.newUserID}
				if you wish to modify their permissions
			{else}
				<form name="addUserDetailsForm" method="post" action="{$CONFIG.general.siteRoot}">
				<input type="hidden" name="templateID" value="{$VIEWER.templateID}" />
				<input type="hidden" name="formName" value="addUserDetailsForm" />
				<input type="hidden" name="moduleName" value="Auth" />
				<table width="400px" border="0" cellspacing="0" cellpadding="5">
				{if $VIEWER.customFields}
				{foreach from=$VIEWER.customFields item="fieldInfo"}
					<tr valign="top">
						<td>{$fieldInfo.niceName}: </td>
						<td>
							{if $VIEWER.formName == "detailsForm"}
							{assign var="name" value=$fieldInfo.fieldName}
							<input type="text" name="{$fieldInfo.fieldName}" value="{$DATA.$name}" />
							{else}
							<input type="text" name="{$fieldInfo.fieldName}" value="{$fieldInfo.value}" />
							{/if}
						</td>
					</tr>
				{/foreach}
				{/if}
					<tr valign="top"> 
						<td>Password: </td>
						<td>
							<input type="text" name="password" />
						</td>
					</tr>
					<tr valign="top">
						<td colspan="2" align="right">
							<input type="submit" name="detailSubmit" value="Add User" align="right" />
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
