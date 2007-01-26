-- MySQL dump 10.9
--
-- Host: localhost    Database: test
-- ------------------------------------------------------
-- Server version	4.0.23a
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `cmscontent`
--

DROP TABLE IF EXISTS `cmscontent`;
CREATE TABLE `cmscontent` (
  `contentid` int(10) unsigned NOT NULL auto_increment,
  `regionid` int(10) unsigned NOT NULL default '0',
  `timestamp` int(10) unsigned NOT NULL default '0',
  `content` blob NOT NULL,
  `userid` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`contentid`)
) TYPE=MyISAM;

--
-- Dumping data for table `cmscontent`
--


/*!40000 ALTER TABLE `cmscontent` DISABLE KEYS */;
LOCK TABLES `cmscontent` WRITE;
INSERT INTO `cmscontent` VALUES (1,1,1120714688,'this is some info!',1),(2,1,1120714434,'some old stuff',1),(3,1,1122131704,'this is some info! But its not very usefulthis is some info!',1),(4,1,1122131778,'this is some info! But its not very useful!',1),(5,1,1122131804,'this is some info! But its not very useful! <img src=\"/svn/supporting/FCKeditor/editor/images/smiley/msn/sad_smile.gif\" alt=\"\" />',1),(12,1,1122155994,'this is some info! But its not very useful! <img src=\"/svn/supporting/FCKeditor/editor/images/smiley/msn/sad_smile.gif\" alt=\"\" />',1),(13,2,1122168682,'hi\n',1),(14,2,1122171315,'One World Week, University of Warwick Students Union, Coventry CV4 7AL\n\nThe World\'s Largest Student Run International Event!\n\n[New website will be launched summer 2005]\n\nclick here to view the One World Week 2005 website',1),(15,1,1122182374,'this is some info! But its not very useful! <img alt=\\\"\\\" src=\\\"/svn/supporting/FCKeditor/editor/images/smiley/msn/sad_smile.gif\\\"/>sdfdsfds',1),(16,1,1122182526,'this is some info! But its not very useful!',1),(17,1,1122188894,'<hr style=\\\"width: 100%; height: 2px;\\\"/>this is some info! But its not very useful! dsfsdf<br/>',1),(18,1,1122188914,'<hr height=\\\"\\\" style=\\\"\\\"/>this is some info! But its not very useful! <br/>',1),(19,1,1122188921,'<hr style=\\\"\\\" height=\\\"\\\\&quot;\\\\&quot;\\\"/>this is some info! But its not very useful! <br/>',1);
UNLOCK TABLES;
/*!40000 ALTER TABLE `cmscontent` ENABLE KEYS */;

--
-- Table structure for table `cmscontent_id_seq`
--

DROP TABLE IF EXISTS `cmscontent_id_seq`;
CREATE TABLE `cmscontent_id_seq` (
  `id` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`id`)
) TYPE=MyISAM;

--
-- Dumping data for table `cmscontent_id_seq`
--


/*!40000 ALTER TABLE `cmscontent_id_seq` DISABLE KEYS */;
LOCK TABLES `cmscontent_id_seq` WRITE;
INSERT INTO `cmscontent_id_seq` VALUES (19);
UNLOCK TABLES;
/*!40000 ALTER TABLE `cmscontent_id_seq` ENABLE KEYS */;

--
-- Table structure for table `cmsregions`
--

DROP TABLE IF EXISTS `cmsregions`;
CREATE TABLE `cmsregions` (
  `regionid` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(32) NOT NULL default '',
  `editrealm` int(10) unsigned NOT NULL default '0',
  `viewrealm` int(10) unsigned NOT NULL default '0',
  `inlinetoolbar` varchar(16) NOT NULL default 'Basic',
  `windowtoolbar` varchar(16) NOT NULL default 'Default',
  PRIMARY KEY  (`regionid`),
  UNIQUE KEY `name` (`name`)
) TYPE=MyISAM;

--
-- Dumping data for table `cmsregions`
--


/*!40000 ALTER TABLE `cmsregions` DISABLE KEYS */;
LOCK TABLES `cmsregions` WRITE;
INSERT INTO `cmsregions` VALUES (1,'A basic test',35,34,'cms_full','cms_full'),(2,'Splash text',35,34,'cms_none','cms_safe');
UNLOCK TABLES;
/*!40000 ALTER TABLE `cmsregions` ENABLE KEYS */;

--
-- Table structure for table `formfields`
--

