CREATE TABLE cmscontent (
  contentid serial NOT NULL,
  regionid int NOT NULL default '0',
  timestamp int NOT NULL default '0',
  content bytea NOT NULL,
  userid int NOT NULL default '0',
  PRIMARY KEY  (contentid)
)

--
-- Dumping data for table `cmscontent`
--


/*!40000 ALTER TABLE `cmscontent` DISABLE KEYS */;
INSERT INTO cmscontent VALUES (1,1,1120714688,'this is some info!',1);
INSERT INTO cmscontent VALUES (2,1,1120714434,'some old stuff',1);
INSERT INTO cmscontent VALUES (3,1,1122131704,'this is some info! But its not very usefulthis is some info!',1);
INSERT INTO cmscontent VALUES (4,1,1122131778,'this is some info! But its not very useful!',1);
INSERT INTO cmscontent VALUES (5,1,1122131804,'this is some info! But its not very useful! <img src=\"/svn/supporting/FCKeditor/editor/images/smiley/msn/sad_smile.gif\" alt=\"\" />',1);
INSERT INTO cmscontent VALUES (12,1,1122155994,'this is some info! But its not very useful! <img src=\"/svn/supporting/FCKeditor/editor/images/smiley/msn/sad_smile.gif\" alt=\"\" />',1);
INSERT INTO cmscontent VALUES (13,2,1122168682,'hi\n',1);
INSERT INTO cmscontent VALUES (14,2,1122171315,'One World Week, University of Warwick Students Union, Coventry CV4 7AL\n\nThe World\'s Largest Student Run International Event!\n\n[New website will be launched summer 2005]\n\nclick here to view the One World Week 2005 website',1);
INSERT INTO cmscontent VALUES (15,1,1122182374,'this is some info! But its not very useful! <img alt=\\\"\\\" src=\\\"/svn/supporting/FCKeditor/editor/images/smiley/msn/sad_smile.gif\\\"/>sdfdsfds',1);
INSERT INTO cmscontent VALUES (16,1,1122182526,'this is some info! But its not very useful!',1);
INSERT INTO cmscontent VALUES (17,1,1122188894,'<hr style=\\\"width: 100%; height: 2px;\\\"/>this is some info! But its not very useful! dsfsdf<br/>',1);
INSERT INTO cmscontent VALUES (18,1,1122188914,'<hr height=\\\"\\\" style=\\\"\\\"/>this is some info! But its not very useful! <br/>',1);
INSERT INTO cmscontent VALUES (19,1,1122188921,'<hr style=\\\"\\\" height=\\\"\\\\&quot;\\\\&quot;\\\"/>this is some info! But its not very useful! <br/>',1);

CREATE TABLE cmsregions (
  regionid serial NOT NULL,
  name varchar(32) NOT NULL default '',
  editrealm int NOT NULL default '0',
  viewrealm int NOT NULL default '0',
  inlinetoolbar varchar(16) NOT NULL default 'Basic',
  windowtoolbar varchar(16) NOT NULL default 'Default',
  PRIMARY KEY  (regionid),
  UNIQUE (name)
);

INSERT INTO cmsregions VALUES (1,'A basic test',35,34,'cms_full','cms_full');
INSERT INTO cmsregions VALUES (2,'Splash text',35,34,'cms_none','cms_safe');

CREATE TABLE formfields (
  fieldid serial NOT NULL,
  templateid int NOT NULL default '0',
  formname varchar(32) NOT NULL default '',
  fieldname varchar(32) NOT NULL default '',
  ruleid int NOT NULL default '0',
  PRIMARY KEY  (fieldid)
);

INSERT INTO formfields VALUES (1,1,'testForm','emailAddress',1)
(2,2,'detailsForm','password',2)
(3,5,'loginForm','authPassword',3)
(4,2,'detailsForm','username',4)
(5,8,'detailsForm','password',2)
(6,8,'detailsForm','username',8)
(7,4,'deleteForm','realmToEdit',5)
(8,4,'deleteForm','realmToEdit',6)
(9,12,'addTemplateForm','fileName',7);

CREATE TABLE groups (
  groupid serial NOT NULL,
  groupname varchar(16) NOT NULL default '',
  description varchar(128) NOT NULL default '',
  PRIMARY KEY  (groupid)
);

INSERT INTO groups VALUES (1,'Administrators','The group for admins');
INSERT INTO groups VALUES (2,'Users','A group for users');

CREATE TABLE logentries (
  entryid serial NOT NULL,
  message text NOT NULL,
  level varchar(16) NOT NULL default '',
  module varchar(16) default NULL,
  notes text,
  notify_date timestamp(14) NOT NULL,
  PRIMARY KEY  (entryid)
);

CREATE TABLE realmgrouplink (
  groupid int NOT NULL default '0',
  realmid int NOT NULL default '0',
  allow char(1) default NULL,
  PRIMARY KEY  (groupid,realmid)
);

