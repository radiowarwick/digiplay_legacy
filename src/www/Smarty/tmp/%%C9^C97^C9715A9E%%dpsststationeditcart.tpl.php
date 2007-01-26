<?php /* Smarty version 2.6.14, created on 2007-01-04 19:09:02
         compiled from rfile:/var/www/DPS/templates/dpsststationeditcart.tpl */ ?>
<html>
  <head>
    <title>Edit a Cart</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXCommon.js"></script>
		<link rel="STYLESHEET" type="text/css" href="DPS/scripts/dhtmlxTree/css/dhtmlXTree.css">
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXTree.js"></script>
		<?php echo '
   	<script language="javascript">
			var tree;
			var xml1="';  echo $this->_tpl_vars['VIEWER']['treeData'];  echo '";
			var browserType;

			if (document.layers) {browserType = "nn4"}
			if (document.all) {browserType = "ie"}
			if (window.navigator.userAgent.toLowerCase().match("gecko")) {browserType= "gecko"}

			function loadTree(){
				tree=new dhtmlXTreeObject(document.getElementById(\'toc_tree\'),"100%","100%",0);
				tree.setImagePath("DPS/scripts/dhtmlxTree/imgs/");
				tree.setOnClickHandler(doOnClick);
				tree.enableTreeLines(false);
				tree.loadXMLString(xml1);
			}

			function doOnClick(id){
				if ((String(id).substring(0,3)) != "dir") {
					//document.getElementById(\'niceName\').value = tree.getItemText(id);
					document.getElementById(\'audioID\').value = (String(id).substring(3,(String(id).length)));
				}
			}
    </script>
    '; ?>
  
  </head>
  <body>
    <div class='alignleft'>
	    <div class='bigTitle'>Editing cart <?php echo $this->_tpl_vars['VIEWER']['cartPos']; ?>
</div>
  	  <hr>
    	<?php if ($this->_tpl_vars['VIEWER']['permError'] == 't'): ?>
      You do not have permission to edit this cart.
    	<?php else: ?>
    	<div class='EditCartDetails'>
      	<?php if ($this->_tpl_vars['VIEWER']['new'] != 't'): ?>
	      <form name="dpsStationCartEditForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
	  	    <input type="hidden" name="formName" value="dpsStationCartEditForm" />
  	  	  <input type="hidden" name="moduleName" value="DPS" />
    	  	<input type="hidden" name="templateID" value="70" />
		      <input type="hidden" name="cartID" value="<?php echo $this->_tpl_vars['VIEWER']['cartInfo']['id']; ?>
" />
	      <?php else: ?>
	      <form name="dpsStationCartAddForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
		      <input type="hidden" name="formName" value="dpsStationCartAddForm" />
		      <input type="hidden" name="moduleName" value="DPS" />
  		    <input type="hidden" name="templateID" value="70" />
    		  <input type="hidden" name="cartPos" value="<?php echo $this->_tpl_vars['VIEWER']['cartPos']; ?>
" />
      		<input type="hidden" name="cartwallID" value="<?php echo $this->_tpl_vars['VIEWER']['cartwallID']; ?>
" />
	      <?php endif; ?>
		      <div class='EditCartDetail'>Text:</div>
		      <?php if ($this->_tpl_vars['DATA']['error'] == 'text'): ?><div class='frame_musicboxerror'>Invalid field entry</div><?php endif; ?>
		      <div class='EditCartValue'><textarea name="text"><?php echo $this->_tpl_vars['VIEWER']['cartInfo']['text']; ?>
</textarea></div>
		      <input type="hidden" name="audioID" id="audioID" value="<?php echo $this->_tpl_vars['VIEWER']['cartInfo']['audioid']; ?>
" />
	      	<div class='EditCartDetail'>Style:</div>
	    	  <?php if ($this->_tpl_vars['ERRORS']['style']): ?><div class='frame_musicboxerror'><?php echo $this->_tpl_vars['ERRORS']['style']; ?>
</div><?php endif; ?>
  		    <?php if ($this->_tpl_vars['DATA']['error'] == 'style'): ?><div class='frame_musicboxerror'>Invalid style selected</div><?php endif; ?>
	  	    <div class='EditCartValue'>
						<select name=style>
							<?php $_from = $this->_tpl_vars['VIEWER']['styles']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['style']):
?>
						  <?php if ($this->_tpl_vars['style']['id'] == $this->_tpl_vars['VIEWER']['cartInfo']['styleid']): ?>
					  	<option value=<?php echo $this->_tpl_vars['style']['id']; ?>
 selected><?php echo $this->_tpl_vars['style']['name']; ?>
</option>
						  <?php else: ?>
						  <option value=<?php echo $this->_tpl_vars['style']['id']; ?>
><?php echo $this->_tpl_vars['style']['name']; ?>
</option>
						  <?php endif; ?>
							<?php endforeach; endif; unset($_from); ?>
						</select>
	    	  </div>
  		    <div class='EditCartDetailSub'><input type="Submit" name="Submit" value="Submit"></div>
	      </form>
    	  <div class='EditCartDetailSub'>
  	    	<?php if ($this->_tpl_vars['VIEWER']['new'] != 't'): ?>
	      	<form name="dpsStationCartDelForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
      			<input type="hidden" name="formName" value="dpsStationCartDelForm" />
      			<input type="hidden" name="moduleName" value="DPS" />
    	  		<input type="hidden" name="templateID" value="70" />
  	    		<input type="hidden" name="cartID" value="<?php echo $this->_tpl_vars['VIEWER']['cartInfo']['id']; ?>
" />
	      		<input type="Submit" name="Submit" value="Clear">
      		</form>
      		<?php endif; ?>
      	</div>
    	</div>
    	<div class='EditCartFile'>
    		<?php if ($this->_tpl_vars['DATA']['error'] == 'audioID'): ?><div class='frame_musicboxerror'>Please select a jingle or advert</div><?php endif; ?>
				<div id="toc_tree" class="fileselect">
	  			<script>
						loadTree();
					</script>
					<noscript>
						A filebrowser will display here if you have javascript enabled
					</noscript>
				</div>
			</div>
    	<br style="clear: both;">
			<?php endif; ?>
    </div>
  </body>
</html>