<html>
	<head>
		<title>RaW DPS website login</title>
		<link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
	</head>
	<body>
		<br><br><br><br>
		{if $ERRORS.permission && $AUTH.user != $CONFIG.Auth.anonuser}
		<p>
			The following error occured while processing your request:
		</p>
		<ul>
			<li>
				{$ERRORS.permission}
			</li>
		</ul>
		If you need to access the logon page you may do so <a href="?templateid=11&fwdtid={$fieldData.templateID}">here</a>.
		{else}
		<div class="login_container">
			<div class="login_header"><img src="DPS/images/dps_header.JPG" alt="RaW DPS Manager" width="294" height="30" /></div>
			<div class="login_title">Login</div>
			<div class="login_form">
				<form name="dpsloginForm" method="post" action="{$CONFIG.general.siteRoot}">
				<input type="hidden" name="templateID" value="{$DATA.fwdtid}" />
				<input type="hidden" name="formName" value="dpsloginForm" />
				<input type="hidden" name="moduleName" value="DPS" />
				
				<div class="login_passwordError">DO NOT USE THIS SITE{$ERRORS.authPassword}</div>
				Username: <input type="text" name="authUser" id="authUser" value="{$DATA.authUser}"/><br>
				Password: <input type="password" name="authPassword" id="authPassword"/><br>
				<input type="submit" value="Login" name="Submit"/>
				</form>
			</div>
		</div>
			<div class="login_container_footer">
				<div class="login_container_footer_left">
					Copyright &#169 RaW 1251AM, 2006
				</div>
				<div class="login_container_footer_right">
					<a href="http://www.radio.warwick.ac.uk"><img src="DPS/images/homeexit.png" alt="Exit"></a>
				</div>
				<div class="login_container_footer_right">
					{templateLink id="59" text="<img src=\"DPS/images/homehelp.png\" alt=\"Help\">" alt="Help"}
				</div>
			</div>
		{/if}
	</body>
</html>
