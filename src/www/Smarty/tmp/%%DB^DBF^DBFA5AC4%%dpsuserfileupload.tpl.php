<?php /* Smarty version 2.6.14, created on 2007-01-05 17:28:40
         compiled from rfile:/var/www/DPS/templates/dpsuserfileupload.tpl */ ?>
<html>
  <head>
    <title><?php echo $this->_tpl_vars['title']; ?>
</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
		<link rel="STYLESHEET" type="text/css" href="DPS/scripts/dhtmlxTree/css/dhtmlXTree.css">
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXCommon.js"></script>
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXTree.js"></script>	
  </head>
  <body>
	<?php if ($this->_tpl_vars['VIEWER']['permError']): ?>
		<div class='bigTitle'>Permission Error</div>
		<div class='subTitle'>You do not have permission to write to that folder</div>
	<?php else: ?>
		<div class='alignleft'>
			<div class='bigTitle'>Advanced Properties: <?php echo $this->_tpl_vars['VIEWER']['folder']['name']; ?>
</div>
			<form name="dpsUserUploadFileForm" enctype="multipart/form-data" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
    	  <input type="hidden" name="formName" value="dpsUserUploadFileForm" />
				<input type="hidden" name="moduleName" value="DPS" />
				<input type="hidden" name="templateID" value="70" />
				<input type="hidden" name="dirID" value="<?php echo $this->_tpl_vars['VIEWER']['folder']['id']; ?>
" />
				Name: <input type="text" name="name" value="" /><br />
				Type: <select name="type"><option value="jingle">Jingle</option><option value="advert">Advert</option></select><br />
				File: <input type="file" name="ufile" /><br />
				<input type="submit" value="Save" />
			</form>
		</div>
		<?php endif; ?>
	</body>
</html>