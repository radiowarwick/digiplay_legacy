-- RaW Digiplay views for database scheme
-- --------------------------------------
--
-- v_tree_getInherited(int,int)
-- Examines explicitly defined permissions on the parent to inherit for the
-- child object. Permissions currently propagate one level down the tree,
-- therefore *every* directory should have explicit permissions so that each
-- audio,carset,script,etc takes on the permissions of the directory it's in
-- unless explicitly set.
--
SET check_function_bodies = false;
CREATE OR REPLACE FUNCTION v_tree_getInherited(IN int8, IN int8) RETURNS bit(8) AS $$
    DECLARE
        int_id ALIAS FOR $1;
        int_userid ALIAS FOR $2;
        result RECORD;
        int_parent int8;
        int_type int8;
        bit_permissions bit(8);
    BEGIN
        SELECT INTO bit_permissions bit_or(permissions) 
                    FROM v_tree_dir_explicit 
                    WHERE id = int_id AND userid = int_userid 
                    GROUP BY id;
        IF NOT FOUND THEN
            RETURN '00000000';
        END IF;
        RETURN bit_permissions;
    END $$ LANGUAGE 'plpgsql';

--
-- array_accum
--
DROP AGGREGATE IF EXISTS array_accum(anyelement) CASCADE;
CREATE AGGREGATE array_accum (
    sfunc = array_append,
    basetype = anyelement,
    stype = anyarray,
    initcond = '{}'
);

--
-- v_tree_dir_explicit
-- Shows the explicit user or group permissions defined on directory objects
--
CREATE OR REPLACE VIEW v_tree_dir_explicit
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  dir.id AS id,
            dir.name AS name,
            dir.parent AS parent,
            users.id AS userid,
            users.username AS username,
            dirusers.permissions AS permissions,
            'user'::text AS causetype,
            users.id AS cause
    FROM    dir, users, dirusers
    WHERE   (dir.id = dirusers.dirid)
        AND (dirusers.userid = users.id)

    UNION

    SELECT  dir.id AS id,
            dir.name AS name,
            dir.parent AS parent,
            users.id AS userid,
            users.username AS username,
            dirgroups.permissions AS permissions,
            'group'::text AS causetype,
            groups.id AS cause
    FROM    dir, groups, dirgroups, usersgroups, users
    WHERE   (dir.id = dirgroups.dirid)
        AND (dirgroups.groupid = groups.id)
        AND (usersgroups.groupid = groups.id)
        AND (usersgroups.userid = users.id)
;

--
-- v_tree_dir_inherited
-- Shows the inherited user and group permissions defined on a directory
--
CREATE OR REPLACE VIEW v_tree_dir_inherited
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  dir.id,
            dir.name,
            dir.parent,
            users.id,
            users.username,
            v_tree_getInherited(dir.parent,users.id) AS permissions,
            'inherited'::text AS causetype,
            users.id AS cause
    FROM    dir cross join users
    WHERE   v_tree_getInherited(dir.parent,users.id) != '00000000'
        AND (dir.inherit = 't');
;
   
--
-- v_tree_dir
-- Shows the overall permissions for each user on each directory object
--
CREATE OR REPLACE VIEW v_tree_dir
    (id,name,parent,userid,username,permissions)
AS
    SELECT id,name,parent,userid,username,bit_or(permissions) AS permissions
    FROM (
        SELECT * FROM v_tree_dir_explicit 
        UNION 
        SELECT * FROM v_tree_dir_inherited
    ) AS Q1
    GROUP BY id,name,parent,userid,username
    HAVING bit_or(permissions) != '00000000'
;

--
-- v_tree_music_explicit
-- Shows explicit permissions defined on music tracks
--
CREATE OR REPLACE VIEW v_tree_music_explicit
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  audio.id AS id,
            audio.title AS name,
            audiodir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            audiousers.permissions AS permissions, 
            'user'::text AS causetype,
            users.id AS cause 
    FROM    audio, audiodir, audiousers, users
    WHERE   (audiodir.audioid = audio.id)
        AND (audiousers.audioid = audio.id)
        AND (audiousers.userid = users.id)
        AND (audio.type = 1)

    UNION

    SELECT  audio.id AS id,
            audio.title AS name,
            audiodir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            audiogroups.permissions AS permissions,
            'group'::text AS causetype,
            groups.id AS cause
    FROM    audio, audiodir, audiogroups, usersgroups, users, groups
    WHERE   (audiodir.audioid = audio.id)
        AND (audiogroups.audioid = audio.id)
        AND (audiogroups.groupid = groups.id)
        AND (usersgroups.groupid = groups.id)
        AND (usersgroups.userid = users.id)
        AND (audio.type = 1)
