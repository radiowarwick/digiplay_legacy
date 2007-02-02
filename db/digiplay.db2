--    This SQL DDL script was generated by Microsoft Visual Studio (Release Date: LOCAL BUILD).

--    Driver Used : Microsoft Visual Studio - IBM DB2 Universal Database Driver.
--    Document    : G:\Data\cc\raw\digiplay\Database Design v2 (VISIO 2002).vsd.
--    Time Created: 16 December 2006 13:53.
--    Operation   : From Visio Generate Wizard.
--    Connected data source : No connection.
--    Connected server      : No connection.
--    Connected database    : Not applicable.



create table "patches" ( 
	"id" INTEGER not null,
	"branch" VARCHAR(10) not null,
	"version" INTEGER not null, constraint "patches_PK" primary key ("id") ); 

create table "audioplaylists" ( 
	"id" INTEGER not null,
	"audio" INTEGER not null,
	"playlist" INTEGER not null, constraint "audioplaylists_PK" primary key ("id") ); 

create table "scriptsdir" ( 
	"id" INTEGER not null,
	"scriptid" INTEGER not null,
	"dir" INTEGER not null,
	"permissions" CHARACTER(2), constraint "scriptsdir_PK" primary key ("id") ); 

create table "showplandir" ( 
	"id" INTEGER not null,
	"showplanid" INTEGER not null,
	"dir" INTEGER not null,
	"linktype" SMALLINT not null, constraint "showplandir_PK" primary key ("id") ); 

create table "cartsetsdir" ( 
	"id" INTEGER not null,
	"cartsetid" INTEGER not null,
	"dir" INTEGER not null,
	"linktype" SMALLINT not null, constraint "cartsetsdir_PK" primary key ("id") ); 

create table "showplangroups" ( 
	"id" INTEGER not null,
	"showplanid" INTEGER not null,
	"groupid" INTEGER not null,
	"permissions" CHARACTER(2), constraint "showplangroups_PK" primary key ("id") ); 

create table "showplanusers" ( 
	"id" INTEGER not null,
	"showplanid" INTEGER not null,
	"userid" INTEGER not null,
	"permissions" CHARACTER(2), constraint "showplanusers_PK" primary key ("id") ); 

create table "showplans" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"creator" INTEGER not null,
	"creationdate" INTEGER not null,
	"showdate" INTEGER, constraint "showplans_PK" primary key ("id") ); 

create table "showitems" ( 
	"id" INTEGER not null,
	"showplanid" INTEGER not null,
	"position" SMALLINT not null,
	"title" VARCHAR(10) not null,
	"audio" INTEGER,
	"script" INTEGER,
	"comment" VARCHAR(10),
	"length" INTEGER not null,
	"state" SMALLINT not null, constraint "showitems_PK" primary key ("id") ); 

create table "scriptusers" ( 
	"id" INTEGER not null,
	"scriptid" INTEGER not null,
	"userid" INTEGER not null,
	"permissions" CHARACTER(2), constraint "scriptusers_PK" primary key ("id") ); 

create table "scriptgroups" ( 
	"id" INTEGER not null,
	"scriptid" INTEGER not null,
	"groupid" INTEGER not null,
	"permissions" CHARACTER(2), constraint "scriptgroups_PK" primary key ("id") ); 

create table "scripts" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"contents" VARCHAR(10),
	"length" INTEGER,
	"creator" INTEGER not null,
	"creationdate" INTEGER not null, constraint "scripts_PK" primary key ("id") ); 

create table "requests" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10),
	"artistname" VARCHAR(10),
	"date" INTEGER not null,
	"userid" INTEGER not null, constraint "requests_PK" primary key ("id") ); 

create table "audiocomments" ( 
	"id" INTEGER not null,
	"audio" INTEGER not null,
	"userid" INTEGER not null,
	"creationdate" INTEGER not null,
	"comment" VARCHAR(10), constraint "audiocomments_PK" primary key ("id") ); 

create table "cartsetsgroups" ( 
	"id" INTEGER not null,
	"cartsetid" INTEGER not null,
	"groupid" INTEGER not null, constraint "cartsetsgroups_PK" primary key ("id") ); 

