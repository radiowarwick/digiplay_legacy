-- inserts for dir(parent,name,notes)
insert into dir values ( 1,-1,'Digiplay','Root node of virtual directory system.' ) ;
insert into dir values ( 2,-2,'Music','Root node of music library.' ) ;
insert into dir values ( 3,-3,'Bin','Root node for audio items to be removed.' ) ;
insert into dir values ( 4,1,'Adverts','Radio station advertisements.' ) ;
insert into dir values ( 5,1,'Departments','Department audio files.' ) ;
insert into dir values ( 6,1,'Jingles','Radio station ident clips.' ) ;
insert into dir values ( 7,1,'Users','User home directories.' ) ;
alter sequence dir_id_seq restart 8;

-- inserts for users(username)
insert into users values ( 1,'System' ) ;
insert into users values ( 2,'Guest' ) ;
alter sequence users_id_seq restart 3;

-- inserts for groups(name,description)
insert into groups values ( 1,'Everyone','All users on the system belong to this group' ) ;
insert into groups values ( 2,'Administrators','Users who can administer the system' ) ;
alter sequence groups_id_seq restart 3;

-- inserts for configs(name,description)
insert into configs values ( 1,'default_cartset','The cartset to be loaded when the user logs in' ) ;
insert into configs values ( 2,'user_lastlogin','The users last login time on the website' ) ;
insert into configs values ( 3,'user_curlogin','The time of the users current login' ) ;
alter sequence configs_id_seq restart 4;

-- inserts for dirgroups
insert into dirgroups values ( 1,1,1,'10000000' ) ;
insert into dirgroups values ( 2,1,2,'11000000' ) ;
insert into dirgroups values ( 3,2,1,'10000000' ) ;
insert into dirgroups values ( 4,3,2,'10000000' ) ;
insert into dirgroups values ( 5,4,1,'10000000' ) ;
insert into dirgroups values ( 6,4,2,'11000000' ) ;
insert into dirgroups values ( 7,5,1,'10000000' ) ;
insert into dirgroups values ( 8,5,2,'11000000' ) ;
insert into dirgroups values ( 9,6,1,'10000000' ) ;
insert into dirgroups values ( 10,6,2,'11000000' ) ;
insert into dirgroups values ( 11,7,1,'10000000' ) ;
insert into dirgroups values ( 12,7,2,'11000000' ) ;
alter sequence dirgroups_id_seq restart 13;

-- inserts for usersgroups(groupid,userid)
insert into usersgroups values ( 1,1,1 ) ;
insert into usersgroups values ( 2,2,1 ) ;
alter sequence usersgroups_id_seq restart 3;

-- inserts for cartproperties(name,note)
insert into cartproperties values ( 1,'ForeColourRGB','Button text colour.' ) ;
insert into cartproperties values ( 2,'BackColourRGB','Button background colour.' ) ;
insert into cartproperties values ( 3,'Font','Text font.' ) ;
insert into cartproperties values ( 4,'FontSize','Text font size.' ) ;
insert into cartproperties values ( 5,'FontBold','Bold text.' ) ;
insert into cartproperties values ( 6,'FontItalic','Italic text.' ) ;
alter sequence cartproperties_id_seq restart 7;

-- inserts for cartstyles(name,description)
insert into cartstyles values ( 1,'Blue','Blue background with black text.' ) ;
insert into cartstyles values ( 2,'RaW Purple','RaW design.' ) ;
insert into cartstyles values ( 3,'Cool Green','Bluish-green background with black text.' ) ;
insert into cartstyles values ( 4,'Bright Green','Green background with black text.' ) ;
alter sequence cartstyles_id_seq restart 5;

-- inserts for cartstylepropsg
insert into cartstyleprops values ( 1,1,1,0 ) ;
insert into cartstyleprops values ( 2,1,2,1214912 ) ;
insert into cartstyleprops values ( 3,2,1,0 ) ;
insert into cartstyleprops values ( 4,2,2,11731183 ) ;
insert into cartstyleprops values ( 5,3,1,0 ) ;
insert into cartstyleprops values ( 6,3,2,49245 ) ;
insert into cartstyleprops values ( 7,4,1,0 ) ;
insert into cartstyleprops values ( 8,4,2,8044544 ) ;
alter sequence cartstyleprops_id_seq restart 9;

-- inserts for audiotypes(name,description)
insert into audiotypes values ( 1,'Music','Music tracks from the CD library or other sources.' ) ;
insert into audiotypes values ( 2,'Jingle','Station or show specific idents.' ) ;
insert into audiotypes values ( 3,'Advert','Advertisement audio clip.' ) ;
alter sequence audiotypes_id_seq restart 4;

-- inserts for lifespansg
insert into lifespans values ( 1,'Permanent','-1','Audio files (e.g. music) which should remain on the system indefinitely.' ) ;
insert into lifespans values ( 2,'Week','604800','Files which may be removed after one week. e.g. one-off show feature.' ) ;
insert into lifespans values ( 3,'Month','2678400','Files which may be removed after 31 days. e.g. event preview clip.' ) ;
insert into lifespans values ( 4,'6-month','15552000','Files which may be removed after 180 days. e.g. time-dependent advertisment.' ) ;
insert into lifespans values ( 5,'Year','31536000','Files which may be removed after 365 days.' ) ;
alter sequence lifespans_id_seq restart 6;

-- inserts for jingletypes(name,description)
insert into jingletypes values ( 1,'Generic','Unclassified' ) ;
insert into jingletypes values ( 2,'Idents','Station Identification' ) ;
insert into jingletypes values ( 3,'Contact','Contact Information' ) ;
insert into jingletypes values ( 4,'News','News Ident' ) ;
insert into jingletypes values ( 5,'Show','Show Identification' ) ;
insert into jingletypes values ( 6,'Event','Event Information' ) ;
alter sequence jingletypes_id_seq restart 7;

-- inserts for albums(name)
insert into albums values ( 1,'(none)' ) ;
alter sequence albums_id_seq restart 2;

-- inserts for configuration
insert into configuration values ( 1,0,'ldap_host','localhost' ) ;
insert into configuration values ( 2,0,'ldap_port','389' ) ;
insert into configuration values ( 3,0,'ldap_dn','ou=People,dc=example,dc=com' ) ;
insert into configuration values ( 4,0,'channel_1','/dev/dsp' ) ;
insert into configuration values ( 5,0,'bin_weighting_1','5' ) ;
insert into configuration values ( 6,0,'bin_weighting_2','9' ) ;
insert into configuration values ( 7,0,'bin_weighting_3','12' ) ;
insert into configuration values ( 8,0,'bin_weighting_4','14' ) ;
insert into configuration values ( 9,0,'bin_weighting_5','15' ) ;
alter sequence configuration_id_seq restart 10;