;

--
-- v_tree_music_inherited
-- Shows the inherited user and group permissions defined on a music track
--
CREATE OR REPLACE VIEW v_tree_music_inherited
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  audio.id,
            audio.title,
            audiodir.dirid,
            users.id,
            users.username,
            v_tree_getInherited(audiodir.dirid,users.id) AS permissions,
            'inherited'::text AS causetype,
            users.id AS cause
    FROM    (audio inner join audiodir ON (audio.id = audiodir.audioid))
             cross join users
    WHERE   v_tree_getInherited(audiodir.dirid,users.id) != '00000000'
		AND (audiodir.inherit = 't')
        AND (audio.type = 1)
;

--
-- v_tree_music
-- Shows the overall permissions on a music track
--
CREATE OR REPLACE VIEW v_tree_music
    (id,name,parent,userid,username,permissions)
AS
    SELECT id,name,parent,userid,username,bit_or(permissions) AS permissions
    FROM (
        SELECT * FROM v_tree_music_explicit
        UNION
        SELECT * FROM v_tree_music_inherited
    ) AS Q1
    GROUP BY id,name,parent,userid,username
    HAVING bit_or(permissions) != '00000000'
;

--
-- v_tree_jingle_explicit
-- Shows the explicit permissions defined on jingle objects
--
CREATE OR REPLACE VIEW v_tree_jingle_explicit
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  audio.id AS id,
            audio.title AS name,
            audiodir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            audiousers.permissions AS permissions,
            'user'::text AS causetype,
            users.id AS cause
    FROM    audio, audiodir, audiousers, users
    WHERE   (audiodir.audioid = audio.id)
        AND (audiousers.audioid = audio.id)
        AND (audiousers.userid = users.id)
        AND (audio.type = 2)

    UNION

    SELECT  audio.id AS id,
            audio.title AS name,
            audiodir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            audiogroups.permissions AS permissions,
            'group'::text AS causetype,
            groups.id AS cause
    FROM    audio, audiodir, audiogroups, usersgroups, users, groups
    WHERE   (audiodir.audioid = audio.id)
        AND (audiogroups.audioid = audio.id)
        AND (audiogroups.groupid = groups.id)
        AND (usersgroups.groupid = groups.id)
        AND (usersgroups.userid = users.id)
        AND (audio.type = 2)
;

--
-- v_tree_jingle_inherited
-- Shows the inherited user and group permissions defined on a jingle
--
CREATE OR REPLACE VIEW v_tree_jingle_inherited
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  audio.id,
            audio.title,
            audiodir.dirid,
            users.id,
            users.username,
            v_tree_getInherited(audiodir.dirid,users.id) AS permissions,
            'inherited'::text AS causetype,
            users.id AS cause
    FROM    (audio inner join audiodir ON (audio.id = audiodir.audioid))
             cross join users
    WHERE   v_tree_getInherited(audiodir.dirid,users.id) != '00000000'
        AND (audiodir.inherit = 't')
        AND (audio.type = 2)
;

--
-- v_tree_jingle
-- Shows the overall permissions on each jingle for each user
--
CREATE OR REPLACE VIEW v_tree_jingle
    (id,name,parent,userid,username,permissions)
AS
    SELECT id,name,parent,userid,username,bit_or(permissions) AS permissions
    FROM (
        SELECT * FROM v_tree_jingle_explicit
        UNION
        SELECT * FROM v_tree_jingle_inherited
    ) AS Q1
    GROUP BY id,name,parent,userid,username
    HAVING bit_or(permissions) != '00000000'
;

