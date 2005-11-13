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
