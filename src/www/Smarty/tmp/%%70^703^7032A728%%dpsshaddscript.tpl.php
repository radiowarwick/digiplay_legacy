<?php /* Smarty version 2.6.14, created on 2007-01-05 14:26:00
         compiled from rfile:/var/www/DPS/templates/dpsshaddscript.tpl */ ?>
<html>
  <head>
    <title>Add Jingle</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
		<link rel="STYLESHEET" type="text/css" href="DPS/scripts/dhtmlxTree/css/dhtmlXTree.css">
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXCommon.js"></script>
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXTree.js"></script>
		<?php echo '
		<script language="javascript" type="text/javascript">
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
					document.getElementById(\'niceName\').value = tree.getItemText(id);
					document.getElementById(\'scriptID\').value = (String(id).substring(3,(String(id).length)));
				}
			}
		</script>
		'; ?>

  </head>
  <body>
    <?php if ($this->_tpl_vars['VIEWER']['error'] != ''): ?>
      <?php echo $this->_tpl_vars['VIEWER']['error']; ?>

    <?php else: ?>
    <div class='alignleft'>
    <div class='bigTitle'>Select Script</div>
		<div class='subTitle'>Showplan: <?php echo $this->_tpl_vars['VIEWER']['show']['name']; ?>
, Item: <?php echo $this->_tpl_vars['VIEWER']['item']['position']; ?>
 
    <hr>
    <div class=''>
      <form name="dpsUserScriptShow" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
      	<input type="hidden" name="formName" value="dpsUserScriptShow" />
      	<input type="hidden" name="moduleName" value="DPS" />
      	<input type="hidden" name="templateID" value="70" />
      	<input type="hidden" name="itemID" value="<?php echo $this->_tpl_vars['VIEWER']['item']['id']; ?>
" />
				<input type="hidden" id="scriptID" name="scriptID" value="<?php echo $this->_tpl_vars['VIEWER']['item']['audio']; ?>
" />
      	<input type="text" id="niceName" name="niceName" readonly value="<?php echo $this->_tpl_vars['VIEWER']['item']['scriptTitle']; ?>
" />
				<input type="Submit" name="Submit" value="Submit" />
      </form>
    </div>
		<hr>
		<div id="toc_tree" class="fileselect">
	  	<script>
				loadTree();
			</script>
			<noscript>
				A filebrowser will display here if you have javascript enabled
			</noscript>
		</div>
    <?php endif; ?>
  </body>
</html>