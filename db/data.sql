/* Archives */
INSERT INTO archives (id, name, mountstring)
	VALUES (0,'store1','/mnt/dps0-0/audio');
	
/* Audio types */
INSERT INTO audiotypes (id, name, description) 
	VALUES (0,'music','Music tracks from the CD library or other sources');
INSERT INTO audiotypes (id, name, description)
	VALUES (1,'jingle','Station Idents');
INSERT INTO audiotypes (id, name, description)
	VALUES (2,'advert','Advertisments');

/* Sustainer source types */
INSERT INTO sust_sources (id, name, description)
	VALUES (0,'file','The source of this audio is the disk array');
INSERT INTO sust_sources (id, name, description)
	VALUES (1,'ext','The source of this audio is a soundcard input');

/* Root directory */
INSERT INTO dir (id, parent, name, notes)
	VALUES (0, -1,'Digiplay','Root node of virtual directory structure');

/* Default users */
INSERT INTO users (id, username, enabled)
	VALUES (0, 'system','t');

/* No album */
INSERT INTO albums (id, name)
	VALUES (0, '(none)');

/* Default Jingle type */
INSERT INTO jingletypes (id, name)
	VALUES (0, 'Idents');

/* Lifespans */
INSERT INTO lifespans (id, name, data, description)
	VALUES (0,'Permenant','-1','Permenant audio file - i.e. music library');

/* Configuration */
INSERT INTO configuration (id, parameter, val)
	VALUES (0,'bin_weighting_1','5');
INSERT INTO configuration (id, parameter, val)
	VALUES (1,'bin_weighting_2','9');
INSERT INTO configuration (id, parameter, val)
	VALUES (2,'bin_weighting_3','12');
INSERT INTO configuration (id, parameter, val)
	VALUES (3,'bin_weighting_4','14');
INSERT INTO configuration (id, parameter, val)
	VALUES (4,'bin_weighting_5','15');
/* Studio Application configuration */
INSERT INTO configuration (id, parameter, val, location)
	VALUES (5,'channel_1','/dev/null',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (6,'channel_2','/dev/null',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (7,'channel_3','/dev/null',1);
INSERT INTO configuration (id, parameter, val, location)
	VALUES (8,'player1_md5','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (9,'player2_md5','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (10,'player3_md5','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (11,'player1_state','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (12,'player2_state','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (13,'player3_state','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (14,'next_on_showplan','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (15,'station_cartwall','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (16,'station_cartwall_next','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (17,'station_cartwall_prev','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (18,'user_cartwall','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (19,'user_cartwall_next','',1);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (20,'user_cartwall_prev','',1);

INSERT INTO configuration (id, parameter, val, location)
    VALUES (21,'channel_1','/dev/null',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (22,'channel_2','/dev/null',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (23,'channel_3','/dev/null',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (24,'player1_md5','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (25,'player2_md5','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (26,'player3_md5','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (27,'player1_state','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (28,'player2_state','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (29,'player3_state','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (30,'next_on_showplan','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (31,'station_cartwall','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (32,'station_cartwall_next','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (33,'station_cartwall_prev','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (34,'user_cartwall','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (35,'user_cartwall_next','',2);
INSERT INTO configuration (id, parameter, val, location)
    VALUES (36,'user_cartwall_prev','',2);

