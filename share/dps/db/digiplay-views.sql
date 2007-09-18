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
CREATE OR REPLACE FUNCTION v_tree_getInherited(IN int8, IN int8) RETURNS bit(8) AS '
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
            RETURN \'00000000\';
        END IF;
        RETURN bit_permissions;
    END' LANGUAGE 'plpgsql';

--
-- array_accum
--
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
CREATE OR REPLACE VIEW v_tree_cartset_explicit
    (id,name,parent,userid,username,permissions,causetype,cause)
AS
    SELECT  cartsets.id AS id,
            cartsets.name AS name,
            cartsetsdir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            cartsetsusers.permissions AS permissions,
            'user'::text AS causetype,
            users.id AS cause
    FROM    cartsets, cartsetsdir, cartsetsusers, users
    WHERE   (cartsetsdir.cartsetid = cartsets.id)
        AND (cartsetsusers.cartsetid = cartsets.id)
        AND (cartsetsusers.userid = users.id)

    UNION

    SELECT  cartsets.id AS id,
            cartsets.name AS name,
            cartsetsdir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            cartsetsgroups.permissions AS permissions,
            'group'::text AS causetype,
            groups.id AS cause
    FROM    cartsets, cartsetsdir, cartsetsgroups, usersgroups, users, groups
    WHERE   (cartsetsdir.cartsetid = cartsets.id)
        AND (cartsetsgroups.cartsetid = cartsets.id)
        AND (cartsetsgroups.groupid = groups.id)
        AND (usersgroups.groupid = groups.id)
        AND (usersgroups.userid = users.id)
;

--
-- v_tree_cartset_inherited
-- Shows the inherited user and group permissions defined on a cartset
--
CREATE OR REPLACE VIEW v_tree_cartset_inherited
    (id,name,parent,userid,username,permissions,causetype,cause)
AS  
    SELECT  cartsets.id,
            cartsets.name,
            cartsetsdir.dirid,
            users.id,
            users.username,
            v_tree_getInherited(cartsetsdir.dirid,users.id) AS permissions,
            'inherited'::text AS causetype,
            users.id AS cause
    FROM    (cartsets inner join cartsetsdir 
                    ON (cartsets.id = cartsetsdir.cartsetid))
             cross join users
    WHERE   v_tree_getInherited(cartsetsdir.dirid,users.id) != '00000000'
        AND (cartsetsdir.inherit = 't')
;

--
-- v_tree_cartset
-- Show the overall permissions defined on cartset objects
--
CREATE OR REPLACE VIEW v_tree_cartset
    (id,name,parent,userid,username,permissions)