-- v_tree_advert_explicit
-- Shows the explicit permissions defined on each advert
--
CREATE OR REPLACE VIEW v_tree_advert_explicit
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  audio.id AS id,
            audio.title AS name,
            audiodir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            audiousers.permissions AS permissions,
            'user'::text AS causetype,
            users.id AS cause
    FROM    audio, audiodir, audiousers, users
    WHERE   (audiodir.audioid = audio.id)
        AND (audiousers.audioid = audio.id)
        AND (audiousers.userid = users.id)
        AND (audio.type = 3)

    UNION

    SELECT  audio.id AS id,
            audio.title AS name,
            audiodir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            audiogroups.permissions AS permissions,
            'group'::text AS causetype,
            groups.id AS cause
    FROM    audio, audiodir, audiogroups, usersgroups, users, groups
    WHERE   (audiodir.audioid = audio.id)
        AND (audiogroups.audioid = audio.id)
        AND (audiogroups.groupid = groups.id)
        AND (usersgroups.groupid = groups.id)
        AND (usersgroups.userid = users.id)
        AND (audio.type = 3)
ORDER BY id;

--
-- v_tree_advert_inherited
-- Shows the inherited user and group permissions defined on a jingle
--
CREATE OR REPLACE VIEW v_tree_advert_inherited
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  audio.id,
            audio.title,
            audiodir.dirid,
            users.id,
            users.username,
            v_tree_getInherited(audiodir.dirid,users.id) AS permissions,
            'inherited'::text AS causetype,
            users.id AS cause
    FROM    (audio inner join audiodir ON (audio.id = audiodir.audioid))
             cross join users
    WHERE   v_tree_getInherited(audiodir.dirid,users.id) != '00000000'
        AND (audiodir.inherit = 't')
        AND (audio.type = 3)
;

--
-- v_tree_advert
-- Shows the overall permissions on an advert
--
CREATE OR REPLACE VIEW v_tree_advert
    (id,name,parent,userid,username,permissions)
AS
    SELECT id,name,parent,userid,username,bit_or(permissions) AS permissions
    FROM (
        SELECT * FROM v_tree_advert_explicit
        UNION
        SELECT * FROM v_tree_advert_inherited
    ) AS Q1
    GROUP BY id,name,parent,userid,username
    HAVING bit_or(permissions) != '00000000'
;

--
-- v_tree_prerec_explicit
-- Shows the explicit permissions defined on prerec objects
--
CREATE OR REPLACE VIEW v_tree_prerec_explicit
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  audio.id AS id,
            audio.title AS name,
            audiodir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            audiousers.permissions AS permissions,
            'user'::text AS causetype,
            users.id AS cause
    FROM    audio, audiodir, audiousers, users
    WHERE   (audiodir.audioid = audio.id)
        AND (audiousers.audioid = audio.id)
        AND (audiousers.userid = users.id)
        AND (audio.type = 4)

    UNION

    SELECT  audio.id AS id,
            audio.title AS name,
            audiodir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            audiogroups.permissions AS permissions,
            'group'::text AS causetype,
            groups.id AS cause
    FROM    audio, audiodir, audiogroups, usersgroups, users, groups
    WHERE   (audiodir.audioid = audio.id)
        AND (audiogroups.audioid = audio.id)
        AND (audiogroups.groupid = groups.id)
        AND (usersgroups.groupid = groups.id)
        AND (usersgroups.userid = users.id)
        AND (audio.type = 4)
;

--
-- v_tree_prerec_inherited
-- Shows the inherited user and group permissions defined on a prerec
--
CREATE OR REPLACE VIEW v_tree_prerec_inherited
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  audio.id,
            audio.title,
            audiodir.dirid,
            users.id,
            users.username,
            v_tree_getInherited(audiodir.dirid,users.id) AS permissions,
            'inherited'::text AS causetype,
            users.id AS cause
    FROM    (audio inner join audiodir ON (audio.id = audiodir.audioid))
             cross join users
    WHERE   v_tree_getInherited(audiodir.dirid,users.id) != '00000000'
        AND (audiodir.inherit = 't')
        AND (audio.type = 4)
;

--
-- v_tree_prerec
-- Shows the overall permissions on each jingle for each user
--
CREATE OR REPLACE VIEW v_tree_prerec
    (id,name,parent,userid,username,permissions)
