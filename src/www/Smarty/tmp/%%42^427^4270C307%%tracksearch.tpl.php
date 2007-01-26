<?php /* Smarty version 2.6.14, created on 2006-06-16 00:24:32
         compiled from rfile:/var/www/toolkit/DPS/templates/tracksearch.tpl */ ?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Please Search for a track</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>
<form name="TrackSearchForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
  <input type="hidden" name="formName" value="TrackSearcgForm" />
  <input type="hidden" name="moduleName" value="DPS" />
  <input type="hidden" name="templateID" value="45" />
  <table width="300" border="0" align="center" cellpadding="5" cellspacing="0">
    <tr> 
      <td colspan="2"><div align="center">Search:</div></td>
    </tr>
    <tr> 
      <td>SearchField:</td>
      <td>
        <input name="DPSSearch" type="text" id="DPSSearch" value="<?php echo $this->_tpl_vars['DATA']['DPSSearch']; ?>
">
      </td>
    </tr>
    <tr>
      <td colspan="2">
        <div align="center">
	  Both:<input type='radio' name='DPSSearchType' value='Both' checked>
	  Title:<input type='radio' name='DPSSearchType' value='Title'>
	  Artist:<input type='radio' name='DPSSearchType' value='Artist'>
	</div>
      </td>
    </tr>
    <tr>
      <td colspan="2">
        <div align="right">
          <input type="submit" name="Submit" value="Search">
        </div>
      </td>
    </tr>
  </table>
</form>
</body>
</html>