CREATE TABLE validationrules (
  ruleid serial NOT NULL,
  vrclassname varchar(45) NOT NULL default '',
  description text NOT NULL,
  modulename varchar(16) NOT NULL default '',
  PRIMARY KEY  (ruleid)
);

INSERT INTO validationrules VALUES (1,'EmailValidator','Validate an email address','MVC');
INSERT INTO validationrules VALUES (2,'PasswordValidator','Check that a new password matches security criteria','Auth');
INSERT INTO validationrules VALUES (3,'AttemptLogin','Attempt to login username/password (user taken from $fieldData)','Auth');
INSERT INTO validationrules VALUES (4,'UniqueUsername','Check that a username is unique','Auth');
INSERT INTO validationrules VALUES (5,'NoTemplatesInRealm','Check that a realm does not have any templates within it. This should be used before deletion','Auth');
INSERT INTO validationrules VALUES (6,'NoSubRealmsInRealm','Check that a realm does not conatain any sub/child templates. This should be used before deletion','Auth');
INSERT INTO validationrules VALUES (7,'ValidUnusedTplFile','Check that a template file exists and is not in use','MVC');
INSERT INTO validationrules VALUES (8,'CMSContentValidator','Ensures that a user has only submitted HTML tags that are avaliable on the toolbar shown','CMS');
INSERT INTO validationrules VALUES (12,'IntValidator','','');
INSERT INTO validationrules VALUES (10,'EmptyStringValidator','Ensures that a string is not empty','tkfecommon');
INSERT INTO validationrules VALUES (11,'StringValidator','Ensures that the data represents a string','tkfecommon');

CREATE TABLE cmscontent (
  contentid serial NOT NULL,
  regionid int NOT NULL default '0',
  timestamp int NOT NULL default '0',
  content bytea NOT NULL,
  userid int NOT NULL default '0',
  PRIMARY KEY  (contentid)
);