AS
    SELECT id,name,parent,userid,username,bit_or(permissions) AS permissions
    FROM (
        SELECT * FROM v_tree_prerec_explicit
        UNION
        SELECT * FROM v_tree_prerec_inherited
    ) AS Q1
    GROUP BY id,name,parent,userid,username
    HAVING bit_or(permissions) != '00000000'
;

--
--
-- v_tree_audio
-- Shows the overall permissions on audio objects for each user
--
CREATE OR REPLACE VIEW v_tree_audio
    (itemtype,id,name,parent,userid,username,permissions) 
AS
    SELECT itemtype, id, name, parent, userid, username,
            bit_or(permissions) AS permissions
    FROM (
        SELECT 'music' AS itemtype, v_tree_music.* FROM v_tree_music
        UNION
        SELECT 'jingle' AS itemtype, v_tree_jingle.* FROM v_tree_jingle
        UNION
        SELECT 'prerec' AS itemtype, v_tree_prerec.* FROM v_tree_prerec
        UNION
        SELECT 'advert' AS itemtype, v_tree_advert.* FROM v_tree_advert
    ) AS Q1
GROUP BY itemtype, id, name, parent, userid, username
HAVING bit_or(permissions) != '00000000'
ORDER BY itemtype, name;

--
-- v_tree_cartset_explicit
-- Show the explicitely defined permissions on cartset objects
--
CREATE OR REPLACE VIEW v_tree_aw_sets_explicit
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  aw_sets.id AS id,
            aw_sets.name AS name,
            aw_sets_dir.dir_id AS parent,
            users.id AS userid,
            users.username AS username,
            aw_sets_users.permissions AS permissions,
            'user'::text AS causetype,
            users.id AS cause
    FROM    aw_sets, aw_sets_dir, aw_sets_users, users
    WHERE   (aw_sets_dir.set_id = aw_sets.id)
        AND (aw_sets_users.set_id = aw_sets.id)
        AND (aw_sets_users.user_id = users.id)

    UNION

    SELECT  aw_sets.id AS id,
            aw_sets.name AS name,
            aw_sets_dir.dir_id AS parent,
            users.id AS userid,
            users.username AS username,
            aw_sets_groups.permissions AS permissions,
            'group'::text AS causetype,
            groups.id AS cause
    FROM    aw_sets, aw_sets_dir, aw_sets_groups, usersgroups, users, groups
    WHERE   (aw_sets_dir.set_id = aw_sets.id)
        AND (aw_sets_groups.set_id = aw_sets.id)
        AND (aw_sets_groups.group_id = groups.id)
        AND (usersgroups.groupid = groups.id)
        AND (usersgroups.userid = users.id)
;

--
-- v_tree_aw_sets_inherited
-- Shows the inherited user and group permissions defined on an audiowall set
--
CREATE OR REPLACE VIEW v_tree_aw_sets_inherited
    (id,name,parent,userid,username,permissions,causetype,cause)
AS  
    SELECT  aw_sets.id,
            aw_sets.name,
            aw_sets_dir.dir_id,
            users.id,
            users.username,
            v_tree_getInherited(aw_sets_dir.dir_id,users.id) AS permissions,
            'inherited'::text AS causetype,
            users.id AS cause
    FROM    (aw_sets inner join aw_sets_dir 
                    ON (aw_sets.id = aw_sets_dir.set_id))
             cross join users
    WHERE   v_tree_getInherited(aw_sets_dir.dir_id,users.id) != '00000000'
        AND (aw_sets_dir.inherit = 't')
;

--
-- v_tree_aw_sets
-- Show the overall permissions defined on cartset objects
--
CREATE OR REPLACE VIEW v_tree_aw_sets
    (id,name,parent,userid,username,permissions)
AS
    SELECT id,name,parent,userid,username,bit_or(permissions) AS permissions
    FROM (
        SELECT * FROM v_tree_aw_sets_explicit
        UNION
        SELECT * FROM v_tree_aw_sets_inherited
    ) AS Q1
    GROUP BY id,name,parent,userid,username
    HAVING bit_or(permissions) != '00000000'
;