create table "cartsetsusers" ( 
	"id" INTEGER not null,
	"cartsetid" INTEGER not null,
	"userid" INTEGER not null,
	"permissions" CHARACTER(2), constraint "cartsetsusers_PK" primary key ("id") ); 

create table "changelog" ( 
	"id" INTEGER not null,
	"datetime" INTEGER not null,
	"user" INTEGER not null,
	"relation" VARCHAR(10) not null,
	"record" INTEGER not null,
	"field" VARCHAR(10) not null,
	"oldvalue" VARCHAR(10) not null,
	"comment" VARCHAR(10), constraint "changelog_PK" primary key ("id") ); 

create table "audioext" ( 
	"id" INTEGER not null,
	"library_id" VARCHAR(10) not null,
	"title" VARCHAR(10) not null,
	"artist_name" VARCHAR(10) not null,
	"album_name" VARCHAR(10), constraint "audioext_PK" primary key ("id") ); 

create table "playlists" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null, constraint "playlists_PK" primary key ("id") ); 

create table "cartstyleprops" ( 
	"id" INTEGER not null,
	"style" INTEGER not null,
	"property" INTEGER not null,
	"value" VARCHAR(10) not null, constraint "cartstyleprops_PK" primary key ("id") ); 

create table "binsaudio" ( 
	"id" INTEGER not null,
	"audio" INTEGER not null,
	"sustbin" INTEGER not null, constraint "binsaudio_PK" primary key ("id") ); 

create table "bins" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"description" VARCHAR(10), constraint "bins_PK" primary key ("id") ); 

create table "audiojinglepkgs" ( 
	"id" INTEGER not null,
	"audio" INTEGER not null,
	"jinglepkg" INTEGER not null,
	"jingletype" INTEGER not null, constraint "audiojinglepkgs_PK" primary key ("id") ); 

create table "groupaccess" ( 
	"id" INTEGER not null,
	"groupid" INTEGER not null,
	"privilage" INTEGER not null, constraint "groupaccess_PK" primary key ("id") ); 

create table "audiodir" ( 
	"id" INTEGER not null,
	"audio" INTEGER not null,
	"directory" INTEGER not null,
	"linktype" SMALLINT not null, constraint "audiodir_PK" primary key ("id") ); 

create table "audioartists" ( 
	"id" INTEGER not null,
	"audio" INTEGER not null,
	"artist" INTEGER not null, constraint "audioartists_PK" primary key ("id") ); 

create table "cartstyle" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"description" VARCHAR(10), constraint "cartstyle_PK" primary key ("id") ); 

create table "lifespans" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"data" INTEGER,
	"description" VARCHAR(10), constraint "lifespans_PK" primary key ("id") ); 

create table "cartproperties" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"note" VARCHAR(10), constraint "cartproperties_PK" primary key ("id") ); 

create table "binsschedule" ( 
	"id" INTEGER not null,
	"sustbin" INTEGER not null,
	"type" INTEGER not null,
	"day_start" INTEGER not null,
	"hour_start" INTEGER not null,
	"length_hours" INTEGER not null,
	"start" INTEGER not null,
	"end" INTEGER not null,
	"notes" VARCHAR(10), constraint "binsschedule_PK" primary key ("id") ); 

create table "binsartists" ( 
	"id" INTEGER not null,
	"artist" INTEGER not null,
	"sustbin" INTEGER not null, constraint "binsartists_PK" primary key ("id") ); 

create table "binskeywords" ( 
	"id" INTEGER not null,
	"keyword" INTEGER not null,
	"sustbin" INTEGER not null, constraint "binskeywords_PK" primary key ("id") ); 

create table "audiolog" ( 
	"id" INTEGER not null,
	"audio" INTEGER not null,
	"userid" INTEGER not null,
	"downloaddate" DATE not null, constraint "audiolog_PK" primary key ("id") ); 

create table "cartsets" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"description" VARCHAR(10), constraint "cartsets_PK" primary key ("id") ); 

create table "jingletypes" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"description" VARCHAR(10), constraint "jingletypes_PK" primary key ("id") ); 

