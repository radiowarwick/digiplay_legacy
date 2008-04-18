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
			
			//Open a window to move an awset
			function moveAwSet() {
				window.name = "dpsmain";
				var left=0;
				var top=20;
				var title = "MoveFile";
				var Nurl = siteRoot + "?" +
					"templateID=48&awsetID=" + String(currentVal).substring(3,String(currentVal).length);
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
					document.awsetLayer = document.getElementById('awsetBar');
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
					document.awsetcEdit = document.getElementById('awsetcEdit');
					document.awsetcMove = document.getElementById('awsetcMove');
					document.awsetcDelete = document.getElementById('awsetcDelete');
					document.scriptcView = document.getElementById('scriptcView');
					document.scriptcEdit = document.getElementById('scriptcEdit');
					document.scriptcMove = document.getElementById('scriptcMove');
					document.scriptcDelete = document.getElementById('scriptcDelete');
					document.showcView = document.getElementById('showcView');
					document.showcEdit = document.getElementById('showcEdit');
					document.showcMove = document.getElementById('showcMove');
					document.showcDelete = document.getElementById('showcDelete');

					document.dirrtext = document.getElementById('dirrtext');
					document.dirRename = document.getElementById('dirRename');
					document.dirDelete = document.getElementById('dirDelete');
					document.awsetView = document.getElementById('awsetView');
					document.awsetEdit = document.getElementById('awsetEdit');
					document.awsetMove = document.getElementById('awsetMove');
					document.awsetDelete = document.getElementById('awsetDelete');
					document.scriptView = document.getElementById('scriptView');
					document.scriptEdit = document.getElementById('scriptEdit');
					document.scriptDelete = document.getElementById('scriptDelete');
					document.showView = document.getElementById('showView');
					document.showEdit = document.getElementById('showEdit');
					document.showDelete = document.getElementById('showDelete');
				} else if (browserType == "ie") {
					document.folderLayer = document.all['folderBar'];
					document.jingleLayer = document.all['jingleBar'];
					document.awsetLayer = document.all['awsetBar'];
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
					document.awsetcEdit = document.all['awsetcEdit'];
					document.awsetcMove = document.all['awsetcMove'];
					document.awsetcDelete = document.all['awsetcDelete'];
					document.scriptcEdit = document.all['scriptcEdit'];
					document.scriptcView = document.all['scriptcView'];
					document.scriptcMove = document.all['scriptcMove'];
					document.scriptcDelete = document.all['scriptcDelete'];
					document.showcView = document.all['showcView'];
					document.showcEdit = document.all['showcEdit'];
					document.showcMove = document.all['showcMove'];
					document.showcDelete = document.all['showcDelete'];

					document.dirrtext = document.all['dirrtext'];
					document.dirRename = document.all['dirRename'];
					document.dirDelete = document.all['dirDelete'];
					document.awsetView = document.all['awsetView'];
					document.awsetEdit = document.all['awsetEdit'];
					document.awsetMove = document.all['awsetMove'];
					document.awsetDelete = document.all['awsetDelete'];
					document.scriptView = document.all['scriptView'];
					document.scriptEdit = document.all['scriptEdit'];
					document.scriptDelete = document.all['scriptDelete'];
					document.showView = document.all['showView'];
					document.showEdit = document.all['showEdit'];
					document.showDelete = document.all['showDelete'];
				} else {
					document.folderLayer = document.layers['folderBar'];
					document.jingleLayer = document.layers['jingleBar'];
					document.awsetLayer = document.layers['awsetBar'];
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
					document.awsetcEdit = document.layers['awsetcEdit'];
					document.awsetcMove = document.layers['awsetcMove'];
					document.awsetcDelete = document.layers['awsetcDelete'];
					document.scriptcView = document.layers['scriptcView'];
					document.scriptcEdit = document.layers['scriptcEdit'];
					document.scriptcMove = document.layers['scriptcMove'];
					document.scriptcDelete = document.layers['scriptcDelete'];
					document.showcView = document.layers['showcView'];
					document.showcEdit = document.layers['showcEdit'];
					document.showcMove = document.layers['showcMove'];
					document.showcDelete = document.layers['showcDelete'];

					document.dirrtext = document.layers['dirrtext'];
					document.dirRename = document.layers['dirRename'];
					document.dirDelete = document.layers['dirDelete'];
					document.awsetView = document.layers['awsetView'];
					document.awsetEdit = document.layers['awsetEdit'];
					document.awsetMove = document.layers['awsetMove'];
					document.awsetDelete = document.layers['awsetDelete'];
					document.scriptView = document.layers['scriptView'];
					document.scriptEdit = document.layers['scriptEdit'];
					document.scriptDelete = document.layers['scriptDelete'];
					document.showView = document.layers['showView'];
					document.showEdit = document.layers['showEdit'];
					document.showDelete = document.layers['showDelete'];
				}
				if((String(val).substring(0,3)) == "jgl") {
					//show&hide sections
					document.folderLayer.style.display = "none";
					document.awsetLayer.style.display = "none";
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
						"trackID=" + String(val).substring(3,String(val).length);
			
				} else if ((String(val).substring(0,3)) == "dir") {
					//show&hide sections
					document.folderLayer.style.display = "block";
					document.awsetLayer.style.display = "none";
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
					document.awsetLayer.style.display = "block";
					document.scriptLayer.style.display = "none";
					document.jingleLayer.style.display = "none";
					document.showLayer.style.display = "none";
					
					//Get permissions and show&hide stuff
					nodePerm = tree.getUserData(val,"perm");
					parentNode = tree.getParentId(val);
					parentPerm = tree.getUserData(parentNode,"perm");
					if((String(parentPerm).substring(1,2)) == "1") {
						document.awsetcMove.style.display = "block";
						document.awsetcDelete.style.display = "block";
					} else {
						document.awsetcMove.style.display = "none";
						document.awsetcDelete.style.display = "none";
					}
					if((String(nodePerm).substring(1,2)) == "1") {
						document.awsetcEdit.style.display = "block";
					} else {
						document.awsetcEdit.style.display = "none";
					}
					
					//Update links
					document.awsetView.href = 
						siteRoot + "?" +
						"templateID=26&awset=" + String(val).substring(3,String(val).length);
					document.awsetEdit.href = 
						siteRoot + "?" +
						"templateID=25&awset=" + String(val).substring(3,String(val).length);
					document.awsetDelete.href = 
						siteRoot + "?" + 
						"templateID=" + templateID + "&formName=dpsUserAwSetDelForm&" + 
						"moduleName=DPS&" +
						"awset=" + String(val).substring(3,String(val).length);
				} else if ((String(val).substring(0,3)) == "scr") {
					//show&hide sections
					document.folderLayer.style.display = "none";
					document.awsetLayer.style.display = "none";
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
						document.scriptcView.style.display = "none";
					} else {
						document.scriptcEdit.style.display = "none";
						document.scriptcView.style.display = "block";
					}
					
					//Update links
					document.scriptEdit.href = 
						siteRoot + "?" +
						"templateID=45&scriptID=" + String(val).substring(3,String(val).length);
					document.scriptView.href = 
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
					document.awsetLayer.style.display = "none";
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
						document.showcView.style.display = "none";
					} else {
						document.showcEdit.style.display = "none";
						document.showcView.style.display = "block";
					}
					
					//Update links
					document.showEdit.href = 
						siteRoot + "?" +
						"templateID=55&showID=" + String(val).substring(3,String(val).length);
					document.showView.href = 
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
					<div class="frame_sidebarstudio">{templateLink id="33" text="Studio Audiowalls"}</div>
					<div class="frame_studiosidebarlinks">
						{templateLink id="34" text="Information"}<br />
						{templateLink id="54" text="My Showplans"}<br />
						{templateLink id="44" text="My Scripts"}<br />
						{templateLink id="51" text="My Files"}
					</div>
				</div>
				<div class="frame_rightside">
					<div class="frame_content">
