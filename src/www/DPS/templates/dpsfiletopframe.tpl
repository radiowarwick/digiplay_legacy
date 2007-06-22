<html>
	<head>
		<title>{$title}</title>
		<link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
		<link rel="STYLESHEET" type="text/css" href="DPS/scripts/dhtmlxTree/css/dhtmlXTree.css">
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXCommon.js"></script>
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXTree.js"></script>
		{literal}
		<script language="javascript" type="text/javascript">
			var templateID={/literal}{$VIEWER.templateID}{literal};
			var siteRoot="{/literal}{$CONFIG.general.siteRoot}{literal}";
			var treeType="{/literal}{$VIEWER.treeType}{literal}";
			var tree;
			var browserType;
			var currentVal=0;
			var win=null;
			//Check browser type
			if (document.layers) {
				browserType = "nn4"
			}
			if (document.all) {
				browserType = "ie"
			}
			if (window.navigator.userAgent.toLowerCase().match("gecko")) {
				browserType= "gecko"
			}
			
			//reopens the current window to refresh content
			function restart() {
				if (win.opener && !win.opener.closed) {
					win.close()
					window.location = siteRoot + "?" + "templateID=" + templateID;
				}
			}
			
			//updates links when text boxes on the dir bar are changed
			function dirChange() {
				var hrefstr = siteRoot + "?" +
					"templateID=" + templateID + "&" +
					"formName=dpsdiradd&moduleName=DPS&" +
					"&rootdir=" + String(currentVal).substring(3,String(currentVal).length) + "&" +
					"dirtext=" + document.getElementById('dirctext').value;
				document.getElementById('dirCreate').href = hrefstr;
			}
			
			//Capture enter events on text boxes and execute the connected link
			function handleKeyPress(e,id) {
				dirChange();
				var key=e.keyCode || e.which;
				if (key==13){
					document.location=document.getElementById(id).href
				}
			}
			//Loads the needed currentValues into the tree structure
			function loadTree(){
				var hrefstr = siteRoot + "?" +
					"templateID=65&treeType=" + treeType;
				tree=new dhtmlXTreeObject(document.getElementById('toc_tree'),"100%","100%",0);
				tree.setXMLAutoLoading(hrefstr);
				tree.setImagePath("DPS/scripts/dhtmlxTree/imgs/");
				tree.setOnClickHandler(doOnClick);
				tree.enableTreeLines(false);
				tree.loadXML(hrefstr + "&id=dir1");
			}
			
			//Open a window to move a cartset
			function moveCartset() {
				window.name = "dpsmain";
				var left=0;
				var top=20;
				var title = "MoveFile";
				var Nurl = siteRoot + "?" +
					"templateID=48&cartsetID=" + String(currentVal).substring(3,String(currentVal).length);
				var settings="width=800,height=600,top=20,left=0,scrollbars=yes," + 
					"location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no";
				win=window.open(Nurl,title,settings);
				win.focus();
			}
			
			//Open a window to move a script
			function moveScript() {
				window.name = "dpsmain";
				var left=0;
				var top=20;
				var title = "MoveFile";
				var Nurl = siteRoot + "?" +
					"templateID=49&scriptID=" + String(currentVal).substring(3,String(currentVal).length);
				var settings="width=800,height=600,top=20,left=0,scrollbars=yes," +
					"location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no";
				win=window.open(Nurl,title,settings);
				win.focus();
			}
			
			//Open a window to move a showplan
			function moveShow() {
				window.name = "dpsmain";
				var left=0;
				var top=20;
				var title = "MoveFile";
				var Nurl = siteRoot + "?" +
					"templateID=66&showplanID=" + String(currentVal).substring(3,String(currentVal).length);
				var settings="width=800,height=600,top=20,left=0,scrollbars=yes," +
					"location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no";
				win=window.open(Nurl,title,settings);
				win.focus();
			}
			
			//Opens a window to move audio
			function moveAudio() {
				window.name = "dpsmain";
				var left=0;
				var top=20;
				var title = "MoveFile";
				var Nurl = siteRoot + "?" +
					"templateID=47&audioID=" + String(currentVal).substring(3,String(currentVal).length);
				var settings="width=800,height=600,top=20,left=0,scrollbars=yes," +
					"location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no";
				win=window.open(Nurl,title,settings);
				win.focus();
			}
			
			//Opens a window to upload a file
			function editDir()
			{
				window.name = "dpsmain";
				var left=0;
				var top=20;
				var title = "UploadFile";
				var Nurl = siteRoot + "?" +
					"templateID=68&rootdir=" + String(currentVal).substring(3,String(currentVal).length);
				var settings="width=800,height=600,top=20,left=0,scrollbars=yes," +
					"location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no";
				win=window.open(Nurl,title,settings);
				win.focus();
			}

			//Opens a window to move a directory
			function moveDir() {
				window.name = "dpsmain"
				var left=0
				var top=20
				var title = "MoveDirectory"
				var Nurl = siteRoot + "?" +
					"templateID=53&rootdir=" + String(currentVal).substring(3,String(currentVal).length)
				var settings="width=800,height=600,top=20,left=0,scrollbars=yes," +
					"location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no"
				win = window.open(Nurl,title,settings)
				win.focus()
			}
			
			//Opens a window to upload a file
			function uploadDir()
			{
				window.name = "dpsmain";
				var left=0;
				var top=20;
				var title = "UploadFile";
				var Nurl = siteRoot + "?" +
					"templateID=50&rootdir=" + String(currentVal).substring(3,String(currentVal).length);
				var settings="width=800,height=600,top=20,left=0,scrollbars=yes," +
					"location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no";
				win=window.open(Nurl,title,settings);
				win.focus();
			}
			
			//Activated when user clicks on tree
			//val holds id value of the node (first 3 chars define type)
			function doOnClick(val){
				currentVal = val;
				//Get items in document
				if (browserType == "gecko" ) {
					document.folderLayer = document.getElementById('folderBar');
					document.jingleLayer = document.getElementById('jingleBar');
					document.cartsetLayer = document.getElementById('cartsetBar');
					document.scriptLayer = document.getElementById('scriptBar');
					document.showLayer = document.getElementById('showBar');

					document.jinglecEdit = document.getElementById('jinglecEdit');
					document.jinglecMove = document.getElementById('jinglecMove');
					document.jinglecDelete = document.getElementById('jinglecDelete');
					document.dircCreate = document.getElementById('dircCreate');
					document.dircRename = document.getElementById('dircRename');
					document.dircDelete = document.getElementById('dircDelete');
					document.dircMove = document.getElementById('dircMove');
					document.dircUpload = document.getElementById('dircUpload');
					document.cartsetcEdit = document.getElementById('cartsetcEdit');
					document.cartsetcMove = document.getElementById('cartsetcMove');
					document.cartsetcDelete = document.getElementById('cartsetcDelete');
					document.scriptcEdit = document.getElementById('scriptcEdit');
					document.scriptcMove = document.getElementById('scriptcMove');
					document.scriptcDelete = document.getElementById('scriptcDelete');
					document.showcEdit = document.getElementById('showcEdit');
					document.showcMove = document.getElementById('showcMove');
					document.showcDelete = document.getElementById('showcDelete');

					document.dirrtext = document.getElementById('dirrtext');
					document.dirRename = document.getElementById('dirRename');
					document.dirDelete = document.getElementById('dirDelete');
					document.cartsetView = document.getElementById('cartsetView');
					document.cartsetEdit = document.getElementById('cartsetEdit');
					document.cartsetMove = document.getElementById('cartsetMove');
					document.cartsetDelete = document.getElementById('cartsetDelete');
					document.scriptEdit = document.getElementById('scriptEdit');
					document.scriptDelete = document.getElementById('scriptDelete');
					document.showEdit = document.getElementById('showEdit');
					document.showDelete = document.getElementById('showDelete');
				} else if (browserType == "ie") {
					document.folderLayer = document.all['folderBar'];
					document.jingleLayer = document.all['jingleBar'];
					document.cartsetLayer = document.all['cartsetBar'];
					document.scriptLayer = document.all['scriptBar'];
					document.showLayer = document.all['showBar'];

					document.jinglecEdit = document.all['jinglecEdit'];
					document.jinglecMove = document.all['jinglecMove'];
					document.jinglecDelete = document.all['jinglecDelete'];
					document.dircCreate = document.all['dircCreate'];
					document.dircRename = document.all['dircRename'];
					document.dircDelete = document.all['dircDelete'];
					document.dircMove = document.all['dircMove'];
					document.dircUpload = document.all['dircUpload'];
					document.cartsetcEdit = document.all['cartsetcEdit'];
					document.cartsetcMove = document.all['cartsetcMove'];
					document.cartsetcDelete = document.all['cartsetcDelete'];
					document.scriptcEdit = document.all['scriptcEdit'];
					document.scriptcMove = document.all['scriptcMove'];
					document.scriptcDelete = document.all['scriptcDelete'];
					document.showcEdit = document.all['showcEdit'];
					document.showcMove = document.all['showcMove'];
					document.showcDelete = document.all['showcDelete'];

					document.dirrtext = document.all['dirrtext'];
					document.dirRename = document.all['dirRename'];
					document.dirDelete = document.all['dirDelete'];
					document.cartsetView = document.all['cartsetView'];
					document.cartsetEdit = document.all['cartsetEdit'];
					document.cartsetMove = document.all['cartsetMove'];
					document.cartsetDelete = document.all['cartsetDelete'];
					document.scriptEdit = document.all['scriptMove'];
					document.scriptDelete = document.all['scriptDelete'];
					document.showEdit = document.all['showMove'];
					document.showDelete = document.all['showDelete'];
				} else {
					document.folderLayer = document.layers['folderBar'];
					document.jingleLayer = document.layers['jingleBar'];
					document.cartsetLayer = document.layers['cartsetBar'];
					document.scriptLayer = document.layers['scriptBar'];
					document.showLayer = document.layers['showBar'];

					document.jinglecEdit = document.layers['jinglecEdit'];
					document.jinglecMove = document.layers['jinglecMove'];
					document.jinglecDelete = document.layers['jinglecDelete'];
					document.dircCreate = document.layers['dircCreate'];
					document.dircRename = document.layers['dircRename'];
					document.dircDelete = document.layers['dircDelete'];
					document.dircMove = document.layers['dircMove'];
					document.dircUpload = document.layers['dircUpload'];
					document.cartsetcEdit = document.layers['cartsetcEdit'];
					document.cartsetcMove = document.layers['cartsetcMove'];
					document.cartsetcDelete = document.layers['cartsetcDelete'];
					document.scriptcEdit = document.layers['scriptcEdit'];
					document.scriptcMove = document.layers['scriptcMove'];
					document.scriptcDelete = document.layers['scriptcDelete'];
					document.showcEdit = document.layers['showcEdit'];
					document.showcMove = document.layers['showcMove'];
					document.showcDelete = document.layers['showcDelete'];

					document.dirrtext = document.layers['dirrtext'];
					document.dirRename = document.layers['dirRename'];
					document.dirDelete = document.layers['dirDelete'];
					document.cartsetView = document.layers['cartsetView'];
					document.cartsetEdit = document.layers['cartsetEdit'];
					document.cartsetMove = document.layers['cartsetMove'];
					document.cartsetDelete = document.layers['cartsetDelete'];
					document.scriptEdit = document.layers['scriptMove'];
					document.scriptDelete = document.layers['scriptDelete'];
					document.showEdit = document.layers['showMove'];
					document.showDelete = document.layers['showDelete'];
				}
				if((String(val).substring(0,3)) == "jgl") {
					//show&hide sections
					document.folderLayer.style.display = "none";
					document.cartsetLayer.style.display = "none";
					document.scriptLayer.style.display = "none";
					document.jingleLayer.style.display = "block";
					document.showLayer.style.display = "none";
					
					//Get permissions and show&hide stuff
					nodePerm = tree.getUserData(val,"perm");
					if((String(nodePerm).substring(1,2)) == "1") {
						document.jinglecEdit.style.display = "block";
						document.jinglecMove.style.display = "block";
						document.jinglecDelete.style.display = "block";
					} else {
						document.jinglecEdit.style.display = "none";
						document.jinglecMove.style.display = "none";
						document.jinglecDelete.style.display = "none";
					}
					
					//Update form links for new ID
					document.getElementById('jingleEdit').href = 
						siteRoot +
						"?templateID=37&trackID=" + String(val).substring(3,String(val).length);
					document.getElementById('jingleDelete').href = 
						siteRoot +
						"?templateID=" + templateID + "&formName=dpsUserDelAudio&" + 
						"moduleName=DPS&" + 
						"audioID=" + String(val).substring(3,String(val).length);
			
				} else if ((String(val).substring(0,3)) == "dir") {
					//show&hide sections
					document.folderLayer.style.display = "block";
					document.cartsetLayer.style.display = "none";
					document.scriptLayer.style.display = "none";
					document.jingleLayer.style.display = "none";
					document.showLayer.style.display = "none";
					
					//Get permissions and show&hide stuff
					nodePerm = tree.getUserData(val,"perm");
					parentNode = tree.getParentId(val);
					parentPerm = tree.getUserData(parentNode,"perm");
					if((String(parentPerm).substring(1,2)) != "1" 
						&& (String(nodePerm).substring(1,2)) != "1") {
						document.folderLayer.style.display = "none";
					}
					if((String(parentPerm).substring(1,2)) == "1") {
						document.dircRename.style.display = "block";
						document.dircDelete.style.display = "block";
						document.dircMove.style.display = "block";
					} else {
						document.dircRename.style.display = "none";
						document.dircDelete.style.display = "none";
						document.dircMove.style.display = "none";
					}
					if((String(nodePerm).substring(1,2)) == "1") {
						document.dircCreate.style.display = "block";
						document.dircUpload.style.display = "block";
					} else {
						document.dircCreate.style.display = "none";
						document.dircUpload.style.display = "none";
					}
			
					//Update links and text boxes
					document.dirDelete.href =
						siteRoot + "?" +
						"templateID=" + templateID + "&" +
						"formName=dpsdirdel&moduleName=DPS&" +
						"rootdir=" + String(val).substring(3,String(val).length);
					var hrefstr = siteRoot + "?" +
						"templateID=" + templateID + "&" +
						"formName=dpsdiradd&moduleName=DPS&" +
						"&rootdir=" + String(val).substring(3,String(val).length) + "&" +
						"dirtext=" + document.getElementById('dirctext').value;
					document.getElementById('dirCreate').href = hrefstr;
				} else if ((String(val).substring(0,3)) == "crt") {
					//show&hide sections
					document.folderLayer.style.display = "none";
					document.cartsetLayer.style.display = "block";
					document.scriptLayer.style.display = "none";
					document.jingleLayer.style.display = "none";
					document.showLayer.style.display = "none";
					
					//Get permissions and show&hide stuff
					nodePerm = tree.getUserData(val,"perm");
					parentNode = tree.getParentId(val);
					parentPerm = tree.getUserData(parentNode,"perm");
					if((String(parentPerm).substring(1,2)) == "1") {
						document.cartsetcMove.style.display = "block";
						document.cartsetcDelete.style.display = "block";
					} else {
						document.cartsetcMove.style.display = "none";
						document.cartsetcDelete.style.display = "none";
					}
					if((String(nodePerm).substring(1,2)) == "1") {
						document.cartsetcEdit.style.display = "block";
					} else {
						document.cartsetcEdit.style.display = "none";
					}
					
					//Update links
					document.cartsetView.href = 
						siteRoot + "?" +
						"templateID=26&cartset=" + String(val).substring(3,String(val).length);
					document.cartsetEdit.href = 
						siteRoot + "?" +
						"templateID=25&cartset=" + String(val).substring(3,String(val).length);
					document.cartsetDelete.href = 
						siteRoot + "?" + 
						"templateID=" + templateID + "&formName=dpsUserCartsetDelForm&" + 
						"moduleName=DPS&" +
						"cartset=" + String(val).substring(3,String(val).length);
				} else if ((String(val).substring(0,3)) == "scr") {
					//show&hide sections
					document.folderLayer.style.display = "none";
					document.cartsetLayer.style.display = "none";
					document.scriptLayer.style.display = "block";
					document.jingleLayer.style.display = "none";
					document.showLayer.style.display = "none";

					//Get permissions and show&hide stuff
					nodePerm = tree.getUserData(val,"perm");
					parentNode = tree.getParentId(val);
					parentPerm = tree.getUserData(parentNode,"perm");
					if((String(parentPerm).substring(1,2)) == "1") {
						document.scriptcMove.style.display = "block";
						document.scriptcDelete.style.display = "block";
					} else {
						document.scriptcMove.style.display = "none";
						document.scriptcDelete.style.display = "none";
					}
					if((String(nodePerm).substring(1,2)) == "1") {
						document.scriptcEdit.style.display = "block";
					} else {
						document.scriptcEdit.style.display = "none";
					}
					
					//Update links
					document.scriptEdit.href = 
						siteRoot + "?" +
						"templateID=45&scriptID=" + String(val).substring(3,String(val).length);
					document.scriptDelete.href = 
						siteRoot + "?" +
						"templateID=" + templateID + "&formName=dpsUserDelScript&" + 
						"moduleName=DPS" + 
						"&scriptID=" + String(val).substring(3,String(val).length);
				} else if ((String(val).substring(0,3)) == "shp") {
					//show&hide sections
					document.folderLayer.style.display = "none";
					document.cartsetLayer.style.display = "none";
					document.scriptLayer.style.display = "none";
					document.jingleLayer.style.display = "none";
					document.showLayer.style.display = "block";

					//Get permissions and show&hide stuff
					nodePerm = tree.getUserData(val,"perm");
					parentNode = tree.getParentId(val);
					parentPerm = tree.getUserData(parentNode,"perm");
					if((String(parentPerm).substring(1,2)) == "1") {
						document.showcMove.style.display = "block";
						document.showcDelete.style.display = "block";
					} else {
						document.showcMove.style.display = "none";
						document.showcDelete.style.display = "none";
					}
					if((String(nodePerm).substring(1,2)) == "1") {
						document.showcEdit.style.display = "block";
					} else {
						document.showcEdit.style.display = "none";
					}
					
					//Update links
					document.showEdit.href = 
						siteRoot + "?" +
						"templateID=55&showID=" + String(val).substring(3,String(val).length);
					document.showDelete.href = 
						siteRoot + "?" +
						"templateID=" + templateID + "&formName=dpsUserDelShow&" + 
						"moduleName=DPS" + 
						"&showID=" + String(val).substring(3,String(val).length);
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
