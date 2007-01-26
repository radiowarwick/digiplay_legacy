<?php /* Smarty version 2.6.14, created on 2006-09-29 13:08:41
         compiled from rfile:/var/www/toolkit/DPS/templates/dpslogin.tpl */ ?>
<html>

<head>
  <title>RaW DPS website login</title>
  <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
</head>

<body>
<br><br><br><br>
<?php if ($this->_tpl_vars['ERRORS']['permission'] && $this->_tpl_vars['AUTH']['user'] != $this->_tpl_vars['CONFIG']['Auth']['anonuser']): ?>
    <p>
      The following error occured while processing your request:
    </p>
    <ul>
      <li>
        <?php echo $this->_tpl_vars['ERRORS']['permission']; ?>

      </li>
    </ul>
    If you need to access the logon page you may do so <a href="?templateid=5&fwdtid=<?php echo $this->_tpl_vars['fieldData']['templateID']; ?>
">here</a>.
<?php else: ?>
  <div class="login_container">
    <div class="login_header"><img src="DPS/images/dps_header.JPG" alt="RaW DPS Manager" width="294" height="30" /></div>
    <div class="login_title">Login</div>
    <div class="login_form">
      <form name="dpsloginForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
      <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['DATA']['fwdtid']; ?>
" />
      <input type="hidden" name="formName" value="dpsloginForm" />
      <input type="hidden" name="moduleName" value="DPS" />
      
      <div class="login_passwordError"><?php echo $this->_tpl_vars['ERRORS']['authPassword']; ?>
 Don't use this site at the moment, major development in progress. </div>
      Username: <input type="text" name="authUser" id="authUser" value="<?php echo $this->_tpl_vars['DATA']['authUser']; ?>
"/><br>
      Password: <input type="password" name="authPassword" id="authPassword"/><br>
      <input type="submit" value="Login" name="Submit"/>
      </form>
    </div>
  </div>
  <div class="login_container_footer">
  <div class="login_container_footer_left">
    Copyright &#169 RaW 1251AM, 2006
  </div>
    <a href="http://www.radio.warwick.ac.uk"><img src="DPS/images/homeexit.png" alt="Exit" border="0" /></a>
    <img src="DPS/images/homehelp.png" alt="Help" border="0" />
  </div>
<?php endif; ?>
</body>

</html>