--
-- v_tree_script_explicit
-- Shows the explicitely defined permissions on script objects
--
CREATE OR REPLACE VIEW v_tree_script_explicit
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  scripts.id AS id,
            scripts.name AS name,
            scriptsdir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            scriptsusers.permissions AS permissions,
            'user'::text AS causetype,
            users.id AS cause
    FROM    scripts, scriptsdir, scriptsusers, users
    WHERE   (scriptsdir.scriptid = scripts.id)
        AND (scriptsusers.scriptid = scripts.id)
        AND (scriptsusers.userid = users.id)

    UNION

    SELECT  scripts.id AS id,
            scripts.name AS name,
            scriptsdir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            scriptsgroups.permissions AS permissions,
            'group'::text AS causetype,
            groups.id AS cause
    FROM    scripts, scriptsdir, scriptsgroups, usersgroups, users, groups
    WHERE   (scriptsdir.scriptid = scripts.id)
        AND (scriptsgroups.scriptid = scripts.id)
        AND (scriptsgroups.groupid = groups.id)
        AND (usersgroups.groupid = groups.id)
        AND (usersgroups.userid = users.id)
;

--
-- v_tree_script_inherited
-- Shows the inherited user and group permissions defined on a script
--
CREATE OR REPLACE VIEW v_tree_script_inherited
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  scripts.id,
            scripts.name,
            scriptsdir.dirid,
            users.id,
            users.username,
            v_tree_getInherited(scriptsdir.dirid,users.id) AS permissions,
            'inherited'::text AS causetype,
            users.id AS cause
    FROM    (scripts inner join scriptsdir 
                    ON (scripts.id = scriptsdir.scriptid))
             cross join users
    WHERE   v_tree_getInherited(scriptsdir.dirid,users.id) != '00000000'
        AND (scriptsdir.inherit = 't')
;

--
-- v_tree_script
-- Shows the overall permissions on a script object for each user
--
CREATE OR REPLACE VIEW v_tree_script
    (id,name,parent,userid,username,permissions)
AS
    SELECT id,name,parent,userid,username,bit_or(permissions) AS permissions
    FROM (
        SELECT * FROM v_tree_script_explicit
        UNION
        SELECT * FROM v_tree_script_inherited
    ) AS Q1
    GROUP BY id,name,parent,userid,username
    HAVING bit_or(permissions) != '00000000'
;

--
-- v_tree_showplan_explicit
-- Shows the explicitely defined permissions on showplan objects
--
CREATE OR REPLACE VIEW v_tree_showplan_explicit
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  showplans.id AS id,
            showplans.name AS name,
            showplansdir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            showplansusers.permissions AS permissions,
            'user'::text AS causetype,
            users.id AS cause
    FROM    showplans, showplansdir, showplansusers, users
    WHERE   (showplansdir.showplanid = showplans.id)
        AND (showplansusers.showplanid = showplans.id)
        AND (showplansusers.userid = users.id)

    UNION

    SELECT  showplans.id AS id,
            showplans.name AS name,
            showplansdir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            showplansgroups.permissions AS permissions,
            'group'::text AS causetype,
            groups.id AS cause
    FROM    showplans, showplansdir, showplansgroups, usersgroups, users, groups
    WHERE   (showplansdir.showplanid = showplans.id)
        AND (showplansgroups.showplanid = showplans.id)
        AND (showplansgroups.groupid = groups.id)
        AND (usersgroups.groupid = groups.id)
        AND (usersgroups.userid = users.id)
;

--
-- v_tree_showplan_inherited
-- Shows the inherited user and group permissions defined on a showplan
--
CREATE OR REPLACE VIEW v_tree_showplan_inherited
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  showplans.id,
            showplans.name,
            showplansdir.dirid,
            users.id,
            users.username,
            v_tree_getInherited(showplansdir.dirid,users.id) AS permissions,
            'inherited'::text AS causetype,
            users.id AS cause
    FROM    (showplans inner join showplansdir 
                    ON (showplans.id = showplansdir.showplanid))
             cross join users
    WHERE   v_tree_getInherited(showplansdir.dirid,users.id) != '00000000'
        AND (showplansdir.inherit = 't')
