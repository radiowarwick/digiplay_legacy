package DPS::Migrate::MigrateAudio;
use DBI;

use strict;
use warnings;
use DPS::Utils;
use Data::Dumper;
use Date::Parse;

my $AUDIO_FILE_TYPE = 1; #Type of an audio element in file
my $SYS_ID = 0; #System user id
my $AUDIO_G = 0; #Group for audio tracks to be owned by
#Audio property ids
my %audioProperty = ('music_track' => 1, 
                     'music_release' => 2, 
                     'advert_company' => 3, 
                     'advert_description' => 4, 
                     'origin' => 5, 
                     'reclibid' => 6,
                     'param_vol' => 7, 
                     'param_sepeed' => 8, 
                     'param_mood' => 9, 
                     'param_endstyle' => 10, 
                     'rip_result' => 11,
                     'lifespan' => 12,
                     'jingle_type' => 13,
                     'jingle_desc' => 14,
                    );

sub printOptions {
	my $out = <<END;
	all - all
	at  - audioTypes
	kw  - keywords
	ar  - artists
	al  - albums
	jl  - jingles
	ad  - audio

END
	print $out;
}

sub migrateAll {
	my ($sourceConn, $destConn, $what) = @_;
	(migrateAudioType($sourceConn, $destConn) || return 0) if processSection($what, "at");
	(migrateKeyword($sourceConn, $destConn) || return 0) if processSection($what, "kw");
	(migrateArtist($sourceConn, $destConn) || return 0) if processSection($what, "ar");
	(migrateAlbum($sourceConn, $destConn) || return 0) if processSection($what, "al");
	(migrateJingle($sourceConn, $destConn) || return 0) if processSection($what, "jl");
	(migrateAudio($sourceConn, $destConn) || return 0) if processSection($what, "ad");
	return 1;
}

sub processSection {
	my ($keyList, $key) = @_;
	return 1 unless(defined $keyList);
	my @bits = split (",", $keyList);
	my $bit;
	foreach $bit  (@bits) {
		return 1 if lc($bit) eq "all";
		return 1 if lc($bit) eq lc($key);
	}
	return 0;
}

sub migrateAudioType {
	my ($sourceConn, $destConn) = @_;
	my @row;
	my $countSQL = $sourceConn->prepare("SELECT count(*) FROM audiotypes");
	$countSQL->execute();
	my ($migrateCount) =  $countSQL->fetchrow_array();
	print "Migrating $migrateCount audio types\n";
	eval {
		my $audioTypeSQL = "SELECT * FROM audiotypes";
		$audioTypeSQL = $sourceConn->prepare($audioTypeSQL);
		$audioTypeSQL->execute();
		my $insertAudiotypeSQL = "INSERT INTO audiotype (audio_type_id, \"name\", description, last_modified) ";
		$insertAudiotypeSQL .= "VALUES (?, ?, ?, ?)";
		$insertAudiotypeSQL = $destConn->prepare($insertAudiotypeSQL);
		while(@row = $audioTypeSQL->fetchrow_array()) {
			my ($id, $name, $desc) = @row;
			$insertAudiotypeSQL->execute($id, $name, $desc, time());
		}
		$destConn->commit();
	};
	if($@) {
		warn "Database error: $DBI::errstr\n";
		$destConn->rollback(); #just die if rollback is failing
		return 0;
	}
	return 1;
}

sub migrateKeyword {
	my ($sourceConn, $destConn) = @_;
	my @row;
	my $countSQL = $sourceConn->prepare("SELECT count(*) FROM keywords");
	$countSQL->execute();
	my ($migrateCount) =  $countSQL->fetchrow_array();
	print "Migrating $migrateCount keywords\n";
	eval {
		my $keywordSQL = "SELECT * FROM keywords";
		$keywordSQL = $sourceConn->prepare($keywordSQL);
		$keywordSQL->execute();
		my $insertKeywordSQL = "INSERT INTO keyword (keyword_id, \"name\", hash, last_modified) ";
		$insertKeywordSQL .= "VALUES (?, ?, ?, ?)";
		$insertKeywordSQL = $destConn->prepare($insertKeywordSQL);
		while(@row = $keywordSQL->fetchrow_array()) {
			my ($id, $name, $similar) = @row;
			my $hash = undef;
			$insertKeywordSQL->execute($id, $name, $hash, time());
		}
		$destConn->commit();
	};
	if($@) {
		warn "Database error: $DBI::errstr\n";
		$destConn->rollback(); #just die if rollback is failing
		return 0;
	}
	return 1;
}

