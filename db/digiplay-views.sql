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
        bit_permissions bit(8);
    BEGIN
        SELECT parent INTO int_parent FROM dir WHERE id = int_id AND parent > 0;
        IF NOT FOUND THEN
            SELECT INTO bit_permissions bit_or(permissions) 
                    FROM v_tree_dir_explicit 
                    WHERE id = int_id AND userid = int_userid 
                    GROUP BY id;
            IF NOT FOUND THEN
                RETURN \'00000000\';
            END IF;
            RETURN bit_permissions;
        END IF;
        SELECT INTO bit_permissions bit_or(permissions) 
                    FROM v_tree_dir_explicit 
                    WHERE id = int_id AND userid = int_userid 
                    GROUP BY id;
        IF NOT FOUND THEN
            bit_permissions = \'00000000\';
        END IF;
--        bit_permissions = bit_permissions 
--                        | v_tree_getInherited(int_parent, int_userid);
        RETURN bit_permissions;
    END' LANGUAGE 'plpgsql';

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
            users.username AS cause
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
            groups.name AS cause
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
            users.username AS cause
    FROM    dir cross join users
    WHERE   v_tree_getInherited(dir.parent,users.id) != '00000000'
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
            users.username AS cause 
    FROM    audio, audiodir, audiousers, users
    WHERE   (audiodir.audioid = audio.id)
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
            groups.name AS cause
    FROM    audio, audiodir, audiogroups, usersgroups, users, groups
    WHERE   (audiodir.audioid = audio.id)
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
            users.username AS cause
    FROM    (audio inner join audiodir ON (audio.id = audiodir.audioid))
             cross join users
    WHERE   v_tree_getInherited(audiodir.dirid,users.id) != '00000000'
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
            users.username AS cause
    FROM    audio, audiodir, audiousers, users
    WHERE   (audiodir.audioid = audio.id)
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
            groups.name AS cause
    FROM    audio, audiodir, audiogroups, usersgroups, users, groups
    WHERE   (audiodir.audioid = audio.id)
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
            users.username AS cause
    FROM    (audio inner join audiodir ON (audio.id = audiodir.audioid))
             cross join users
    WHERE   v_tree_getInherited(audiodir.dirid,users.id) != '00000000'
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

--
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
            users.username AS cause
    FROM    audio, audiodir, audiousers, users
    WHERE   (audiodir.audioid = audio.id)
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
            groups.name AS cause
    FROM    audio, audiodir, audiogroups, usersgroups, users, groups
    WHERE   (audiodir.audioid = audio.id)
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
            users.username AS cause
    FROM    (audio inner join audiodir ON (audio.id = audiodir.audioid))
             cross join users
    WHERE   v_tree_getInherited(audiodir.dirid,users.id) != '00000000'
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
            users.username AS cause
    FROM    cartsets, cartsetsdir, cartsetsusers, users
    WHERE   (cartsetsdir.cartsetid = cartsets.id)
        AND (cartsetsusers.userid = users.id)

    UNION

    SELECT  cartsets.id AS id,
            cartsets.name AS name,
            cartsetsdir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            cartsetsgroups.permissions AS permissions,
            'group'::text AS causetype,
            groups.name AS cause
    FROM    cartsets, cartsetsdir, cartsetsgroups, usersgroups, users, groups
    WHERE   (cartsetsdir.cartsetid = cartsets.id)
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
            users.username AS cause
    FROM    (cartsets inner join cartsetsdir 
                    ON (cartsets.id = cartsetsdir.cartsetid))
             cross join users
    WHERE   v_tree_getInherited(cartsetsdir.dirid,users.id) != '00000000'
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
            users.username AS cause
    FROM    scripts, scriptsdir, scriptsusers, users
    WHERE   (scriptsdir.scriptid = scripts.id)
        AND (scriptsusers.userid = users.id)

    UNION

    SELECT  scripts.id AS id,
            scripts.name AS name,
            scriptsdir.dirid AS parent,
            users.id AS userid,
            users.username AS username,
            scriptsgroups.permissions AS permissions,
            'group'::text AS causetype,
            groups.name AS cause
    FROM    scripts, scriptsdir, scriptsgroups, usersgroups, users, groups
    WHERE   (scriptsdir.scriptid = scripts.id)
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
            users.username AS cause
    FROM    (scripts inner join scriptsdir 
                    ON (scripts.id = scriptsdir.scriptid))
             cross join users
    WHERE   v_tree_getInherited(scriptsdir.dirid,users.id) != '00000000'
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
        SELECT 'advert' AS itemtype, v_tree_advert.* FROM v_tree_advert
    ) AS Q1
GROUP BY itemtype, id, name, parent, userid, username
HAVING bit_or(permissions) != '00000000'
ORDER BY itemtype, name;