DROP TABLE IF EXISTS `formfields`;
CREATE TABLE `formfields` (
  `fieldid` int(10) unsigned NOT NULL auto_increment,
  `templateid` int(10) unsigned NOT NULL default '0',
  `formname` varchar(32) NOT NULL default '',
  `fieldname` varchar(32) NOT NULL default '',
  `ruleid` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`fieldid`)
) TYPE=MyISAM;

--
-- Dumping data for table `formfields`
--


/*!40000 ALTER TABLE `formfields` DISABLE KEYS */;
LOCK TABLES `formfields` WRITE;
INSERT INTO `formfields` VALUES (1,1,'testForm','emailAddress',1),(2,2,'detailsForm','password',2),(3,5,'loginForm','authPassword',3),(4,2,'detailsForm','username',4),(5,8,'detailsForm','password',2),(6,8,'detailsForm','username',8),(7,4,'deleteForm','realmToEdit',5),(8,4,'deleteForm','realmToEdit',6),(9,12,'addTemplateForm','fileName',7);
UNLOCK TABLES;
/*!40000 ALTER TABLE `formfields` ENABLE KEYS */;

--
-- Table structure for table `groups`
--

DROP TABLE IF EXISTS `groups`;
CREATE TABLE `groups` (
  `groupid` int(10) unsigned NOT NULL auto_increment,
  `groupname` varchar(16) NOT NULL default '',
  `description` varchar(128) NOT NULL default '',
  PRIMARY KEY  (`groupid`)
) TYPE=MyISAM;

--
-- Dumping data for table `groups`
--


/*!40000 ALTER TABLE `groups` DISABLE KEYS */;
LOCK TABLES `groups` WRITE;
INSERT INTO `groups` VALUES (1,'Administrators','The group for admins'),(2,'Users','A group for users');
UNLOCK TABLES;
/*!40000 ALTER TABLE `groups` ENABLE KEYS */;

--
-- Table structure for table `groups_id_seq`
--

DROP TABLE IF EXISTS `groups_id_seq`;
CREATE TABLE `groups_id_seq` (
  `id` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`id`)
) TYPE=MyISAM;

--
-- Dumping data for table `groups_id_seq`
--


/*!40000 ALTER TABLE `groups_id_seq` DISABLE KEYS */;
LOCK TABLES `groups_id_seq` WRITE;
INSERT INTO `groups_id_seq` VALUES (8);
UNLOCK TABLES;
/*!40000 ALTER TABLE `groups_id_seq` ENABLE KEYS */;

--
-- Table structure for table `logentries`
--

DROP TABLE IF EXISTS `logentries`;
CREATE TABLE `logentries` (
  `entryid` int(10) unsigned NOT NULL auto_increment,
  `message` text NOT NULL,
  `level` varchar(16) NOT NULL default '',
  `module` varchar(16) default NULL,
  `notes` text,
  `notify_date` timestamp(14) NOT NULL,
  PRIMARY KEY  (`entryid`)
) TYPE=MyISAM;

--
-- Dumping data for table `logentries`
--


/*!40000 ALTER TABLE `logentries` DISABLE KEYS */;
LOCK TABLES `logentries` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `logentries` ENABLE KEYS */;

--
-- Table structure for table `logentries_id_seq`
--

DROP TABLE IF EXISTS `logentries_id_seq`;
CREATE TABLE `logentries_id_seq` (
  `id` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`id`)
) TYPE=MyISAM;

--
-- Dumping data for table `logentries_id_seq`
--


/*!40000 ALTER TABLE `logentries_id_seq` DISABLE KEYS */;
LOCK TABLES `logentries_id_seq` WRITE;
INSERT INTO `logentries_id_seq` VALUES (29317);
UNLOCK TABLES;
/*!40000 ALTER TABLE `logentries_id_seq` ENABLE KEYS */;

--
-- Table structure for table `realmgrouplink`
--

DROP TABLE IF EXISTS `realmgrouplink`;
CREATE TABLE `realmgrouplink` (
  `groupid` int(10) unsigned NOT NULL default '0',
  `realmid` int(10) unsigned NOT NULL default '0',
  `allow` char(1) default NULL,
  PRIMARY KEY  (`groupid`,`realmid`)
) TYPE=MyISAM;

--
-- Dumping data for table `realmgrouplink`
--


/*!40000 ALTER TABLE `realmgrouplink` DISABLE KEYS */;
LOCK TABLES `realmgrouplink` WRITE;
INSERT INTO `realmgrouplink` VALUES (1,1,'y'),(1,35,'y'),(2,2,'y'),(2,8,'y'),(2,34,'y');
UNLOCK TABLES;
/*!40000 ALTER TABLE `realmgrouplink` ENABLE KEYS */;

