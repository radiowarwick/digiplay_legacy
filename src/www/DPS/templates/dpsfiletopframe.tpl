<html>
	<head>
		<title>{$title}</title>
		<link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
		<link rel="STYLESHEET" type="text/css" href="DPS/scripts/dhtmlxTree/css/dhtmlXTree.css">
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXCommon.js"></script>
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXTree.js"></script>	
		<script src="DPS/scripts/dpsfile.js"></script>
		{literal}
		<script language="javascript" type="text/javascript">
			var tree;
			var browserType;
			var val=0;
			var win=null;
			if (document.layers) {browserType = "nn4"}
			if (document.all) {browserType = "ie"}
			if (window.navigator.userAgent.toLowerCase().match("gecko")) {browserType= "gecko"}
			
			function restart() {
				if (win.opener && !win.opener.closed) {
					win.close()
					window.location = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID=86"
				}
			}
			
			function dirChange() {
				document.getElementById('dirCreate').href = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID={/literal}{$VIEWER.templateID}{literal}&formName=dpsdiradd&moduleName=DPS&rootdir=" + String(val).substring(3,String(val).length) + "&dirtext=" + document.getElementById('dirctext').value;
				document.getElementById('dirRename').href = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID=86&formName=dpsdirrename&moduleName=DPS&rootdir=" + String(val).substring(3,String(val).length) + "&dirtext=" + document.getElementById('dirrtext').value;
			}

			function handleKeyPress(e,id) {
				dirChange();
				var key=e.keyCode || e.which;
				if (key==13){
					document.location=document.getElementById(id).href
				}
			}

			function loadTree(){
				tree=new dhtmlXTreeObject(document.getElementById('toc_tree'),"100%","100%",0);
				tree.setXMLAutoLoading("{/literal}{$CONFIG.general.toolkitRootURL}{literal}?templateID=65&treeType={/literal}{$VIEWER.treeType}{literal}");;
				tree.setImagePath("DPS/scripts/dhtmlxTree/imgs/");
				tree.setOnClickHandler(doOnClick);
				tree.enableTreeLines(false);
				tree.loadXML("{/literal}{$CONFIG.general.toolkitRootURL}{literal}?templateID=65&treeType={/literal}{$VIEWER.treeType}{literal}&id=dir1");
			}

			function moveCartset() {
				window.name = "dpsmain";
				var left=0;
				var top=20;
				var title = "MoveFile";
				var Nurl = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID=97&cartsetID=" + String(val).substring(3,String(val).length);
				var settings="width=800,height=600,top=20,left=0,scrollbars=yes,location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no";
				win=window.open(Nurl,title,settings);
				win.focus();
			}

			function moveScript() {
				window.name = "dpsmain";
				var left=0;
				var top=20;
				var title = "MoveFile";
				var Nurl = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID=98&scriptID=" + String(val).substring(3,String(val).length);
				var settings="width=800,height=600,top=20,left=0,scrollbars=yes,location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no";
				win=window.open(Nurl,title,settings);
				win.focus();
			}
			function moveAudio() {
				window.name = "dpsmain";
				var left=0;
				var top=20;
				var title = "MoveFile";
				var Nurl = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID=96&audioID=" + String(val).substring(3,String(val).length);
				var settings="width=800,height=600,top=20,left=0,scrollbars=yes,location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no";
				win=window.open(Nurl,title,settings);
				win.focus();
			}

			function moveDir() {
				window.name = "dpsmain"
				var left=0
				var top=20
				var title = "MoveDirectory"
				var Nurl = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID=88&rootdir=" + String(val).substring(3,String(val).length)
				var settings="width=800,height=600,top=20,left=0,scrollbars=yes,location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no"
				win = window.open(Nurl,title,settings)
				win.focus()
			}

			function uploadDir()
			{
				window.name = "dpsmain";
				var left=0;
				var top=20;
				var title = "UploadFile";
				var Nurl = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID=99&rootdir=" + String(val).substring(3,String(val).length);
				var settings="width=800,height=600,top=20,left=0,scrollbars=yes,location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no";
				win=window.open(Nurl,title,settings);
				win.focus();
			}

			function doOnClick(id){
				if (browserType == "gecko" ) {
					document.folderLayer = eval('document.getElementById(\'folderBar\')');
					document.jingleLayer = eval('document.getElementById(\'jingleBar\')');
					document.cartsetLayer = eval('document.getElementById(\'cartsetBar\')');
					document.scriptLayer = eval('document.getElementById(\'scriptBar\')');
				} else if (browserType == "ie") {
					document.folderLayer = eval('document.all[\'folderBar\']');
					document.jingleLayer = eval('document.all[\'jingleBar\']');
					document.cartsetLayer = eval('document.all[\'cartsetBar\']');
					document.scriptLayer = eval('document.getElementById(\'scriptBar\')');
				} else {
					document.folderLayer = eval('document.layers[\'folderBar\']');
					document.jingleLayer = eval('document.layers[\'jingleBar\']');
					document.cartsetLayer = eval('document.layers[\'cartsetBar\']');
					document.scriptLayer = eval('document.getElementById(\'scriptBar\')');
				}
				val = id;
				if((String(id).substring(0,3)) == "jgl") {
					document.folderLayer.style.display = "none";
					document.cartsetLayer.style.display = "none";
					document.scriptLayer.style.display = "none";
					document.jingleLayer.style.display = "block";
					//Link to jingle editing
					document.getElementById('jingleEdit').href = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID=87&trackID=" + String(id).substring(3,String(id).length);
					//Delete Jingle Model
					document.getElementById('jingleDelete').href = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID=86&formName=dpsUserDelAudio&moduleName=DPS&audioID=" + String(val).substring(3,String(val).length);
					//Open Move window
					//javascript:moveAudio();
				} else if ((String(id).substring(0,3)) == "dir") {
					document.folderLayer.style.display = "block";
					document.cartsetLayer.style.display = "none";
					document.scriptLayer.style.display = "none";
					document.jingleLayer.style.display = "none";
					nodePerm = tree.getUserData(id,"perm");
					if (tree.getParentId(id) == 0) {
						pNodePerm = "00000000";
					} else {
						pNodePerm = tree.getUserData(tree.getParentId(id),"perm");
					}

					doDir(nodePerm,pNodePerm);
					document.getElementById('dirrtext').value = tree.getItemText(id);
					document.getElementById('dirRename').href = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID=86&formName=dpsdirrename&moduleName=DPS&rootdir=" + String(val).substring(3,String(val).length);
					document.getElementById('dirDel').href = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID=86&formName=dpsdirdel&moduleName=DPS&rootdir=" + String(val).substring(3,String(val).length);
				} else if ((String(id).substring(0,3)) == "crt") {
					document.folderLayer.style.display = "none";
					document.cartsetLayer.style.display = "none";
					document.scriptLayer.style.display = "block";
					document.jingleLayer.style.display = "none";
					//edit a cartset
					document.getElementById('cartsetEdit').href = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID=68&cartset=" + String(id).substring(3,String(id).length);
					//delete a cartset
					document.getElementById('cartsetDel').href = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID=86&formName=dpsUserCartsetDelForm&moduleName=DPS&cartset=" + String(val).substring(3,String(val).length);
					//move a cartset
				} else if ((String(id).substring(0,3)) == "scr") {
					document.folderLayer.style.display = "none";
					document.cartsetLayer.style.display = "none";
					document.scriptLayer.style.display = "block";
					document.jingleLayer.style.display = "none";
					//Edit link
					document.getElementById('scriptEdit').href = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID=94&scriptID=" + String(id).substring(3,String(id).length);
					//Delete Script Model
					document.getElementById('scriptDel').href = "{/literal}{$CONFIG.general.siteRoot}{literal}?templateID=86&formName=dpsUserDelScript&moduleName=DPS&scriptID=" + String(val).substring(3,String(val).length);
					//Open a Move window
				}
			}
		</script>
		{/literal}
	</head>
	<body>
		<div class="centreContainer">
			<div class="frame_bottom">
				<div class="frame_showsidebar">
					<img class="frame_sidebarlogo" src="DPS/images/homenavshow.png" alt="Studio">
					<div class="frame_sidebarmusic">{templateLink id="31" text="Music Library"}</div>
					<div class="frame_sidebarsue">{templateLink id="32" text="Sue Stamp"}</div>
					<div class="frame_sidebarstudio">{templateLink id="33" text="Studio Cartwalls"}</div>
					<div class="frame_studiosidebarlinks">
						{templateLink id="34" text="Information"}<br />
						{templateLink id="54" text="My Showplans"}<br />
						{templateLink id="44" text="My Scripts"}<br />
						{templateLink id="51" text="My Files"}
					</div>
				</div>
				<div class="frame_rightside">
					<div class="frame_content">
