--
-- Database patch for version 0.99.11-2
--

BEGIN transaction;

-- Create the correct views table
DROP VIEW IF EXISTS v_playlists
CREATE VIEW v_playlists
AS
    SELECT audio.id,
           audio.title,
           artists.name AS artist,
           audio.length_smpl,
           playlists.id AS playlistid,
           playlists.name AS playlist
    FROM   audio, audioplaylists, playlists, audioartists, artists
    WHERE  (audioartists.audioid = audio.id)
       AND (audioartists.artistid = artists.id)
       AND (audioplaylists.audioid = audio.id)
       AND (audioplaylists.playlistid = playlists.id)
    ORDER BY playlistid, title;
GRANT ALL ON v_playlists TO digiplay_user;
GRANT ALL ON v_playlists TO www;

-- New template information for website
INSERT INTO
  templates (templateid, filename, viewerclassname, realmid, modulename)
  VALUES (71, 'dpsstplaylistmanage.tpl', 'DPSStudioPlaylistManageViewer', 33, 'DPS');

-- New forms for website
insert into
    forms (formname, modelclass, modulename, realmid)
    values ('dpsPlaylistManageDeleteForm', 'DPSPlaylistManageModel', 'DPS', 33);

insert into
    forms (formname, modelclass, modulename, realmid)
    values ('dpsPlaylistManageRenameForm', 'DPSPlaylistManageModel', 'DPS', 33);

insert into
    forms (formname, modelclass, modulename, realmid)
    values ('dpsPlaylistManageAddForm', 'DPSPlaylistManageModel', 'DPS', 33);

END transaction;
