<?php /* Smarty version 2.6.14, created on 2006-06-16 01:45:09
         compiled from rfile:/var/www/toolkit/DPS/templates/libsearchresults.tpl */ ?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>Lib search results</title>
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
      <td colspan="3"><div align="center">Search:</div></td>
    </tr>
    <tr>
      <td>SearchField:</td>
      <td>
        <input name="DPSSearch" type="text" id="DPSSearch" value="<?php echo $this->_tpl_vars['DATA']['DPSSearch']; ?>
">
      </td>
      <td>
        <input type="submit" name="Submit" value="Search">
      </td>
    </tr>
    <tr>
      <td colspan="3">
        <div align="center">
          <?php if ($this->_tpl_vars['DATA']['DPSSearchType'] == 'Both'): ?>
	    Both:<input type='radio' name='DPSSearchType' value='Both' checked>
	    Title:<input type='radio' name='DPSSearchType' value='Title'>
	    Artist:<input type='radio' name='DPSSearchType' value='Artist'>
	  <?php elseif ($this->_tpl_vars['DATA']['DPSSearchType'] == 'Title'): ?>
	    Both:<input type='radio' name='DPSSearchType' value='Both'>
	    Title:<input type='radio' name='DPSSearchType' value='Title' checked>
	    Artist:<input type='radio' name='DPSSearchType' value='Artist'>
	  <?php elseif ($this->_tpl_vars['DATA']['DPSSearchType'] == 'Artist'): ?>
	    Both:<input type='radio' name='DPSSearchType' value='Both'>
	    Title:<input type='radio' name='DPSSearchType' value='Title'>
	    Artist:<input type='radio' name='DPSSearchType' value='Artist' checked>
	  <?php endif; ?>
        </div>
      </td>
    </tr>
  </table>
</form>
<?php echo $this->_tpl_vars['VIEWER']['linkString']; ?>

<table>
  <tr>
  <?php $_from = $this->_tpl_vars['VIEWER']['title']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['field']):
?>
    <th><?php echo $this->_tpl_vars['field']; ?>
</th>
  <?php endforeach; endif; unset($_from); ?>
  </tr>
<?php $_from = $this->_tpl_vars['VIEWER']['searchList']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['result']):
?>
  <tr>
  <?php $_from = $this->_tpl_vars['result']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['field']):
?>
    <td><?php echo $this->_tpl_vars['field']; ?>
</td>
  <?php endforeach; endif; unset($_from); ?>
  </tr>
<?php endforeach; endif; unset($_from); ?>
</table>
</body>
</html>