INSERT INTO realmgrouplink VALUES (1,1,'y');
INSERT INTO realmgrouplink VALUES (1,35,'y');
INSERT INTO realmgrouplink VALUES (2,2,'y');
INSERT INTO realmgrouplink VALUES (2,8,'y');
INSERT INTO realmgrouplink VALUES (2,34,'y');

CREATE TABLE realms (
  realmid serial NOT NULL,
  name varchar(32) NOT NULL default '',
  parentid int NOT NULL default '0',
  description varchar(128) default NULL,
  depth smallint default NULL,
  realmpath text,
  PRIMARY KEY  (realmid)
);

INSERT INTO realms VALUES (1,'Administration',0,'Realm Administration',0,'01');
INSERT INTO realms VALUES (2,'User',0,'User realm',0,'02');
INSERT INTO realms VALUES (5,'Vote',2,'User voting realm',1,'02.05');
INSERT INTO realms VALUES (6,'Comment',2,'User commenting realm',1,'02.06');
INSERT INTO realms VALUES (7,'Email Updates',6,'Receive email updates',2,'02.06.07');
INSERT INTO realms VALUES (8,'Site',0,'Public website',0,'08.06.07');
INSERT INTO realms VALUES (9,'Login',8,'Login page for user and admin areas',1,'08.09.07');
INSERT INTO realms VALUES (19,'Authentication',1,'Authentication configuration',1,'01.19.07');
INSERT INTO realms VALUES (20,'Users',19,'User Administration',2,'01.19.20');
INSERT INTO realms VALUES (21,'Groups',19,'Group Administration',2,'01.19.21');
INSERT INTO realms VALUES (22,'Realms',19,'Realm Administration',2,'01.19.22');
INSERT INTO realms VALUES (23,'Add',20,'',3,'01.19.20.23');
INSERT INTO realms VALUES (24,'Modify',20,'',3,'01.19.20.24');
INSERT INTO realms VALUES (25,'Delete',20,'',3,'01.19.20.25');
INSERT INTO realms VALUES (26,'Add',22,'',3,'01.19.22.26');
INSERT INTO realms VALUES (27,'Modify',22,'',3,'01.19.22.27');
INSERT INTO realms VALUES (28,'Delete',22,'',3,'01.19.22.28');
INSERT INTO realms VALUES (29,'Add',21,'',3,'01.19.21.29');
INSERT INTO realms VALUES (30,'Modify',21,'',3,'01.19.21.30');
INSERT INTO realms VALUES (31,'Delete',21,'',3,'01.19.21.31');
INSERT INTO realms VALUES (32,'Templates',1,'',1,'01.32.21.31');
INSERT INTO realms VALUES (33,'Content',0,'A realm describing read/write access for the CMS module',0,'33.32.21.31');
INSERT INTO realms VALUES (34,'View',33,'',1,'33.34.21.31');
INSERT INTO realms VALUES (35,'Edit',33,'',1,'33.35.21.31');

CREATE TABLE realmuserlink (
  userid serial NOT NULL,
  realmid int NOT NULL default '0',
  allow char(1) default NULL,
  PRIMARY KEY  (userid,realmid)
);

INSERT INTO realmuserlink VALUES (18,8,'y');
INSERT INTO realmuserlink VALUES (14,2,'y');
INSERT INTO realmuserlink VALUES (14,5,'n');
INSERT INTO realmuserlink VALUES (14,7,'n');
INSERT INTO realmuserlink VALUES (17,5,'n');

CREATE TABLE sessions (
  sessionid serial NOT NULL,
  useragent varchar(128) NOT NULL default '',
  ip varchar(15) NOT NULL default '',
  rndidentifier varchar(14) NOT NULL default '',
  lastaccess timestamp(14) NOT NULL,
  PRIMARY KEY  (sessionid)
);

INSERT INTO sessions VALUES (321,'Mozilla/5.0 (Macintosh; U; PPC Mac OS X Mach-O; en-US; rv:1.7.8) Gecko/20050511 Firefox/1.0.4','127.0.0.1','L44Y41K5Ak393p','20050727141526');
INSERT INTO sessions VALUES (322,'Mozilla/5.0 (Macintosh; U; PPC Mac OS X Mach-O; en-US; rv:1.7.8) Gecko/20050511 Firefox/1.0.4','127.0.0.1','L44Y41K5Ak393p',20050727142841);

CREATE TABLE sessionvalues (
  valueid serial NOT NULL,
  sessionid int NOT NULL default '0',
  skey varchar(32) NOT NULL default '',
  svalue bytea NOT NULL,
  PRIMARY KEY  (valueid)
);

INSERT INTO sessionvalues VALUES (292,321,'auth_user','admin');
INSERT INTO sessionvalues VALUES (294,321,'auth_lastRequestTime','1122474492');
INSERT INTO sessionvalues VALUES (301,322,'auth_user','admin');
INSERT INTO sessionvalues VALUES (304,322,'auth_lastRequestTime','1122474551');