AS
    SELECT id,name,parent,userid,username,bit_or(permissions) AS permissions
    FROM (
        SELECT * FROM v_tree_cartset_explicit
        UNION
        SELECT * FROM v_tree_cartset_inherited
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
            showplandir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            showplanusers.permissions AS permissions,
            'user'::text AS causetype,
            users.id AS cause
    FROM    showplans, showplandir, showplanusers, users
    WHERE   (showplandir.showplanid = showplans.id)
        AND (showplanusers.showplanid = showplans.id)
        AND (showplanusers.userid = users.id)

    UNION

    SELECT  showplans.id AS id,
            showplans.name AS name,
            showplandir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            showplangroups.permissions AS permissions,
            'group'::text AS causetype,
            groups.id AS cause
    FROM    showplans, showplandir, showplangroups, usersgroups, users, groups
    WHERE   (showplandir.showplanid = showplans.id)
        AND (showplangroups.showplanid = showplans.id)
        AND (showplangroups.groupid = groups.id)
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
            showplandir.dirid,
            users.id,
            users.username,
            v_tree_getInherited(showplandir.dirid,users.id) AS permissions,
            'inherited'::text AS causetype,
            users.id AS cause
    FROM    (showplans inner join showplandir 
                    ON (showplans.id = showplandir.showplanid))
             cross join users
    WHERE   v_tree_getInherited(showplandir.dirid,users.id) != '00000000'
        AND (showplandir.inherit = 't')
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
        SELECT 'cartset' AS itemtype, v_tree_cartset.* FROM v_tree_cartset
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

-- v_cartwalls
CREATE OR REPLACE VIEW v_cartwalls
AS
    SELECT  audio.md5 AS md5, 
            archives.localpath AS path, 
            audio.start_smpl AS start, 
            audio.end_smpl AS end, 
            cartsaudio.cart AS cart, 
            cartsaudio.text AS text, 
            cartwalls.name AS wall_name, 
            cartwalls.description AS wall_desc,
            cartwalls.page AS page, 
            cartsets.id AS cartset_id, 
            cartsets.name AS cartset, 
            cartsets.description AS cartset_desc, 
            cartproperties.name AS prop_name, 
            cartstyleprops.value AS prop_value
    FROM    audio, cartsaudio, cartwalls, cartsets, cartstyles, cartstyleprops,
            cartproperties, archives
    WHERE   (cartsaudio.audioid = audio.id)
        AND (cartsaudio.cartwallid = cartwalls.id)
        AND (cartwalls.cartsetid = cartsets.id)
        AND (cartsaudio.cartstyleid = cartstyles.id)
        AND (cartstyleprops.cartstyleid = cartstyles.id)
        AND (cartstyleprops.cartpropertyid = cartproperties.id)
        AND (audio.archive = archives.id)
    ORDER BY cartwalls.id, cartsaudio.cart, cartproperties.id;

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
            audio.sustainer AS sustainer
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
            audio.intro_smpl, audio.extro_smpl, lifespans.data, audio.sustainer
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
            lifespans.data AS lifespan
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
            'f'::character(1) AS sustainer
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
            audio.sustainer AS sustainer
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
            audio.intro_smpl, audio.extro_smpl, lifespans.data, audio.sustainer
    ORDER BY audio.md5;

-- v_audio
CREATE OR REPLACE VIEW v_audio
    (audiotype,id,md5,title,artist,album,archiveid,archive,path,track,released,
        length_smpl,start_smpl,end_smpl,intro_smpl,extro_smpl,lifespan,
        sustainer)
AS
    SELECT 'Music'::character varying,id,md5,title,artist,album,archiveid,
			archive,path,track,released,length_smpl,start_smpl,end_smpl,
			intro_smpl,extro_smpl,lifespan,sustainer
    FROM v_audio_music
    UNION
    SELECT 'Jingle'::character varying,id,md5,title,'' AS artist,pkg AS album,
			archiveid,archive,path,'0' AS track,'0' AS released,length_smpl,
			start_smpl,end_smpl,intro_smpl,extro_smpl,lifespan,
			enabled AS sustainer
    FROM v_audio_jingles
    UNION
    SELECT 'Advert'::character varying,id,md5,title,'' AS artist,
			company AS album,archiveid,archive,path,'0' AS track,
			'0' AS released,length_smpl,start_smpl,end_smpl,intro_smpl,
			extro_smpl,lifespan,sustainer
    FROM v_audio_adverts
    UNION
    SELECT 'Prerec'::character varying,id,md5,title,'' AS artist,pkg AS album,
			archiveid,archive,path,'0' AS track,'0' AS released,length_smpl,
			start_smpl,end_smpl,intro_smpl,extro_smpl,lifespan,
			enabled AS sustainer
    FROM v_audio_jingles
ORDER BY id;

-- v_cartwalls
CREATE OR REPLACE VIEW v_cartwalls
AS
	SELECT 	audio.md5 AS md5, 
			archives.localpath AS path, 
			audio.start_smpl AS start, 
			audio.end_smpl AS end, 
			cartsaudio.cart AS cart, 
			cartsaudio.text AS text, 
			cartwalls.name AS wall_name, 
			cartwalls.description AS wall_desc, 
			cartwalls.page AS page, 
			cartsets.id AS cartset_id, 
			cartsets.name AS cartset, 
			cartsets.description AS cartset_desc, 
			cartproperties.name AS prop_name, 
			cartstyleprops.value AS prop_value
	FROM 	audio, cartsaudio, cartwalls, cartsets, cartstyles,
			cartstyleprops, cartproperties, archives
	WHERE 	(cartsaudio.audioid = audio.id)
    	AND (cartsaudio.cartwallid = cartwalls.id)
    	AND (cartwalls.cartsetid = cartsets.id)
    	AND (cartsaudio.cartstyleid = cartstyles.id)
    	AND (cartstyleprops.cartstyleid = cartstyles.id)
    	AND (cartstyleprops.cartpropertyid = cartproperties.id)
    	AND (audio.archive = archives.id)
	ORDER BY cartwalls.id, cartsaudio.cart, cartproperties.id
;