-- inserts for patches(branch,version)
insert into patches values ( 1,'dps',0 ) ;
insert into patches values ( 2,'web',0 ) ;
alter sequence patches_id_seq restart 3;


-- WEBSITE STUFF
-- realms
INSERT INTO realms VALUES (1, 'Administration', 0, 'Realm Administration', 0, '01');
INSERT INTO realms VALUES (2, 'Site', 0, 'Public website', 0, '02');
INSERT INTO realms VALUES (3, 'DPS', 0, 'DPS Root Realm', 0, '03');
INSERT INTO realms VALUES (4, 'Authentication', 1, 'Authentication configuration', 1, '01.04');
INSERT INTO realms VALUES (5, 'Users', 4, 'User Administration', 2, '01.04.05');
INSERT INTO realms VALUES (6, 'Groups', 4, 'Group Administration', 2, '01.04.06');
INSERT INTO realms VALUES (7, 'Realms', 4, 'Realm Administration', 2, '01.04.07');
INSERT INTO realms VALUES (8, 'Add', 5, '', 3, '01.04.05.08');
INSERT INTO realms VALUES (9, 'Modify', 5, '', 3, '01.04.05.09');
INSERT INTO realms VALUES (10, 'Delete', 5, '', 3, '01.04.05.10');
INSERT INTO realms VALUES (11, 'Add', 6, '', 3, '01.04.06.11');
INSERT INTO realms VALUES (12, 'Modify', 6, '', 3, '01.04.06.12');
INSERT INTO realms VALUES (13, 'Delete', 6, '', 3, '01.04.06.13');
INSERT INTO realms VALUES (14, 'Add', 7, '', 3, '01.04.07.14');
INSERT INTO realms VALUES (15, 'Modify', 7, '', 3, '01.04.07.15');
INSERT INTO realms VALUES (16, 'Delete', 7, '', 3, '01.04.07.16');
INSERT INTO realms VALUES (22, 'Studio', 3, 'Alter Studio stuff', 1, '03.21');
INSERT INTO realms VALUES (35, 'Studio Cartwall', 21, 'Alter the studio cartwall', 2, '03.21.34');
INSERT INTO realms VALUES (17, 'Templates', 1, '', 1, '01.17');
INSERT INTO realms VALUES (18, 'Public Site', 2, 'Public site for visitors', 1, '02.18');
INSERT INTO realms VALUES (19, 'Private Site', 2, 'Viewable pages for all other users', 1, '02.19');
INSERT INTO realms VALUES (20, 'Sue', 3, 'DPS Root Sue', 1, '03.20');
INSERT INTO realms VALUES (24, 'Edit Sue Playlist', 20, 'DPS Edit Sue Track', 2, '03.20.24');
INSERT INTO realms VALUES (25, 'View Sue Statistics', 20, 'DPS View Sue stats', 2, '03.20.25');
INSERT INTO realms VALUES (26, 'View Sue Playlist', 20, 'DPS View Sue playlist', 2, '03.20.26');
INSERT INTO realms VALUES (21, 'Music Library', 3, 'DPS Root Music Library', 1, '03.21');
INSERT INTO realms VALUES (27, 'Edit Track', 21, 'DPS Edit Track', 2, '03.21.27');
INSERT INTO realms VALUES (28, 'Search Track', 21, 'DPS Search Track', 2, '03.21.28');
INSERT INTO realms VALUES (29, 'Request Track', 21, 'DPS Request Track', 2, '03.21.29');
INSERT INTO realms VALUES (30, 'Censor Track', 21, 'DPS Censor track', 2, '03.21.30');
INSERT INTO realms VALUES (31, 'Remove Track Request', 21, 'DPS Remove a track request', 2, '03.21.31');
INSERT INTO realms VALUES (32, 'Delete Track', 21, 'Delete a track from the system', 2, '03.21.32');
INSERT INTO realms VALUES (33, 'Playlist', 21, 'Playlist', 2, '03.21.33');
INSERT INTO realms VALUES (34, 'Comment Track', 21, 'Comment on a track', 2, '03.21.34');
INSERT INTO realms VALUES (23, 'CMS', 3, 'CMS Regions', 1, '03.23');
INSERT INTO realms VALUES (36, 'Edit Help', 23, 'Edit the help pages', 2, '03.23.36');
INSERT INTO realms VALUES (37, 'Edit Music', 23, 'Edit the music page', 2, '03.23.37');
INSERT INTO realms VALUES (38, 'Edit Sue', 23, 'Edit the sue page', 2, '03.23.38');
INSERT INTO realms VALUES (39, 'Edit Studio', 23, 'Edit the studio page', 2, '03.23.39');
INSERT INTO realms VALUES (40, 'Edit Show', 23, 'Edit the show page', 2, '03.23.40');
INSERT INTO realms VALUES (41, 'Edit Logout', 23, 'Edit the logout page', 2, '03.23.41');
INSERT INTO realms VALUES (42, 'Edit Home', 23, 'Edit the home page', 2, '03.23.42');
INSERT INTO realms VALUES (43, 'Report Track', 21, 'DPS Report Track', 2, '03.21.43');
ALTER SEQUENCE realms_realmid_seq RESTART 44;

-- realmuserlink
INSERT INTO realmuserlink VALUES (2, 18, 'y');

-- realmgrouplink
INSERT INTO realmgrouplink VALUES (1, 28, 'y');
INSERT INTO realmgrouplink VALUES (1, 29, 'y');
INSERT INTO realmgrouplink VALUES (1, 43, 'y');
INSERT INTO realmgrouplink VALUES (1, 19, 'y');
INSERT INTO realmgrouplink VALUES (1, 18, 'y');
INSERT INTO realmgrouplink VALUES (1, 25, 'y');
INSERT INTO realmgrouplink VALUES (1, 26, 'y');
INSERT INTO realmgrouplink VALUES (1, 34, 'y');
INSERT INTO realmgrouplink VALUES (2, 1, 'y');
INSERT INTO realmgrouplink VALUES (2, 3, 'y');
INSERT INTO realmgrouplink VALUES (2, 2, 'y');