--
-- Table structure for table `realms`
--

DROP TABLE IF EXISTS `realms`;
CREATE TABLE `realms` (
  `realmid` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(32) NOT NULL default '',
  `parentid` int(10) unsigned NOT NULL default '0',
  `description` varchar(128) default NULL,
  `depth` tinyint(4) default NULL,
  `realmpath` text,
  PRIMARY KEY  (`realmid`)
) TYPE=MyISAM;

--
-- Dumping data for table `realms`
--


/*!40000 ALTER TABLE `realms` DISABLE KEYS */;
LOCK TABLES `realms` WRITE;
INSERT INTO `realms` VALUES (1,'Administration',0,'Realm Administration',0,'01'),(2,'User',0,'User realm',0,'02'),(5,'Vote',2,'User voting realm',1,'02.05'),(6,'Comment',2,'User commenting realm',1,'02.06'),(7,'Email Updates',6,'Receive email updates',2,'02.06.07'),(8,'Site',0,'Public website',0,'08.06.07'),(9,'Login',8,'Login page for user and admin areas',1,'08.09.07'),(19,'Authentication',1,'Authentication configuration',1,'01.19.07'),(20,'Users',19,'User Administration',2,'01.19.20'),(21,'Groups',19,'Group Administration',2,'01.19.21'),(22,'Realms',19,'Realm Administration',2,'01.19.22'),(23,'Add',20,'',3,'01.19.20.23'),(24,'Modify',20,'',3,'01.19.20.24'),(25,'Delete',20,'',3,'01.19.20.25'),(26,'Add',22,'',3,'01.19.22.26'),(27,'Modify',22,'',3,'01.19.22.27'),(28,'Delete',22,'',3,'01.19.22.28'),(29,'Add',21,'',3,'01.19.21.29'),(30,'Modify',21,'',3,'01.19.21.30'),(31,'Delete',21,'',3,'01.19.21.31'),(32,'Templates',1,'',1,'01.32.21.31'),(33,'Content',0,'A realm describing read/write access for the CMS module',0,'33.32.21.31'),(34,'View',33,'',1,'33.34.21.31'),(35,'Edit',33,'',1,'33.35.21.31');
UNLOCK TABLES;
/*!40000 ALTER TABLE `realms` ENABLE KEYS */;

--
-- Table structure for table `realms_id_seq`
--

DROP TABLE IF EXISTS `realms_id_seq`;
CREATE TABLE `realms_id_seq` (
  `id` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`id`)
) TYPE=MyISAM;

--
-- Dumping data for table `realms_id_seq`
--


/*!40000 ALTER TABLE `realms_id_seq` DISABLE KEYS */;
LOCK TABLES `realms_id_seq` WRITE;
INSERT INTO `realms_id_seq` VALUES (36);
UNLOCK TABLES;
/*!40000 ALTER TABLE `realms_id_seq` ENABLE KEYS */;

--
-- Table structure for table `realmuserlink`
--

DROP TABLE IF EXISTS `realmuserlink`;
CREATE TABLE `realmuserlink` (
  `userid` int(10) unsigned NOT NULL auto_increment,
  `realmid` int(10) unsigned NOT NULL default '0',
  `allow` char(1) default NULL,
  PRIMARY KEY  (`userid`,`realmid`)
) TYPE=MyISAM;

--
-- Dumping data for table `realmuserlink`
--


/*!40000 ALTER TABLE `realmuserlink` DISABLE KEYS */;
LOCK TABLES `realmuserlink` WRITE;
INSERT INTO `realmuserlink` VALUES (18,8,'y'),(14,2,'y'),(14,5,'n'),(14,7,'n'),(17,5,'n');
UNLOCK TABLES;
/*!40000 ALTER TABLE `realmuserlink` ENABLE KEYS */;

--
-- Table structure for table `sessions`
--

DROP TABLE IF EXISTS `sessions`;
CREATE TABLE `sessions` (
  `sessionid` int(10) unsigned NOT NULL auto_increment,
  `useragent` varchar(128) NOT NULL default '',
  `ip` varchar(15) NOT NULL default '',
  `rndidentifier` varchar(14) NOT NULL default '',
  `lastaccess` timestamp(14) NOT NULL,
  PRIMARY KEY  (`sessionid`)
) TYPE=MyISAM;

--
-- Dumping data for table `sessions`
--