create table "cartsaudio" ( 
	"id" INTEGER not null,
	"audio" INTEGER not null,
	"style" INTEGER not null,
	"cart" INTEGER not null,
	"cartwall" INTEGER not null,
	"text" VARCHAR(10) not null, constraint "cartsaudio_PK" primary key ("id") ); 

create table "audiotypes" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"description" VARCHAR(10), constraint "audiotypes_PK" primary key ("id") ); 

create table "cartwalls" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"cartset" INTEGER not null,
	"page" INTEGER not null,
	"description" VARCHAR(10), constraint "cartwalls_PK" primary key ("id") ); 

create table "artistskeywords" ( 
	"id" INTEGER not null,
	"artist" INTEGER not null,
	"keyword" INTEGER not null, constraint "artistskeywords_PK" primary key ("id") ); 

create table "tasks" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"description" VARCHAR(10) not null,
	"sql_query" VARCHAR(10),
	"process" VARCHAR(10),
	"parameters" VARCHAR(10), constraint "tasks_PK" primary key ("id") ); 

create table "archives" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"localpath" VARCHAR(10) not null,
	"remotepath" VARCHAR(10) not null, constraint "archives_PK" primary key ("id") ); 

create table "companies" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null, constraint "companies_PK" primary key ("id") ); 

create table "jinglepkgs" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"description" VARCHAR(10) not null,
	"enabled" CHARACTER(1) not null, constraint "jinglepkgs_PK" primary key ("id") ); 

create table "audiogroups" ( 
	"id" INTEGER not null,
	"audio" INTEGER not null,
	"groupid" INTEGER not null,
	"permissions" CHARACTER(2), constraint "audiogroups_PK" primary key ("id") ); 

create table "audiousers" ( 
	"id" INTEGER not null,
	"audio" INTEGER not null,
	"userid" INTEGER not null,
	"permissions" CHARACTER(2), constraint "audiousers_PK" primary key ("id") ); 

create table "audio" ( 
	"id" INTEGER not null,
	"md5" CHARACTER(32) not null,
	"archive" INTEGER not null,
	"length_smpl" INTEGER not null,
	"start_smpl" INTEGER not null,
	"end_smpl" INTEGER not null,
	"intro_smpl" INTEGER not null,
	"extro_smpl" INTEGER not null,
	"type" INTEGER not null,
	"creator" INTEGER not null,
	"creation_date" INTEGER not null,
	"import_date" INTEGER not null,
	"title" VARCHAR(10) not null,
	"music_album" INTEGER,
	"music_track" SMALLINT,
	"music_released" SMALLINT,
	"advert_company" INTEGER,
	"advert_description" VARCHAR(10),
	"origin" VARCHAR(10),
	"reclibid" VARCHAR(10),
	"sustainer" CHARACTER(1),
	"flagged" CHARACTER(1),
	"censor" CHARACTER(1) not null,
	"notes" VARCHAR(10),
	"param_vol" SMALLINT,
	"param_speed" SMALLINT,
	"param_mood" SMALLINT,
	"param_endstyle" SMALLINT,
	"lifespan" INTEGER not null,
	"rip_result" VARCHAR(10), constraint "audio_PK" primary key ("id") ); 

create table "dirusers" ( 
	"id" INTEGER not null,
	"directory" INTEGER not null,
	"userid" INTEGER not null,
	"permissions" CHARACTER(2), constraint "dirusers_PK" primary key ("id") ); 

create table "dirgroups" ( 
	"id" INTEGER not null,
	"directory" INTEGER not null,
	"groupid" INTEGER not null,
	"permissions" CHARACTER(2), constraint "dirgroups_PK" primary key ("id") ); 

create table "groupmembers" ( 
	"id" INTEGER not null,
	"groupid" INTEGER not null,
	"userid" INTEGER not null, constraint "groupmembers_PK" primary key ("id") ); 

create table "groups" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"description" VARCHAR(10) not null, constraint "groups_PK" primary key ("id") ); 

create table "dir" ( 
	"id" INTEGER not null,
	"parent" INTEGER not null,
	"name" VARCHAR(10) not null,
	"notes" VARCHAR(10), constraint "dir_PK" primary key ("id") ); 