;

--
-- v_tree_showplan
-- Shows the overall permissions on a showplan object for each user
--
CREATE OR REPLACE VIEW v_tree_showplan
    (id,name,parent,userid,username,permissions)
AS
    SELECT id,name,parent,userid,username,bit_or(permissions) AS permissions
    FROM (
        SELECT * FROM v_tree_showplan_explicit
        UNION
        SELECT * FROM v_tree_showplan_inherited
    ) AS Q1
    GROUP BY id,name,parent,userid,username
    HAVING bit_or(permissions) != '00000000'
;

--
-- v_tree
-- Shows the overall permissions on all objects for each user
--
CREATE OR REPLACE VIEW v_tree 
    (itemtype,id,name,parent,userid,username,permissions) 
AS
    SELECT itemtype, id, name, parent, userid, username,
            bit_or(permissions) AS permissions
    FROM (
        SELECT 'dir' AS itemtype, v_tree_dir.* FROM v_tree_dir
        UNION
        SELECT 'aw_set' AS itemtype, v_tree_aw_sets.* FROM v_tree_aw_sets
        UNION
        SELECT 'script' AS itemtype, v_tree_script.* FROM v_tree_script
        UNION
        SELECT 'music' AS itemtype, v_tree_music.* FROM v_tree_music
        UNION
        SELECT 'jingle' AS itemtype, v_tree_jingle.* FROM v_tree_jingle
        UNION
        SELECT 'prerec' AS itemtype, v_tree_prerec.* FROM v_tree_prerec
        UNION
        SELECT 'advert' AS itemtype, v_tree_advert.* FROM v_tree_advert
        UNION
        SELECT 'showplan' AS itemtype, v_tree_showplan.* FROM v_tree_showplan
    ) AS Q1
GROUP BY itemtype, id, name, parent, userid, username
HAVING bit_or(permissions) != '00000000'
ORDER BY itemtype, name;

-- v_audiowalls
CREATE OR REPLACE VIEW v_audiowalls
AS
    SELECT  audio.md5 AS md5, 
            archives.localpath AS path, 
            audio.start_smpl AS start, 
            audio.end_smpl AS end, 
            aw_items.item AS item, 
            aw_items.text AS text, 
            aw_walls.name AS wall_name, 
            aw_walls.description AS wall_desc,
            aw_walls.page AS page, 
            aw_sets.id AS set_id, 
            aw_sets.name AS set, 
            aw_sets.description AS set_desc, 
            aw_props.name AS prop_name, 
            aw_styles_props.value AS prop_value
    FROM    audio, aw_items, aw_walls, aw_sets, aw_styles, aw_styles_props,
            aw_props, archives
    WHERE   (aw_items.audio_id = audio.id)
        AND (aw_items.wall_id = aw_walls.id)
        AND (aw_walls.set_id = aw_sets.id)
        AND (aw_items.style_id = aw_styles.id)
        AND (aw_styles_props.style_id = aw_styles.id)
        AND (aw_styles_props.prop_id = aw_props.id)
        AND (audio.archive = archives.id)
    ORDER BY aw_walls.id, aw_items.item, aw_props.id;

-- v_scripts
CREATE OR REPLACE VIEW v_scripts
AS
    SELECT  scripts.id AS id,
            scripts.name AS name,
            scripts.contents AS contents,
            scripts.length AS length,
            users.username AS userid
    FROM    scripts, users
    WHERE   (scripts.userid = users.id)
    ORDER BY scripts.id;

-- v_showplan
CREATE OR REPLACE VIEW v_showplan
AS
    SELECT  showitems.showplanid AS id,
            showitems.position AS position,
            audio.id AS key,
            audio.md5 AS md5,
            'audio'::text AS itemtype,
            audiotypes.name AS audiotype,
            showitems.comment AS comment
    FROM    audio,audiotypes,showitems
    WHERE   (showitems.audioid = audio.id)
        AND (audiotypes.id = audio.type)
    UNION
    SELECT  showitems.showplanid AS id,
            showitems.position AS position,
            scripts.id AS key,
            ''::text AS md5,
            'script'::text AS itemtype,
            ''::text AS audiotype,
            showitems.comment AS comment
    FROM    scripts, showitems
    WHERE   (showitems.scriptid = scripts.id)
    UNION
    SELECT  showitems.showplanid AS id,
            showitems.position AS position,
            showitems.id AS key,
            ''::text AS md5,
            'note'::text AS itemtype,
            ''::text AS audiotype,
            showitems.comment AS comment
    FROM    showitems
    WHERE   (showitems.audioid IS NULL)
        AND (showitems.scriptid IS NULL)
    ORDER BY position;

