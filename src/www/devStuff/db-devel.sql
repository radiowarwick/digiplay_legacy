-- MySQL dump 10.9
--
-- Host: localhost    Database: test
-- ------------------------------------------------------
-- Server version	4.1.13a

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `_validationrules`
--

DROP TABLE IF EXISTS `_validationrules`;
CREATE TABLE `_validationrules` (
  `ruleid` int(10) unsigned NOT NULL auto_increment,
  `vrclassname` varchar(45) NOT NULL default '',
  `description` text NOT NULL,
  `modulename` varchar(16) NOT NULL default '',
  PRIMARY KEY  (`ruleid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `_validationrules`
--


/*!40000 ALTER TABLE `_validationrules` DISABLE KEYS */;
LOCK TABLES `_validationrules` WRITE;
INSERT INTO `_validationrules` VALUES (1,'EmailValidator','Validate an email address','MVC'),(2,'PasswordValidator','Check that a new password matches security criteria','Auth'),(3,'AttemptLogin','Attempt to login username/password (user taken from $fieldData)','Auth'),(4,'UniqueUsername','Check that a username is unique','Auth'),(5,'NoTemplatesInRealm','Check that a realm does not have any templates within it. This should be used before deletion','Auth'),(6,'NoSubRealmsInRealm','Check that a realm does not conatain any sub/child templates. This should be used before deletion','Auth'),(7,'ValidUnusedTplFile','Check that a template file exists and is not in use','MVC'),(8,'CMSContentValidator','Ensures that a user has only submitted HTML tags that are avaliable on the toolbar shown','CMS'),(12,'IntValidator','',''),(10,'EmptyStringValidator','Ensures that a string is not empty','tkfecommon'),(11,'StringValidator','Ensures that the data represents a string','tkfecommon');
UNLOCK TABLES;
/*!40000 ALTER TABLE `_validationrules` ENABLE KEYS */;

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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `cmscontent`
--


/*!40000 ALTER TABLE `cmscontent` DISABLE KEYS */;
LOCK TABLES `cmscontent` WRITE;
INSERT INTO `cmscontent` VALUES (1,1,1120714688,'this is some info!',1),(2,1,1120714434,'some old stuff',1),(3,1,1122131704,'this is some info! But its not very usefulthis is some info!',1),(4,1,1122131778,'this is some info! But its not very useful!',1),(5,1,1122131804,'this is some info! But its not very useful! <img src=\"/svn/supporting/FCKeditor/editor/images/smiley/msn/sad_smile.gif\" alt=\"\" />',1),(12,1,1122155994,'this is some info! But its not very useful! <img src=\"/svn/supporting/FCKeditor/editor/images/smiley/msn/sad_smile.gif\" alt=\"\" />',1),(15,1,1122186182,'this is some info! But its not very useful!&nbsp; Well, ok , its good for testing<img alt=\\\"\\\" src=\\\"/svn/supporting/FCKeditor/editor/images/smiley/msn/sad_smile.gif\\\"/>',1),(16,1,1122186196,'this is some info! But its not very useful!&nbsp; Well, ok , its good for testing<img src=\\\"\\\\&quot;/svn/supporting/FCKeditor/editor/images/smiley/msn/sad_smile.gif\\\\&quot;/\\\" alt=\\\"\\\\&quot;\\\\&quot;\\\" style=\\\"width: 14px; height: 19px;\\\"/>',1),(17,1,1122186329,'this is some info! But its not very useful!&nbsp; Well, ok , its good for testing',1),(22,1,1122187464,'this is some info! But its not very useful!&nbsp; Well, ok , its good for testing <img src=\\\"/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\" alt=\\\"\\\"/><br/>',1),(23,1,1122187495,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing <img alt=\\\"\\\\&quot;\\\\&quot;/\\\" src=\\\"\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\&quot;\\\"/><br/>',1),(24,1,1122187558,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing <img src=\\\"\\\\&quot;\\\\\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\\\\\&quot;\\\\&quot;/\\\" alt=\\\"\\\\&quot;\\\\\\\\&quot;\\\\\\\\&quot;/\\\\&quot;\\\"/><br/>',1),(25,1,1122187560,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing <img alt=\\\"\\\\&quot;\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;/\\\\\\\\&quot;\\\\&quot;/\\\" src=\\\"\\\\&quot;\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\\\\\\\\\\\\\&quot;\\\\\\\\&quot;/\\\\&quot;\\\"/><br/>',1),(26,1,1122187854,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing&nbsp;&nbsp; <img src=\\\"/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\" alt=\\\"\\\"/><img src=\\\"\\\\&quot;\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;/\\\\\\\\&quot;\\\\&quot;/\\\" alt=\\\"\\\\&quot;\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;/\\\\\\\\\\\\\\\\&quot;\\\\\\\\&quot;/\\\\&quot;\\\"/><br/>',1),(27,1,1122187862,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing <img alt=\\\"\\\\&quot;\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;/\\\\\\\\&quot;\\\\&quot;/\\\" src=\\\"\\\\&quot;\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;/\\\\\\\\\\\\\\\\&quot;\\\\\\\\&quot;/\\\\&quot;\\\"/><br/>',1),(28,1,1122187914,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing',1),(29,1,1122187926,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing <img src=\\\"/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\" alt=\\\"\\\"/><br/>',1),(30,1,1122187950,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing <img alt=\\\"\\\\&quot;\\\\&quot;/\\\" src=\\\"\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\&quot;\\\"/><br/>',1),(31,1,1122188943,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing&nbsp;&nbsp;&nbsp;&nbsp; fhgh<img src=\"\\&quot;\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\&quot;\\&quot;/\" alt=\"\\&quot;\\\\&quot;\\\\&quot;/\\&quot;\"/><br/>',1),(32,1,1122188964,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing&nbsp; <img src=\"/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\" alt=\"\"/><img alt=\"\\&quot;\\\\&quot;\\\\&quot;/\\&quot;\" src=\"\\&quot;\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\&quot;\\&quot;/\"/><br/>',1),(33,1,1122188967,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing&nbsp; <img alt=\"\" src=\"/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\"/><img src=\"\\&quot;\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\&quot;\\&quot;/\" alt=\"\\&quot;\\\\&quot;\\\\&quot;/\\&quot;\"/><br/>',1),(34,1,1122188969,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing&nbsp; <img src=\"/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\" alt=\"\"/><img alt=\"\\&quot;\\\\&quot;\\\\&quot;/\\&quot;\" src=\"\\&quot;\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\&quot;\\&quot;/\"/><br/>',1),(35,1,1122189163,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing',1),(59,1,1122381993,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing<br/>\r\n<br/>\r\nYeah but it\'s bloody cool. :D',1),(160,1,1138118837,'Notes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><br /><a href=\"?templateID=39&amp;p=moo\">empty page</a><br /><span style=\"text-decoration: line-through;\"></span>',2),(161,40,1138118944,'Cows go moo and eat grass!',2),(158,1,1138109492,'Notes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><br /><a href=\"?templateID=39&amp;p=moo\">empty page</a><br /><span style=\"text-decoration: line-through;\"></span>',2),(159,1,1138109509,'Notes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><br /><a href=\"?templateID=39&amp;p=moo\">empty page</a><br /><span style=\"text-decoration: line-through;\"></span>',2),(156,1,1138109408,'Notes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><br /><a href=\"?templateID=39&amp;p=moo\">empty page</a><br /><span style=\"text-decoration: line-through;\"></span>',2),(157,1,1138109455,'Notes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><br /><a href=\"?templateID=39&amp;p=moo\">empty page</a><br /><span style=\"text-decoration: line-through;\"></span>',2),(148,30,1137893782,'Im not empty any more!',2),(149,33,1137893926,'It now exists!',2),(150,35,1137893964,'Not empty now!',2),(151,37,1137894064,'Not empty now!',2),(152,38,1137894116,'Not empty now!',2),(153,39,1137894202,'here it is!',2),(154,1,1138007201,'Notes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><span style=\"text-decoration: line-through;\"></span>',2),(155,1,1138107376,'Notes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><br /><a href=\"?templateID=39&amp;p=moo\">empty page</a><br /><span style=\"text-decoration: line-through;\"></span>',2),(143,1,1137892400,'<h1>The Main Page<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2),(144,1,1137892403,'<h1>The Main Page<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2),(145,1,1137892421,'<h1>The Main Page<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br />Test with new page processing<br /><span style=\"text-decoration: line-through;\"></span>',2),(146,1,1137892470,'<h1>The Main Page<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><span style=\"text-decoration: line-through;\"></span>',2),(147,1,1137893691,'<h1>The Main Page<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><span style=\"text-decoration: line-through;\"></span>',2),(140,1,1137872876,'<h1>The Main Page<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2),(135,16,1137870587,'',2),(136,20,1137870981,'',2),(137,21,1137871124,'',2),(138,23,1137871153,'',2),(139,23,1137871172,'HELLO!',2),(68,1,1129918284,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing<br /> <br /> Yeah but it\'s bloody cool. :D',1),(69,1,1129918290,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing<br /> <br style=\"font-weight: bold;\" /><span style=\"font-weight: bold;\"> Yeah but it\'s bloody cool. :D</span>',1),(70,1,1129918333,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing<br /> <br style=\"font-weight: bold; font-style: italic;\" /><span style=\"font-weight: bold; font-style: italic;\"> Yeah but it\'s bloody cool. :D</span>',1),(71,1,1129918338,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing<br /> <br style=\"font-weight: bold; font-style: italic;\" /><span style=\"font-weight: bold; font-style: italic; text-decoration: underline;\"> Yeah but it\'s bloody cool. :D</span>',1),(72,1,1129918360,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing<br /> <br style=\"font-weight: bold; font-style: italic;\" /><span style=\"font-weight: bold; font-style: italic; text-decoration: underline;\"> Yeah but it\'s bloody cool. :D</span>',1),(73,1,1129918393,'this is some info! But its not very useful!&nbsp; Well, ok , its good for testing<br /> <br style=\"font-weight: bold; font-style: italic;\" /><span style=\"font-weight: bold; font-style: italic; text-decoration: underline;\"> Yeah but it\'s bloody cool. :D</span>',1),(74,1,1129918403,'this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /> <br style=\"font-weight: bold; font-style: italic;\" /><span style=\"font-weight: bold; font-style: italic; text-decoration: underline;\"> Yeah but it\'s bloody cool. :D</span>',1),(75,1,1129918405,'this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /> <br style=\"font-weight: bold; font-style: italic;\" /><span style=\"font-weight: bold; font-style: italic; text-decoration: underline;\"> Yeah but it\'s bloody cool. :D</span>',1),(76,1,1129918650,'this is some info! But its not very useful!&nbsp; Well, ok, its good for mooing<br /><br /><span style=\"font-weight: bold; font-style: italic; text-decoration: underline;\"><br />Yeah but it\'s bloody cool. :D</span>',1),(77,1,1132098256,'this is some info! But its not very useful!&nbsp; Well, ok, its good for mooing<br /><br /><br />Yeah but it\'s bloody cool. :D',2),(78,1,1132098266,'this is some info! But its not very useful!&nbsp; Well, ok, its good for mooing<br /><br /><br /><span style=\"font-weight: bold; text-decoration: underline;\">Yeah but it\'s bloody cool. :D</span>',2),(79,1,1132098274,'this is some info! But its not very useful!&nbsp; Well, ok, its good for mooing<br /><br /><br /><span style=\"font-weight: bold; text-decoration: underline; font-style: italic;\">Yeah but it\'s bloody cool. :D</span>',2),(80,1,1132098289,'this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br /><br /><span style=\"font-weight: bold; text-decoration: underline; font-style: italic;\">Yeah but it\'s bloody cool. :D</span>',2),(81,1,1132098488,'this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(82,1,1132099730,'<span class=\"Title\">MOOO!!</span><br /><br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',1),(83,1,1132099744,'<span class=\"Title\">MOOO!!</span><br /><br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',1),(84,1,1132099754,'<span class=\"Title\">MOOO!!</span><br /><br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',1),(85,1,1132099769,'<span class=\"Title\">MOOO!!</span><br /><br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(86,1,1132099826,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',1),(87,1,1132099832,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(88,1,1132099964,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(89,1,1132099994,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(90,1,1132100000,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(91,1,1132100012,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(92,1,1132100576,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(93,1,1132100808,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',1),(94,1,1132101847,'<h1>MOOO!!</h1>\r\nNotes:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(95,1,1132101889,'<h1>MOOO!!</h1>\r\nNotes:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(96,1,1132137508,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(97,1,1136476701,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(98,1,1136481399,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(99,1,1136481527,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(100,1,1136481562,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(101,1,1136481599,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(102,1,1136481604,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(103,1,1136481684,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(104,1,1136481688,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(105,1,1136481712,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(106,1,1136481721,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(107,1,1136481734,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(108,1,1136481738,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(109,1,1136727224,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(110,1,1136727251,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(111,1,1136741066,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://127.0.0.1/svn/ctree/trunk/toolkit/index.php?templateID=39&amp;edit=1&amp;p=myPage\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(112,1,1136742318,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://127.0.0.1/svn/ctree/trunk/toolkit/index.php?templateID=39&amp;edit=1&amp;p=myPage\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(113,1,1136742474,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://127.0.0.1/svn/ctree/trunk/toolkit/index.php?templateID=39&amp;p=myPage\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(114,1,1136742478,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://127.0.0.1/svn/ctree/trunk/toolkit/index.php?templateID=39&amp;p=myPage\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(115,1,1136742600,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://127.0.0.1/svn/ctree/trunk/toolkit/index.php?templateID=39&amp;p=myPage\">Test link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(117,12,1136762207,'MOOOO',2),(118,12,1136762219,'sdfsdfsdfsdfdsf',2),(119,12,1136763454,'sdfsdfsdfsdfdsf<br /><br /><a href=\"http://127\\.0\\.0\\.1/svn/ctree/trunk/toolkit/index\\.php\\?templateID=39&amp;p=A_page¬called_moo\">A link to a new page</a>',2),(120,12,1136763474,'sdfsdfsdfsdfdsf<br /><br /><a href=\"http://127\\.0\\.0\\.1/svn/ctree/trunk/toolkit/index\\.php\\?templateID=39&amp;p=A_page¬called_moo\">A link to a new page</a>',2),(121,12,1136764121,'sdfsdfsdfsdfdsf<br /><br /><a href=\"http://127\\.0\\.0\\.1/svn/ctree/trunk/toolkit/index\\.php\\?templateID=39&amp;p=A_page¬called_moo\">A link to a new page</a>',2),(122,12,1136764146,'sdfsdfsdfsdfdsf<br /><br /><a href=\"?templateID=39&amp;p=a_test_page\">A link to a new page</a>',2),(123,13,1136764318,'This is the main page!!!!',2),(124,1,1136764349,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://127.0.0.1/svn/ctree/trunk/toolkit/index.php?templateID=39&amp;p=myPage\">Test link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(125,1,1136764367,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(126,1,1136764645,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li><strong><em>Anchors should not be avaliable!</em></strong></li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2),(127,14,1136764664,'moo',2),(128,14,1136764710,'<a href=\"?templateID=39&amp;p=matts_page\">moo</a>',2),(129,1,1136770567,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2),(130,1,1136771255,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2),(131,1,1136771300,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2),(132,1,1137705927,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=Moo_Page,_a_page_about_cows\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2),(133,15,1137705947,'They go moo',2),(134,1,1137707355,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2);
UNLOCK TABLES;
/*!40000 ALTER TABLE `cmscontent` ENABLE KEYS */;

--
-- Table structure for table `cmscontent_id_seq`
--

DROP TABLE IF EXISTS `cmscontent_id_seq`;
CREATE TABLE `cmscontent_id_seq` (
  `id` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `cmscontent_id_seq`
--


/*!40000 ALTER TABLE `cmscontent_id_seq` DISABLE KEYS */;
LOCK TABLES `cmscontent_id_seq` WRITE;
INSERT INTO `cmscontent_id_seq` VALUES (161);
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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `cmsregions`
--


/*!40000 ALTER TABLE `cmsregions` DISABLE KEYS */;
LOCK TABLES `cmsregions` WRITE;
INSERT INTO `cmsregions` VALUES (1,'A basic test',8,8,'TKWiki','TKWiki'),(23,'A_new_page',8,8,'TKWiki','TKWiki'),(12,'test_page',8,8,'TKWiki','TKWiki'),(13,'Main_Page',8,8,'TKWiki','TKWiki'),(14,'a_test_page',8,8,'TKWiki','TKWiki'),(15,'Moo_Page,_a_page_about_cows',8,8,'TKWiki','TKWiki'),(39,'Non_existant_page',8,8,'TKWiki','TKWiki'),(40,'moo',8,8,'TKWiki','TKWiki');
UNLOCK TABLES;
/*!40000 ALTER TABLE `cmsregions` ENABLE KEYS */;

--
-- Table structure for table `cmsregions_id_seq`
--

DROP TABLE IF EXISTS `cmsregions_id_seq`;
CREATE TABLE `cmsregions_id_seq` (
  `id` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `cmsregions_id_seq`
--


/*!40000 ALTER TABLE `cmsregions_id_seq` DISABLE KEYS */;
LOCK TABLES `cmsregions_id_seq` WRITE;
INSERT INTO `cmsregions_id_seq` VALUES (40);
UNLOCK TABLES;
/*!40000 ALTER TABLE `cmsregions_id_seq` ENABLE KEYS */;

--
-- Table structure for table `fieldvalidators`
--

DROP TABLE IF EXISTS `fieldvalidators`;
CREATE TABLE `fieldvalidators` (
  `ruleid` int(10) unsigned NOT NULL default '0',
  `vrclassname` varchar(45) NOT NULL default '',
  `description` text NOT NULL,
  `modulename` varchar(16) NOT NULL default ''
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `fieldvalidators`
--


/*!40000 ALTER TABLE `fieldvalidators` DISABLE KEYS */;
LOCK TABLES `fieldvalidators` WRITE;
INSERT INTO `fieldvalidators` VALUES (1,'EmailValidator','Validate an email address','MVC'),(2,'PasswordValidator','Check that a new password matches security criteria','Auth'),(3,'AttemptLogin','Attempt to login username/password (user taken from $fieldData)','Auth'),(4,'UniqueUsername','Check that a username is unique','Auth'),(5,'NoTemplatesInRealm','Check that a realm does not have any templates within it. This should be used before deletion','Auth'),(6,'NoSubRealmsInRealm','Check that a realm does not conatain any sub/child templates. This should be used before deletion','Auth'),(7,'ValidUnusedTplFile','Check that a template file exists and is not in use','MVC'),(8,'CMSContentValidator','Ensures that a user has only submitted HTML tags that are avaliable on the toolbar shown','CMS'),(12,'IntValidator','Ensures that the data represents an integer',''),(10,'EmptyStringValidator','Ensures that a string is not empty','tkfecommon'),(11,'StringValidator','Ensures that the data represents a string','tkfecommon');
UNLOCK TABLES;
/*!40000 ALTER TABLE `fieldvalidators` ENABLE KEYS */;

--
-- Table structure for table `formfields`
--

DROP TABLE IF EXISTS `formfields`;
CREATE TABLE `formfields` (
  `fieldid` int(10) unsigned NOT NULL auto_increment,
  `formname` varchar(32) NOT NULL default '',
  `fieldname` varchar(32) NOT NULL default '',
  `ruleid` int(10) unsigned NOT NULL default '0',
  `modulename` varchar(16) NOT NULL default '',
  PRIMARY KEY  (`fieldid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `formfields`
--


/*!40000 ALTER TABLE `formfields` DISABLE KEYS */;
LOCK TABLES `formfields` WRITE;
INSERT INTO `formfields` VALUES (3,'loginForm','authPassword',3,'Auth'),(7,'groupRealmForm','groupToEdit',10,'Auth'),(8,'groupRealmForm','rguid',10,'Auth'),(9,'groupRealmForm','task',11,'Auth'),(4,'groupSelForm','groupToEdit',10,'Auth'),(6,'groupDeleteForm','groupToEdit',10,'Auth'),(5,'groupDetailsForm','groupToEdit',10,'Auth');
UNLOCK TABLES;
/*!40000 ALTER TABLE `formfields` ENABLE KEYS */;

--
-- Table structure for table `forms`
--

DROP TABLE IF EXISTS `forms`;
CREATE TABLE `forms` (
  `formid` int(10) unsigned NOT NULL auto_increment,
  `formname` varchar(32) NOT NULL default '',
  `modelclass` varchar(32) NOT NULL default '',
  `modulename` varchar(32) NOT NULL default '',
  `realmid` int(11) NOT NULL default '0',
  `validatorname` varchar(32) default NULL,
  `validatormodule` varchar(32) default NULL,
  PRIMARY KEY  (`formid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `forms`
--


/*!40000 ALTER TABLE `forms` DISABLE KEYS */;
LOCK TABLES `forms` WRITE;
INSERT INTO `forms` VALUES (1,'loginForm','LoginModel','Auth',8,NULL,NULL),(3,'groupDetailsForm','GroupModel','Auth',8,NULL,NULL),(6,'groupSelForm','GroupModel','Auth',8,NULL,NULL),(4,'groupRealmForm','GroupModel','Auth',8,NULL,NULL),(7,'addGroupForm','GroupModel','Auth',8,NULL,NULL),(8,'groupDeleteForm','GroupModel','Auth',8,NULL,NULL),(10,'addRealmSelForm','RealmModel','Auth',8,NULL,NULL),(14,'modifyRealmDetailsForm','RealmModel','Auth',8,NULL,NULL),(11,'realmDeleteForm','RealmModel','Auth',8,NULL,NULL),(12,'addRealmDetailsForm','RealmModel','Auth',8,NULL,NULL),(13,'realmDeleteForm','RealmModel','Auth',8,NULL,NULL),(15,'userPermissionForm','UserModel','Auth',8,NULL,NULL),(18,'userDeleteForm','UserModel','Auth',8,NULL,NULL),(17,'modifyUserDetailsForm','UserModel','Auth',8,NULL,NULL),(16,'addUserDetailsForm','UserModel','Auth',8,NULL,NULL),(19,'selectRegionForm','EditContentModel','CMS',8,NULL,NULL),(20,'regionModifyForm','EditContentModel','CMS',8,NULL,NULL),(21,'addPostTKNews','ProposeAddModel','TKNews',8,NULL,NULL),(22,'modifyPostDetailsForm','PostModfyModel','TKNews',8,NULL,NULL),(23,'boardPermForm','AuthModifyModel','TKNews',8,NULL,NULL),(24,'uploadFile','UploadModel','TKFile',8,NULL,NULL),(25,'applyForm','ApplyModel','OWW',8,NULL,NULL),(26,'UWSUReturnForm','UWSUReturnModel','OWW',8,NULL,NULL),(27,'inlineEdit','EditContentModel','CMS',8,NULL,NULL),(28,'newPageForm','NewPageModel','TKWiki',8,NULL,NULL),(29,'pageForm','PageModel','TKWiki',8,NULL,NULL);
UNLOCK TABLES;
/*!40000 ALTER TABLE `forms` ENABLE KEYS */;

--
-- Table structure for table `groups`
--

DROP TABLE IF EXISTS `groups`;
CREATE TABLE `groups` (
  `groupid` int(10) unsigned NOT NULL auto_increment,
  `groupname` varchar(255) NOT NULL default '',
  `description` varchar(128) NOT NULL default '',
  `open` tinyint(3) NOT NULL default '0',
  PRIMARY KEY  (`groupid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `groups`
--


/*!40000 ALTER TABLE `groups` DISABLE KEYS */;
LOCK TABLES `groups` WRITE;
INSERT INTO `groups` VALUES (1,'Administrators','The group for admins',0),(2,'Users','A group for users',0);
UNLOCK TABLES;
/*!40000 ALTER TABLE `groups` ENABLE KEYS */;

--
-- Table structure for table `groups_id_seq`
--

DROP TABLE IF EXISTS `groups_id_seq`;
CREATE TABLE `groups_id_seq` (
  `id` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `groups_id_seq`
--


/*!40000 ALTER TABLE `groups_id_seq` DISABLE KEYS */;
LOCK TABLES `groups_id_seq` WRITE;
INSERT INTO `groups_id_seq` VALUES (9);
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
  `notify_date` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (`entryid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `logentries_id_seq`
--


/*!40000 ALTER TABLE `logentries_id_seq` DISABLE KEYS */;
LOCK TABLES `logentries_id_seq` WRITE;
INSERT INTO `logentries_id_seq` VALUES (79555);
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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `realmgrouplink`
--


/*!40000 ALTER TABLE `realmgrouplink` DISABLE KEYS */;
LOCK TABLES `realmgrouplink` WRITE;
INSERT INTO `realmgrouplink` VALUES (1,1,'y'),(1,35,'y'),(2,2,'y'),(2,8,'y'),(2,34,'y'),(2,37,'n'),(1,46,'y'),(1,51,'y'),(2,50,'y'),(1,47,'y'),(1,49,'y'),(1,48,'y'),(1,52,'y');
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
  `realmpath` varchar(255) default NULL,
  PRIMARY KEY  (`realmid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `realms`
--


/*!40000 ALTER TABLE `realms` DISABLE KEYS */;
LOCK TABLES `realms` WRITE;
INSERT INTO `realms` VALUES (1,'Administration',0,'Realm Administration',0,'01'),(2,'User',0,'User realm',0,'02'),(5,'Vote',2,'User voting realm',1,'02.05'),(6,'Comment',2,'User commenting realm',1,'02.06'),(7,'Email Updates',6,'Receive Email updates',2,'02.06.07'),(8,'Site',0,'Public website',0,'08'),(19,'Authentication',1,'Authentication configuration',1,'01.19'),(20,'Users',19,'User Administration',2,'01.19.20'),(21,'Groups',19,'Group Administration',2,'01.19.21'),(22,'Realms',19,'Realm Administration',2,'01.19.22'),(23,'Add',20,'',3,'01.19.20.23'),(24,'Modify',20,'',3,'01.19.20.24'),(25,'Delete',20,'',3,'01.19.20.25'),(26,'Add',22,'',3,'01.19.22.26'),(27,'Modify',22,'',3,'01.19.22.27'),(28,'Delete',22,'',3,'01.19.22.28'),(29,'Add',21,'',3,'01.19.21.29'),(30,'Modify',21,'',3,'01.19.21.30'),(31,'Delete',21,'',3,'01.19.21.31'),(32,'Templates',1,'',1,'01.32'),(33,'Content',0,'A realm describing read/write access for the CMS module',0,'33'),(34,'View',33,'',1,'33.34'),(35,'Edit',33,'',1,'33.35'),(40,'TKNews',0,'',0,'40'),(41,'0',40,'',1,'40.41'),(42,'1',40,'',1,'40.42'),(43,'2',40,'',1,'40.43'),(46,'View',42,'',2,'40.42.46'),(47,'Post',42,'',2,'40.42.47'),(48,'Admin',42,'',2,'40.42.48'),(50,'View',43,'',2,'40.43.50'),(51,'Post',43,'',2,'40.43.51'),(52,'Admin',43,'',2,'40.43.52'),(55,'Public Site',8,'Public Site for Visitors',1,'08.55'),(56,'Private Site',8,'Viewable pages for all other users',1,'08.56'),(57,'TKFile',0,'visitor',0,'57'),(73,'Users',57,NULL,1,'57.73'),(78,'visitor',73,NULL,2,'57.73.78');
UNLOCK TABLES;
/*!40000 ALTER TABLE `realms` ENABLE KEYS */;

--
-- Table structure for table `realms_id_seq`
--

DROP TABLE IF EXISTS `realms_id_seq`;
CREATE TABLE `realms_id_seq` (
  `id` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `realms_id_seq`
--


/*!40000 ALTER TABLE `realms_id_seq` DISABLE KEYS */;
LOCK TABLES `realms_id_seq` WRITE;
INSERT INTO `realms_id_seq` VALUES (78);
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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `realmuserlink`
--


/*!40000 ALTER TABLE `realmuserlink` DISABLE KEYS */;
LOCK TABLES `realmuserlink` WRITE;
INSERT INTO `realmuserlink` VALUES (3,6,'n'),(5,8,'y'),(14,2,'y'),(14,5,'n'),(14,7,'n'),(5,34,'y'),(1,49,'y'),(1,52,'y'),(22,46,'y'),(22,47,'y');
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
  `lastaccess` varchar(12) NOT NULL default '',
  PRIMARY KEY  (`sessionid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `sessions`
--


/*!40000 ALTER TABLE `sessions` DISABLE KEYS */;
LOCK TABLES `sessions` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `sessions` ENABLE KEYS */;

--
-- Table structure for table `sessions_id_seq`
--

DROP TABLE IF EXISTS `sessions_id_seq`;
CREATE TABLE `sessions_id_seq` (
  `id` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `sessions_id_seq`
--


/*!40000 ALTER TABLE `sessions_id_seq` DISABLE KEYS */;
LOCK TABLES `sessions_id_seq` WRITE;
INSERT INTO `sessions_id_seq` VALUES (594);
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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `sessionvalues`
--


/*!40000 ALTER TABLE `sessionvalues` DISABLE KEYS */;
LOCK TABLES `sessionvalues` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `sessionvalues` ENABLE KEYS */;

--
-- Table structure for table `templates`
--

DROP TABLE IF EXISTS `templates`;
CREATE TABLE `templates` (
  `templateid` int(10) unsigned NOT NULL auto_increment,
  `filename` varchar(32) NOT NULL default '',
  `viewerclassname` varchar(32) NOT NULL default '',
  `realmid` int(11) NOT NULL default '0',
  `modulename` varchar(16) NOT NULL default '',
  PRIMARY KEY  (`templateid`,`filename`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `templates`
--


/*!40000 ALTER TABLE `templates` DISABLE KEYS */;
LOCK TABLES `templates` WRITE;
INSERT INTO `templates` VALUES (27,'TitleViewer.tpl','TitleViewer',8,'TKNews'),(2,'userModify.tpl','UserViewer',1,'Auth'),(3,'groupModify.tpl','GroupViewer',1,'Auth'),(4,'realmModify.tpl','RealmViewer',1,'Auth'),(5,'utility/login.tpl','LoginViewer',8,'TKWiki'),(6,'utility/permissionError.tpl','LoginViewer',8,'TKWiki'),(7,'logout.tpl','LogoutViewer',8,'Auth'),(8,'userAdd.tpl','UserViewer',1,'Auth'),(9,'groupAdd.tpl','GroupViewer',1,'Auth'),(10,'realmAdd.tpl','RealmViewer',1,'Auth'),(11,'listTemplates.tpl','TemplateListViewer',1,'MVC'),(12,'addTemplate.tpl','AddTemplateViewer',32,'MVC'),(13,'editContentWindow.tpl','EditContentViewer',35,'CMS'),(14,'editContent.tpl','EditContentViewer',35,'CMS'),(15,'editContentWindow.rpl','editContentWindowViewer',35,'CMS'),(16,'main.tpl','Viewer',8,'OWW'),(17,'editorForm.tpl','EditorFormViewer',8,'CMS'),(18,'UWSULogin.tpl','LoginViewer',8,'OWW'),(19,'newUserInfo.tpl','Viewer',8,'CMS'),(20,'rPermissionError.tpl','Viewer',8,'Auth'),(21,'ProposePost.tpl','Viewer',8,'TKNews'),(22,'postModify.tpl','PostModifyViewer',8,'TKNews'),(23,'authModify.tpl','AuthModifyViewer',8,'TKNews'),(24,'RaWFrontPage.tpl','Viewer',55,'RaW'),(25,'ShortViewer.tpl','ShortViewer',8,'TKNews'),(26,'Rexception.tpl','RenderedExceptionViewer',8,'Auth'),(29,'LongViewer.tpl','LongViewer',8,'TKNews'),(28,'RaWFullNews.tpl','Viewer',8,'RaW'),(31,'ArchiveViewer.tpl','ArchiveViewer',8,'TKNews'),(30,'RaWArchiveNews.tpl','Viewer',8,'RaW'),(32,'RaWProposeNews.tpl','Viewer',8,'RaW'),(33,'RaWModifyPost.tpl','Viewer',8,'RaW'),(34,'browse.tpl','BrowserViewer',8,'TKFile'),(35,'upload.tpl','TKFileViewer',8,'TKFile'),(36,'fileInfo.tpl','FileInfoViewer',8,'TKFile'),(37,'apply.tpl','ApplyViewer',8,'OWW'),(38,'viewApplications.tpl','ApplicationsViewer',8,'OWW'),(39,'page.tpl','PageViewer',8,'TKWiki'),(40,'edit.tpl','Viewer',8,'TKWiki'),(41,'fckWindows/link.tpl','fckWindows/LinkViewer',8,'TKWiki'),(42,'newPage.tpl','NewPageViewer',8,'TKWiki'),(43,'admin/changePagePerms.tpl','admin/PagePermsViewer',8,'TKWiki');
UNLOCK TABLES;
/*!40000 ALTER TABLE `templates` ENABLE KEYS */;

--
-- Table structure for table `tknews_boards`
--

DROP TABLE IF EXISTS `tknews_boards`;
CREATE TABLE `tknews_boards` (
  `boardid` int(11) NOT NULL auto_increment,
  `name` varchar(75) NOT NULL default '',
  PRIMARY KEY  (`boardid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `tknews_boards`
--


/*!40000 ALTER TABLE `tknews_boards` DISABLE KEYS */;
LOCK TABLES `tknews_boards` WRITE;
INSERT INTO `tknews_boards` VALUES (1,'Proposals'),(2,'RaW News');
UNLOCK TABLES;
/*!40000 ALTER TABLE `tknews_boards` ENABLE KEYS */;

--
-- Table structure for table `tknews_posts`
--

DROP TABLE IF EXISTS `tknews_posts`;
CREATE TABLE `tknews_posts` (
  `postid` int(11) NOT NULL auto_increment,
  `boardid` int(11) NOT NULL default '0',
  `title` varchar(75) default NULL,
  `short` varchar(255) default NULL,
  `content` text,
  `viewcount` int(11) NOT NULL default '0',
  `rating` double NOT NULL default '0',
  `poster` int(11) NOT NULL default '0',
  `timestamp` int(11) NOT NULL default '0',
  PRIMARY KEY  (`postid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `tknews_posts`
--


/*!40000 ALTER TABLE `tknews_posts` DISABLE KEYS */;
LOCK TABLES `tknews_posts` WRITE;
INSERT INTO `tknews_posts` VALUES (1,2,'A Winter of RaW','Thanks to everyone for continuing to listen to raw even though we have been away on holiday have a good one! 22','Thanks to everyone for continuing to listen to raw even though we have been away on holiday have a good one!22 <br>Thanks to everyone for continuing to listen to raw even though we have been away on holiday have a good one!22',0,0.5,22,12200),(2,2,'A Summer of RaW','asd','asd',0,0.93,22,12341),(3,2,'A thing','jaklsdjalsd','sdadjaslkdjaskldj',0,0.5,21,501231),(4,1,'Boom Boom','Well what more can i say??','<h1><span style=\"font-family: courier new;\">I love <span style=\"font-style: italic;\">girls<img src=\"/Phil/Supporting/FCKeditor/editor/images/smiley/msn/broken_heart.gif\" alt=\"\"/></span></span></h1>',0,0.5,2,0);
UNLOCK TABLES;
/*!40000 ALTER TABLE `tknews_posts` ENABLE KEYS */;

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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

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
  `status` tinyint(3) NOT NULL default '1',
  PRIMARY KEY  (`userid`,`groupid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `usergrouplink`
--


/*!40000 ALTER TABLE `usergrouplink` DISABLE KEYS */;
LOCK TABLES `usergrouplink` WRITE;
INSERT INTO `usergrouplink` VALUES (1,1,1),(1,2,1),(2,2,1),(3,2,1),(4,2,1),(8,2,1),(12,2,1),(13,2,1),(20,2,1),(21,2,1),(21,1,1),(22,1,1),(22,2,1);
UNLOCK TABLES;
/*!40000 ALTER TABLE `usergrouplink` ENABLE KEYS */;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `userid` int(10) unsigned NOT NULL auto_increment,
  `username` varchar(50) NOT NULL default '',
  `password` varchar(50) NOT NULL default '',
  `password_temp` varchar(50) NOT NULL default '',
  `firstName` varchar(32) default NULL,
  `lastName` varchar(32) default NULL,
  `email` varchar(100) NOT NULL default '',
  `email_temp` varchar(110) NOT NULL default '',
  `hide_email` tinyint(1) NOT NULL default '0',
  `active` tinyint(1) NOT NULL default '0',
  `user_data` text NOT NULL,
  `signature` text NOT NULL,
  `threaded_list` tinyint(4) NOT NULL default '0',
  `posts` int(10) NOT NULL default '0',
  `admin` tinyint(1) NOT NULL default '0',
  `threaded_read` tinyint(4) NOT NULL default '0',
  `date_added` int(10) unsigned NOT NULL default '0',
  `date_last_active` int(10) unsigned NOT NULL default '0',
  `last_active_forum` int(10) unsigned NOT NULL default '0',
  `hide_activity` tinyint(1) NOT NULL default '0',
  PRIMARY KEY  (`userid`),
  UNIQUE KEY `username` (`username`),
  KEY `active` (`active`),
  KEY `userpass` (`username`,`password`),
  KEY `activity` (`date_last_active`,`hide_activity`,`last_active_forum`),
  KEY `date_added` (`date_added`),
  KEY `email_temp` (`email_temp`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `users`
--


/*!40000 ALTER TABLE `users` DISABLE KEYS */;
LOCK TABLES `users` WRITE;
INSERT INTO `users` VALUES (1,'adam','5f4dcc3b5aa765d61d8327deb882cf99','5f4dcc3b5aa765d61d8327deb882cf99','Adam','Charnock','adam@cheesetree.com','adam@cheesetree.com',0,1,'','',0,0,1,0,1123752213,1123752213,0,0),(2,'visitor','','','','','','',1,1,'','',0,0,0,0,1123752213,1123752213,0,0),(21,'0325391','','','Adam','Charnock','adam@cheesetree.com','',0,1,'','',0,0,1,0,1123752213,1123752213,0,0),(22,'phil','5f4dcc3b5aa765d61d8327deb882cf99','','phil','sharpe','','',0,0,'','',0,0,0,0,0,0,0,0);
UNLOCK TABLES;
/*!40000 ALTER TABLE `users` ENABLE KEYS */;

--
-- Table structure for table `users_id_seq`
--

DROP TABLE IF EXISTS `users_id_seq`;
CREATE TABLE `users_id_seq` (
  `id` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `users_id_seq`
--


/*!40000 ALTER TABLE `users_id_seq` DISABLE KEYS */;
LOCK TABLES `users_id_seq` WRITE;
INSERT INTO `users_id_seq` VALUES (22);
UNLOCK TABLES;
/*!40000 ALTER TABLE `users_id_seq` ENABLE KEYS */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