sub migrateArtist {
	my ($sourceConn, $destConn) = @_;
	my @row;
	my $countSQL = $sourceConn->prepare("SELECT count(*) FROM artists");
	$countSQL->execute();
	my ($migrateCount) =  $countSQL->fetchrow_array();
	print "Migrating $migrateCount artists\n";
	eval {
		my $artistSQL = "SELECT * FROM artists";
		$artistSQL = $sourceConn->prepare($artistSQL);
		$artistSQL->execute();
		my $insertArtistSQL = "INSERT INTO artist (artist_id, \"name\", last_modified) ";
		$insertArtistSQL .= "VALUES (?, ?, ?)";
		$insertArtistSQL = $destConn->prepare($insertArtistSQL);
		while(@row = $artistSQL->fetchrow_array()) {
			my ($id, $name, $alt_name) = @row;
			$insertArtistSQL->execute($id, $name, time());
		}

		my $artistKeywordSQL = "SELECT * from artistskeywords";
		$artistKeywordSQL = $sourceConn->prepare($artistKeywordSQL);
		$artistKeywordSQL->execute();
		my $insertkeywordSQL = "INSERT INTO artistkeyword (artist_id, keyword_id) VALUES (?, ?)";
		$insertkeywordSQL = $destConn->prepare($insertkeywordSQL);
		while(@row = $artistKeywordSQL->fetchrow_array()) {
			my ($id, $artistID, $keywordID) = @row;
			$insertkeywordSQL->execute($artistID, $keywordID);
		}
		$destConn->commit();
	};
	if($@) {
		warn "Database error: $DBI::errstr\n";
		$destConn->rollback(); #just die if rollback is failing
		return 0;
	}
	return 1;
}

sub migrateAlbum {
	my ($sourceConn, $destConn) = @_;
	my @row;
	my $countSQL = $sourceConn->prepare("SELECT count(*) FROM albums");
	$countSQL->execute();
	my ($migrateCount) =  $countSQL->fetchrow_array();
	print "Migrating $migrateCount albums\n";
	eval {
		my $albumSQL = "SELECT * FROM albums";
		$albumSQL = $sourceConn->prepare($albumSQL);
		$albumSQL->execute();
		my $insertAlbumSQL = "INSERT INTO album (album_id, \"name\", last_modified) ";
		$insertAlbumSQL .= "VALUES (?, ?, ?)";
		$insertAlbumSQL = $destConn->prepare($insertAlbumSQL);
		while(@row = $albumSQL->fetchrow_array()) {
			my ($id, $name, $alt_name) = @row;
			$insertAlbumSQL->execute($id, $name, time());
		}
		$destConn->commit();
	};
	if($@) {
		warn "Database error: $DBI::errstr\n";
		$destConn->rollback(); #just die if rollback is failing
		return 0;
	}
	return 1;
}

sub migrateJingle {
	my ($sourceConn, $destConn) = @_;
	my @row;
	my $countSQL = $sourceConn->prepare("SELECT count(*) FROM jinglepkgs");
	$countSQL->execute();
	my ($migrateCount) =  $countSQL->fetchrow_array();
	print "Migrating $migrateCount jingle packages\n";

	eval {
		my $jingleSQL = "SELECT * FROM jinglepkgs";
		$jingleSQL = $sourceConn->prepare($jingleSQL);
		$jingleSQL->execute();
		my $insertJingleSQL = "INSERT INTO jinglepkg (jingle_pkg_id, \"name\", description, enabled, last_modified) ";
		$insertJingleSQL .= "VALUES (?, ?, ?, ?, ?)";
		$insertJingleSQL = $destConn->prepare($insertJingleSQL);
		while(@row = $jingleSQL->fetchrow_array()) {
			my ($id, $name, $desc, $enabled) = @row;
			$insertJingleSQL->execute($id, $name, $desc, $enabled, time());
		}
		$destConn->commit();
	};
	if($@) {
		warn "Database error: $DBI::errstr\n";
		$destConn->rollback(); #just die if rollback is failing
		return 0;
	}
	return 1;
}

