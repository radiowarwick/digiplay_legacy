package DPS::Migrate::MigrateSustainer;
use DBI;

use strict;
use warnings;
use DPS::Utils;
use Data::Dumper;
use Date::Parse;

sub printOptions {
	my $out = <<END;
	all - all
	ex  - external Feeds
	sc  - schedule
	bs  - bins schedule
	bn  - bins

END
	print $out;
}

sub migrateAll {
	my ($sourceConn, $destConn, $what) = @_;
	(migrateFeeds($sourceConn, $destConn) || return 0) if processSection($what, "ex");
	(migrateSchedule($sourceConn, $destConn) || return 0) if processSection($what, "sc");
	(migrateBinSchedule($sourceConn, $destConn) || return 0) if processSection($what, "bs");
	(migrateBins($sourceConn, $destConn) || return 0) if processSection($what, "bn");
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

sub migrateFeeds {
	my ($sourceConn, $destConn) = @_;
	my @row;
	my $countSQL = $sourceConn->prepare("SELECT count(*) FROM extfeeds");
	$countSQL->execute();
	my ($migrateCount) =  $countSQL->fetchrow_array();
	print "Migrating $migrateCount external feeds\n";
	eval {
		my $feedSQL = "SELECT * FROM extfeeds";
		$feedSQL = $sourceConn->prepare($feedSQL);
		$feedSQL->execute();
		my $insertFeedSQL = "INSERT INTO extfeed (ext_feed_id, \"name\", device, last_modified) ";
		$insertFeedSQL .= "VALUES (?, ?, ?, ?)";
		$insertFeedSQL = $destConn->prepare($insertFeedSQL);
		while(@row = $feedSQL->fetchrow_array()) {
			my ($id, $name, $device) = @row;
			$insertFeedSQL->execute($id, $name, $device, time());
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

sub migrateSchedule {
	my ($sourceConn, $destConn) = @_;
	my @row;
	my $countSQL = $sourceConn->prepare("SELECT count(*) FROM sustschedule");
	$countSQL->execute();
	my ($migrateCount) =  $countSQL->fetchrow_array();
	print "Migrating $migrateCount Scheduled sustainer tracks\n";
	eval {
		my $sustSQL = "SELECT * FROM sustschedule";
		$sustSQL = $sourceConn->prepare($sustSQL);
		$sustSQL->execute();
		my $insertSustSQL = "INSERT INTO sustschedule (sust_schedule_id, audio_id, ext_feed_id, ext_feed_length, start, trim_start_smpl, trim_end_smpl, fade_in, fade_out, last_modified) ";
		$insertSustSQL .= "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
		$insertSustSQL = $destConn->prepare($insertSustSQL);
		while(@row = $sustSQL->fetchrow_array()) {
			my ($id, $audio, $feed, $feedLength, $start, $trim_s, $trim_e, $fade_i, $fade_o) = @row;
			$insertSustSQL->execute($id, $audio, $feed, $feedLength, $start, $trim_s, $trim_e, $fade_i, $fade_o, time());
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

sub migrateBinSchedule {
	my ($sourceConn, $destConn) = @_;
	my @row;
	my $countSQL = $sourceConn->prepare("SELECT count(*) FROM binsschedule");
	$countSQL->execute();
	my ($migrateCount) =  $countSQL->fetchrow_array();
	print "Migrating $migrateCount Scheduled bins\n";
	eval {
		my $sustSQL = "SELECT * FROM binsschedule";
		$sustSQL = $sourceConn->prepare($sustSQL);
		$sustSQL->execute();
		my $insertSustSQL = "INSERT INTO binschedule (bin_schedule_id, bin_id, bin_type_id, day_start, hour_start, length_hours, bin_start, bin_end, description, last_modified) ";
		$insertSustSQL .= "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
		$insertSustSQL = $destConn->prepare($insertSustSQL);
		while(@row = $sustSQL->fetchrow_array()) {
			my ($bin_schedule_id, $bin_id, $bin_type_id, $day_start, $hour_start, $length_hours, $bin_start, $bin_end, $description) = @row;
			$insertSustSQL->execute($bin_schedule_id, $bin_id, $bin_type_id, $day_start, $hour_start, $length_hours, $bin_start, $bin_end, $description, time());
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

sub migrateBins {
	my ($sourceConn, $destConn) = @_;
	my $migrationCountSQL = $sourceConn->prepare("SELECT count(*) FROM bins");
	$migrationCountSQL->execute();
	my ($migrateCount) =  $migrationCountSQL->fetchrow_array();

	if($migrateCount) {
		print "Migrating $migrateCount bins\n";

		my @row;
		my $binsSQL = $sourceConn->prepare("SELECT * FROM bins ORDER BY id asc");
		$binsSQL->execute();
		my $i = 0;
		while(@row = $binsSQL->fetchrow_array()) {
			my ($id, $name, $desc) = @row;
			$i++;
			print "Migrating item: $id  ($i/$migrateCount)\n";
			migrateBin($sourceConn, $destConn, $id, $name, $desc) || return 0;
		}
	} else {
		print "No data to migrate, aborting\n";
		return 1;
	}

	return 1;
}

sub migrateBin {
	my($sourceConn, $destConn, $binID, $binName, $binDesc) = @_;
	eval {	
		my @row;
		my $checkSQL = $destConn->prepare("SELECT count(bin_id) FROM bin WHERE bin_id = ?");
		$checkSQL->execute($binID);
		my ($binCount) =  $checkSQL->fetchrow_array();
		if($binCount) {
			print "Located bin with id $binID in destination DB, skipping\n";
			return 1;
		}
		
		# SORT OUT BIN
		my $insertBinSQL = "INSERT INTO bin ";
		$insertBinSQL .= "(bin_id, name, description, last_modified) ";
		$insertBinSQL .= " VALUES (?, ?, ?, ?)";
		$insertBinSQL = $destConn->prepare($insertBinSQL);
		$insertBinSQL->execute($binID, $binName, $binDesc, time());
		
		# SORT OUT BINSAUDIO
		my $insertBinAudioSQL = "INSERT INTO binaudio (bin_id, audio_id) ";
		$insertBinAudioSQL .= "VALUES (?, ?)";
		$insertBinAudioSQL = $destConn->prepare($insertBinAudioSQL);

		my $binAudioSQL = "SELECT * from binsaudio WHERE binid = ?";
		$binAudioSQL = $sourceConn->prepare($binAudioSQL);
		$binAudioSQL->execute($binID);
                while(@row = $binAudioSQL->fetchrow_array()) {
                	my ($id, $audioID, $binID) = @row;
			$insertBinAudioSQL->execute($audioID, $binID);
		}

		# SORT OUT BINSARTIST
		my $insertBinArtistSQL = "INSERT INTO binartist (bin_id, artist_id) ";
		$insertBinArtistSQL .= "VALUES (?, ?)";
		$insertBinArtistSQL = $destConn->prepare($insertBinArtistSQL);

		my $binArtistSQL = "SELECT * from binsartists WHERE binid = ?";
		$binArtistSQL = $sourceConn->prepare($binArtistSQL);
		$binArtistSQL->execute($binID);
                while(@row = $binArtistSQL->fetchrow_array()) {
                	my ($id, $artistID, $binID) = @row;
			$insertBinArtistSQL->execute($artistID, $binID);
		}

		# SORT OUT BINSKEYWORDS
		my $insertBinKeywordSQL = "INSERT INTO binkeyword (bin_id, keyword_id) ";
		$insertBinKeywordSQL .= "VALUES (?, ?)";
		$insertBinKeywordSQL = $destConn->prepare($insertBinKeywordSQL);

		my $binKeywordSQL = "SELECT * from binskeywords WHERE binid = ?";
		$binKeywordSQL = $sourceConn->prepare($binAudioSQL);
		$binKeywordSQL->execute($binID);
                while(@row = $binKeywordSQL->fetchrow_array()) {
                	my ($id, $keywordID, $binID) = @row;
			$insertBinKeywordSQL->execute($keywordID, $binID);
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

return 1;
