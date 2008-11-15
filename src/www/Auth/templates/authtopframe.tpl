<html>
	<head>
		<title>{$title}</title>
		<link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
		{if $type != ''}
		<link rel="STYLESHEET" type="text/css" href="DPS/scripts/dhtmlxTree/css/dhtmlXTree.css">
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXCommon.js"></script>
		<script src="DPS/scripts/dhtmlxTree/js/dhtmlXTree.js"></script>	
		{literal}
		<script language="javascript" type="text/javascript">
			var tree;
			var siteRoot="{/literal}{$CONFIG.general.toolkitRootURL}{literal}";
			var treeUser="{/literal}{$VIEWER.treeUser}{literal}";
			var guid="{/literal}{$VIEWER.id}{literal}";
			var template="{/literal}{$VIEWER.templateID}{literal}";
			{/literal}{if $type=='user'}
				var formname="userPermissionForm";
				var toedit="userToEdit";
			{/if}
			{if $type=='group'}
				var formname="groupRealmForm";
				var toedit="groupToEdit";
			{/if}{literal}

			function loadTree(){
				var hrefstr = siteRoot + "?" +
					"templateID=67&treeUser=" + treeUser + "&guid=" + guid;
				tree=new dhtmlXTreeObject(document.getElementById('toc_tree'),"100%","100%",0);
				tree.setXMLAutoLoading(hrefstr);
				tree.setImagePath("DPS/scripts/dhtmlxTree/imgs/");
				tree.setOnClickHandler(doOnClick);
				tree.enableTreeLines(false);
				tree.loadXML(hrefstr + "&id=rlm0");
			}

			function doOnClick(id){
				if ((String(id).substring(0,3)) == "opa") {
					document.location.href=siteRoot+"?templateID="+template+
						"&formName="+formname+"&moduleName=Auth"+
						"&task=realmAllow&"+toedit+"=" + guid + 
						"&rguid=" + String(id).substring(3,String(id).length);
				}else if ((String(id).substring(0,3)) == "opd") {
					document.location.href=siteRoot+"?templateID="+template+
						"&formName="+formname+"&moduleName=Auth"+
						"&task=realmDeny&"+toedit+"=" + guid + 
						"&rguid=" + String(id).substring(3,String(id).length);
				}else if ((String(id).substring(0,3)) == "opi") {
					document.location.href=siteRoot+"?templateID="+template+
						"&formName="+formname+"&moduleName=Auth"+
						"&task=realmIgnore&"+toedit+"=" + guid + 
						"&rguid=" + String(id).substring(3,String(id).length);
				}
			}
		</script>
		{/literal}
		{/if}
	</head>
	<body>
		<div class="centreContainer">
			<div class="frame_bottom">
				<div class="frame_showsidebar">
					<img class="frame_sidebarlogo" src="DPS/images/homenavadmin.png" alt="Admin">
					<div class="frame_studiosidebarlinks">
						<div class="frame_submenuitem">{templateLink id="1" text="Users"}</div>
						<div class="frame_submenuitem">{templateLink id="2" text="Groups"}</div>
						<div class="frame_submenuitem">{templateLink id="5" text="Location Management"}</div>
						<div class="frame_submenuitem">{templateLink id="4" text="Configuration"}</div>
					</div>
					<div class="frame_sidebarmusic">{templateLink id="31" text="Music Library"}</div>
					<div class="frame_sidebarshow">{templateLink id="34" text="Show Planning"}</div>
					<div class="frame_sidebarsue">{templateLink id="32" text="Sue Stamp"}</div>
					<div class="frame_sidebarstudio">{templateLink id="33" text="Studio Audiowalls"}</div>
							</div>
							<div class="frame_rightside">
								<div class="frame_content">