-- cmsregions
INSERT INTO cmsregions VALUES (1, 'Help Page', 36, 18, 'cms_simple', 'cms_safe');
INSERT INTO cmsregions VALUES (3, 'Sue Page', 38, 18, 'cms_simple', 'cms_safe');
INSERT INTO cmsregions VALUES (4, 'Studio Page', 39, 18, 'cms_simple', 'cms_safe');
INSERT INTO cmsregions VALUES (5, 'Show Page', 40, 18, 'cms_simple', 'cms_safe');
INSERT INTO cmsregions VALUES (2, 'Music Page', 37, 18, 'cms_simple', 'cms_safe');
INSERT INTO cmsregions VALUES (6, 'Public Help', 36, 18, 'cms_simple', 'cms_safe');
INSERT INTO cmsregions VALUES (7, 'Logout Page', 41, 18, 'cms_simple', 'cms_safe');
INSERT INTO cmsregions VALUES (8, 'Home Page', 42, 18, 'cms_none', 'cms_safe');
ALTER SEQUENCE cmsregions_regionid_seq RESTART 9;

-- cmscontent
INSERT INTO cmscontent VALUES (1, 1, 1161100854, '<div align="center"><strong>The RaW Digiplay Management system</strong><br /></div><br />This is a Beta version of the new RaW Digiplay web management system. This means that it is likely that you will encounter some problems.<br /><br />Please forward any queries you have to the <a href="mailto:webmaster@warwick.ac.uk?subject=%5BDPS%20-%20Help%5D%20Query">webmaster</a>.<br /><br />If you receive an Authentication error when trying to access a page you beleive you should have access to please also contact the <a href="mailto:webmaster@warwick.ac.uk?subject=%5BDPS%20-%20Help%5D%20">webmaster</a>.', 1);
INSERT INTO cmscontent VALUES (2, 2, 1161101112, '<div align="center"><strong>The Music Library<br /></strong><div align="left"><br />The music library section of the webpage allows you to edit and manage the RaW Music library, including:<br /></div><div align="left"><ul>    <li>Search the library</li>    <li>Editing track information</li>    <li>Commenting on track</li>    <li>Reporting tracks as unsuitable</li>    <li>Requesting new tracks for the library</li>    <li>And much more ...</li></ul>Watch this space for new and exciting developments.</div></div>', 1);
INSERT INTO cmscontent VALUES (3, 5, 1161101557, '<div align="center"><strong>RaW Show Plans<br /></strong><div align="left"><br />The show plan section of this webpage is still in development but will soon allow you to create and plan personal showplans that you can load directly into the studio. This will allow you to create scripts incorperating:<br /></div><div align="left"><ul>    <li>Tracks from the Library<br />    </li>    <li>Scripts<br />    </li>    <li>Link information<br />    </li>    <li>External tracks</li></ul>Watch this space for new and exciting developments.</div></div>', 1);
INSERT INTO cmscontent VALUES (4, 3, 1161102133, '<div align="center"><strong>Sue Stamp Manager</strong><br /><strong><br /></strong><div align="left"><div align="center"><strong></strong><div align="left">This section of the webpage allows you to manage RaW''s sustainer service (sue) It also allows you to view some statistics regarding the service.<br /><br />If you feel that you should have access to these tools please contact the <a href="mailto:webmaster@radio.warwick.ac.uk?subject=%5BDPS%20-%20Access%5D">webmaster</a>.<br /></div></div></div></div>', 1);
INSERT INTO cmscontent VALUES (5, 4, 1161102371, '<div align="center"><strong>The Studio Cartwalls<br /></strong><div align="left"><br />This section allows you to build your own personal cartwalls that can then be loaded into the studio cartwall. It provides access to:<br /><ul>    <li>Create new cartsets</li>    <li>Load in custom jingles</li>    <li>Select from a variety of button styles</li>    <li>View the current Station cartset</li>    <li>Manage the current Station cartset</li></ul></div></div>', 14);
INSERT INTO cmscontent VALUES (6, 6, 1168011808, '<div align="center"><strong>Public Help</strong><br /></div><br />This help will be available in the near future. In the meantime if you need help please contact the webmaster <a href="mailto:webmaster@radio.warwick.ac.uk?subject=DPS%20Website%20-%20Help">here</a>.', 1);
INSERT INTO cmscontent VALUES (7, 7, 1168015727, '<div align="center"><strong>You are now logged out</strong><br /></div><strong><br /></strong><div align="left">Click <a href="https://www.radio.warwick.ac.uk">here</a> to go to the main RaW page.<br /></div><div align="left">Click <a href="https://www.radio.warwick.ac.uk/dps-dev/">here</a> to return to the Digiplay login page.</div>', 1);
INSERT INTO cmscontent VALUES (8, 8, 1171467945, '<strong>Other Features<br /></strong><a href="https://www.radio.warwick.ac.uk/dps-dev/?templateID=59">Requested Tracks</a><br /><a href="http://www.radio.warwick.ac.uk/dps-dev/?templateID=52">Censored Tracks<br /></a>', 1);
ALTER SEQUENCE cmscontent_contentid_seq RESTART 9;