create table "usersconfigs" ( 
	"id" INTEGER not null,
	"userid" INTEGER not null,
	"configoption" INTEGER not null,
	"val" VARCHAR(10) not null, constraint "usersconfigs_PK" primary key ("id") ); 

create table "configs" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"description" VARCHAR(10), constraint "configs_PK" primary key ("id") ); 

create table "email" ( 
	"id" INTEGER not null,
	"new_flag" CHARACTER(1) not null,
	"datetime" INTEGER not null,
	"sender" VARCHAR(10) not null,
	"subject" VARCHAR(10),
	"body" VARCHAR(10), constraint "email_PK" primary key ("id") ); 

create table "useraccess" ( 
	"id" INTEGER not null,
	"userid" INTEGER not null,
	"privilage" INTEGER not null, constraint "useraccess_PK" primary key ("id") ); 

create table "privilages" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"description" VARCHAR(10), constraint "privilages_PK" primary key ("id") ); 

create table "users" ( 
	"id" INTEGER not null,
	"username" VARCHAR(10) not null,
	"password" CHARACTER(32),
	"enabled" CHARACTER(1) not null, constraint "users_PK" primary key ("id") ); 

create table "taskschedule" ( 
	"id" INTEGER not null,
	"task" INTEGER not null,
	"dayofweek" SMALLINT not null,
	"timeofday" INTEGER not null, constraint "taskschedule_PK" primary key ("id") ); 

create table "configuration" ( 
	"id" INTEGER not null,
	"parameter" VARCHAR(10) not null,
	"val" VARCHAR(10) not null,
	"location" INTEGER not null, constraint "configuration_PK" primary key ("id") ); 

create table "sustschedule" ( 
	"id" INTEGER not null,
	"audio" INTEGER,
	"extfeed" INTEGER,
	"extfeed_length" INTEGER,
	"start" INTEGER not null,
	"trim_start_smpl" INTEGER not null,
	"trim_end_smpl" INTEGER not null,
	"fade_in" INTEGER not null,
	"fade_out" INTEGER not null, constraint "sustschedule_PK" primary key ("id") ); 

create table "advertschedule" ( 
	"id" INTEGER not null,
	"advert" INTEGER not null,
	"start_date" DATE not null,
	"end_date" DATE not null,
	"time_start" TIME,
	"time_end" TIME,
	"frequency" SMALLINT not null, constraint "advertschedule_PK" primary key ("id") ); 

create table "extfeeds" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"device" VARCHAR(10) not null, constraint "extfeeds_PK" primary key ("id") ); 

create table "log" ( 
	"id" INTEGER not null,
	"location" INTEGER not null,
	"userid" INTEGER not null,
	"datetime" INTEGER not null,
	"track_title" VARCHAR(10) not null,
	"track_artist" VARCHAR(10) not null, constraint "log_PK" primary key ("id") ); 

create table "audiokeywords" ( 
	"id" INTEGER not null,
	"audio" INTEGER not null,
	"keyword" INTEGER not null, constraint "audiokeywords_PK" primary key ("id") ); 

create table "keywords" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"similar" VARCHAR(10), constraint "keywords_PK" primary key ("id") ); 

create table "albums" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"alt_name" VARCHAR(10), constraint "albums_PK" primary key ("id") ); 

create table "artists" ( 
	"id" INTEGER not null,
	"name" VARCHAR(10) not null,
	"alt_name" VARCHAR(10), constraint "artists_PK" primary key ("id") ); 

create index "scriptsdir_i2" on "scriptsdir" (
	"scriptid" ASC); 


create index "scriptsdir_i1" on "scriptsdir" (
	"dir" ASC); 


create index "scriptusers_i1" on "scriptusers" (
	"scriptid" ASC); 


create index "scriptusers_i2" on "scriptusers" (
	"userid" ASC); 


create index "scriptgroups_i2" on "scriptgroups" (
	"scriptid" ASC); 


create index "scriptgroups_i1" on "scriptgroups" (
	"groupid" ASC); 


create index "audiodir_i1" on "audiodir" (
	"audio" ASC); 


