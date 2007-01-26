<?php /* Smarty version 2.6.14, created on 2007-01-07 22:48:59
         compiled from rfile:contents.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'templateLink', 'rfile:contents.tpl', 4, false),)), $this); ?>
<ul class="contentsList"> 
  <li>Authentication</li> 
  <ul> 
    <li><?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "userModify.tpl",'text' => 'Modify User'), $this);?>
</li> 
    <li><?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "userAdd.tpl",'text' => 'Add User'), $this);?>
<br /></li> 
    <br />
    <li><?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "groupModify.tpl",'text' => 'Modify Group'), $this);?>
</li> 
    <li><?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "groupAdd.tpl",'text' => 'Add Group'), $this);?>
</li> 
    <br />
    <li><?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "realmModify.tpl",'text' => 'Modify Realm'), $this);?>
</li> 
    <li><?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "realmAdd.tpl",'text' => 'Add Realm'), $this);?>
</li> 
    <br />
    <li><?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "logout.tpl",'text' => 'Logout'), $this);?>
</li> 
  </ul> 
  
  <li>Content Management System</li> 
  <ul>
    <li><?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "editContent.tpl",'text' => 'Edit a Region'), $this);?>
</li>
  </ul>
  
  <li>MVC Management</li> 
  <ul>
    <li><?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "listTemplates.tpl",'text' => 'List Templates'), $this);?>
</li>
    <li><?php echo SmartyFunctions::SMARTY_templateLink(array('name' => "addTemplate.tpl",'text' => 'Add Template'), $this);?>
</li>
  </ul>
</ul>