-- fieldvalidators
INSERT INTO fieldvalidators VALUES (1, 'EmailValidator', 'Validate an email address', 'MVC');
INSERT INTO fieldvalidators VALUES (2, 'DPSUserDirWriteValidator', 'Checks that the user has write permissions on a directory', 'DPS');
INSERT INTO fieldvalidators VALUES (3, 'AttemptLogin', 'Attempt to login username/password (user taken from $fieldData)', 'Auth');
INSERT INTO fieldvalidators VALUES (4, 'UniqueUsername', 'Check that a username is unique', 'Auth');
INSERT INTO fieldvalidators VALUES (5, 'NoTemplatesInRealm', 'Check that a realm does not have any templates within it. This should be used before deletion', 'Auth');
INSERT INTO fieldvalidators VALUES (6, 'NoSubRealmsInRealm', 'Check that a realm does not conatain any sub/child templates. This should be used before deletion', 'Auth');
INSERT INTO fieldvalidators VALUES (7, 'ValidUnusedTplFile', 'Check that a template file exists and is not in use', 'MVC');
INSERT INTO fieldvalidators VALUES (8, 'CMSContentValidator', 'Ensures that a user has only submitted HTML tags that are avaliable on the toolbar shown', 'CMS');
INSERT INTO fieldvalidators VALUES (9, 'DPSUserAudioOwnValidator', 'Checks a user owns an audio file', 'DPS');
INSERT INTO fieldvalidators VALUES (12, 'IntValidator', 'Ensures that the data represents an integer', '');
INSERT INTO fieldvalidators VALUES (10, 'EmptyStringValidator', 'Ensures that a string is not empty', 'tkfecommon');
INSERT INTO fieldvalidators VALUES (11, 'StringValidator', 'Ensures that the data represents a string', 'tkfecommon');
INSERT INTO fieldvalidators VALUES (13, 'DPSMusicSearchTypeValidator', 'Checks if the field is set to (Both, Artist, Title)', 'DPS');
INSERT INTO fieldvalidators VALUES (14, 'DPSRequestTitleValidator', 'Checks that the field is a string and not set to Title', 'DPS');
INSERT INTO fieldvalidators VALUES (15, 'DPSRequestArtistValidator', 'Checks that the field is a string and not set to Artist', 'DPS');
INSERT INTO fieldvalidators VALUES (16, 'DPSSystemCartsetEditValidator', 'Checks system can edit a cartset', 'DPS');
INSERT INTO fieldvalidators VALUES (17, 'DPSSystemCartwallEditValidator', 'Checks system can edit a cartset', 'DPS');
INSERT INTO fieldvalidators VALUES (18, 'DPSSystemCartEditValidator', 'Checks system can edit a cartset', 'DPS');
INSERT INTO fieldvalidators VALUES (19, 'DPSUserCartsetEditValidator', 'Checks user can edit a cartset', 'DPS');
INSERT INTO fieldvalidators VALUES (20, 'DPSUserCartwallEditValidator', 'Checks user can edit a cartset', 'DPS');
INSERT INTO fieldvalidators VALUES (21, 'DPSUserCartEditValidator', 'Checks user can edit a cartset', 'DPS');
INSERT INTO fieldvalidators VALUES (22, 'DPSSystemCartsetOwnValidator', 'Checks system owns a cartset', 'DPS');
INSERT INTO fieldvalidators VALUES (23, 'DPSSystemCartwallOwnValidator', 'Checks system owns a cartset', 'DPS');
INSERT INTO fieldvalidators VALUES (24, 'DPSUserAudioEditValidator', 'Checks a user can write to an audio file', 'DPS');
INSERT INTO fieldvalidators VALUES (25, 'DPSSystemCartOwnValidator', 'Checks system owns a cartset', 'DPS');
INSERT INTO fieldvalidators VALUES (26, 'DPSUserCartsetOwnValidator', 'Checks user owns a cartset', 'DPS');
INSERT INTO fieldvalidators VALUES (27, 'DPSUserCartwallOwnValidator', 'Checks user owns a cartset', 'DPS');
INSERT INTO fieldvalidators VALUES (28, 'DPSUserCartOwnValidator', 'Checks user owns a cartset', 'DPS');
INSERT INTO fieldvalidators VALUES (29, 'DPSSystemCartsetReadValidator', 'Checks system can read a cartset', 'DPS');
INSERT INTO fieldvalidators VALUES (30, 'DPSUserCartsetReadValidator', 'Checks user can read a cartset', 'DPS');
INSERT INTO fieldvalidators VALUES (31, 'DPSJAAudioIDValidator', 'Checks that an audio id isa jingle or advert', 'DPS');
INSERT INTO fieldvalidators VALUES (32, 'DPSUserDirDelValidator', 'Checks that the user can delete a dir', 'DPS');
INSERT INTO fieldvalidators VALUES (33, 'DPSUserShowOwnValidator', 'Checks user owns a showplan', 'DPS');
INSERT INTO fieldvalidators VALUES (34, 'DPS24HourValidator', 'Checks an hour is in 24 format', 'DPS');
INSERT INTO fieldvalidators VALUES (35, 'DPSMinutesValidator', 'Checks valid minutes', 'DPS');
INSERT INTO fieldvalidators VALUES (36, 'DPSUserShowitemEditValidator', 'Checks uer can edit a showitem', 'DPS');
INSERT INTO fieldvalidators VALUES (37, 'DPSUserShowEditValidator', 'Checks uer can edit a show', 'DPS');
INSERT INTO fieldvalidators VALUES (38, 'DPSUserScriptDelValidator', 'Checks that a user can delete a script', 'DPS');
INSERT INTO fieldvalidators VALUES (39, 'DPSUserScriptEditValidator', 'Checks that a user can edit a script', 'DPS');
ALTER SEQUENCE fieldvalidators_ruleid_seq RESTART 40;

