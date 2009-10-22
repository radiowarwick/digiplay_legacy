--
-- Rules for notifying software apps of updates to tables and maintaining
-- data consistency.
--

--
-- Logging table
--
CREATE OR REPLACE RULE r_log_insert AS ON INSERT TO log DO 
	NOTIFY t_log;
CREATE OR REPLACE RULE r_log_update AS ON UPDATE TO log DO 
	NOTIFY t_log;
CREATE OR REPLACE RULE r_log_delete AS ON DELETE TO log DO 
	NOTIFY t_log;

--
-- Email table
--
CREATE OR REPLACE RULE r_email_insert AS ON INSERT TO email DO 
	NOTIFY t_email;
CREATE OR REPLACE RULE r_email_update AS ON UPDATE TO email DO 
	NOTIFY t_email;
CREATE OR REPLACE RULE r_email_delete AS ON DELETE TO email DO 
	NOTIFY t_email;

--
-- Playlists tables
--
CREATE OR REPLACE RULE r_audioplaylists_insert AS ON INSERT TO audioplaylists DO 
	NOTIFY t_playlists;
CREATE OR REPLACE RULE r_audioplaylists_update AS ON UPDATE TO audioplaylists DO 
	NOTIFY t_playlists;
CREATE OR REPLACE RULE r_audioplaylists_delete AS ON DELETE TO audioplaylists DO 
	NOTIFY t_playlists;
CREATE OR REPLACE RULE r_playlists_insert AS ON INSERT TO playlists DO 
	NOTIFY t_playlists;
CREATE OR REPLACE RULE r_playlists_update AS ON UPDATE TO playlists DO 
	NOTIFY t_playlists;
CREATE OR REPLACE RULE r_playlists_delete AS ON DELETE TO playlists DO 
	NOTIFY t_playlists;

--
-- Configuration tables
--
CREATE OR REPLACE RULE r_configuration_insert AS ON INSERT TO configuration DO 
	NOTIFY t_configuration;
CREATE OR REPLACE RULE r_configuration_update AS ON UPDATE TO configuration DO 
	NOTIFY t_configuration;

--
-- Audio walls
--    
CREATE OR REPLACE RULE r_aw_items_insert AS ON INSERT TO aw_items DO 
	NOTIFY t_audiowall;
CREATE OR REPLACE RULE r_aw_items_update AS ON UPDATE TO aw_items DO 
	NOTIFY t_audiowall;
CREATE OR REPLACE RULE r_aw_items_delete AS ON DELETE TO aw_items DO 
	NOTIFY t_audiowall;
	
--
-- Broadcast programming schedule tables
--
CREATE OR REPLACE RULE r_txschedule_insert AS
	ON INSERT TO txschedule DO NOTIFY t_txschedule;
CREATE OR REPLACE RULE r_txschedule_update AS
	ON UPDATE TO txschedule DO NOTIFY t_txschedule;
CREATE OR REPLACE RULE r_txschedule_delete AS
	ON DELETE TO txschedule DO NOTIFY t_txschedule;
CREATE OR REPLACE RULE r_txshowsusers_update AS
	ON UPDATE TO txshows DO NOTIFY t_txschedule;

--
-----------------------------------------------------------
-- Triggers and functions
-----------------------------------------------------------
--

--
-- GENERAL ROUTINES
--

-- f_user_required(integer)
-- Returns TRUE if a user is required to exist and kept as a ghost.
-- if FALSE, the user can be safely removed completey.
CREATE OR REPLACE FUNCTION f_user_required(INTEGER)
	RETURNS BOOLEAN AS $$
	DECLARE
		temp RECORD;
	BEGIN
		SELECT INTO temp * FROM audio WHERE audio.creator = $1;
		IF FOUND THEN
			RETURN TRUE;
		END IF;
		SELECT INTO temp * FROM audiolog WHERE userid = $1;
		IF FOUND THEN
			RETURN TRUE;
		END IF;
		SELECT INTO temp * FROM audiocomments WHERE userid = $1;
		IF FOUND THEN
			RETURN TRUE;
		END IF;
		RETURN FALSE;
	END $$ LANGUAGE 'plpgsql';

--
-- TRIGGER ROUTINES
--

-- f_aw_walls_delete()
CREATE OR REPLACE FUNCTION f_aw_walls_delete() 
	RETURNS TRIGGER AS $$ 
	BEGIN
		DELETE FROM aw_items WHERE wall_id = OLD.id;
		RETURN OLD;
	END	$$ LANGUAGE 'plpgsql';