create index "audiodir_i2" on "audiodir" (
	"directory" ASC); 


create index "audioartists_i2" on "audioartists" (
	"audio" ASC); 


create index "audioartists_i1" on "audioartists" (
	"artist" ASC); 


create index "cartsaudio_i1" on "cartsaudio" (
	"cartwall" ASC); 


create index "audiogroups_i1" on "audiogroups" (
	"audio" ASC); 


create index "audiogroups_i2" on "audiogroups" (
	"groupid" ASC); 


create index "audiousers_i1" on "audiousers" (
	"audio" ASC); 


create index "audiousers_i2" on "audiousers" (
	"userid" ASC); 


create index "audio_i1" on "audio" (
	"md5" ASC); 


create index "groupmembers_i2" on "groupmembers" (
	"userid" ASC); 


create index "groupmembers_i1" on "groupmembers" (
	"groupid" ASC); 


create index "audiokeywords_i1" on "audiokeywords" (
	"audio" ASC); 


create index "audiokeywords_i2" on "audiokeywords" (
	"keyword" ASC); 


alter table "audioplaylists"
	add constraint "audio_FK14" foreign key (
		"audio")
	 references "audio" (
		"id") on update restrict on delete restrict; 

alter table "audioplaylists"
	add constraint "playlists_FK1" foreign key (
		"playlist")
	 references "playlists" (
		"id") on update restrict on delete restrict; 

alter table "scriptsdir"
	add constraint "scripts_FK4" foreign key (
		"scriptid")
	 references "scripts" (
		"id") on update restrict on delete restrict; 

alter table "scriptsdir"
	add constraint "dir_FK6" foreign key (
		"dir")
	 references "dir" (
		"id") on update restrict on delete restrict; 

alter table "showplandir"
	add constraint "showplans_FK4" foreign key (
		"dir")
	 references "showplans" (
		"id") on update restrict on delete restrict; 

alter table "showplandir"
	add constraint "dir_FK5" foreign key (
		"showplanid")
	 references "dir" (
		"id") on update restrict on delete restrict; 

alter table "cartsetsdir"
	add constraint "cartsets_FK4" foreign key (
		"cartsetid")
	 references "cartsets" (
		"id") on update restrict on delete restrict; 

alter table "cartsetsdir"
	add constraint "dir_FK4" foreign key (
		"dir")
	 references "dir" (
		"id") on update restrict on delete restrict; 

alter table "showplangroups"
	add constraint "showplans_FK3" foreign key (
		"showplanid")
	 references "showplans" (
		"id") on update restrict on delete restrict; 

alter table "showplangroups"
	add constraint "groups_FK7" foreign key (
		"groupid")
	 references "groups" (
		"id") on update restrict on delete restrict; 

alter table "showplanusers"
	add constraint "showplans_FK2" foreign key (
		"showplanid")
	 references "showplans" (
		"id") on update restrict on delete restrict; 

alter table "showplanusers"
	add constraint "users_FK16" foreign key (
		"userid")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "showplans"
	add constraint "users_FK15" foreign key (
		"creator")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "showitems"
	add constraint "audio_FK13" foreign key (
		"audio")
	 references "audio" (
		"id") on update restrict on delete restrict; 

alter table "showitems"
	add constraint "scripts_FK3" foreign key (
		"script")
	 references "scripts" (
		"id") on update restrict on delete restrict; 

alter table "showitems"
	add constraint "showplans_FK1" foreign key (
		"showplanid")
	 references "showplans" (
		"id") on update restrict on delete restrict; 

alter table "scriptusers"
	add constraint "users_FK13" foreign key (
		"userid")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "scriptusers"
	add constraint "scripts_FK1" foreign key (
		"scriptid")
	 references "scripts" (
		"id") on update restrict on delete restrict; 

alter table "scriptgroups"
	add constraint "groups_FK6" foreign key (
		"groupid")
	 references "groups" (
		"id") on update restrict on delete restrict; 

alter table "scriptgroups"
	add constraint "scripts_FK2" foreign key (
		"scriptid")
	 references "scripts" (
		"id") on update restrict on delete restrict; 