INSERT INTO cmscontent VALUES (1,1,1120714688,'this is some info!',1);
NSERT INTO cmscontent VALUES (2,1,1120714434,'some old stuff',1);
INSERT INTO cmscontent VALUES (3,1,1122131704,'this is some info! But its not very usefulthis is some info!',1);
INSERT INTO cmscontent VALUES (4,1,1122131778,'this is some info! But its not very useful!',1);
INSERT INTO cmscontent VALUES (5,1,1122131804,'this is some info! But its not very useful! <img src=\"/svn/supporting/FCKeditor/editor/images/smiley/msn/sad_smile.gif\" alt=\"\" />',1);
INSERT INTO cmscontent VALUES (12,1,1122155994,'this is some info! But its not very useful! <img src=\"/svn/supporting/FCKeditor/editor/images/smiley/msn/sad_smile.gif\" alt=\"\" />',1);
INSERT INTO cmscontent VALUES (15,1,1122186182,'this is some info! But its not very useful!&nbsp; Well, ok , its good for testing<img alt=\\\"\\\" src=\\\"/svn/supporting/FCKeditor/editor/images/smiley/msn/sad_smile.gif\\\"/>',1);
INSERT INTO cmscontent VALUES (16,1,1122186196,'this is some info! But its not very useful!&nbsp; Well, ok , its good for testing<img src=\\\"\\\\&quot;/svn/supporting/FCKeditor/editor/images/smiley/msn/sad_smile.gif\\\\&quot;/\\\" alt=\\\"\\\\&quot;\\\\&quot;\\\" style=\\\"width: 14px; height: 19px;\\\"/>',1);
INSERT INTO cmscontent VALUES (17,1,1122186329,'this is some info! But its not very useful!&nbsp; Well, ok , its good for testing',1);
INSERT INTO cmscontent VALUES (22,1,1122187464,'this is some info! But its not very useful!&nbsp; Well, ok , its good for testing <img src=\\\"/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\" alt=\\\"\\\"/><br/>',1);
INSERT INTO cmscontent VALUES (23,1,1122187495,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing <img alt=\\\"\\\\&quot;\\\\&quot;/\\\" src=\\\"\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\&quot;\\\"/><br/>',1);
INSERT INTO cmscontent VALUES (24,1,1122187558,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing <img src=\\\"\\\\&quot;\\\\\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\\\\\&quot;\\\\&quot;/\\\" alt=\\\"\\\\&quot;\\\\\\\\&quot;\\\\\\\\&quot;/\\\\&quot;\\\"/><br/>',1);
INSERT INTO cmscontent VALUES (25,1,1122187560,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing <img alt=\\\"\\\\&quot;\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;/\\\\\\\\&quot;\\\\&quot;/\\\" src=\\\"\\\\&quot;\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\\\\\\\\\\\\\&quot;\\\\\\\\&quot;/\\\\&quot;\\\"/><br/>',1);
INSERT INTO cmscontent VALUES (26,1,1122187854,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing&nbsp;&nbsp; <img src=\\\"/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\" alt=\\\"\\\"/><img src=\\\"\\\\&quot;\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;/\\\\\\\\&quot;\\\\&quot;/\\\" alt=\\\"\\\\&quot;\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;/\\\\\\\\\\\\\\\\&quot;\\\\\\\\&quot;/\\\\&quot;\\\"/><br/>',1);
INSERT INTO cmscontent VALUES (27,1,1122187862,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing <img alt=\\\"\\\\&quot;\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;/\\\\\\\\&quot;\\\\&quot;/\\\" src=\\\"\\\\&quot;\\\\\\\\&quot;\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\&quot;/\\\\\\\\\\\\\\\\&quot;\\\\\\\\&quot;/\\\\&quot;\\\"/><br/>',1);
INSERT INTO cmscontent VALUES (28,1,1122187914,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing',1);
INSERT INTO cmscontent VALUES (29,1,1122187926,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing <img src=\\\"/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\" alt=\\\"\\\"/><br/>',1);
INSERT INTO cmscontent VALUES (30,1,1122187950,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing <img alt=\\\"\\\\&quot;\\\\&quot;/\\\" src=\\\"\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\&quot;\\\"/><br/>',1);
INSERT INTO cmscontent VALUES (31,1,1122188943,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing&nbsp;&nbsp;&nbsp;&nbsp; fhgh<img src=\"\\&quot;\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\&quot;\\&quot;/\" alt=\"\\&quot;\\\\&quot;\\\\&quot;/\\&quot;\"/><br/>',1);
INSERT INTO cmscontent VALUES (32,1,1122188964,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing&nbsp; <img src=\"/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\" alt=\"\"/><img alt=\"\\&quot;\\\\&quot;\\\\&quot;/\\&quot;\" src=\"\\&quot;\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\&quot;\\&quot;/\"/><br/>',1);
INSERT INTO cmscontent VALUES (33,1,1122188967,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing&nbsp; <img alt=\"\" src=\"/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\"/><img src=\"\\&quot;\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\&quot;\\&quot;/\" alt=\"\\&quot;\\\\&quot;\\\\&quot;/\\&quot;\"/><br/>',1);
INSERT INTO cmscontent VALUES (34,1,1122188969,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing&nbsp; <img src=\"/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\" alt=\"\"/><img alt=\"\\&quot;\\\\&quot;\\\\&quot;/\\&quot;\" src=\"\\&quot;\\\\&quot;/supporting/FCKeditor/editor/images/smiley/msn/regular_smile.gif\\\\&quot;\\&quot;/\"/><br/>',1);
INSERT INTO cmscontent VALUES (35,1,1122189163,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing',1);
INSERT INTO cmscontent VALUES (59,1,1122381993,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing<br/>\r\n<br/>\r\nYeah but it\'s bloody cool. :D',1);
INSERT INTO cmscontent VALUES (160,1,1138118837,'Notes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><br /><a href=\"?templateID=39&amp;p=moo\">empty page</a><br /><span style=\"text-decoration: line-through;\"></span>',2);
INSERT INTO cmscontent VALUES (161,40,1138118944,'Cows go moo and eat grass!',2);
INSERT INTO cmscontent VALUES (158,1,1138109492,'Notes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><br /><a href=\"?templateID=39&amp;p=moo\">empty page</a><br /><span style=\"text-decoration: line-through;\"></span>',2);
INSERT INTO cmscontent VALUES (159,1,1138109509,'Notes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><br /><a href=\"?templateID=39&amp;p=moo\">empty page</a><br /><span style=\"text-decoration: line-through;\"></span>',2);
INSERT INTO cmscontent VALUES (156,1,1138109408,'Notes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><br /><a href=\"?templateID=39&amp;p=moo\">empty page</a><br /><span style=\"text-decoration: line-through;\"></span>',2);
INSERT INTO cmscontent VALUES (157,1,1138109455,'Notes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><br /><a href=\"?templateID=39&amp;p=moo\">empty page</a><br /><span style=\"text-decoration: line-through;\"></span>',2);
INSERT INTO cmscontent VALUES (148,30,1137893782,'Im not empty any more!',2);
INSERT INTO cmscontent VALUES (149,33,1137893926,'It now exists!',2);
INSERT INTO cmscontent VALUES (150,35,1137893964,'Not empty now!',2);
INSERT INTO cmscontent VALUES (151,37,1137894064,'Not empty now!',2);
INSERT INTO cmscontent VALUES (152,38,1137894116,'Not empty now!',2);
INSERT INTO cmscontent VALUES (153,39,1137894202,'here it is!',2);
INSERT INTO cmscontent VALUES (154,1,1138007201,'Notes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><span style=\"text-decoration: line-through;\"></span>',2);
INSERT INTO cmscontent VALUES (155,1,1138107376,'Notes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><br /><a href=\"?templateID=39&amp;p=moo\">empty page</a><br /><span style=\"text-decoration: line-through;\"></span>',2);
INSERT INTO cmscontent VALUES (143,1,1137892400,'<h1>The Main Page<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2);
INSERT INTO cmscontent VALUES (144,1,1137892403,'<h1>The Main Page<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2);
INSERT INTO cmscontent VALUES (145,1,1137892421,'<h1>The Main Page<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br />Test with new page processing<br /><span style=\"text-decoration: line-through;\"></span>',2);
INSERT INTO cmscontent VALUES (146,1,1137892470,'<h1>The Main Page<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><span style=\"text-decoration: line-through;\"></span>',2);
INSERT INTO cmscontent VALUES (147,1,1137893691,'<h1>The Main Page<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br /><a href=\"?templateID=39&amp;p=Non_existant_page\">Non existant page</a><br /><span style=\"text-decoration: line-through;\"></span>',2);
INSERT INTO cmscontent VALUES (140,1,1137872876,'<h1>The Main Page<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2);
INSERT INTO cmscontent VALUES (135,16,1137870587,'',2);
INSERT INTO cmscontent VALUES (136,20,1137870981,'',2);
INSERT INTO cmscontent VALUES (137,21,1137871124,'',2);
INSERT INTO cmscontent VALUES (138,23,1137871153,'',2);
INSERT INTO cmscontent VALUES (139,23,1137871172,'HELLO!',2);
INSERT INTO cmscontent VALUES (68,1,1129918284,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing<br /> <br /> Yeah but it\'s bloody cool. :D',1);
INSERT INTO cmscontent VALUES (69,1,1129918290,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing<br /> <br style=\"font-weight: bold;\" /><span style=\"font-weight: bold;\"> Yeah but it\'s bloody cool. :D</span>',1);
INSERT INTO cmscontent VALUES (70,1,1129918333,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing<br /> <br style=\"font-weight: bold; font-style: italic;\" /><span style=\"font-weight: bold; font-style: italic;\"> Yeah but it\'s bloody cool. :D</span>',1);
INSERT INTO cmscontent VALUES (71,1,1129918338,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing<br /> <br style=\"font-weight: bold; font-style: italic;\" /><span style=\"font-weight: bold; font-style: italic; text-decoration: underline;\"> Yeah but it\'s bloody cool. :D</span>',1);
INSERT INTO cmscontent VALUES (72,1,1129918360,'this is some info! But its not very useful!&nbsp; Well, ok , its good for dfdf testing<br /> <br style=\"font-weight: bold; font-style: italic;\" /><span style=\"font-weight: bold; font-style: italic; text-decoration: underline;\"> Yeah but it\'s bloody cool. :D</span>',1);
INSERT INTO cmscontent VALUES (73,1,1129918393,'this is some info! But its not very useful!&nbsp; Well, ok , its good for testing<br /> <br style=\"font-weight: bold; font-style: italic;\" /><span style=\"font-weight: bold; font-style: italic; text-decoration: underline;\"> Yeah but it\'s bloody cool. :D</span>',1);
INSERT INTO cmscontent VALUES (74,1,1129918403,'this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /> <br style=\"font-weight: bold; font-style: italic;\" /><span style=\"font-weight: bold; font-style: italic; text-decoration: underline;\"> Yeah but it\'s bloody cool. :D</span>',1);
INSERT INTO cmscontent VALUES (75,1,1129918405,'this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /> <br style=\"font-weight: bold; font-style: italic;\" /><span style=\"font-weight: bold; font-style: italic; text-decoration: underline;\"> Yeah but it\'s bloody cool. :D</span>',1);
INSERT INTO cmscontent VALUES (76,1,1129918650,'this is some info! But its not very useful!&nbsp; Well, ok, its good for mooing<br /><br /><span style=\"font-weight: bold; font-style: italic; text-decoration: underline;\"><br />Yeah but it\'s bloody cool. :D</span>',1);
INSERT INTO cmscontent VALUES (77,1,1132098256,'this is some info! But its not very useful!&nbsp; Well, ok, its good for mooing<br /><br /><br />Yeah but it\'s bloody cool. :D',2);
INSERT INTO cmscontent VALUES (78,1,1132098266,'this is some info! But its not very useful!&nbsp; Well, ok, its good for mooing<br /><br /><br /><span style=\"font-weight: bold; text-decoration: underline;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (79,1,1132098274,'this is some info! But its not very useful!&nbsp; Well, ok, its good for mooing<br /><br /><br /><span style=\"font-weight: bold; text-decoration: underline; font-style: italic;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (80,1,1132098289,'this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br /><br /><span style=\"font-weight: bold; text-decoration: underline; font-style: italic;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (81,1,1132098488,'this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (82,1,1132099730,'<span class=\"Title\">MOOO!!</span><br /><br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',1);
INSERT INTO cmscontent VALUES (83,1,1132099744,'<span class=\"Title\">MOOO!!</span><br /><br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',1);
INSERT INTO cmscontent VALUES (84,1,1132099754,'<span class=\"Title\">MOOO!!</span><br /><br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',1);
INSERT INTO cmscontent VALUES (85,1,1132099769,'<span class=\"Title\">MOOO!!</span><br /><br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (86,1,1132099826,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',1);
INSERT INTO cmscontent VALUES (87,1,1132099832,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (88,1,1132099964,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (89,1,1132099994,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (90,1,1132100000,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (91,1,1132100012,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (92,1,1132100576,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (93,1,1132100808,'<h1>MOOO!!</h1>\r\n<br />this is some info! But its not very useful!&nbsp; Well, ok, its good for testing<br /><br style=\"text-decoration: line-through;\" /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',1);
INSERT INTO cmscontent VALUES (94,1,1132101847,'<h1>MOOO!!</h1>\r\nNotes:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (95,1,1132101889,'<h1>MOOO!!</h1>\r\nNotes:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (96,1,1132137508,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (97,1,1136476701,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (98,1,1136481399,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (99,1,1136481527,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (100,1,1136481562,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (101,1,1136481599,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (102,1,1136481604,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (103,1,1136481684,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (104,1,1136481688,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (105,1,1136481712,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (106,1,1136481721,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (107,1,1136481734,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (108,1,1136481738,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (109,1,1136727224,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (110,1,1136727251,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://www.google.co.uk\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (111,1,1136741066,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://127.0.0.1/svn/ctree/trunk/toolkit/index.php?templateID=39&amp;edit=1&amp;p=myPage\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (112,1,1136742318,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://127.0.0.1/svn/ctree/trunk/toolkit/index.php?templateID=39&amp;edit=1&amp;p=myPage\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (113,1,1136742474,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://127.0.0.1/svn/ctree/trunk/toolkit/index.php?templateID=39&amp;p=myPage\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (114,1,1136742478,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://127.0.0.1/svn/ctree/trunk/toolkit/index.php?templateID=39&amp;p=myPage\">Google link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (115,1,1136742600,'<h1>MOOO!!</h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://127.0.0.1/svn/ctree/trunk/toolkit/index.php?templateID=39&amp;p=myPage\">Test link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (117,12,1136762207,'MOOOO',2);
INSERT INTO cmscontent VALUES (118,12,1136762219,'sdfsdfsdfsdfdsf',2);
INSERT INTO cmscontent VALUES (119,12,1136763454,'sdfsdfsdfsdfdsf<br /><br /><a href=\"http://127\\.0\\.0\\.1/svn/ctree/trunk/toolkit/index\\.php\\?templateID=39&amp;p=A_page¬called_moo\">A link to a new page</a>',2);
INSERT INTO cmscontent VALUES (120,12,1136763474,'sdfsdfsdfsdfdsf<br /><br /><a href=\"http://127\\.0\\.0\\.1/svn/ctree/trunk/toolkit/index\\.php\\?templateID=39&amp;p=A_page¬called_moo\">A link to a new page</a>',2);
INSERT INTO cmscontent VALUES (121,12,1136764121,'sdfsdfsdfsdfdsf<br /><br /><a href=\"http://127\\.0\\.0\\.1/svn/ctree/trunk/toolkit/index\\.php\\?templateID=39&amp;p=A_page¬called_moo\">A link to a new page</a>',2);
INSERT INTO cmscontent VALUES (122,12,1136764146,'sdfsdfsdfsdfdsf<br /><br /><a href=\"?templateID=39&amp;p=a_test_page\">A link to a new page</a>',2);
INSERT INTO cmscontent VALUES (123,13,1136764318,'This is the main page!!!!',2);
INSERT INTO cmscontent VALUES (124,1,1136764349,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"http://127.0.0.1/svn/ctree/trunk/toolkit/index.php?templateID=39&amp;p=myPage\">Test link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (125,1,1136764367,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (126,1,1136764645,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li><strong><em>Anchors should not be avaliable!</em></strong></li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><br /><br style=\"text-decoration: line-through;\" /><span style=\"text-decoration: line-through;\">Yeah but it\'s bloody cool. :D</span>',2);
INSERT INTO cmscontent VALUES (127,14,1136764664,'moo',2);
INSERT INTO cmscontent VALUES (128,14,1136764710,'<a href=\"?templateID=39&amp;p=matts_page\">moo</a>',2);
INSERT INTO cmscontent VALUES (129,1,1136770567,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2);
INSERT INTO cmscontent VALUES (130,1,1136771255,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2);
INSERT INTO cmscontent VALUES (131,1,1136771300,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2);
INSERT INTO cmscontent VALUES (132,1,1137705927,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=Moo_Page,_a_page_about_cows\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2);
INSERT INTO cmscontent VALUES (133,15,1137705947,'They go moo',2);
INSERT INTO cmscontent VALUES (134,1,1137707355,'<h1>The Main Page!!<br /></h1>\r\nNotes for FCKEditor:<br />\r\n<div style=\"margin-left: 40px;\">\r\n<ul>\r\n    <li>Anchors should not be avaliable!</li>\r\n</ul>\r\n</div>\r\n<a href=\"?templateID=39&amp;p=A_new_page\">Existing page</a><br /><br /><a href=\"?templateID=39&amp;p=test_page\">Test link</a><span style=\"text-decoration: line-through;\"><br /></span>',2);

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

INSERT INTO cmsregions VALUES (1,'A basic test',8,8,'TKWiki','TKWiki');
INSERT INTO cmsregions VALUES (23,'A_new_page',8,8,'TKWiki','TKWiki');
INSERT INTO cmsregions VALUES (12,'test_page',8,8,'TKWiki','TKWiki');
INSERT INTO cmsregions VALUES (13,'Main_Page',8,8,'TKWiki','TKWiki');
INSERT INTO cmsregions VALUES (14,'a_test_page',8,8,'TKWiki','TKWiki');
INSERT INTO cmsregions VALUES (15,'Moo_Page,_a_page_about_cows',8,8,'TKWiki','TKWiki');
INSERT INTO cmsregions VALUES (39,'Non_existant_page',8,8,'TKWiki','TKWiki');
INSERT INTO cmsregions VALUES (40,'moo',8,8,'TKWiki','TKWiki');


CREATE TABLE fieldvalidators (
  ruleid int NOT NULL default '0',
  vrclassname varchar(45) NOT NULL default '',
  description text NOT NULL,
  modulename varchar(16) NOT NULL default ''
);

INSERT INTO fieldvalidators VALUES (1,'EmailValidator','Validate an email address','MVC');
NSERT INTO fieldvalidators VALUES (2,'PasswordValidator','Check that a new password matches security criteria','Auth');
INSERT INTO fieldvalidators VALUES (3,'AttemptLogin','Attempt to login username/password (user taken from $fieldData)','Auth');
INSERT INTO fieldvalidators VALUES (4,'UniqueUsername','Check that a username is unique','Auth');
INSERT INTO fieldvalidators VALUES (5,'NoTemplatesInRealm','Check that a realm does not have any templates within it. This should be used before deletion','Auth');
INSERT INTO fieldvalidators VALUES (6,'NoSubRealmsInRealm','Check that a realm does not conatain any sub/child templates. This should be used before deletion','Auth');
INSERT INTO fieldvalidators VALUES (7,'ValidUnusedTplFile','Check that a template file exists and is not in use','MVC');
INSERT INTO fieldvalidators VALUES (8,'CMSContentValidator','Ensures that a user has only submitted HTML tags that are avaliable on the toolbar shown','CMS');
INSERT INTO fieldvalidators VALUES (12,'IntValidator','Ensures that the data represents an integer','');
INSERT INTO fieldvalidators VALUES (10,'EmptyStringValidator','Ensures that a string is not empty','tkfecommon');
INSERT INTO fieldvalidators VALUES (11,'StringValidator','Ensures that the data represents a string','tkfecommon');


CREATE TABLE formfields (
  fieldid serial NOT NULL,
  formname varchar(32) NOT NULL default '',
  fieldname varchar(32) NOT NULL default '',
  ruleid int NOT NULL default '0',
  modulename varchar(16) NOT NULL default '',
  PRIMARY KEY  (fieldid)
);

INSERT INTO formfields VALUES (3,'loginForm','authPassword',3,'Auth');
INSERT INTO formfields VALUES (8,'groupRealmForm','rguid',10,'Auth');
INSERT INTO formfields VALUES (9,'groupRealmForm','task',11,'Auth');
INSERT INTO formfields VALUES (4,'groupSelForm','groupToEdit',10,'Auth');
INSERT INTO formfields VALUES (6,'groupDeleteForm','groupToEdit',10,'Auth');
INSERT INTO formfields VALUES (5,'groupDetailsForm','groupToEdit',10,'Auth');

CREATE TABLE forms (
  formid serial NOT NULL,
  formname varchar(32) NOT NULL default '',
  modelclass varchar(32) NOT NULL default '',
  modulename varchar(32) NOT NULL default '',
  realmid int NOT NULL default '0',
  validatorname varchar(32) default NULL,
  validatormodule varchar(32) default NULL,
  PRIMARY KEY  (formid)
);

INSERT INTO forms VALUES (1,'loginForm','LoginModel','Auth',8,NULL,NULL);
INSERT INTO forms VALUES (3,'groupDetailsForm','GroupModel','Auth',8,NULL,NULL);
INSERT INTO forms VALUES (6,'groupSelForm','GroupModel','Auth',8,NULL,NULL);
INSERT INTO forms VALUES (4,'groupRealmForm','GroupModel','Auth',8,NULL,NULL);
INSERT INTO forms VALUES (7,'addGroupForm','GroupModel','Auth',8,NULL,NULL);
INSERT INTO forms VALUES (8,'groupDeleteForm','GroupModel','Auth',8,NULL,NULL);
INSERT INTO forms VALUES (10,'addRealmSelForm','RealmModel','Auth',8,NULL,NULL);
INSERT INTO forms VALUES (14,'modifyRealmDetailsForm','RealmModel','Auth',8,NULL,NULL);
INSERT INTO forms VALUES (11,'realmDeleteForm','RealmModel','Auth',8,NULL,NULL);
INSERT INTO forms VALUES (12,'addRealmDetailsForm','RealmModel','Auth',8,NULL,NULL);
INSERT INTO forms VALUES (13,'realmDeleteForm','RealmModel','Auth',8,NULL,NULL);
INSERT INTO forms VALUES (15,'userPermissionForm','UserModel','Auth',8,NULL,NULL);
INSERT INTO forms VALUES (18,'userDeleteForm','UserModel','Auth',8,NULL,NULL);
INSERT INTO forms VALUES (17,'modifyUserDetailsForm','UserModel','Auth',8,NULL,NULL);
INSERT INTO forms VALUES (16,'addUserDetailsForm','UserModel','Auth',8,NULL,NULL);
INSERT INTO forms VALUES (19,'selectRegionForm','EditContentModel','CMS',8,NULL,NULL);
INSERT INTO forms VALUES (20,'regionModifyForm','EditContentModel','CMS',8,NULL,NULL);
INSERT INTO forms VALUES (21,'addPostTKNews','ProposeAddModel','TKNews',8,NULL,NULL);
INSERT INTO forms VALUES (22,'modifyPostDetailsForm','PostModfyModel','TKNews',8,NULL,NULL);
INSERT INTO forms VALUES (23,'boardPermForm','AuthModifyModel','TKNews',8,NULL,NULL);
INSERT INTO forms VALUES (24,'uploadFile','UploadModel','TKFile',8,NULL,NULL);
INSERT INTO forms VALUES (25,'applyForm','ApplyModel','OWW',8,NULL,NULL);
INSERT INTO forms VALUES (26,'UWSUReturnForm','UWSUReturnModel','OWW',8,NULL,NULL);
INSERT INTO forms VALUES (27,'inlineEdit','EditContentModel','CMS',8,NULL,NULL);
INSERT INTO forms VALUES (28,'newPageForm','NewPageModel','TKWiki',8,NULL,NULL);
INSERT INTO forms VALUES (29,'pageForm','PageModel','TKWiki',8,NULL,NULL);

/*!40000 ALTER TABLE forms ENABLE KEYS */;

--
-- Table structure for table groups
--


CREATE TABLE groups (
  groupid serial NOT NULL,
  groupname varchar(255) NOT NULL default '',
  description varchar(128) NOT NULL default '',
  open smallint NOT NULL default '0',
  PRIMARY KEY  (groupid)
);


INSERT INTO groups VALUES (1,'Administrators','The group for admins',0);
INSERT INTO groups VALUES (2,'Users','A group for users',0);


CREATE TABLE logentries (
  entryid serial NOT NULL,
  message text NOT NULL,
  level varchar(16) NOT NULL default '',
  module varchar(16) default NULL,
  notes text,
  notify_date timestamp(8) DEFAULT now() NOT NULL,
  PRIMARY KEY  (entryid)
);

CREATE TABLE realmgrouplink (
  groupid int NOT NULL default '0',
  realmid int NOT NULL default '0',
  allow char(1) default NULL,
  PRIMARY KEY  (groupid,realmid)
);

--
-- Dumping data for table realmgrouplink
--


/*!40000 ALTER TABLE realmgrouplink DISABLE KEYS */;

INSERT INTO realmgrouplink VALUES (1,1,'y');
INSERT INTO realmgrouplink VALUES (1,35,'y');
INSERT INTO realmgrouplink VALUES (2,2,'y');
INSERT INTO realmgrouplink VALUES (2,8,'y');
INSERT INTO realmgrouplink VALUES (2,34,'y');
INSERT INTO realmgrouplink VALUES (2,37,'n');
INSERT INTO realmgrouplink VALUES (1,46,'y');
INSERT INTO realmgrouplink VALUES (1,51,'y');
INSERT INTO realmgrouplink VALUES (2,50,'y');
INSERT INTO realmgrouplink VALUES (1,47,'y');
INSERT INTO realmgrouplink VALUES (1,49,'y');
INSERT INTO realmgrouplink VALUES (1,48,'y');
INSERT INTO realmgrouplink VALUES (1,52,'y');

/*!40000 ALTER TABLE realmgrouplink ENABLE KEYS */;

--
-- Table structure for table realms
--


CREATE TABLE realms (
  realmid serial NOT NULL,
  name varchar(32) NOT NULL default '',
  parentid int NOT NULL default '0',
  description varchar(128) default NULL,
  depth smallint default NULL,
  realmpath varchar(255) default NULL,
  PRIMARY KEY  (realmid)
);

--
-- Dumping data for table realms
--


/*!40000 ALTER TABLE realms DISABLE KEYS */;
INSERT INTO realms VALUES (1,'Administration',0,'Realm Administration',0,'01');
INSERT INTO realms VALUES (2,'User',0,'User realm',0,'02');
INSERT INTO realms VALUES (5,'Vote',2,'User voting realm',1,'02.05');
INSERT INTO realms VALUES (6,'Comment',2,'User commenting realm',1,'02.06');
INSERT INTO realms VALUES (7,'Email Updates',6,'Receive Email updates',2,'02.06.07');
INSERT INTO realms VALUES (8,'Site',0,'Public website',0,'08');
INSERT INTO realms VALUES (19,'Authentication',1,'Authentication configuration',1,'01.19');
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
INSERT INTO realms VALUES (32,'Templates',1,'',1,'01.32');
INSERT INTO realms VALUES (33,'Content',0,'A realm describing read/write access for the CMS module',0,'33');
INSERT INTO realms VALUES (34,'View',33,'',1,'33.34');
INSERT INTO realms VALUES (35,'Edit',33,'',1,'33.35');
INSERT INTO realms VALUES (40,'TKNews',0,'',0,'40');
INSERT INTO realms VALUES (41,'0',40,'',1,'40.41');
INSERT INTO realms VALUES (42,'1',40,'',1,'40.42');
INSERT INTO realms VALUES (43,'2',40,'',1,'40.43');
INSERT INTO realms VALUES (46,'View',42,'',2,'40.42.46');
INSERT INTO realms VALUES (47,'Post',42,'',2,'40.42.47');
INSERT INTO realms VALUES (48,'Admin',42,'',2,'40.42.48');
INSERT INTO realms VALUES (50,'View',43,'',2,'40.43.50');
INSERT INTO realms VALUES (51,'Post',43,'',2,'40.43.51');
INSERT INTO realms VALUES (52,'Admin',43,'',2,'40.43.52');
INSERT INTO realms VALUES (55,'Public Site',8,'Public Site for Visitors',1,'08.55');
INSERT INTO realms VALUES (56,'Private Site',8,'Viewable pages for all other users',1,'08.56');
INSERT INTO realms VALUES (57,'TKFile',0,'visitor',0,'57');
INSERT INTO realms VALUES (73,'Users',57,NULL,1,'57.73');
INSERT INTO realms VALUES (78,'visitor',73,NULL,2,'57.73.78');

CREATE TABLE realmuserlink (
  userid serial NOT NULL,
  realmid int NOT NULL default '0',
  allow char(1) default NULL,
  PRIMARY KEY  (userid,realmid)
);

--
-- Dumping data for table realmuserlink
--


/*!40000 ALTER TABLE realmuserlink DISABLE KEYS */;
INSERT INTO realmuserlink VALUES (3,6,'n');
INSERT INTO realmuserlink VALUES (5,8,'y');
INSERT INTO realmuserlink VALUES (14,2,'y');
INSERT INTO realmuserlink VALUES (14,5,'n');
INSERT INTO realmuserlink VALUES (14,7,'n');
INSERT INTO realmuserlink VALUES (5,34,'y');
INSERT INTO realmuserlink VALUES (1,49,'y');
INSERT INTO realmuserlink VALUES (1,52,'y');
INSERT INTO realmuserlink VALUES (22,46,'y');
INSERT INTO realmuserlink VALUES (22,47,'y');

/*!40000 ALTER TABLE realmuserlink ENABLE KEYS */;

--
-- Table structure for table sessions
--

CREATE TABLE sessions (
  sessionid serial NOT NULL,
  useragent varchar(128) NOT NULL default '',
  ip varchar(15) NOT NULL default '',
  rndidentifier varchar(14) NOT NULL default '',
  lastaccess varchar(12) NOT NULL default '',
  PRIMARY KEY  (sessionid)
);

CREATE TABLE sessionvalues (
  valueid serial NOT NULL,
  sessionid int NOT NULL default '0',
  skey varchar(32) NOT NULL default '',
  svalue bytea NOT NULL,
  PRIMARY KEY  (valueid)
);

CREATE TABLE templates (
  templateid serial NOT NULL,
  filename varchar(32) NOT NULL default '',
  viewerclassname varchar(32) NOT NULL default '',
  realmid int NOT NULL default '0',
  modulename varchar(16) NOT NULL default '',
  PRIMARY KEY  (templateid,filename)
);

INSERT INTO templates VALUES (27,'TitleViewer.tpl','TitleViewer',8,'TKNews');
INSERT INTO templates VALUES (2,'userModify.tpl','UserViewer',1,'Auth');
INSERT INTO templates VALUES (3,'groupModify.tpl','GroupViewer',1,'Auth');
INSERT INTO templates VALUES (4,'realmModify.tpl','RealmViewer',1,'Auth');
INSERT INTO templates VALUES (5,'utility/login.tpl','LoginViewer',8,'TKWiki');
INSERT INTO templates VALUES (6,'utility/permissionError.tpl','LoginViewer',8,'TKWiki');
INSERT INTO templates VALUES (7,'logout.tpl','LogoutViewer',8,'Auth');
INSERT INTO templates VALUES (8,'userAdd.tpl','UserViewer',1,'Auth');
INSERT INTO templates VALUES (9,'groupAdd.tpl','GroupViewer',1,'Auth');
INSERT INTO templates VALUES (10,'realmAdd.tpl','RealmViewer',1,'Auth');
INSERT INTO templates VALUES (11,'listTemplates.tpl','TemplateListViewer',1,'MVC');
INSERT INTO templates VALUES (12,'addTemplate.tpl','AddTemplateViewer',32,'MVC');
INSERT INTO templates VALUES (13,'editContentWindow.tpl','EditContentViewer',35,'CMS');
INSERT INTO templates VALUES (14,'editContent.tpl','EditContentViewer',35,'CMS');
INSERT INTO templates VALUES (15,'editContentWindow.rpl','editContentWindowViewer',35,'CMS');
INSERT INTO templates VALUES (16,'main.tpl','Viewer',8,'OWW');
INSERT INTO templates VALUES (17,'editorForm.tpl','EditorFormViewer',8,'CMS');
INSERT INTO templates VALUES (18,'UWSULogin.tpl','LoginViewer',8,'OWW');
INSERT INTO templates VALUES (19,'newUserInfo.tpl','Viewer',8,'CMS');
INSERT INTO templates VALUES (20,'rPermissionError.tpl','Viewer',8,'Auth');
INSERT INTO templates VALUES (21,'ProposePost.tpl','Viewer',8,'TKNews');
INSERT INTO templates VALUES (22,'postModify.tpl','PostModifyViewer',8,'TKNews');
INSERT INTO templates VALUES (23,'authModify.tpl','AuthModifyViewer',8,'TKNews');
INSERT INTO templates VALUES (24,'RaWFrontPage.tpl','Viewer',55,'RaW');
INSERT INTO templates VALUES (25,'ShortViewer.tpl','ShortViewer',8,'TKNews');
INSERT INTO templates VALUES (26,'Rexception.tpl','RenderedExceptionViewer',8,'Auth');
INSERT INTO templates VALUES (29,'LongViewer.tpl','LongViewer',8,'TKNews');
INSERT INTO templates VALUES (28,'RaWFullNews.tpl','Viewer',8,'RaW');
INSERT INTO templates VALUES (31,'ArchiveViewer.tpl','ArchiveViewer',8,'TKNews');
(30,'RaWArchiveNews.tpl','Viewer',8,'RaW');
INSERT INTO templates VALUES (32,'RaWProposeNews.tpl','Viewer',8,'RaW');
INSERT INTO templates VALUES (33,'RaWModifyPost.tpl','Viewer',8,'RaW');
INSERT INTO templates VALUES (34,'browse.tpl','BrowserViewer',8,'TKFile');
INSERT INTO templates VALUES (35,'upload.tpl','TKFileViewer',8,'TKFile');
INSERT INTO templates VALUES (36,'fileInfo.tpl','FileInfoViewer',8,'TKFile');
INSERT INTO templates VALUES (37,'apply.tpl','ApplyViewer',8,'OWW');
INSERT INTO templates VALUES (38,'viewApplications.tpl','ApplicationsViewer',8,'OWW');
INSERT INTO templates VALUES (39,'page.tpl','PageViewer',8,'TKWiki');
INSERT INTO templates VALUES (40,'edit.tpl','Viewer',8,'TKWiki');
INSERT INTO templates VALUES (41,'fckWindows/link.tpl','fckWindows/LinkViewer',8,'TKWiki');
INSERT INTO templates VALUES (42,'newPage.tpl','NewPageViewer',8,'TKWiki');
INSERT INTO templates VALUES (43,'admin/changePagePerms.tpl','admin/PagePermsViewer',8,'TKWiki');
 
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
  status smallint NOT NULL default '1',
  PRIMARY KEY  (userid,groupid)
);

INSERT INTO usergrouplink VALUES (1,1,1);
INSERT INTO usergrouplink VALUES (1,2,1);
INSERT INTO usergrouplink VALUES (2,2,1);
INSERT INTO usergrouplink VALUES (3,2,1);
INSERT INTO usergrouplink VALUES (4,2,1);
INSERT INTO usergrouplink VALUES (8,2,1);
INSERT INTO usergrouplink VALUES (12,2,1);
INSERT INTO usergrouplink VALUES (13,2,1);
INSERT INTO usergrouplink VALUES (20,2,1);
INSERT INTO usergrouplink VALUES (21,2,1);
INSERT INTO usergrouplink VALUES (21,1,1);
INSERT INTO usergrouplink VALUES (22,1,1);
INSERT INTO usergrouplink VALUES (22,2,1);

CREATE TABLE users (
  userid serial NOT NULL,
  username varchar(50) NOT NULL default '',
  password varchar(50) NOT NULL default '',
  password_temp varchar(50) NOT NULL default '',
  firstName varchar(32) default NULL,
  lastName varchar(32) default NULL,
  email varchar(100) NOT NULL default '',
  email_temp varchar(110) NOT NULL default '',
  hide_email smallint NOT NULL default '0',
  active smallint NOT NULL default '0',
  user_data text NOT NULL,
  signature text NOT NULL,
  threaded_list smallint NOT NULL default '0',
  posts int NOT NULL default '0',
  admin smallint NOT NULL default '0',
  threaded_read smallint NOT NULL default '0',
  date_added int NOT NULL default '0',
  date_last_active int NOT NULL default '0',
  last_active_forum int NOT NULL default '0',
  hide_activity smallint NOT NULL default '0',
  PRIMARY KEY  (userid),
  UNIQUE (username)
);

INSERT INTO users VALUES (1,'adam','5f4dcc3b5aa765d61d8327deb882cf99','5f4dcc3b5aa765d61d8327deb882cf99','Adam','Charnock','adam@cheesetree.com','adam@cheesetree.com',0,1,'','',0,0,1,0,1123752213,1123752213,0,0);
INSERT INTO users VALUES (2,'visitor','','','','','','',1,1,'','',0,0,0,0,1123752213,1123752213,0,0);
INSERT INTO users VALUES (21,'0325391','','','Adam','Charnock','adam@cheesetree.com','',0,1,'','',0,0,1,0,1123752213,1123752213,0,0);
INSERT INTO users VALUES (22,'phil','5f4dcc3b5aa765d61d8327deb882cf99','','phil','sharpe','','',0,0,'','',0,0,0,0,0,0,0,0);