-- v_audio_track
CREATE OR REPLACE VIEW v_audio_music
AS
    SELECT  audio.id AS id, 
            audio.md5 AS md5, 
            audio.title AS title, 
            array_to_string(array_accum(artists.name),'; ') AS artist, 
            albums.name AS album, 
            archives.id AS archiveid, 
            archives.name AS archive,
            archives.localpath AS path, 
            audio.music_track AS track, 
            audio.music_released AS released, 
            audio.origin AS origin, 
            audio.censor AS censor, 
            audiodir.dirid AS dir, 
            audio.length_smpl AS length_smpl, 
            audio.start_smpl AS start_smpl, 
            audio.end_smpl AS end_smpl, 
            audio.intro_smpl AS intro_smpl, 
            audio.extro_smpl AS extro_smpl, 
            lifespans.data AS lifespan, 
            audio.sustainer AS sustainer,
            audio.filetype AS filetype
    FROM audio, audioartists, artists, albums, archives, lifespans, 
         audiodir, dir
    WHERE   (audioartists.audioid = audio.id)
        AND (audioartists.artistid = artists.id)
        AND (audio.archive = archives.id)
        AND (audio.music_album = albums.id)
        AND (audio.lifespan = lifespans.id)
        AND (audiodir.audioid = audio.id)
        AND (audiodir.dirid = dir.id)
        AND (audiodir.linktype = 0)
        AND (audio.type = 1)
    GROUP BY audio.id,  audio.md5, audio.title, albums.name, archives.id,
            archives.name, archives.localpath, audio.music_track,
            audio.music_released, audio.origin, audio.censor, audiodir.dirid,
            audio.length_smpl, audio.start_smpl, audio.end_smpl, 
            audio.intro_smpl, audio.extro_smpl, lifespans.data, 
            audio.sustainer, audio.filetype
    ORDER BY audio.md5;

-- v_audio_jingles
CREATE OR REPLACE VIEW v_audio_jingles
AS
    SELECT  audio.id AS id, 
            audio.md5 AS md5, 
            audio.title AS title, 
            archives.id AS archiveid, 
            archives.name AS archive,
            archives.localpath AS path,
            jinglepkgs.name AS pkg, 
            jinglepkgs.enabled AS enabled, 
            jingletypes.name AS type, 
            dir.id AS dirid, 
            dir.name AS dir, 
            audio.length_smpl AS length_smpl, 
            audio.start_smpl AS start_smpl, 
            audio.end_smpl AS end_smpl, 
            audio.intro_smpl AS intro_smpl, 
            audio.extro_smpl AS extro_smpl, 
            lifespans.data AS lifespan,
            audio.filetype AS filetype
    FROM audio, archives, audiojinglepkgs, jinglepkgs, jingletypes, audiodir,
         dir, lifespans
    WHERE   (archives.id = audio.archive)
        AND (audio.type = 2)
        AND (jinglepkgs.id = audiojinglepkgs.jinglepkgid)
        AND (audiojinglepkgs.audioid = audio.id)
        AND (audiojinglepkgs.jingletypeid = jingletypes.id)
        AND (audiodir.audioid = audio.id)
        AND (audiodir.dirid = dir.id)
        AND (audio.lifespan = lifespans.id)
    ORDER BY audio.md5;