sub migrateAudio {
	my ($sourceConn, $destConn) = @_;
	my $sourceAudioCountSQL = $sourceConn->prepare("SELECT count(audio.id) FROM audio");
	$sourceAudioCountSQL->execute();
	my ($migrateCount) =  $sourceAudioCountSQL->fetchrow_array();

	if($migrateCount) {
		print "Migrating $migrateCount audio items\n";

		my @row;
		my $sourceAudioSQL = $sourceConn->prepare("SELECT audio.id, audio.type FROM audio ORDER BY id asc");
		$sourceAudioSQL->execute();
		my $i = 0;
		while(@row = $sourceAudioSQL->fetchrow_array()) {
			my ($audioID, $audioType) = @row;
			$i++;
			print "Migrating item: $audioID  ($i/$migrateCount)\n";
			migrateTrack($sourceConn, $destConn, $audioID) || return 0;
		}
	} else {
		print "No data to migrate, aborting\n";
		return 1;
	}

	return 1;
}

sub migrateTrack {
	my($sourceConn, $destConn, $audioID) = @_;
	eval {	
		my @row;
		my $checkSQL = $destConn->prepare("SELECT count(audio_id) FROM audio WHERE audio_id = ?");
		$checkSQL->execute($audioID);
		my ($audioCount) =  $checkSQL->fetchrow_array();
		if($audioCount) {
			print "Located audio with id $audioID in destination DB, skipping\n";
			return 1;
		}
		my $audioSQL = $sourceConn->prepare("SELECT * FROM audio WHERE id = ?");
		$audioSQL->execute($audioID);
		my @srcAData =  $audioSQL->fetchrow_array();
		
		# SORT OUT FILE
		my $fileID;
		if($srcAData[8] == 1) {
			$fileID = getAudioFile($sourceConn, $destConn, $audioID, $srcAData[12], $srcAData[10]);
		} elsif($srcAData[8] == 2) {
			$fileID = getJingleFile($sourceConn, $destConn, $audioID, $srcAData[12], $srcAData[10]);
		} elsif($srcAData[8] == 3) {
			$fileID = getAdvertFile($sourceConn, $destConn, $audioID, $srcAData[12], $srcAData[10]);
		} elsif($srcAData[8] == 4) {
			$fileID = getPrerecFile($sourceConn, $destConn, $audioID, $srcAData[12], $srcAData[10]);	
		} else {
			die "Unable to process unknown audio type: " + $srcAData[8] + " for audio item: " + $audioID;
		}

		# SORT OUT AUDIO
		my $insertAudioSQL = "INSERT INTO audio ";
		$insertAudioSQL .= "(audio_id, file_id, md5, length_smpl, start_smpl, end_smpl, intro_smpl, extro_smpl, ";
		$insertAudioSQL .= "audio_type_id, creator_id, import_date, title, sustainer, flagged, censor, filetype, last_modified) ";
		$insertAudioSQL .= " VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
		$insertAudioSQL = $destConn->prepare($insertAudioSQL);

		if(lc($srcAData[20]) eq 't') {
			$srcAData[20] = 1;
		} elsif(lc($srcAData[20]) eq 'f') {
			$srcAData[20] = 0;
		}
		if(lc($srcAData[21]) eq 't') {
			$srcAData[21] = 1;
		} elsif(lc($srcAData[21]) eq 'f') {
			$srcAData[21] = 0;
		}
		if(lc($srcAData[22]) eq 't') {
			$srcAData[22] = 1;
		} elsif(lc($srcAData[22]) eq 'f') {
			$srcAData[22] = 0;
		}
		$insertAudioSQL->execute($srcAData[0], $fileID, $srcAData[1], $srcAData[3], $srcAData[4], $srcAData[5], $srcAData[6], $srcAData[7],
		                         $srcAData[8], $srcAData[9], $srcAData[11], $srcAData[12], $srcAData[20], $srcAData[21], $srcAData[22],$srcAData[30], time());
		
		#This is used when moving stuff into properties table
		my $insertAudioPropertySQL = "INSERT INTO audioproperty (audio_id, property_id, val, last_modified) VALUES (?, ?, ?, ?)";
		$insertAudioPropertySQL = $destConn->prepare($insertAudioPropertySQL);
		
		# SORT OUT COMMENTS
		my $insertCommentSQL = "INSERT INTO audiocomment (audio_id, user_id, creation_date, \"comment\", last_modified) ";
		$insertCommentSQL .= "VALUES (?, ?, ?, ?, ?)";
		$insertCommentSQL = $destConn->prepare($insertCommentSQL);
		if($srcAData[23]) {
			$insertCommentSQL->execute($audioID, $srcAData[9], $srcAData[10], $srcAData[23], time());
		}

		my $audioCommentsSQL = "SELECT * from audiocomments WHERE audioid = ?";
		$audioCommentsSQL = $sourceConn->prepare($audioCommentsSQL);
		$audioCommentsSQL->execute($audioID);
                while(@row = $audioCommentsSQL->fetchrow_array()) {
                	my ($id, $audioID, $userID, $creationDate, $comment) = @row;
			$insertCommentSQL->execute($audioID, $userID, $creationDate, $comment, time());	
		}

		# SORT OUT ARCHIVES
		if($srcAData[2]) {
			my $audioArchiveSQL = "SELECT * FROM archives WHERE id = ?";
			$audioArchiveSQL = $sourceConn->prepare($audioArchiveSQL);
			$audioArchiveSQL->execute($srcAData[2]);
			my $insertAudioArchiveSQL = "INSERT INTO audioarchive (audio_id, priority, \"name\", localpath, remotepath, last_modified) ";
			$insertAudioArchiveSQL .= " VALUES (?, ?, ?, ?, ?, ?)";
			$insertAudioArchiveSQL = $destConn->prepare($insertAudioArchiveSQL);
			while(@row = $audioArchiveSQL->fetchrow_array()) {
				my($id, $name, $localpath, $remotepath) = @row;
				$insertAudioArchiveSQL->execute($audioID, 1, $name, $localpath, $remotepath, time());
			}
		}

		# SORT OUT AUDIOLOG
		my $audioLogSQL = "SELECT * from audiolog WHERE audioid = ?";
		$audioLogSQL = $sourceConn->prepare($audioLogSQL);
		$audioLogSQL->execute($audioID);
		my $insertAudiologSQL = "INSERT INTO audiolog (audio_log_id, audio_id, user_id, download_date, last_modified) ";
		$insertAudiologSQL .= "VALUES (?, ?, ?, ?, ?)";
		$insertAudiologSQL = $destConn->prepare($insertAudiologSQL);
		while(@row = $audioLogSQL->fetchrow_array()) {
			my ($id, $audioID, $userID, $downloadDate) = @row;
			$downloadDate = str2time($downloadDate);
			$insertAudiologSQL->execute($id, $audioID, $userID, $downloadDate, time());
		}

		# SORT OUT KEYWORDS
		my $audioKeywordSQL = "SELECT * from audiokeywords WHERE audioid = ?";
		$audioKeywordSQL = $sourceConn->prepare($audioKeywordSQL);
		$audioKeywordSQL->execute($audioID);
		my $insertAudioKeywordSQL = "INSERT INTO audiokeyword (audio_id, keyword_id) ";
		$insertAudioKeywordSQL .= "VALUES (?, ?)";
		$insertAudioKeywordSQL = $destConn->prepare($insertAudioKeywordSQL);
		while(@row = $audioKeywordSQL->fetchrow_array()) {
			my ($id, $audioID, $keywordID) = @row;
			$insertAudioKeywordSQL->execute($audioID, $keywordID);
		}

		# SORT OUT PLAYLIST
		my $audioPlaylistSQL = "SELECT * from audioplaylists WHERE audioid = ?";
		$audioPlaylistSQL = $sourceConn->prepare($audioPlaylistSQL);
		$audioPlaylistSQL->execute($audioID);
		my $insertAudioPlaylistSQL = "INSERT INTO audioplaylist (audio_id, playlist_id) ";
		$insertAudioPlaylistSQL .= "VALUES (?, ?)";
		$insertAudioPlaylistSQL = $destConn->prepare($insertAudioPlaylistSQL);
		while(@row = $audioPlaylistSQL->fetchrow_array()) {
			my ($id, $audioID, $playlistID) = @row;
			$insertAudioPlaylistSQL->execute($audioID, $playlistID);
		}

		# SORT OUT ARTIST
		my $audioArtistSQL = "SELECT * from audioartists WHERE audioid = ?";
		$audioArtistSQL = $sourceConn->prepare($audioArtistSQL);
		$audioArtistSQL->execute($audioID);
		my $insertAudioArtistSQL = "INSERT INTO audioartist (audio_id, artist_id) ";
		$insertAudioArtistSQL .= "VALUES (?, ?)";
		$insertAudioArtistSQL = $destConn->prepare($insertAudioArtistSQL);
		while(@row = $audioArtistSQL->fetchrow_array()) {
			my ($id, $audioID, $artistID) = @row;
			$insertAudioArtistSQL->execute($audioID, $artistID);
		}

		# SORT OUT JINGLEPKGS
		my $audioJingleSQL = "SELECT * from audiojinglepkgs WHERE audioid = ?";
		$audioJingleSQL = $sourceConn->prepare($audioJingleSQL);
		$audioJingleSQL->execute($audioID);
		my $insertAudioJingleSQL = "INSERT INTO audiojinglepkg (audio_id, jingle_pkg_id) ";
		$insertAudioJingleSQL .= "VALUES (?, ?)";
		$insertAudioJingleSQL = $destConn->prepare($insertAudioJingleSQL);
		my $first = 1;
		while(@row = $audioJingleSQL->fetchrow_array()) {
			my ($id, $audioID, $jinglepkg, $jingletype) = @row;
			$insertAudioJingleSQL->execute($audioID, $jinglepkg);
			if($first && defined $jingletype) {
				$first = 0;
				my $jingleTypeSQL = "SELECT name, description FROM jingletypes WHERE id = ?";
				$jingleTypeSQL = $sourceConn->prepare($jingleTypeSQL);
				$jingleTypeSQL->execute($jingletype);
				my ($jingleTypeStr, $jingleTypeDesc) = $jingleTypeSQL->fetchrow_array(); 
				$insertAudioPropertySQL->execute($audioID, $audioProperty{'jingle_type'}, $jingleTypeStr, time());
				$insertAudioPropertySQL->execute($audioID, $audioProperty{'jingle_desc'}, $jingleTypeDesc, time());
			}
		}

		# SORT OUT ALBUM
		if($srcAData[13]) {
			my $insertAudioAlbum = "INSERT INTO audioalbum (audio_id, album_id) VALUES (?, ?)";
			$insertAudioAlbum = $destConn->prepare($insertAudioAlbum);
			$insertAudioAlbum->execute($audioID, $srcAData[13]);
		}

		# SORT OUT ADVERTSCHEDULE
		my $audioAdvertSQL = "SELECT * from advertschedule WHERE audioid = ?";
		$audioAdvertSQL = $sourceConn->prepare($audioAdvertSQL);
		$audioAdvertSQL->execute($audioID);
		my $insertAudioAdvertSQL = "INSERT INTO advertschedule (advert_schedule_id, audio_id, start_date, end_date, time_start, time_end, frequency, last_modified) ";
		$insertAudioAdvertSQL .= "VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
		$insertAudioAdvertSQL = $destConn->prepare($insertAudioAdvertSQL);
		while(@row = $audioAdvertSQL->fetchrow_array()) {
			my ($id, $audioID, $start_date, $end_date, $time_start, $time_end, $frequency) = @row;
			$start_date = str2time($start_date);
			$end_date = str2time($end_date);
			$time_start = str2time("1970/01/01 $time_start UTC");
			$time_end = str2time("1970/01/01 $time_end UTC");
			$insertAudioAdvertSQL->execute($id, $audioID, $start_date, $end_date, $time_start, $time_end, $frequency, time());
		}

		# SORT OUT REMAINING AUDIO PROPERTIES
		if(defined $srcAData[14]) {
			$insertAudioPropertySQL->execute($audioID, $audioProperty{'music_track'}, $srcAData[14], time());
		}
		if(defined $srcAData[15]) {
			$insertAudioPropertySQL->execute($audioID, $audioProperty{'music_release'}, $srcAData[15], time());
		}
		if(defined $srcAData[16]) {
			my $companySQL = "SELECT name FROM companies WHERE id = ?";
			$companySQL = $sourceConn->prepare($companySQL);
			$companySQL->execute($srcAData[16]);
			my ($company) =  $companySQL->fetchrow_array();	
			$insertAudioPropertySQL->execute($audioID, $audioProperty{'advert_company'}, $company, time());
		}
		if(defined $srcAData[17]) {
			$insertAudioPropertySQL->execute($audioID, $audioProperty{'advert_description'}, $srcAData[17], time());
		}
		if(defined $srcAData[18]) {
			$insertAudioPropertySQL->execute($audioID, $audioProperty{'origin'}, $srcAData[18], time());
		}
		if(defined $srcAData[19] && $srcAData[19] ne "") {
			$insertAudioPropertySQL->execute($audioID, $audioProperty{'reclibid'}, $srcAData[19], time());
		}
		if(defined $srcAData[24]) {
			$insertAudioPropertySQL->execute($audioID, $audioProperty{'param_vol'}, $srcAData[24], time());
		}
		if(defined $srcAData[25]) {
			$insertAudioPropertySQL->execute($audioID, $audioProperty{'param_speed'}, $srcAData[25], time());
		}
		if(defined $srcAData[26]) {
			$insertAudioPropertySQL->execute($audioID, $audioProperty{'param_mood'}, $srcAData[26], time());
		}
		if(defined $srcAData[27]) {
			$insertAudioPropertySQL->execute($audioID, $audioProperty{'param_endstyle'}, $srcAData[27], time());
		}
		if(defined $srcAData[28]) {
			my $lifespanSQL = "SELECT data FROM lifespans WHERE id = ?";
			$lifespanSQL = $sourceConn->prepare($lifespanSQL);
			$lifespanSQL->execute($srcAData[28]);
			my ($lifespan) =  $lifespanSQL->fetchrow_array();	
			$insertAudioPropertySQL->execute($audioID, $audioProperty{'lifespan'}, $lifespan, time());
		}
		if(defined $srcAData[29]) {
			$insertAudioPropertySQL->execute($audioID, $audioProperty{'rip_result'}, $srcAData[29], time());
		}

		$destConn->commit();
	};
	if($@) {
		warn "Database error: $DBI::errstr\n";
		$destConn->rollback(); #just die if rollback is failing
		return 0;	
	}
	return 1;
}

