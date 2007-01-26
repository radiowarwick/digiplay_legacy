<?php /* Smarty version 2.6.14, created on 2006-09-21 23:08:53
         compiled from rfile:/var/www/toolkit/DPS/templates/dpsststationeditcart.tpl */ ?>
<html>
  <head>
    <title>Edit a Cart</title>
    <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
    <script language="javascript" src="DPS/scripts/ua.js"></script>
    <script language="javascript">
    <?php echo '
      function updateAudio(AudioID) {
	document.getElementById("hAudioID").value = AudioID;
      }
    '; ?>
  
    </script>
    <!-- Infrastructure code for the tree -->
    <script language="javascript" src="DPS/scripts/ftiens4.js"></script>
<!-- Execution of the code that actually builds the specific tree.
     The variable foldersTree creates its structure with calls to
     gFld, insFld, and insDoc -->
    <script>
      USETEXTLINKS = 1
      PRESERVESTATE = 0
      ICONPATH = 'DPS/images/'
      STARTALLOPEN = 0
      HIGHLIGHT = 1

      var MUSIC = 'note.jpg'
      foldersTree = gFld('Digiplay')
      foldersTree.treeID='phpBrowser'
      foldersTree.xID = 0;
      <?php echo $this->_tpl_vars['VIEWER']['treeData']; ?>

      //musicLib = insDoc(foldersTree, gLnk("Gs", "Music Library", "www.radio.warwick.ac.uk/dps/"))
      //musicLib.iconSrc = ICONPATH + "cds.jpg"
      // Load a page as if a node on the tree was clicked (synchronize frames)
      // (Highlights selection if highlight is available.)
      <?php echo '
      function loadSynchPage(node)
      {	
	node.forceOpeningOfAncestorFolders();
	clickOnLink(node.xID,node.link,\'_top\');
      }
      /*
      function clickOnLink(node,link,target) {
	highlightObjLink(findObj(node));
	hAudioID.value = AudioID;
      }
      */
      '; ?>

    </script>
  </head>
  <body>
    <div class='alignLeft'>
    <div class='EditCartTitle'>Editing cart <?php echo $this->_tpl_vars['VIEWER']['cartPos']; ?>
</div>
    <hr>
    <?php if ($this->_tpl_vars['VIEWER']['permError'] == 't'): ?>
      You do not have permission to edit this cart.
    <?php else: ?>
    <div class='EditCartDetails'>
      <?php if ($this->_tpl_vars['VIEWER']['new'] != 't'): ?>
      <form name="dpsStationCartEditForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
      <input type="hidden" name="formName" value="dpsStationCartEditForm" />
      <input type="hidden" name="moduleName" value="DPS" />
      <input type="hidden" name="templateID" value="70" />
      <input type="hidden" name="cartID" value="<?php echo $this->_tpl_vars['VIEWER']['cartInfo']['id']; ?>
" />
      <?php else: ?>
      <form name="dpsStationCartAddForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
      <input type="hidden" name="formName" value="dpsStationCartAddForm" />
      <input type="hidden" name="moduleName" value="DPS" />
      <input type="hidden" name="templateID" value="70" />
      <input type="hidden" name="cartPos" value="<?php echo $this->_tpl_vars['VIEWER']['cartPos']; ?>
" />
      <input type="hidden" name="cartwallID" value="<?php echo $this->_tpl_vars['VIEWER']['cartwallID']; ?>
" />
      <?php endif; ?>
      <div class='EditCartDetail'>Text:</div>
      <div class='EditCartValue'><textarea name="text"><?php echo $this->_tpl_vars['VIEWER']['cartInfo']['text']; ?>
</textarea></div>
      <input type="hidden" name="audioID" id="hAudioID" value="<?php echo $this->_tpl_vars['VIEWER']['cartInfo']['audioid']; ?>
" />
      <div class='EditCartDetail'>Style:</div>
      <div class='EditCartValue'>
	<select name=style>
	<?php $_from = $this->_tpl_vars['VIEWER']['styles']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['style']):
?>
	  <?php if ($this->_tpl_vars['style']['id'] == $this->_tpl_vars['VIEWER']['cartInfo']['styleid']): ?>
	  <option value=<?php echo $this->_tpl_vars['style']['id']; ?>
 selected><?php echo $this->_tpl_vars['style']['name']; ?>
</option>
	  <?php else: ?>
	  <option value=<?php echo $this->_tpl_vars['style']['id']; ?>
><?php echo $this->_tpl_vars['style']['name']; ?>
</option>
	  <?php endif; ?>
	<?php endforeach; endif; unset($_from); ?>
	</select>
      </div>
      <div class='EditCartDetailSub'><input type="Submit" name="Submit" value="Submit"></div>
      </form>
      <div class='EditCartDetailSub'>
      <?php if ($this->_tpl_vars['VIEWER']['new'] != 't'): ?>
      <form name="dpsStationCartDelForm" method="post" action="<?php echo $this->_tpl_vars['CONFIG']['general']['siteRoot']; ?>
">
      <input type="hidden" name="formName" value="dpsStationCartDelForm" />
      <input type="hidden" name="moduleName" value="DPS" />
      <input type="hidden" name="templateID" value="70" />
      <input type="hidden" name="cartID" value="<?php echo $this->_tpl_vars['VIEWER']['cartInfo']['id']; ?>
" />
      <input type="Submit" name="Submit" value="Clear">
      </form>
      <?php endif; ?>
      </div>
    </div>
    <div class='EditCartFile'>
      <div style="position:relative; top:0; left:0; ">
	<table border=0><tr><td>
	  <font size=-2>
	    <a style="font-size:7pt;text-decoration:none;color:rgb(50,100,255)" href="http://www.treemenu.net/" target=_blank>JavaScript Tree Menu</a>
	  </font>
	</td></tr></table>
      </div>
      <script LANGUAGE="JavaScript">
        initializeDocument()
        <?php if ($this->_tpl_vars['VIEWER']['new'] != 't'): ?>
        loadSynchPage(<?php echo $this->_tpl_vars['VIEWER']['activeNode']; ?>
)
        <?php endif; ?>
      </script>
      <noscript>
        A tree for site navigation will open here if you enable JavaScript in your browser.
      </noscript>
    </div>
    <?php endif; ?>
    <br style="clear: both;">
    </div>
  </body>
</html>