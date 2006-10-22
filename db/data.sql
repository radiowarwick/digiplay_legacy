BEGIN TRANSACTION;

INSERT INTO patches (branch, version)
	VALUES ('dps',0);

/* Audio types */
INSERT INTO audiotypes (name, description) 
	VALUES ('music','Music tracks from the CD library or other sources');
INSERT INTO audiotypes (name, description)
	VALUES ('jingle','Station Idents');
INSERT INTO audiotypes (name, description)
	VALUES ('advert','Advertisments');

/* Root directory */
INSERT INTO dir (parent, name, notes)
	VALUES (-1,'Digiplay','Root node of virtual directory structure');
INSERT INTO dir (parent, name, notes)
	VALUES (1,'Music','Music Library');
INSERT INTO dir (parent, name, notes)
	VALUES (1,'Jingles','Station and show idents');
INSERT INTO dir (parent, name, notes)
	VALUES (1,'Adverts','Station sponsorship messages and adverts');
INSERT INTO dir (parent, name, notes)
	VALUES (1,'Departments','Departmental files');
INSERT INTO dir (parent, name, notes)
	VALUES (1,'Users','User areas');

/* Default users */
INSERT INTO users (username, enabled) VALUES ('system','t');
INSERT INTO users (username, enabled) VALUES ('guest','t');

/* User Privilages */
INSERT INTO privilages (name, description)
	VALUES ('sust_stats','Web access to sustainer configuration');
INSERT INTO privilages (name, description)
	VALUES ('sust_view','View tracks available to sustainer');
INSERT INTO privilages (name, description)
	VALUES ('admin','Can manage user accounts, create user managers, and assign any access privilages. Is God.');
INSERT INTO privilages (name, description)
	VALUES ('sust_edit','Can edit the playlist for the sustainer service');
INSERT iNTO privilages (name, description)
	VALUES ('music_flag','Can flag a track to be assessed by a member of the music team');
INSERT INTO privilages (name, description)
	VALUES ('music_censor','Can censor a track making it unavailable for playout on air');
INSERT INTO privilages (name, description)
	VALUES ('music_edit_info','Can edit the track information for music');
INSERT INTO privilages (name, description)
	VALUES ('music_manager','Can assign sust_edit, music_flag, music_censor, music_edit_info rights to users');
INSERT INTO privilages (name, description)
	VALUES ('production_manager','Can organise jingles and jingle packages, and enabled them');
INSERT INTO privilages (name, description)
	VALUES ('marketing_manager','Can organise and schedule adverts');

/* Default groups */
INSERT INTO groups (name, description)
	VALUES ('music_team','Members of the music team');

/* No album */
INSERT INTO albums (name)
	VALUES ('(none)');

/* Default Jingle type */
INSERT INTO jingletypes (name, description)
	VALUES ('Generic','Unclassified');
INSERT INTO jingletypes (name, description)
	VALUES ('Idents','Station Identification');
INSERT INTO jingletypes (name, description)
	VALUES ('Contact','Contact Information');
INSERT INTO jingletypes (name, description)
	VALUES ('News','News Ident');
INSERT INTO jingletypes (name, description)
	VALUES ('Shows','Show Identification');

/* Lifespans */
INSERT INTO lifespans (name, data, description)
	VALUES ('Permenant','-1','Permenant audio file - i.e. music library');

/* Cartwalls */
INSERT INTO cartproperties (name)
	VALUES ('ForeColourRGB');
INSERT INTO cartproperties (name)
	VALUES ('BackColourRGB');
INSERT INTO cartproperties (name)
	VALUES ('Font');
INSERT INTO cartproperties (name)
	VALUES ('Fontsize');
INSERT INTO cartproperties (name)
	VALUES ('FontBold');
INSERT INTO cartstyle (name, description)
	VALUES ('Blue','Blue background with black text');
INSERT INTO cartstyle (name, description)
	VALUES ('RaW Purple','RaW Purple background with black text');
