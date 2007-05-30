CREATE RULE r_log_delete
AS
    ON DELETE TO log DO NOTIFY trig_id4;

CREATE RULE r_log_insert
AS
    ON INSERT TO log DO NOTIFY trig_id4;
    
CREATE RULE r_log_update
AS
    ON UPDATE TO log DO NOTIFY trig_id4;

CREATE RULE r_email_delete
AS
    ON DELETE TO email DO NOTIFY trig_id2;

CREATE RULE r_email_insert
AS
    ON INSERT TO email DO NOTIFY trig_id2;
    
CREATE RULE r_email_update
AS
    ON UPDATE TO email DO NOTIFY trig_id2;

CREATE RULE r_audioplaylists_delete
AS
    ON DELETE TO audioplaylists DO NOTIFY trig_id5;

CREATE RULE r_audioplaylists_insert
AS
    ON INSERT TO audioplaylists DO NOTIFY trig_id5;
    
CREATE RULE r_audioplaylists_update
AS
    ON UPDATE TO audioplaylists DO NOTIFY trig_id5;

CREATE RULE r_playlists_delete
AS
    ON DELETE TO playlists DO NOTIFY trig_id5;

CREATE RULE r_playlists_insert
AS
    ON INSERT TO playlists DO NOTIFY trig_id5;
    
CREATE RULE r_playlists_update
AS
    ON UPDATE TO playlists DO NOTIFY trig_id5;

CREATE RULE r_configuration_insert
AS
    ON INSERT TO configuration DO NOTIFY trig_id1;
    
CREATE RULE r_configuration_update
AS
    ON UPDATE TO configuration DO NOTIFY trig_id1;

CREATE RULE r_cartsaudio_delete
AS
    ON DELETE TO cartsaudio DO NOTIFY trig_id3;

CREATE RULE r_cartsaudio_insert
AS
    ON INSERT TO cartsaudio DO NOTIFY trig_id3;
    
CREATE RULE r_cartsaudio_update
AS
    ON UPDATE TO cartsaudio DO NOTIFY trig_id3;

