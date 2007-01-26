<?php /* Smarty version 2.6.14, created on 2007-01-05 14:54:33
         compiled from rfile:dpsstudiotopframe.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:dpsstudiotopframe.tpl', 33, false),)), $this); ?>
<html>
  <head>
    <title><?php echo $this->_tpl_vars['title']; ?>
</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
<?php echo '
<SCRIPT LANGUAGE=\'livescript\' type=\'text/javascript\'>
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
var Nurl = "';  echo $this->_tpl_vars['CONFIG']['general']['siteRoot'];  echo '" + url
settings="width=" + w + ",height=" + h + ",top=" + top + ",left=" + left + ",scrollbars=yes,location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no"
win=window.open(Nurl,title,settings)
win.focus()
}
'; ?>

</script>
  </head>
  <body>
    <div class="centreContainer">
      <div class="frame_bottom">
	<div class="frame_studiosidebar">
	  <img class="frame_sidebarlogo" src="DPS/images/homenavstudio.png" alt="Studio">
	  <div class="frame_sidebarmusic"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '76','text' => 'Music Library'), $this);?>
</div>
	  <div class="frame_sidebarshow"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '79','text' => 'Show Planning'), $this);?>
</div>
	  <div class="frame_sidebarsue"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '77','text' => 'Sue Stamp'), $this);?>
</div>
	  <div class="frame_studiosidebarlinks">
	    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '78','text' => 'Information'), $this);?>
<br>
	    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '66','text' => 'Personal Cartwalls'), $this);?>
<br>
	    <?php if ($this->_tpl_vars['studio'] == 't'): ?>
	    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '72','text' => 'Station Cartwalls'), $this);?>
<br>
	    <?php endif; ?>
		<?php if ($this->_tpl_vars['access_playlist'] == 't'): ?>
		<?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '80','text' => 'Playlists'), $this);?>

		<?php endif; ?>
	  </div>
        </div>
        <div class="frame_rightside">
          <div class="frame_content">