-- f_aw_sets_delete()
CREATE OR REPLACE FUNCTION f_aw_sets_delete()
	RETURNS TRIGGER AS $$ 
	BEGIN
		DELETE FROM aw_walls WHERE set_id = OLD.id;
		DELETE FROM aw_sets_users WHERE set_id = OLD.id;
		DELETE FROM aw_sets_groups WHERE set_id = OLD.id;
		DELETE FROM aw_sets_dir WHERE set_id = OLD.id;
        DELETE FROM usersconfigs USING configs 
            WHERE configs.id = usersconfigs.configid
            AND configs.name = 'default_aw_set'
            AND usersconfigs.val = CAST(OLD.id AS VARCHAR);
		RETURN OLD;
	END $$ LANGUAGE 'plpgsql';

-- f_aw_styles_delete()
CREATE OR REPLACE FUNCTION f_aw_styles_delete()
	RETURNS TRIGGER AS $$
	DECLARE
		styles RECORD;
	BEGIN
		DELETE FROM aw_styles_props WHERE style_id = OLD.id;
		SELECT INTO styles id FROM aw_styles WHERE id != OLD.id LIMIT 1;
		IF NOT FOUND THEN
			RAISE EXCEPTION 'Cannot delete last style %!', OLD.name;
			RETURN NULL;
		END IF;
		UPDATE aw_items SET style_id = styles.id WHERE style_id = OLD.id;
		RETURN OLD;
	END $$ LANGUAGE 'plpgsql';

-- f_aw_props_delete()
CREATE OR REPLACE FUNCTION f_aw_props_delete()
	RETURNS TRIGGER AS $$
	BEGIN
		DELETE FROM aw_style_props WHERE style_id = OLD.id;
		RETURN OLD;
	END $$ LANGUAGE 'plpgsql';

-- f_users_delete()
CREATE OR REPLACE FUNCTION f_users_delete()
	RETURNS TRIGGER AS $$
	BEGIN
		DELETE FROM usersconfigs WHERE userid = OLD.id;
		DELETE FROM dirusers WHERE userid = OLD.id;
		DELETE FROM scriptsusers WHERE userid = OLD.id;
		DELETE FROM showplanusers WHERE userid = OLD.id;
		DELETE FROM usersgroups WHERE userid = OLD.id;
		DELETE FROM aw_sets_users WHERE user_id = OLD.id;
		DELETE FROM audiousers WHERE userid = OLD.id;
		IF f_user_required(OLD.id) THEN
			UPDATE users SET ghost = 't' WHERE id = OLD.id;
			RETURN NULL;
		END IF;
		RETURN OLD;
	END $$ LANGUAGE 'plpgsql';
	
-- f_groups_delete()
CREATE OR REPLACE FUNCTION f_groups_delete()
	RETURNS TRIGGER AS $$
	BEGIN
		DELETE FROM dirgroups WHERE groupid = OLD.id;
		DELETE FROM usersgroups WHERE groupid = OLD.id;
		DELETE FROM aw_sets_groups WHERE group_id = OLD.id;		
		DELETE FROM audiogroups WHERE groupid = OLD.id;
		RETURN OLD;
	END $$ LANGUAGE 'plpgsql';

-- f_dir_delete()
CREATE OR REPLACE FUNCTION f_dir_delete()
	RETURNS TRIGGER AS $$
	DECLARE
		audio_keys RECORD;
	BEGIN
		FOR audio_keys IN SELECT audioid FROM audiodir WHERE dirid = OLD.id AND linktype = 0 LOOP
			DELETE FROM AUDIO WHERE id = audio_keys.audioid;
		END LOOP;
		DELETE FROM audiodir WHERE id = OLD.id;
		DELETE FROM dirusers WHERE dirid = OLD.id;
		DELETE FROM dirgroups WHERE dirid = OLD.id;
		RETURN OLD;
	END $$ LANGUAGE 'plpgsql';

