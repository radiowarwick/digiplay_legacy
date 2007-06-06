<html>
  <head>
    <title>{$title}</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
{literal}
<SCRIPT LANGUAGE='livescript' type='text/javascript'>
var win=null
var sURL = unescape(window.location.pathname)
function restart() {
  if (win.opener && !win.opener.closed) {
    win.close()
    window.location.reload( false )
  }
}
function NewWindow(url,title,w,h)
{
window.name = "dpsmain"
var left=0
var top=20
var Nurl = "{/literal}{$CONFIG.general.siteRoot}{literal}" + url
settings="width=" + w + ",height=" + h + ",top=" + top + ",left=" + left + ",scrollbars=yes,location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no"
win=window.open(Nurl,title,settings)
win.focus()
}
{/literal}
</script>
  </head>
  <body>
    <div class="centreContainer">
      <div class="frame_bottom">
	<div class="frame_studiosidebar">
	  <img class="frame_sidebarlogo" src="DPS/images/homenavstudio.png" alt="Studio">
	  <div class="frame_sidebarmusic">{templateLink id="31" text="Music Library"}</div>
	  <div class="frame_sidebarshow">{templateLink id="34" text="Show Planning"}</div>
	  <div class="frame_sidebarsue">{templateLink id="32" text="Sue Stamp"}</div>
	  <div class="frame_studiosidebarlinks">
	    {templateLink id="33" text="Information"}<br>
	    {templateLink id="23" text="Personal Cartwalls"}<br>
	    {if $studio == 't'}
	    {templateLink id="27" text="Station Cartwalls"}<br>
	    {/if}
		{if $access_playlist == 't'}
		{templateLink id="39" text="Playlists"}<br>
	  {templateLink id="51" text="My Files"}
		{/if}
	  </div>
        </div>
        <div class="frame_rightside">
          <div class="frame_content">