alter table "scripts"
	add constraint "users_FK14" foreign key (
		"creator")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "requests"
	add constraint "users_FK12" foreign key (
		"userid")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "audiocomments"
	add constraint "audio_FK12" foreign key (
		"audio")
	 references "audio" (
		"id") on update restrict on delete restrict; 

alter table "audiocomments"
	add constraint "users_FK11" foreign key (
		"userid")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "cartsetsgroups"
	add constraint "cartsets_FK3" foreign key (
		"cartsetid")
	 references "cartsets" (
		"id") on update restrict on delete restrict; 

alter table "cartsetsgroups"
	add constraint "groups_FK5" foreign key (
		"groupid")
	 references "groups" (
		"id") on update restrict on delete restrict; 

alter table "cartsetsusers"
	add constraint "cartsets_FK2" foreign key (
		"cartsetid")
	 references "cartsets" (
		"id") on update restrict on delete restrict; 

alter table "cartsetsusers"
	add constraint "users_FK10" foreign key (
		"userid")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "changelog"
	add constraint "users_FK9" foreign key (
		"user")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "cartstyleprops"
	add constraint "cartstyle_FK2" foreign key (
		"style")
	 references "cartstyle" (
		"id") on update restrict on delete restrict; 

alter table "cartstyleprops"
	add constraint "cartproperties_FK1" foreign key (
		"property")
	 references "cartproperties" (
		"id") on update restrict on delete restrict; 

alter table "binsaudio"
	add constraint "audio_FK11" foreign key (
		"audio")
	 references "audio" (
		"id") on update restrict on delete restrict; 

alter table "binsaudio"
	add constraint "bins_FK1" foreign key (
		"sustbin")
	 references "bins" (
		"id") on update restrict on delete restrict; 

alter table "audiojinglepkgs"
	add constraint "audio_FK10" foreign key (
		"audio")
	 references "audio" (
		"id") on update restrict on delete restrict; 

alter table "audiojinglepkgs"
	add constraint "jinglepkgs_FK1" foreign key (
		"jinglepkg")
	 references "jinglepkgs" (
		"id") on update restrict on delete restrict; 

alter table "audiojinglepkgs"
	add constraint "jingletypes_FK1" foreign key (
		"jingletype")
	 references "jingletypes" (
		"id") on update restrict on delete restrict; 

alter table "groupaccess"
	add constraint "groups_FK4" foreign key (
		"groupid")
	 references "groups" (
		"id") on update restrict on delete restrict; 

alter table "groupaccess"
	add constraint "privilages_FK2" foreign key (
		"privilage")
	 references "privilages" (
		"id") on update restrict on delete restrict; 

alter table "audiodir"
	add constraint "audio_FK9" foreign key (
		"audio")
	 references "audio" (
		"id") on update restrict on delete restrict; 

alter table "audiodir"
	add constraint "dir_FK3" foreign key (
		"directory")
	 references "dir" (
		"id") on update restrict on delete restrict; 

alter table "audioartists"
	add constraint "audio_FK8" foreign key (
		"audio")
	 references "audio" (
		"id") on update restrict on delete restrict; 

alter table "audioartists"
	add constraint "artists_FK3" foreign key (
		"artist")
	 references "artists" (
		"id") on update restrict on delete restrict; 

alter table "binsschedule"
	add constraint "bins_FK4" foreign key (
		"sustbin")
	 references "bins" (
		"id") on update restrict on delete restrict; 

alter table "binsartists"
	add constraint "bins_FK2" foreign key (
		"sustbin")
	 references "bins" (
		"id") on update restrict on delete restrict; 

alter table "binsartists"
	add constraint "artists_FK2" foreign key (
		"artist")
	 references "artists" (
		"id") on update restrict on delete restrict; 

alter table "binskeywords"
	add constraint "bins_FK3" foreign key (
		"sustbin")
	 references "bins" (
		"id") on update restrict on delete restrict; 

alter table "binskeywords"
	add constraint "keywords_FK3" foreign key (
		"keyword")
	 references "keywords" (
		"id") on update restrict on delete restrict; 