-- f_audio_delete()
CREATE OR REPLACE FUNCTION f_audio_delete()
	RETURNS TRIGGER AS $$
	BEGIN
		DELETE FROM audiodir WHERE audioid = OLD.id;
		DELETE FROM audiogroups WHERE audioid = OLD.id;
		DELETE FROM audiousers WHERE audioid = OLD.id;
		DELETE FROM audioplaylists WHERE audioid = OLD.id;
		DELETE FROM audiolog WHERE audioid = OLD.id;
		DELETE FROM audiocomments WHERE audioid = OLD.id;
		DELETE FROM advertschedule WHERE audioid = OLD.id;
		DELETE FROM audioartists WHERE audioid = OLD.id;
		DELETE FROM audiokeywords WHERE audioid = OLD.id;
		DELETE FROM audiojinglepkgs WHERE audioid = OLD.id;
		DELETE FROM aw_items WHERE audio_id = OLD.id;
		UPDATE showitems SET audioid = NULL WHERE audioid = OLD.id;
		DELETE FROM binsaudio WHERE audioid = OLD.id;
		RETURN OLD;
	END $$ LANGUAGE 'plpgsql';

-- f_showplans_delete()
CREATE OR REPLACE FUNCTION f_showplans_delete()
	RETURNS TRIGGER AS $$
	BEGIN
		DELETE FROM showitems WHERE showplanid = OLD.id;
		DELETE FROM showplansdir WHERE showplanid = OLD.id;
		DELETE FROM showplansusers WHERE showplanid = OLD.id;
		DELETE FROM showplansgroups WHERE showplanid = OLD.id;
		RETURN OLD;
	END $$ LANGUAGE 'plpgsql';
	
-- f_scripts_delete()
CREATE OR REPLACE FUNCTION f_scripts_delete()
	RETURNS TRIGGER AS $$
	BEGIN
		UPDATE showitems SET scriptid = NULL WHERE scriptid = OLD.id;
		DELETE FROM scriptsdir WHERE scriptid = OLD.id;
		DELETE FROM scriptsusers WHERE scriptid = OLD.id;
		DELETE FROM scriptsgroups WHERE scriptid = OLD.id;
		RETURN OLD;
	END $$ LANGUAGE 'plpgsql';
	
	
--
-- TRIGGERS
--	
DROP TRIGGER IF EXISTS t_aw_walls_delete ON aw_walls;
CREATE TRIGGER t_aw_walls_delete BEFORE DELETE ON aw_walls
	FOR EACH ROW EXECUTE PROCEDURE f_aw_walls_delete();
DROP TRIGGER IF EXISTS t_aw_sets_delete ON aw_sets;
CREATE TRIGGER t_aw_sets_delete BEFORE DELETE ON aw_sets
	FOR EACH ROW EXECUTE PROCEDURE f_aw_sets_delete();
DROP TRIGGER IF EXISTS t_aw_styles_delete ON aw_styles;
CREATE TRIGGER t_aw_styles_delete BEFORE DELETE ON aw_styles
	FOR EACH ROW EXECUTE PROCEDURE f_aw_styles_delete();
DROP TRIGGER IF EXISTS t_aw_props_delete ON aw_props;
CREATE TRIGGER t_aw_props_delete BEFORE DELETE ON aw_props
	FOR EACH ROW EXECUTE PROCEDURE f_aw_props_delete();
DROP TRIGGER IF EXISTS t_users_delete ON users;
CREATE TRIGGER t_users_delete BEFORE DELETE ON users
	FOR EACH ROW EXECUTE PROCEDURE f_users_delete();
DROP TRIGGER IF EXISTS t_groups_delete ON groups;
CREATE TRIGGER t_groups_delete BEFORE DELETE ON groups
	FOR EACH ROW EXECUTE PROCEDURE f_groups_delete();
DROP TRIGGER IF EXISTS t_dir_delete ON dir;
CREATE TRIGGER t_dir_delete BEFORE DELETE ON dir
	FOR EACH ROW EXECUTE PROCEDURE f_dir_delete();
DROP TRIGGER IF EXISTS t_audio_delete ON audio;
CREATE TRIGGER t_audio_delete BEFORE DELETE ON audio
	FOR EACH ROW EXECUTE PROCEDURE f_audio_delete();
DROP TRIGGER IF EXISTS t_showplans_delete ON showplans;
CREATE TRIGGER t_showplans_delete BEFORE DELETE ON showplans
	FOR EACH ROW EXECUTE PROCEDURE f_showplans_delete();
DROP TRIGGER IF EXISTS t_scripts_delete ON scripts;
CREATE TRIGGER t_scripts_delete BEFORE DELETE ON scripts
	FOR EACH ROW EXECUTE PROCEDURE f_scripts_delete();