/*!40000 ALTER TABLE `sessions` DISABLE KEYS */;
LOCK TABLES `sessions` WRITE;
INSERT INTO `sessions` VALUES (321,'Mozilla/5.0 (Macintosh; U; PPC Mac OS X Mach-O; en-US; rv:1.7.8) Gecko/20050511 Firefox/1.0.4','127.0.0.1','L44Y41K5Ak393p',20050727141526),(322,'Mozilla/5.0 (Macintosh; U; PPC Mac OS X Mach-O; en-US; rv:1.7.8) Gecko/20050511 Firefox/1.0.4','127.0.0.1','L44Y41K5Ak393p',20050727142841);
UNLOCK TABLES;
/*!40000 ALTER TABLE `sessions` ENABLE KEYS */;

--
-- Table structure for table `sessions_id_seq`
--

DROP TABLE IF EXISTS `sessions_id_seq`;
CREATE TABLE `sessions_id_seq` (
  `id` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`id`)
) TYPE=MyISAM;

--
-- Dumping data for table `sessions_id_seq`
--


/*!40000 ALTER TABLE `sessions_id_seq` DISABLE KEYS */;
LOCK TABLES `sessions_id_seq` WRITE;
INSERT INTO `sessions_id_seq` VALUES (322);
UNLOCK TABLES;
/*!40000 ALTER TABLE `sessions_id_seq` ENABLE KEYS */;

--
-- Table structure for table `sessionvalues`
--

DROP TABLE IF EXISTS `sessionvalues`;
CREATE TABLE `sessionvalues` (
  `valueid` int(10) unsigned NOT NULL auto_increment,
  `sessionid` int(10) unsigned NOT NULL default '0',
  `skey` varchar(32) NOT NULL default '',
  `svalue` blob NOT NULL,
  PRIMARY KEY  (`valueid`)
) TYPE=MyISAM;

--
-- Dumping data for table `sessionvalues`
--


/*!40000 ALTER TABLE `sessionvalues` DISABLE KEYS */;
LOCK TABLES `sessionvalues` WRITE;
INSERT INTO `sessionvalues` VALUES (292,321,'auth_user','admin'),(294,321,'auth_lastRequestTime','1122474492'),(301,322,'auth_user','admin'),(304,322,'auth_lastRequestTime','1122474551');
UNLOCK TABLES;
/*!40000 ALTER TABLE `sessionvalues` ENABLE KEYS */;

--
-- Table structure for table `templates`
--