INSERT INTO cartstyle (name, description)
	VALUES ('Cool Green','A bluish green background with black text');
INSERT INTO cartstyle (name, description)
	VALUES ('Bright Green','Green background with black text');
INSERT INTO cartstyleprops (style, property, value)
	VALUES (1,1,0);
INSERT INTO cartstyleprops (style, property, value)
	VALUES (1,2,1214912);
INSERT INTO cartstyleprops (style, property, value)
    VALUES (2,1,0);
INSERT INTO cartstyleprops (style, property, value)
    VALUES (2,2,11731183);
INSERT INTO cartstyleprops (style, property, value)
    VALUES (3,1,0);
INSERT INTO cartstyleprops (style, property, value)
    VALUES (3,2,49245);
INSERT INTO cartstyleprops (style, property, value)
    VALUES (4,1,0);
INSERT INTO cartstyleprops (style, property, value)
    VALUES (4,2,8044544);

/* Configuration
 * Sustainer is LOCATION=0
 */
INSERT INTO configuration (parameter, val, location)
	VALUES ('bin_weighting_1','5',0);
INSERT INTO configuration (parameter, val, location)
	VALUES ('bin_weighting_2','9',0);
INSERT INTO configuration (parameter, val, location)
	VALUES ('bin_weighting_3','12',0);
INSERT INTO configuration (parameter, val, location)
	VALUES ('bin_weighting_4','14',0);
INSERT INTO configuration (parameter, val, location)
	VALUES ('bin_weighting_5','15',0);
INSERT intO configuration (parameter, val, location)
	VALUES ('channel_1','/dev/dsp',0);

/* First Studio Application configuration */
INSERT INTO configuration (parameter, val, location)
	VALUES ('channel_1','/dev/dsp',1);
INSERT INTO configuration (parameter, val, location)
    VALUES ('channel_2','/dev/null',1);
INSERT INTO configuration (parameter, val, location)
    VALUES ('channel_3','/dev/null',1);
INSERT intO configuration (parameter, val, location)
	VALUES ('channel_4','/dev/null',1);
INSERT INTO configuration (parameter, val, location)
	VALUES ('player1_md5','',1);
INSERT INTO configuration (parameter, val, location)
    VALUES ('player2_md5','',1);
INSERT INTO configuration (parameter, val, location)
    VALUES ('player3_md5','',1);
INSERT INTO configuration (parameter, val, location)
    VALUES ('player1_state','',1);
INSERT INTO configuration (parameter, val, location)
    VALUES ('player2_state','',1);
INSERT INTO configuration (parameter, val, location)
    VALUES ('player3_state','',1);
INSERT INTO configuration (parameter, val, location)
    VALUES ('next_on_showplan','',1);
INSERT INTO configuration (parameter, val, location)
	VALUES ('station_cartset','0',1);

/* Second studio configuration */
INSERT INTO configuration (parameter, val, location)
    VALUES ('channel_1','/dev/dsp',2);
INSERT INTO configuration (parameter, val, location)
    VALUES ('channel_2','/dev/null',2);
INSERT INTO configuration (parameter, val, location)
    VALUES ('channel_3','/dev/null',2);
INSERT iNTO configuration (parameter, val, location)
	VALUES ('channel_4','/dev/null',2);
INSERT INTO configuration (parameter, val, location)
    VALUES ('player1_md5','',2);
INSERT INTO configuration (parameter, val, location)
    VALUES ('player2_md5','',2);
INSERT INTO configuration (parameter, val, location)
    VALUES ('player3_md5','',2);
INSERT INTO configuration (parameter, val, location)
    VALUES ('player1_state','',2);
INSERT INTO configuration (parameter, val, location)
    VALUES ('player2_state','',2);
INSERT INTO configuration (parameter, val, location)
    VALUES ('player3_state','',2);
INSERT INTO configuration (parameter, val, location)
    VALUES ('next_on_showplan','',2);
INSERT INTO configuration (parameter, val, location)
	VALUES ('station_cartset','0',2);
END TRANSACTION;
