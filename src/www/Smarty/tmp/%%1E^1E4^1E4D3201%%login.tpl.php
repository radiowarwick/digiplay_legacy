<?php /* Smarty version 2.6.14, created on 2006-07-04 19:41:25
         compiled from rfile:/var/www/toolkit/tkfecommon/templates/login.tpl */ ?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Please Login</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>
<form name="loginForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
<!--<form name="loginForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>
">-->
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
">here</a>
<?php else: ?>
  <?php if ($this->_tpl_vars['DATA']['fwdtid']): ?>
  <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['DATA']['fwdtid']; ?>
" />
  <?php endif; ?>
  
  <?php if ($this->_tpl_vars['ERRORS']['permission'] && $this->_tpl_vars['AUTH']['user'] == $this->_tpl_vars['CONFIG']['Auth']['anonuser']): ?>
    You do not seem to have permission to access that page. Logging in may 
    resolve this problem:
  <?php endif; ?>
  
  <input type="hidden" name="formName" value="loginForm" />
  <input type="hidden" name="moduleName" value="Auth" />
  <input type="hidden" name="templateID" value="<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
" />
  <table width="300" border="0" align="center" cellpadding="5" cellspacing="0">
    <tr> 
      <td colspan="2"><div align="center">Login:</div></td>
    </tr>
    <tr> 
      <td>Username:</td>
      <td><input name="authUser" type="text" id="authUser" value="<?php echo $this->_tpl_vars['DATA']['authUser']; ?>
"></td>
    </tr>
    <tr> 
      <td>Password: <?php echo $this->_tpl_vars['ERRORS']['authPassword']; ?>
</td>
      <td><input name="authPassword" type="password" id="authPassword"></td>
    </tr>
    <tr>
      <td colspan="2"><div align="right">
          <input type="submit" name="Submit" value="Login">
        </div></td>
    </tr>
  </table>
<?php endif; ?>
</form>
</body>
</html>