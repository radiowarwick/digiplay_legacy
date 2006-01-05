BEGIN TRANSACTION;

/* Audio types */
INSERT INTO audiotypes (id, name, description) 
	VALUES (0,'music','Music tracks from the CD library or other sources');
INSERT INTO audiotypes (id, name, description)
	VALUES (1,'jingle','Station Idents');
INSERT INTO audiotypes (id, name, description)
	VALUES (2,'advert','Advertisments');

/* Root directory */
INSERT INTO dir (id, parent, name, notes)
	VALUES (0, -1,'Digiplay','Root node of virtual directory structure');

/* Default users */
INSERT INTO users (id, username, enabled)
	VALUES (0, 'system','t');

/* User Privilages */
INSERT INTO privilages (id, name, description)
	VALUES (1,'sust_stats','Web access to sustainer configuration');
INSERT INTO privilages (id, name, description)
	VALUES (3,'admin','Can manage user accounts, create user managers, and assign any access privilages. Is God.');
INSERT INTO privilages (id, name, description)
	VALUES (4,'sust_edit','Can edit the playlist for the sustainer service');
INSERT iNTO privilages (id, name, description)
	VALUES (5,'music_flag','Can flag a track to be assessed by a member of the music team');
INSERT INTO privilages (id, name, description)
	VALUES (6,'music_censor','Can censor a track making it unavailable for playout on air');
INSERT INTO privilages (id, name, description)
	VALUES (7,'music_edit_info','Can edit the track information for music');
INSERT INTO privilages (id, name, description)
	VALUES (8,'music_manager','Can assign sust_edit, music_flag, music_censor, music_edit_info rights to users');
INSERT INTO privilages (id, name, description)
	VALUES (9,'production_manager','Can organise jingles and jingle packages, and enabled them');
INSERT INTO privilages (id, name, description)
	VALUES (10,'marketing_manager','Can organise and schedule adverts');

/* Default groups */
INSERT INTO groups (id, name, description)
	VALUES (1,'music_team','Members of the music team');

/* No album */
INSERT INTO albums (id, name)
	VALUES (0, '(none)');

/* Default Jingle type */
INSERT INTO jingletypes (id, name, description)
	VALUES (0, 'Generic','Unclassified');
INSERT INTO jingletypes (id, name, description)
	VALUES (1, 'Idents','Station Identification');
INSERT INTO jingletypes (id, name, description)
	VALUES (2, 'Contact','Contact Information');
INSERT INTO jingletypes (id, name, description)
	VALUES (3, 'News','News Ident');
INSERT INTO jingletypes (id, name, description)
	VALUES (4, 'Shows','Show Identification');

/* Lifespans */
INSERT INTO lifespans (id, name, data, description)
	VALUES (0,'Permenant','-1','Permenant audio file - i.e. music library');

/* Cart Walls */
INSERT INTO cartsets (id, name, userid, directory, description)
	VALUES (0,'RaW 1251AM',0,0,'RaW 1251AM Station Audio Wall');
INSERT INTO cartwalls (id, name, cartset, page, description)
	VALUES (0,'Page 1',0,0,'Main station jingles');
INSERT INTO cartproperties (id, name)
	VALUES (0,'ForeColourRGB');
INSERT INTO cartproperties (id, name)
	VALUES (1,'BackColourRGB');
INSERT INTO cartproperties (id, name)
	VALUES (2,'Font');
INSERT INTO cartproperties (id, name)
	VALUES (3,'Fontsize');
INSERT INTO cartproperties (id, name)
	VALUES (4,'FontBold');
INSERT INTO cartstyle (id, name, description)
	VALUES (0,'Blue','Blue background with black text');
INSERT INTO cartstyle (id, name, description)
	VALUES (1,'RaW Purple','RaW Purple background with black text');
INSERT INTO cartstyle (id, name, description)
	VALUES (2,'Cool Green','A bluish green background with black text');
INSERT INTO cartstyle (id, name, description)
	VALUES (3,'Bright Green','Green background with black text');
INSERT INTO cartstyleprops (id, style, property, value)
	VALUES (0,0,0,0);
INSERT INTO cartstyleprops (id, style, property, value)
	VALUES (1,0,1,1214912);
INSERT INTO cartstyleprops (id, style, property, value)
    VALUES (2,1,0,0);
INSERT INTO cartstyleprops (id, style, property, value)
    VALUES (3,1,1,11731183);
INSERT INTO cartstyleprops (id, style, property, value)
    VALUES (4,2,0,0);
INSERT INTO cartstyleprops (id, style, property, value)
    VALUES (5,2,1,49245);
INSERT INTO cartstyleprops (id, style, property, value)
    VALUES (6,3,0,0);
INSERT INTO cartstyleprops (id, style, property, value)
    VALUES (7,3,1,8044544);

/* Configuration */
INSERT INTO configuration (id, parameter, val, location)
	VALUES (0,'bin_weighting_1','5',0);
INSERT INTO configuration (id, parameter, val, location)
	VALUES (1,'bin_weighting_2','9',0);
INSERT INTO configuration (id, parameter, val, location)
	VALUES (2,'bin_weighting_3','12',0);
INSERT INTO configuration (id, parameter, val, location)
	VALUES (3,'bin_weighting_4','14',0);
INSERT INTO configuration (id, parameter, val, location)
	VALUES (4,'bin_weighting_5','15',0);
INSERT intO configuration (id, parameter, val, location)
	VALUES (5,'channel_1','/dev/dsp',0);
/* Studio Application configuration */
INSERT INTO configuration (id, parameter, val, location)
	VALUES (6,'channel_1','/dev/dsp',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (7,'channel_2','/dev/null',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (8,'channel_3','/dev/null',1);
INSERT intO configuration (id, parameter, val, location)
	VALUES (9,'channel_4','/dev/null',1);
INSERT INTO configuration (id, parameter, val, location)
	VALUES (10,'player1_md5','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (11,'player2_md5','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (12,'player3_md5','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (13,'player1_state','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (14,'player2_state','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (15,'player3_state','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (16,'next_on_showplan','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (17,'station_cartwall','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (18,'station_cartwall_next','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (19,'station_cartwall_prev','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (20,'user_cartwall','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (21,'user_cartwall_next','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (22,'user_cartwall_prev','',1);

INSERT INTO configuration (id, parameter, val, location)
    VALUES (23,'channel_1','/dev/dsp',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (24,'channel_2','/dev/null',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (25,'channel_3','/dev/null',2);
INSERT iNTO configuration (id, parameter, val, location)
	VALUES (26,'channel_4','/dev/null',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (27,'player1_md5','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (28,'player2_md5','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (29,'player3_md5','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (30,'player1_state','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (31,'player2_state','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (32,'player3_state','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (33,'next_on_showplan','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (34,'station_cartwall','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (35,'station_cartwall_next','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (36,'station_cartwall_prev','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (37,'user_cartwall','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (38,'user_cartwall_next','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (39,'user_cartwall_prev','',2);
END TRANSACTION;