-- forms
INSERT INTO forms VALUES (1, 'regionModifyForm', 'EditContentModel', 'CMS', 2, NULL, NULL);
INSERT INTO forms VALUES (2, 'dpsMusicSearchViewForm', 'DPSViewTracksModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (3, 'groupDetailsForm', 'GroupModel', 'Auth', 1, NULL, NULL);
INSERT INTO forms VALUES (4, 'groupSelForm', 'GroupModel', 'Auth', 1, NULL, NULL);
INSERT INTO forms VALUES (5, 'groupRealmForm', 'GroupModel', 'Auth', 1, NULL, NULL);
INSERT INTO forms VALUES (6, 'addGroupForm', 'GroupModel', 'Auth', 1, NULL, NULL);
INSERT INTO forms VALUES (7, 'groupDeleteForm', 'GroupModel', 'Auth', 1, NULL, NULL);
INSERT INTO forms VALUES (8, 'addRealmSelForm', 'RealmModel', 'Auth', 1, NULL, NULL);
INSERT INTO forms VALUES (9, 'modifyRealmDetailsForm', 'RealmModel', 'Auth', 1, NULL, NULL);
INSERT INTO forms VALUES (10, 'realmDeleteForm', 'RealmModel', 'Auth', 1, NULL, NULL);
INSERT INTO forms VALUES (11, 'addRealmDetailsForm', 'RealmModel', 'Auth', 1, NULL, NULL);
INSERT INTO forms VALUES (12, 'realmDeleteForm', 'RealmModel', 'Auth', 1, NULL, NULL);
INSERT INTO forms VALUES (13, 'userPermissionForm', 'UserModel', 'Auth', 1, NULL, NULL);
INSERT INTO forms VALUES (14, 'userDeleteForm', 'UserModel', 'Auth', 1, NULL, NULL);
INSERT INTO forms VALUES (15, 'modifyUserDetailsForm', 'UserModel', 'Auth', 1, NULL, NULL);
INSERT INTO forms VALUES (16, 'addUserDetailsForm', 'UserModel', 'Auth', 1, NULL, NULL);
INSERT INTO forms VALUES (17, 'dpsMusicReportForm', 'DPSReportTrackModel', 'DPS', 43, NULL, NULL);
INSERT INTO forms VALUES (18, 'dpsEditTrackForm', 'DPSEditTrackModel', 'DPS', 27, NULL, NULL);
INSERT INTO forms VALUES (19, 'dpsMusicRequestForm', 'DPSRequestTrackModel', 'DPS', 29, NULL, NULL);
INSERT INTO forms VALUES (20, 'dpsMusicRemoveRequestForm', 'DPSMusicRemoveRequestModel', 'DPS', 31, NULL, NULL);
INSERT INTO forms VALUES (21, 'dpsSuePlaylistForm', 'DPSRemoveSueTrackModel', 'DPS', 24, NULL, NULL);
INSERT INTO forms VALUES (22, 'dpsSueAddPlaylistForm', 'DPSAddSueTrackModel', 'DPS', 24, NULL, NULL);
INSERT INTO forms VALUES (23, 'dpsTrackAddCensorForm', 'DPSAddCensorTrackModel', 'DPS', 30, NULL, NULL);
INSERT INTO forms VALUES (24, 'dpsTrackCensorForm', 'DPSCensorTrackModel', 'DPS', 30, NULL, NULL);
INSERT INTO forms VALUES (25, 'dpsMusicDeleteForm', 'DPSDeleteTrackModel', 'DPS', 32, NULL, NULL);
INSERT INTO forms VALUES (26, 'dpsloginForm', 'DPSLoginModel', 'DPS', 18, NULL, NULL);
INSERT INTO forms VALUES (27, 'inlineEdit', 'EditInlineModel', 'CMS', 2, NULL, NULL);
INSERT INTO forms VALUES (28, 'dpsUserDelCartsetForm', 'DPSUserDeleteCartsetModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (29, 'dpsUserActCartsetForm', 'DPSUserUpdateActCartsetModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (30, 'dpsUserNewCartsetForm', 'DPSUserAddCartsetModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (31, 'dpsUserCartwallEditForm', 'DPSUserUpdateCartwallModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (32, 'dpsUserAddCartwallPageForm', 'DPSUserAddCartPageModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (33, 'dpsUserCartAddForm', 'DPSUserAddCartModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (34, 'dpsUserCartEditForm', 'DPSUserUpdateCartModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (35, 'dpsStationNewCartsetForm', 'DPSStationAddCartsetModel', 'DPS', 39, NULL, NULL);
INSERT INTO forms VALUES (36, 'dpsStationDelCartsetForm', 'DPSStationDeleteCartsetModel', 'DPS', 39, NULL, NULL);
INSERT INTO forms VALUES (37, 'dpsStationActCartsetForm', 'DPSStationUpdateActCartsetModel', 'DPS', 39, NULL, NULL);
INSERT INTO forms VALUES (38, 'dpsStationCartwallEditForm', 'DPSStationUpdateCartwallModel', 'DPS', 39, NULL, NULL);
INSERT INTO forms VALUES (39, 'dpsStationAddCartwallPageForm', 'DPSStationAddCartPageModel', 'DPS', 39, NULL, NULL);
INSERT INTO forms VALUES (40, 'dpsStationCartEditForm', 'DPSStationUpdateCartModel', 'DPS', 39, NULL, NULL);
INSERT INTO forms VALUES (41, 'dpsStationCartAddForm', 'DPSStationAddCartModel', 'DPS', 39, NULL, NULL);
INSERT INTO forms VALUES (42, 'dpsStationCartDelForm', 'DPSStationDeleteCartModel', 'DPS', 39, NULL, NULL);
INSERT INTO forms VALUES (43, 'dpsUserCartDelForm', 'DPSUserDeleteCartModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (44, 'dpsStAddPlaylistForm', 'DPSAddPlaylistModel', 'DPS', 33, NULL, NULL);
INSERT INTO forms VALUES (45, 'dpsdiradd', 'DPSCreateDirectoryModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (46, 'dpsdirdel', 'DPSDeleteDirectoryModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (47, 'dpsdirrename', 'DPSRenameDirectoryModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (48, 'dpsMusicCommentForm', 'DPSCommentTrackModel', 'DPS', 34, NULL, NULL);
INSERT INTO forms VALUES (49, 'dpsMusicDeleteCommentForm', 'DPSDeleteCommentTrackModel', 'DPS', 34, NULL, NULL);
INSERT INTO forms VALUES (50, 'dpsUserMoveDirForm', 'DPSMoveDirectoryModel', 'DPS', 19, 'DPSDirMoveValidator', 'DPS');
INSERT INTO forms VALUES (51, 'dpsUserAddShow', 'DPSUserAddShowModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (52, 'dpsUserDelShow', 'DPSUserDeleteShowModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (53, 'dpsUserEditShow', 'DPSUserEditShowModel', 'DPS', 19, 'DPSUserShowDetailsValidator', 'DPS');
INSERT INTO forms VALUES (54, 'dpsUserShowItemUp', 'DPSUserUpShowItemModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (55, 'dpsUserShowItemDown', 'DPSUserDownShowItemModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (56, 'dpsUserDelShowItem', 'DPSUserDeleteShowItemModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (57, 'dpsUserAudioShow', 'DPSUserTrackShowModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (58, 'dpsUserDelAudioShow', 'DPSUserDelTrackShowModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (59, 'dpsUserAddShowItem', 'DPSUserAddShowItemModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (60, 'dpsUserCompleteShow', 'DPSUserCompleteShowModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (61, 'dpsUserUnCompleteShow', 'DPSUserUnCompleteShowModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (62, 'dpsUserEditShowItem', 'DPSUserEditShowItemModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (63, 'dpsUserAddScript', 'DPSUserAddScriptModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (64, 'dpsUserDelScript', 'DPSUserDeleteScriptModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (65, 'dpsUserEditScript', 'DPSUserEditScript', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (66, 'dpsUserScriptShow', 'DPSUserScriptShowModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (67, 'dpsUserDelScriptShow', 'DPSUserDelScriptShowModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (68, 'dpsUserDelAudio', 'DPSDeleteTrackModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (69, 'dpsUserMoveAudioForm', 'DPSMoveAudioModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (70, 'dpsUserMoveCartsetForm', 'DPSMoveCartsetModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (71, 'dpsUserMoveScriptForm', 'DPSMoveScriptModel', 'DPS', 19, NULL, NULL);
INSERT INTO forms VALUES (72, 'dpsUserUploadFileForm', 'DPSUserFileDirectoryModel', 'DPS', 19, NULL, NULL);
ALTER SEQUENCE forms_formid_seq RESTART 73;

-- formfields
INSERT INTO formfields VALUES (1, 'loginForm', 'authPassword', 3, 'Auth');
INSERT INTO formfields VALUES (2, 'groupRealmForm', 'rguid', 10, 'Auth');
INSERT INTO formfields VALUES (3, 'groupRealmForm', 'task', 11, 'Auth');
INSERT INTO formfields VALUES (4, 'groupSelForm', 'groupToEdit', 10, 'Auth');
INSERT INTO formfields VALUES (5, 'groupDeleteForm', 'groupToEdit', 10, 'Auth');
INSERT INTO formfields VALUES (6, 'groupDetailsForm', 'groupToEdit', 10, 'Auth');
INSERT INTO formfields VALUES (7, 'dpsloginForm', 'authPassword', 3, 'Auth');
INSERT INTO formfields VALUES (8, 'dpsMusicSearchForm', 'dpsSearchType', 13, 'DPS');
INSERT INTO formfields VALUES (9, 'dpsMusicRequestForm', 'artist', 15, 'DPS');
INSERT INTO formfields VALUES (10, 'dpsMusicRequestForm', 'title', 14, 'DPS');
INSERT INTO formfields VALUES (11, 'dpsStationActCartsetForm', 'cartset', 29, 'DPS');
INSERT INTO formfields VALUES (12, 'dpsStationDelCartsetForm', 'cartset', 22, 'DPS');
INSERT INTO formfields VALUES (13, 'dpsStationAddCartwallPageForm', 'cartset', 16, 'DPS');
INSERT INTO formfields VALUES (14, 'dpsStationCartwallEditForm', 'cartset', 16, 'DPS');
INSERT INTO formfields VALUES (15, 'dpsStationCartAddForm', 'cartwallID', 17, 'DPS');
INSERT INTO formfields VALUES (16, 'dpsStationCartEditForm', 'cartID', 18, 'DPS');
INSERT INTO formfields VALUES (17, 'dpsUserDelCartsetForm', 'cartset', 26, 'DPS');
INSERT INTO formfields VALUES (18, 'dpsUserActCartsetForm', 'cartset', 30, 'DPS');
INSERT INTO formfields VALUES (19, 'dpsStationCartDelForm', 'cartID', 18, 'DPS');
INSERT INTO formfields VALUES (20, 'dpsUserAddCartwallPageForm', 'cartset', 19, 'DPS');
INSERT INTO formfields VALUES (21, 'dpsUserCartwallEditForm', 'cartset', 19, 'DPS');
INSERT INTO formfields VALUES (22, 'dpsUserCartDelForm', 'cartID', 21, 'DPS');
INSERT INTO formfields VALUES (23, 'dpsMusicSearchForm', 'dpsSearchVal', 10, 'DPS');
INSERT INTO formfields VALUES (24, 'dpsSueSearchForm', 'dpsSearchType', 13, 'DPS');
INSERT INTO formfields VALUES (25, 'dpsSueSearchForm', 'dpsSearchVal', 10, 'DPS');
INSERT INTO formfields VALUES (26, 'dpsMusicCommentForm', 'comment', 10, 'DPS');
INSERT INTO formfields VALUES (27, 'dpsEditTrackForm', 'title', 10, 'DPS');
INSERT INTO formfields VALUES (28, 'dpsEditTrackForm', 'origin', 10, 'DPS');
INSERT INTO formfields VALUES (29, 'dpsUserNewCartsetForm', 'name', 10, 'DPS');
INSERT INTO formfields VALUES (30, 'dpsUserNewCartsetForm', 'desc', 11, 'DPS');
INSERT INTO formfields VALUES (31, 'dpsUserCartwallEditForm', 'desc', 11, 'DPS');
INSERT INTO formfields VALUES (32, 'dpsUserCartwallEditForm', 'name', 10, 'DPS');
INSERT INTO formfields VALUES (33, 'dpsStationNewCartsetForm', 'name', 10, 'DPS');
INSERT INTO formfields VALUES (34, 'dpsStationNewCartsetForm', 'desc', 11, 'DPS');
INSERT INTO formfields VALUES (35, 'dpsStationCartwallEditForm', 'desc', 11, 'DPS');
INSERT INTO formfields VALUES (36, 'dpsStationCartwallEditForm', 'name', 10, 'DPS');
INSERT INTO formfields VALUES (37, 'dpsUserCartEditForm', 'text', 10, 'DPS');
INSERT INTO formfields VALUES (38, 'dpsUserCartEditForm', 'audioID', 31, 'DPS');
INSERT INTO formfields VALUES (39, 'dpsUserCartAddForm', 'text', 10, 'DPS');
INSERT INTO formfields VALUES (40, 'dpsUserCartAddForm', 'audioID', 31, 'DPS');
INSERT INTO formfields VALUES (41, 'dpsStationCartEditForm', 'text', 10, 'DPS');
INSERT INTO formfields VALUES (42, 'dpsStationCartEditForm', 'audioID', 31, 'DPS');
INSERT INTO formfields VALUES (43, 'dpsStationCartAddForm', 'text', 10, 'DPS');
INSERT INTO formfields VALUES (44, 'dpsStationCartAddForm', 'audioID', 31, 'DPS');
INSERT INTO formfields VALUES (45, 'dpsdiradd', 'rootdir', 2, 'DPS');
INSERT INTO formfields VALUES (46, 'dpsdiradd', 'dirtext', 10, 'DPS');
INSERT INTO formfields VALUES (47, 'dpsdirdel', 'rootdir', 32, 'DPS');
INSERT INTO formfields VALUES (48, 'dpsdirrename', 'rootdir', 2, 'DPS');
INSERT INTO formfields VALUES (49, 'dpsdirrename', 'dirtext', 10, 'DPS');
INSERT INTO formfields VALUES (50, 'dpsUserMoveDirForm', 'dirID', 2, 'DPS');
INSERT INTO formfields VALUES (51, 'dpsUserMoveDirForm', 'newParent', 2, 'DPS');
INSERT INTO formfields VALUES (52, 'dpsUserDelShow', 'showID', 33, 'DPS');
INSERT INTO formfields VALUES (53, 'dpsUserEditShow', 'mins', 35, 'DPS');
INSERT INTO formfields VALUES (54, 'dpsUserEditShow', 'hours', 34, 'DPS');
INSERT INTO formfields VALUES (55, 'dpsUserEditShow', 'name', 10, 'DPS');
INSERT INTO formfields VALUES (56, 'dpsUserShowItemUp', 'itemID', 36, 'DPS');
INSERT INTO formfields VALUES (57, 'dpsUserShowItemDown', 'itemID', 36, 'DPS');
INSERT INTO formfields VALUES (58, 'dpsUserEditShow', 'showID', 37, 'DPS');
INSERT INTO formfields VALUES (59, 'dpsUserDelShowItem', 'itemID', 36, 'DPS');
INSERT INTO formfields VALUES (60, 'dpsUserAudioShow', 'itemID', 36, 'DPS');
INSERT INTO formfields VALUES (61, 'dpsUserAudioShow', 'audioID', 12, 'DPS');
INSERT INTO formfields VALUES (62, 'dpsUserDelAudioShow', 'itemID', 36, 'DPS');
INSERT INTO formfields VALUES (63, 'dpsUserAddShowItem', 'showID', 37, 'DPS');
INSERT INTO formfields VALUES (64, 'dpsUserUnCompleteShow', 'showID', 37, 'DPS');
INSERT INTO formfields VALUES (65, 'dpsUserCompleteShow', 'showID', 37, 'DPS');
INSERT INTO formfields VALUES (66, 'dpsUserEditShowItem', 'itemID', 36, 'DPS');
INSERT INTO formfields VALUES (67, 'dpsUserEditShowItem', 'title', 10, 'DPS');
INSERT INTO formfields VALUES (68, 'dpsUserEditShowItem', 'mins', 35, 'DPS');
INSERT INTO formfields VALUES (69, 'dpsUserEditShowItem', 'secs', 35, 'DPS');
INSERT INTO formfields VALUES (70, 'dpsUserDelScript', 'scriptID', 38, 'DPS');
INSERT INTO formfields VALUES (71, 'dpsUserEditScript', 'scriptID', 39, 'DPS');
INSERT INTO formfields VALUES (72, 'dpsUserEditScript', 'name', 10, 'DPS');
INSERT INTO formfields VALUES (73, 'dpsUserScriptShow', 'itemID', 36, 'DPS');
INSERT INTO formfields VALUES (74, 'dpsUserDelScriptShow', 'itemID', 36, 'DPS');
INSERT INTO formfields VALUES (75, 'dpsUserScriptShow', 'scriptID', 12, 'DPS');
INSERT INTO formfields VALUES (76, 'dpsUserDelAudio', 'audioID', 9, 'DPS');
INSERT INTO formfields VALUES (77, 'dpsUserMoveAudioForm', 'audioID', 24, 'DPS');
INSERT INTO formfields VALUES (78, 'dpsUserMoveAudioForm', 'newParent', 2, 'DPS');
INSERT INTO formfields VALUES (79, 'dpsUserMoveScriptForm', 'newParent', 2, 'DPS');
INSERT INTO formfields VALUES (80, 'dpsUserMoveCartsetForm', 'newParent', 2, 'DPS');
INSERT INTO formfields VALUES (81, 'dpsUserMoveScriptForm', 'scriptID', 39, 'DPS');
INSERT INTO formfields VALUES (82, 'dpsUserMoveCartsetForm', 'cartsetID', 19, 'DPS');
INSERT INTO formfields VALUES (83, 'dpsUserUploadFileForm', 'name', 10, 'DPS');
INSERT INTO formfields VALUES (84, 'dpsUserUploadFileForm', 'dirID', 2, 'DPS');
ALTER SEQUENCE formfields_fieldid_seq RESTART 85;

-- templates
INSERT INTO templates VALUES (1, 'userModify.tpl', 'UserViewer', 1, 'Auth');
INSERT INTO templates VALUES (2, 'groupModify.tpl', 'GroupViewer', 1, 'Auth');
INSERT INTO templates VALUES (3, 'realmModify.tpl', 'RealmViewer', 1, 'Auth');
INSERT INTO templates VALUES (4, 'userAdd.tpl', 'UserViewer', 1, 'Auth');
INSERT INTO templates VALUES (5, 'groupAdd.tpl', 'GroupViewer', 1, 'Auth');
INSERT INTO templates VALUES (6, 'realmAdd.tpl', 'RealmViewer', 1, 'Auth');
INSERT INTO templates VALUES (7, 'listTemplates.tpl', 'TemplateListViewer', 1, 'MVC');
INSERT INTO templates VALUES (8, 'addTemplate.tpl', 'AddTemplateViewer', 17, 'MVC');
INSERT INTO templates VALUES (9, 'dpstsedit.tpl', 'DPSTracksEditViewer', 19, 'DPS');
INSERT INTO templates VALUES (10, 'dpstview.tpl', 'DPSTracksViewViewer', 19, 'DPS');
INSERT INTO templates VALUES (11, 'dpslogin.tpl', 'LoginViewer', 18, 'DPS');
INSERT INTO templates VALUES (12, 'dpshome.tpl', 'DPSHomeViewer', 19, 'DPS');
INSERT INTO templates VALUES (13, 'dpspermissionError.tpl', 'LoginViewer', 18, 'DPS');
INSERT INTO templates VALUES (14, 'rPermissionError.tpl', 'Viewer', 19, 'Auth');
INSERT INTO templates VALUES (15, 'Rexception.tpl', 'RenderedExceptionViewer', 18, 'Auth');
INSERT INTO templates VALUES (16, 'logout.tpl', 'LogoutViewer', 18, 'Auth');
INSERT INTO templates VALUES (17, 'newUserInfo.tpl', 'Viewer', 1, 'CMS');
INSERT INTO templates VALUES (18, 'dpsgetfile.tpl', 'DPSMp3PreviewViewer', 19, 'DPS');
INSERT INTO templates VALUES (19, 'dpstrequest.tpl', 'DPSTrackRequestViewer', 19, 'DPS');
INSERT INTO templates VALUES (20, 'dpsmsearch.tpl', 'DPSMusicSearchViewer', 28, 'DPS');
INSERT INTO templates VALUES (21, 'dpshelp.tpl', 'DPSHelpViewer', 19, 'DPS');
INSERT INTO templates VALUES (22, 'dpssteditcartredirect.tpl', 'Viewer', 19, 'DPS');
INSERT INTO templates VALUES (23, 'dpsstusercartsets.tpl', 'DPSUserCartsetsViewer', 19, 'DPS');
INSERT INTO templates VALUES (24, 'dpssteditcart.tpl', 'DPSUserEditCartViewer', 19, 'DPS');
INSERT INTO templates VALUES (25, 'dpssteditcartwall.tpl', 'DPSUserEditCartsetViewer', 19, 'DPS');
INSERT INTO templates VALUES (26, 'dpsstviewcartwall.tpl', 'DPSUserCartwallsViewer', 19, 'DPS');
INSERT INTO templates VALUES (27, 'dpsststationcartsets.tpl', 'DPSStationCartsetsViewer', 39, 'DPS');
INSERT INTO templates VALUES (28, 'dpsststationeditcartwall.tpl', 'DPSStationEditCartsetViewer', 39, 'DPS');
INSERT INTO templates VALUES (29, 'dpsststationeditcart.tpl', 'DPSStationEditCartViewer', 39, 'DPS');
INSERT INTO templates VALUES (30, 'dpsststationviewcartwall.tpl', 'DPSStationCartwallsViewer', 39, 'DPS');
INSERT INTO templates VALUES (31, 'dpsmusicfront.tpl', 'DPSMusicFrontViewer', 19, 'DPS');
INSERT INTO templates VALUES (32, 'dpssuefront.tpl', 'DPSSueFrontViewer', 19, 'DPS');
INSERT INTO templates VALUES (33, 'dpsstudiofront.tpl', 'DPSStudioFrontViewer', 19, 'DPS');
INSERT INTO templates VALUES (34, 'dpsshowfront.tpl', 'DPSShowFrontViewer', 19, 'DPS');
INSERT INTO templates VALUES (35, 'dpssaddplaylist.tpl', 'DPSSueAddPlaylistViewer', 24, 'DPS');
INSERT INTO templates VALUES (36, 'dpssstats.tpl', 'DPSSueStatsViewer', 25, 'DPS');
INSERT INTO templates VALUES (37, 'dpstedit.tpl', 'DPSTrackEditViewer', 27, 'DPS');
INSERT INTO templates VALUES (38, 'dpstcensor.tpl', 'DPSTrackCensorViewer', 19, 'DPS');
INSERT INTO templates VALUES (39, 'dpsstplaylist.tpl', 'DPSStudioPlaylistViewer', 33, 'DPS');
INSERT INTO templates VALUES (40, 'dpssplaylist.tpl', 'DPSSuePlaylistViewer', 26, 'DPS');
INSERT INTO templates VALUES (41, 'dpsshaddjingle.tpl', 'DPSShowPlanSelectJingleViewer', 19, 'DPS');
INSERT INTO templates VALUES (42, 'dpsshaddadvert.tpl', 'DPSShowPlanSelectAdvertViewer', 19, 'DPS');
INSERT INTO templates VALUES (43, 'dpsshaddmusic.tpl', 'DPSShowPlanSelectMusicViewer', 19, 'DPS');
INSERT INTO templates VALUES (44, 'dpsshscript.tpl', 'DPSShowUserScriptViewer', 19, 'DPS');
INSERT INTO templates VALUES (45, 'dpssheditscript.tpl', 'DPSUserEditScriptViewer', 19, 'DPS');
INSERT INTO templates VALUES (46, 'dpsshaddscript.tpl', 'DPSShowPlanSelectScriptViewer', 19, 'DPS');
INSERT INTO templates VALUES (47, 'dpsuseraudiomove.tpl', 'DPSUserAudioMoveViewer', 19, 'DPS');
INSERT INTO templates VALUES (48, 'dpsusercartsetmove.tpl', 'DPSUserCartsetMoveViewer', 19, 'DPS');
INSERT INTO templates VALUES (49, 'dpsuserscriptmove.tpl', 'DPSUserScriptMoveViewer', 19, 'DPS');
INSERT INTO templates VALUES (50, 'dpsuserfileupload.tpl', 'DPSUserFileUploadViewer', 19, 'DPS');
INSERT INTO templates VALUES (51, 'dpsuserfile.tpl', 'DPSUserFileViewer', 19, 'DPS');
INSERT INTO templates VALUES (52, 'dpsusertedit.tpl', 'DPSUserTrackEditViewer', 19, 'DPS');
INSERT INTO templates VALUES (53, 'dpsuserdirmove.tpl', 'DPSUserFileMoveViewer', 19, 'DPS');
INSERT INTO templates VALUES (54, 'dpsshplan.tpl', 'DPSShowPlanViewer', 19, 'DPS');
INSERT INTO templates VALUES (55, 'dpsshedit.tpl', 'DPSShowPlanEditViewer', 19, 'DPS');
INSERT INTO templates VALUES (56, 'dpsshreorder.tpl', 'DPSShowPlanEditViewer', 19, 'DPS');
INSERT INTO templates VALUES (57, 'dpssheditdetails.tpl', 'DPSShowPlanDetailsViewer', 19, 'DPS');
INSERT INTO templates VALUES (58, 'dpsshedititem.tpl', 'DPSShowPlanEditItemViewer', 19, 'DPS');
INSERT INTO templates VALUES (59, 'dpspublichelp.tpl', 'DPSHelpViewer', 18, 'DPS');
INSERT INTO templates VALUES (60, 'dpslogout.tpl', 'DPSLogoutViewer', 18, 'DPS');
INSERT INTO templates VALUES (61, 'editContentWindow.tpl', 'EditContentViewer', 18, 'CMS');
INSERT INTO templates VALUES (62, 'editContent.tpl', 'EditContentViewer', 18, 'CMS');
INSERT INTO templates VALUES (63, 'editContentWindow.rpl', 'editContentWindowViewer', 18, 'CMS');
INSERT INTO templates VALUES (64, 'editorForm.tpl', 'EditorFormViewer', 18, 'CMS');
INSERT INTO templates VALUES (65, 'dpsempty.tpl', 'DPSUserSubFileViewer', 18, 'DPS');
ALTER SEQUENCE templates_templateid_seq RESTART 66;
