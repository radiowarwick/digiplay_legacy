<html>
  <head>
    <title>{$title}</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
		<script language='javascript' type='text/javascript'>
		{literal}
		var win = null;
		
		function restart() {
			if (win.opener && !win.opener.closed) {
				win.close();
			}
			document.location.href= "{/literal}{$CONFIG.general.toolkitRootURL}?templateID={$VIEWER.templateID}&itemID={$VIEWER.item.id}{literal}";
			//document.location.reload(true);
		}

		function NewWindow(url,title,w,h)
		{
			window.name = "dpsmain";
			var offleft=0;
			var offtop=20;
			var Nurl = "{/literal}{$CONFIG.general.toolkitRootURL}{literal}" + url;
			var settings = "width=" + w + ",height=" + h + ",top=" + offtop + ",left=" + offleft + ",scrollbars=yes,location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no";
			title="";
			win = window.open(Nurl,title,settings);
			win.focus();
		}
		{/literal}
		</script>
  </head>
  <body>
    <div class="centreContainer">
      <div class="frame_bottom">
	<div class="frame_showsidebar">
	  <img class="frame_sidebarlogo" src="DPS/images/homenavshow.png" alt="Show">
	  <div class="frame_sidebarmusic">{templateLink id="31" text="Music Library"}</div>
	  <div class="frame_sidebarshow">{templateLink id="32" text="Sue Stamp"}</div>
	  <div class="frame_sidebarsue">{templateLink id="33" text="Studio Cartwalls"}</div>
	  <div class="frame_studiosidebarlinks">
	    {templateLink id="34" text="Information"}<br />
	    {templateLink id="54" text="My Showplans"}<br />
	    {templateLink id="44" text="My Scripts"}<br />
	    {templateLink id="51" text="My Files"}
	  </div>
        </div>
        <div class="frame_rightside">
          <div class="frame_content">