-- v_audio_adverts
CREATE OR REPLACE VIEW v_audio_adverts
AS
    SELECT  audio.id AS id, 
            audio.md5 AS md5, 
            audio.title AS title, 
            archives.id AS archiveid, 
            archives.name AS archive, 
            archives.localpath AS path,
            dir.id AS dirid, 
            dir.name AS dir, 
            companies.name AS company, 
            audio.advert_description AS description, 
            audio.length_smpl AS length_smpl, 
            audio.start_smpl AS start_smpl, 
            audio.end_smpl AS end_smpl, 
            audio.intro_smpl AS intro_smpl, 
            audio.extro_smpl AS extro_smpl,
            lifespans.data AS lifespan, 
            'f'::character(1) AS sustainer,
            audio.filetype AS filetype
    FROM audio, archives, audiodir, dir, lifespans, companies
    WHERE   (archives.id = audio.archive)
        AND (audio.type = 3)
        AND (audiodir.audioid = audio.id)
        AND (audiodir.dirid = dir.id)
        AND (audio.lifespan = lifespans.id)
        AND (audio.advert_company = companies.id)
    ORDER BY audio.md5;

-- v_audio_prerec
CREATE OR REPLACE VIEW v_audio_prerec
AS
    SELECT  audio.id AS id, 
            audio.md5 AS md5, 
            audio.title AS title, 
            array_to_string(array_accum(artists.name),', ') AS artist, 
            albums.name AS album, 
            archives.id AS archiveid, 
            archives.name AS archive,
            archives.localpath AS path, 
            audio.music_track AS track, 
            audio.music_released AS released, 
            audio.origin AS origin, 
            audio.censor AS censor, 
            audiodir.dirid AS dir, 
            audio.length_smpl AS length_smpl, 
            audio.start_smpl AS start_smpl, 
            audio.end_smpl AS end_smpl, 
            audio.intro_smpl AS intro_smpl, 
            audio.extro_smpl AS extro_smpl, 
            lifespans.data AS lifespan, 
            audio.sustainer AS sustainer,
            audio.filetype AS filetype
    FROM audio, audioartists, artists, albums, archives, lifespans, 
         audiodir, dir
    WHERE   (audioartists.audioid = audio.id)
        AND (audioartists.artistid = artists.id)
        AND (audio.archive = archives.id)
        AND (audio.music_album = albums.id)
        AND (audio.lifespan = lifespans.id)
        AND (audiodir.audioid = audio.id)
        AND (audiodir.dirid = dir.id)
        AND (audiodir.linktype = 0)
        AND (audio.type = 4)
    GROUP BY audio.id,  audio.md5, audio.title, albums.name, archives.id,
            archives.name, archives.localpath, audio.music_track,
            audio.music_released, audio.origin, audio.censor, audiodir.dirid,
            audio.length_smpl, audio.start_smpl, audio.end_smpl, 
            audio.intro_smpl, audio.extro_smpl, lifespans.data, audio.sustainer,
            audio.filetype
    ORDER BY audio.md5;

-- v_audio
CREATE OR REPLACE VIEW v_audio
    (audiotype,id,md5,title,artist,album,archiveid,archive,path,track,released,
        length_smpl,start_smpl,end_smpl,intro_smpl,extro_smpl,lifespan,
        sustainer,filetype)
AS
    SELECT 'Music'::character varying,id,md5,title,artist,album,archiveid,
			archive,path,track,released,length_smpl,start_smpl,end_smpl,
			intro_smpl,extro_smpl,lifespan,sustainer,filetype
    FROM v_audio_music
    UNION
    SELECT 'Jingle'::character varying,id,md5,title,'' AS artist,pkg AS album,
			archiveid,archive,path,'0' AS track,'0' AS released,length_smpl,
			start_smpl,end_smpl,intro_smpl,extro_smpl,lifespan,
			enabled AS sustainer,filetype
    FROM v_audio_jingles
    UNION
    SELECT 'Advert'::character varying,id,md5,title,'' AS artist,
			company AS album,archiveid,archive,path,'0' AS track,
			'0' AS released,length_smpl,start_smpl,end_smpl,intro_smpl,
			extro_smpl,lifespan,sustainer,filetype
    FROM v_audio_adverts
    UNION
    SELECT 'Prerec'::character varying,id,md5,title,artist,album,
			archiveid,archive,path,'0' AS track,'0' AS released,length_smpl,
			start_smpl,end_smpl,intro_smpl,extro_smpl,lifespan,sustainer, 
			filetype
    FROM v_audio_prerec
ORDER BY id;