CREATE TABLE templates (
  templateid serial NOT NULL,
  filename varchar(32) NOT NULL default '',
  modelclassname varchar(32) NOT NULL default '',
  viewerclassname varchar(32) NOT NULL default '',
  realmid int NOT NULL default '0',
  PRIMARY KEY  (templateid,filename)
);

INSERT INTO templates VALUES (1,'exampleTemplate.tpl','Model','Viewer',8);INSERT INTO templates VALUES 
INSERT INTO templates VALUES (2,'userModify.tpl','UserModel','UserViewer',1);
INSERT INTO templates VALUES (3,'groupModify.tpl','GroupModel','GroupViewer',1);
INSERT INTO templates VALUES (4,'realmModify.tpl','RealmModel','RealmViewer',1);
INSERT INTO templates VALUES (5,'login.tpl','LoginModel','LoginViewer',8);
INSERT INTO templates VALUES (6,'permissionError.tpl','LoginModel','LoginViewer',8);
INSERT INTO templates VALUES (7,'logout.tpl','LogoutModel','Viewer',8);
INSERT INTO templates VALUES (8,'userAdd.tpl','UserModel','UserViewer',1);
INSERT INTO templates VALUES (9,'groupAdd.tpl','GroupModel','GroupViewer',1);
INSERT INTO templates VALUES (10,'realmAdd.tpl','RealmModel','RealmViewer',1);
INSERT INTO templates VALUES (11,'listTemplates.tpl','TemplateModel','TemplateListViewer',1);
INSERT INTO templates VALUES (12,'addTemplate.tpl','AddTemplateModel','AddTemplateViewer',32);
INSERT INTO templates VALUES (13,'editContentWindow.tpl','EditContentModel','EditContentViewer',35);
INSERT INTO templates VALUES (14,'editContent.tpl','EditContentModel','EditContentViewer',35);
INSERT INTO templates VALUES (15,'editContentWindow.rpl','editContentModel','editContentWindowViewer',25);
INSERT INTO templates VALUES (16,'main.tpl','Model','Viewer',8);

CREATE TABLE unittestdata (
  id serial NOT NULL,
  "user" varchar(32) NOT NULL default '',
  firstName varchar(32) NOT NULL default '',
  lastName varchar(32) NOT NULL default '',
  PRIMARY KEY  (id)
);

INSERT INTO unittestdata VALUES (1,'adam','Adam','Charnock');
INSERT INTO unittestdata VALUES (2,'rachel','Rachel','Stroud');
INSERT INTO unittestdata VALUES (3,'nom','Naiomi','Bunch');
INSERT INTO unittestdata VALUES (4,'claire','Claire','Hugget');
INSERT INTO unittestdata VALUES (5,'dan','33084-33084','Hammond');

CREATE TABLE usergrouplink (
  userid int NOT NULL default '0',
  groupid int NOT NULL default '0',
  PRIMARY KEY  (userid,groupid)
);

INSERT INTO usergrouplink VALUES (8,2);
INSERT INTO usergrouplink VALUES (12,2);
INSERT INTO usergrouplink VALUES (13,2);
INSERT INTO usergrouplink VALUES (15,1);
INSERT INTO usergrouplink VALUES (15,2);
INSERT INTO usergrouplink VALUES (16,2);
INSERT INTO usergrouplink VALUES (17,2);

CREATE TABLE users (
  userid serial NOT NULL,
  username varchar(16) NOT NULL default '',
  password varchar(32) default NULL,
  firstName varchar(32) default NULL,
  lastName varchar(32) default NULL,
  PRIMARY KEY  (userid,username)
);

INSERT INTO users VALUES (18,'visitor','d41d8cd98f00b204e9800998ecf8427e','','');
INSERT INTO users VALUES (15,'admin','5f4dcc3b5aa765d61d8327deb882cf99','','');
INSERT INTO users VALUES (16,'user1','5f4dcc3b5aa765d61d8327deb882cf99','','');
INSERT INTO users VALUES (17,'user2','5f4dcc3b5aa765d61d8327deb882cf99','','');

CREATE TABLE validationrules (
  ruleid serial NOT NULL,
  vrclassname varchar(45) NOT NULL default '',
  description text NOT NULL,
  PRIMARY KEY  (ruleid)
);

INSERT INTO validationrules VALUES (1,'EmailValidator','Validate an email address');
INSERT INTO validationrules VALUES (2,'PasswordValidator','Check that a new password matches security criteria');
INSERT INTO validationrules VALUES (3,'AttemptLogin','Attempt to login username/password (user taken from $fieldData)');
INSERT INTO validationrules VALUES (4,'UniqueUsername','Check that a username is unique');
INSERT INTO validationrules VALUES (5,'NoTemplatesInRealm','Check that a realm does not have any templates within it. This should be used before deletion');
INSERT INTO validationrules VALUES (6,'NoSubRealmsInRealm','Check that a realm does not conatain any sub/child templates. This should be used before deletion');
INSERT INTO validationrules VALUES (7,'ValidUnusedTplFile','Check that a template file exists and is not in use');
INSERT INTO validationrules VALUES (8,'UniqueNewUsername','Check that a new username is unique');