DROP TABLE IF EXISTS `templates`;
CREATE TABLE `templates` (
  `templateid` int(10) unsigned NOT NULL auto_increment,
  `filename` varchar(32) NOT NULL default '',
  `modelclassname` varchar(32) NOT NULL default '',
  `viewerclassname` varchar(32) NOT NULL default '',
  `realmid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`templateid`,`filename`)
) TYPE=MyISAM;

--
-- Dumping data for table `templates`
--


/*!40000 ALTER TABLE `templates` DISABLE KEYS */;
LOCK TABLES `templates` WRITE;
INSERT INTO `templates` VALUES (1,'exampleTemplate.tpl','Model','Viewer',8),(2,'userModify.tpl','UserModel','UserViewer',1),(3,'groupModify.tpl','GroupModel','GroupViewer',1),(4,'realmModify.tpl','RealmModel','RealmViewer',1),(5,'login.tpl','LoginModel','LoginViewer',8),(6,'permissionError.tpl','LoginModel','LoginViewer',8),(7,'logout.tpl','LogoutModel','Viewer',8),(8,'userAdd.tpl','UserModel','UserViewer',1),(9,'groupAdd.tpl','GroupModel','GroupViewer',1),(10,'realmAdd.tpl','RealmModel','RealmViewer',1),(11,'listTemplates.tpl','TemplateModel','TemplateListViewer',1),(12,'addTemplate.tpl','AddTemplateModel','AddTemplateViewer',32),(13,'editContentWindow.tpl','EditContentModel','EditContentViewer',35),(14,'editContent.tpl','EditContentModel','EditContentViewer',35),(15,'editContentWindow.rpl','editContentModel','editContentWindowViewer',25),(16,'main.tpl','Model','Viewer',8);
UNLOCK TABLES;
/*!40000 ALTER TABLE `templates` ENABLE KEYS */;

--
-- Table structure for table `unittestdata`
--

DROP TABLE IF EXISTS `unittestdata`;
CREATE TABLE `unittestdata` (
  `id` int(11) unsigned NOT NULL auto_increment,
  `user` varchar(32) NOT NULL default '',
  `firstName` varchar(32) NOT NULL default '',
  `lastName` varchar(32) NOT NULL default '',
  PRIMARY KEY  (`id`)
) TYPE=MyISAM;

--
-- Dumping data for table `unittestdata`
--


/*!40000 ALTER TABLE `unittestdata` DISABLE KEYS */;
LOCK TABLES `unittestdata` WRITE;
INSERT INTO `unittestdata` VALUES (1,'adam','Adam','Charnock'),(2,'rachel','Rachel','Stroud'),(3,'nom','Naiomi','Bunch'),(4,'claire','Claire','Hugget'),(5,'dan','33084-33084','Hammond');
UNLOCK TABLES;
/*!40000 ALTER TABLE `unittestdata` ENABLE KEYS */;

--
-- Table structure for table `usergrouplink`
--

DROP TABLE IF EXISTS `usergrouplink`;
CREATE TABLE `usergrouplink` (
  `userid` int(10) unsigned NOT NULL default '0',
  `groupid` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`userid`,`groupid`)
) TYPE=MyISAM;

--
-- Dumping data for table `usergrouplink`
--


/*!40000 ALTER TABLE `usergrouplink` DISABLE KEYS */;
LOCK TABLES `usergrouplink` WRITE;
INSERT INTO `usergrouplink` VALUES (8,2),(12,2),(13,2),(15,1),(15,2),(16,2),(17,2);
UNLOCK TABLES;
/*!40000 ALTER TABLE `usergrouplink` ENABLE KEYS */;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `userid` int(10) unsigned NOT NULL auto_increment,
  `username` varchar(16) NOT NULL default '',
  `password` varchar(32) default NULL,
  `firstName` varchar(32) default NULL,
  `lastName` varchar(32) default NULL,
  PRIMARY KEY  (`userid`,`username`)
) TYPE=MyISAM;

--
-- Dumping data for table `users`
--


/*!40000 ALTER TABLE `users` DISABLE KEYS */;
LOCK TABLES `users` WRITE;
INSERT INTO `users` VALUES (18,'visitor','d41d8cd98f00b204e9800998ecf8427e','',''),(15,'admin','5f4dcc3b5aa765d61d8327deb882cf99','',''),(16,'user1','5f4dcc3b5aa765d61d8327deb882cf99','',''),(17,'user2','5f4dcc3b5aa765d61d8327deb882cf99','','');
UNLOCK TABLES;
/*!40000 ALTER TABLE `users` ENABLE KEYS */;

--
-- Table structure for table `users_id_seq`
--

DROP TABLE IF EXISTS `users_id_seq`;
CREATE TABLE `users_id_seq` (
  `id` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`id`)
) TYPE=MyISAM;

--
-- Dumping data for table `users_id_seq`
--


/*!40000 ALTER TABLE `users_id_seq` DISABLE KEYS */;
LOCK TABLES `users_id_seq` WRITE;
INSERT INTO `users_id_seq` VALUES (18);
UNLOCK TABLES;
/*!40000 ALTER TABLE `users_id_seq` ENABLE KEYS */;

--
-- Table structure for table `validationrules`
--

DROP TABLE IF EXISTS `validationrules`;
CREATE TABLE `validationrules` (
  `ruleid` int(10) unsigned NOT NULL auto_increment,
  `vrclassname` varchar(45) NOT NULL default '',
  `description` text NOT NULL,
  PRIMARY KEY  (`ruleid`)
) TYPE=MyISAM;

--
-- Dumping data for table `validationrules`
--


/*!40000 ALTER TABLE `validationrules` DISABLE KEYS */;
LOCK TABLES `validationrules` WRITE;
INSERT INTO `validationrules` VALUES (1,'EmailValidator','Validate an email address'),(2,'PasswordValidator','Check that a new password matches security criteria'),(3,'AttemptLogin','Attempt to login username/password (user taken from $fieldData)'),(4,'UniqueUsername','Check that a username is unique'),(5,'NoTemplatesInRealm','Check that a realm does not have any templates within it. This should be used before deletion'),(6,'NoSubRealmsInRealm','Check that a realm does not conatain any sub/child templates. This should be used before deletion'),(7,'ValidUnusedTplFile','Check that a template file exists and is not in use'),(8,'UniqueNewUsername','Check that a new username is unique');
UNLOCK TABLES;
/*!40000 ALTER TABLE `validationrules` ENABLE KEYS */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

