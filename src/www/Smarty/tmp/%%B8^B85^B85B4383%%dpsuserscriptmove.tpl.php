<?php /* Smarty version 2.6.14, created on 2007-01-05 15:24:16
         compiled from rfile:/var/www/DPS/templates/dpsuserscriptmove.tpl */ ?>
<html>
  <head>
    <title><?php echo $this->_tpl_vars['title']; ?>
</title>
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
				if ((String(id).substring(0,3)) == "dir") {
					document.getElementById(\'newparent\').value = (String(id).substring(3,(String(id).length)));
				}
			}
		</script>
		'; ?>

  </head>
  <body>
	<?php if ($this->_tpl_vars['VIEWER']['permError']): ?>
		<div class='bigTitle'>Permission Error</div>
		<div class='subTitle'>You do not have permission to move that item</div>
	<?php else: ?>
		<div class='alignleft'>
			<div class='bigTitle'>Advanced Properties: <?php echo $this->_tpl_vars['VIEWER']['script']['name']; ?>
</div>
			<form name="dpsUserMoveScriptForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
    	  <input type="hidden" name="formName" value="dpsUserMoveScriptForm" />
				<input type="hidden" name="moduleName" value="DPS" />
				<input type="hidden" name="templateID" value="70" />
				<input type="hidden" name="scriptID" value="<?php echo $this->_tpl_vars['VIEWER']['script']['id']; ?>
" />
				<input type="hidden" id="newparent" name="newParent" value="<?php echo $this->_tpl_vars['VIEWER']['folder']['parent']; ?>
" />
				<?php if ($this->_tpl_vars['VIEWER']['own'] == 't'): ?>
<!--				<div class='subTitle'>Select the items permissions from the options below</div>
				Private : <input type="radio" name="perm" value="private" checked/>
				Public read : <input type="radio" name="perm" value="aread" />
				Public write : <input type="radio" name="perm" value="awrite" />
-->
			<?php endif; ?>
				<div class='subTitle'>If you want to move this item please select a new subfolder</div>
				<input type="submit" value="Save" />
				<?php if ($this->_tpl_vars['DATA']['error'] == 'perm'): ?>
				<div class='error'>You do not have permission to move the item to the selected location</div>
				<?php endif; ?>
	  		<div id="toc_tree" class="filebrowser">
					<script>
						loadTree();
					</script>
					<noscript>
						A filebrowser will display here if you have javascript enabled
					</noscript>
				</div>
			</form>
		</div>
		<?php endif; ?>
	</body>
</html>