alter table "audiolog"
	add constraint "audio_FK7" foreign key (
		"audio")
	 references "audio" (
		"id") on update restrict on delete restrict; 

alter table "audiolog"
	add constraint "users_FK7" foreign key (
		"userid")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "cartsaudio"
	add constraint "audio_FK6" foreign key (
		"audio")
	 references "audio" (
		"id") on update restrict on delete restrict; 

alter table "cartsaudio"
	add constraint "cartstyle_FK1" foreign key (
		"style")
	 references "cartstyle" (
		"id") on update restrict on delete restrict; 

alter table "cartsaudio"
	add constraint "cartwalls_FK1" foreign key (
		"cartwall")
	 references "cartwalls" (
		"id") on update restrict on delete restrict; 

alter table "cartwalls"
	add constraint "cartsets_FK1" foreign key (
		"cartset")
	 references "cartsets" (
		"id") on update restrict on delete restrict; 

alter table "artistskeywords"
	add constraint "artists_FK1" foreign key (
		"artist")
	 references "artists" (
		"id") on update restrict on delete restrict; 

alter table "artistskeywords"
	add constraint "keywords_FK1" foreign key (
		"keyword")
	 references "keywords" (
		"id") on update restrict on delete restrict; 

alter table "audiogroups"
	add constraint "groups_FK3" foreign key (
		"groupid")
	 references "groups" (
		"id") on update restrict on delete restrict; 

alter table "audiogroups"
	add constraint "audio_FK5" foreign key (
		"audio")
	 references "audio" (
		"id") on update restrict on delete restrict; 

alter table "audiousers"
	add constraint "users_FK6" foreign key (
		"userid")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "audiousers"
	add constraint "audio_FK4" foreign key (
		"audio")
	 references "audio" (
		"id") on update restrict on delete restrict; 

alter table "audio"
	add constraint "archives_FK1" foreign key (
		"archive")
	 references "archives" (
		"id") on update restrict on delete restrict; 

alter table "audio"
	add constraint "users_FK5" foreign key (
		"creator")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "audio"
	add constraint "companies_FK1" foreign key (
		"advert_company")
	 references "companies" (
		"id") on update restrict on delete restrict; 

alter table "audio"
	add constraint "albums_FK1" foreign key (
		"music_album")
	 references "albums" (
		"id") on update restrict on delete restrict; 

alter table "audio"
	add constraint "audiotypes_FK1" foreign key (
		"type")
	 references "audiotypes" (
		"id") on update restrict on delete restrict; 

alter table "audio"
	add constraint "lifespans_FK1" foreign key (
		"lifespan")
	 references "lifespans" (
		"id") on update restrict on delete restrict; 

alter table "dirusers"
	add constraint "dir_FK2" foreign key (
		"directory")
	 references "dir" (
		"id") on update restrict on delete restrict; 

alter table "dirusers"
	add constraint "users_FK4" foreign key (
		"userid")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "dirgroups"
	add constraint "dir_FK1" foreign key (
		"directory")
	 references "dir" (
		"id") on update restrict on delete restrict; 

alter table "dirgroups"
	add constraint "groups_FK2" foreign key (
		"groupid")
	 references "groups" (
		"id") on update restrict on delete restrict; 

alter table "groupmembers"
	add constraint "groups_FK1" foreign key (
		"groupid")
	 references "groups" (
		"id") on update restrict on delete restrict; 

alter table "groupmembers"
	add constraint "users_FK3" foreign key (
		"userid")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "usersconfigs"
	add constraint "users_FK2" foreign key (
		"userid")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "usersconfigs"
	add constraint "configs_FK1" foreign key (
		"configoption")
	 references "configs" (
		"id") on update restrict on delete restrict; 

alter table "useraccess"
	add constraint "users_FK1" foreign key (
		"userid")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "useraccess"
	add constraint "privilages_FK1" foreign key (
		"privilage")
	 references "privilages" (
		"id") on update restrict on delete restrict; 

alter table "taskschedule"
	add constraint "tasks_FK1" foreign key (
		"task")
	 references "tasks" (
		"id") on update restrict on delete restrict; 

