<?php /* Smarty version 2.6.14, created on 2007-01-08 17:02:20
         compiled from rfile:dpsshowtopframe.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:dpsshowtopframe.tpl', 36, false),)), $this); ?>
<html>
  <head>
    <title><?php echo $this->_tpl_vars['title']; ?>
</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
		<script language='javascript' type='text/javascript'>
		<?php echo '
		var win = null;
		
		function restart() {
			if (win.opener && !win.opener.closed) {
				win.close();
			}
			document.location.href= "';  echo $this->_tpl_vars['CONFIG']['general']['toolkitRootURL']; ?>
?templateID=<?php echo $this->_tpl_vars['VIEWER']['templateID']; ?>
&itemID=<?php echo $this->_tpl_vars['VIEWER']['item']['id'];  echo '";
			//document.location.reload(true);
		}

		function NewWindow(url,title,w,h)
		{
			window.name = "dpsmain";
			var offleft=0;
			var offtop=20;
			var Nurl = "';  echo $this->_tpl_vars['CONFIG']['general']['toolkitRootURL'];  echo '" + url;
			var settings = "width=" + w + ",height=" + h + ",top=" + offtop + ",left=" + offleft + ",scrollbars=yes,location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=no";
			title="";
			win = window.open(Nurl,title,settings);
			win.focus();
		}
		'; ?>

		</script>
  </head>
  <body>
    <div class="centreContainer">
      <div class="frame_bottom">
	<div class="frame_showsidebar">
	  <img class="frame_sidebarlogo" src="DPS/images/homenavshow.png" alt="Show">
	  <div class="frame_sidebarmusic"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '76','text' => 'Music Library'), $this);?>
</div>
	  <div class="frame_sidebarshow"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '77','text' => 'Sue Stamp'), $this);?>
</div>
	  <div class="frame_sidebarsue"><?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '78','text' => 'Studio Cartwalls'), $this);?>
</div>
	  <div class="frame_studiosidebarlinks">
	    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '79','text' => 'Information'), $this);?>
<br />
	    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '81','text' => 'My Showplans'), $this);?>
<br />
	    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '93','text' => 'My Scripts'), $this);?>
<br />
	    <?php echo SmartyFunctions::SMARTY_templateLink(array('id' => '86','text' => 'My Files'), $this);?>

	  </div>
        </div>
        <div class="frame_rightside">
          <div class="frame_content">