sub getAudioFile {
	my ($sourceConn, $destConn, $audioID, $name, $created) = @_;
	#TODO sort out parent dir
	my $fileID = DPS::Utils::makeFile($destConn, 1, $name, $SYS_ID, $AUDIO_G, $audioID, 
	               $AUDIO_FILE_TYPE, 1, 1, 1, 1, 1 ,1, 1, 0, 0, $created);
	return $fileID;
}

sub getJingleFile {
	my ($sourceConn, $destConn, $audioID, $name, $created) = @_;
	#TODO sort out parent dir
	my $fileID = DPS::Utils::makeFile($destConn, 1, $name, $SYS_ID, $AUDIO_G, $audioID, 
	               $AUDIO_FILE_TYPE, 1, 1, 1, 1, 1 ,1, 1, 0, 0, $created);
	return $fileID;

}

sub getAdvertFile {
	my ($sourceConn, $destConn, $audioID, $name, $created) = @_;
	#TODO sort out parent dir
	my $fileID = DPS::Utils::makeFile($destConn, 1, $name, $SYS_ID, $AUDIO_G, $audioID, 
	               $AUDIO_FILE_TYPE, 1, 1, 1, 1, 1 ,1, 1, 0, 0, $created);
	return $fileID;

}

sub getPrerecFile {
	my ($sourceConn, $destConn, $audioID, $name, $created) = @_;
	#TODO sort out parent dir
	my $fileID = DPS::Utils::makeFile($destConn, 1, $name, $SYS_ID, $AUDIO_G, $audioID, 
	               $AUDIO_FILE_TYPE, 1, 1, 1, 1, 1 ,1, 1, 0, 0, $created);
	return $fileID;
}

return 1;