alter table "sustschedule"
	add constraint "audio_FK3" foreign key (
		"audio")
	 references "audio" (
		"id") on update restrict on delete restrict; 

alter table "sustschedule"
	add constraint "extfeeds_FK1" foreign key (
		"extfeed")
	 references "extfeeds" (
		"id") on update restrict on delete restrict; 

alter table "advertschedule"
	add constraint "audio_FK2" foreign key (
		"advert")
	 references "audio" (
		"id") on update restrict on delete restrict; 

alter table "log"
	add constraint "users_FK8" foreign key (
		"userid")
	 references "users" (
		"id") on update restrict on delete restrict; 

alter table "audiokeywords"
	add constraint "audio_FK1" foreign key (
		"audio")
	 references "audio" (
		"id") on update restrict on delete restrict; 

alter table "audiokeywords"
	add constraint "keywords_FK2" foreign key (
		"keyword")
	 references "keywords" (
		"id") on update restrict on delete restrict; 

create view music (id, md5, title, artist, album) as
select audio.id as id,
	audio.md5 as md5,
	audio.title as title, 
	artists.name as artist, 
	albums.name as album 
from audio, artists, audioartists, albums 
where audioartists.audio = audio.id 
	and audioartists.artist = artists.id 
	and audio.music_album = albums.id
	and audio.type = 0 
order by title;


create view jingles (title, package, type, active) as
select audio.title as title,
    jinglepkgs.name as package,
    jingletypes.description as type,
    jinglepkgs.enabled as active
from audio, jinglepkgs, audiojinglepkgs, jingletypes
where audiojinglepkgs.audio = audio.id
    and audiojinglepkgs.jinglepkg = jinglepkgs.id
    and audiojinglepkgs.jingletype = jingletypes.id
    and audio.type = 1
order by active desc, package, type, title;


create view v_playlists (md5, title, artist, album, length_smpl, playlistid) as              
SELECT DISTINCT audio.md5, 
	audio.title as title, 
	artists.name as artist, 
	albums.name as album,                                       
	audio.length_smpl as length_smpl,
	playlists.id as playlistid
FROM playlists, audio, audioplaylists, artists, audioartists, albums
WHERE audio.id = audioplaylists.audio 
	AND playlists.id = audioplaylists.playlist
	AND audioartists.artist = artists.id 
	AND audioartists.audio = audio.id 
	AND albums.id = audio.music_album
ORDER BY playlistid, title;


create rule r_log_delete 
as on delete 
to log 
do NOTIFY trig_id4;


create rule r_log_insert 
as on insert 
to log 
do NOTIFY trig_id4;


create rule r_log_update 
as on update 
to log 
do NOTIFY trig_id4;


create rule r_email_update 
as on update 
to email 
do NOTIFY trig_id2;


create rule r_email_insert 
as on insert 
to email 
do NOTIFY trig_id2;


create rule r_email_delete 
as on delete 
to email 
do NOTIFY trig_id2;


create rule r_audioplaylists_delete
as on delete 
to audioplaylists 
do NOTIFY trig_id5;


create rule r_audioplaylists_insert
as on insert 
to audioplaylists 
do NOTIFY trig_id5;


create rule r_audioplaylists_update
as on update 
to audioplaylists 
do NOTIFY trig_id5;


create rule r_playlists_delete
as on delete 
to playlists 
do NOTIFY trig_id5;


create rule r_playlists_insert
as on insert 
to playlists 
do NOTIFY trig_id5;


create rule r_playlists_update 
as on update 
to playlists 
do NOTIFY trig_id5;


create rule r_configuration_update 
as on update 
to configuration 
do NOTIFY trig_id1;


create rule r_configuration_insert 
as on insert 
to configuration 
do NOTIFY trig_id1;


create rule r_cartsaudio_update 
as on update 
to cartsaudio 
do NOTIFY trig_id3;


create rule r_cartsaudio_insert
as on insert 
to cartsaudio 
do NOTIFY trig_id3;


create rule r_cartsaudio_delete 
as on delete 
to cartsaudio 
do NOTIFY trig_id3;



-- This is the end of the Microsoft Visual Studio generated SQL DDL script.