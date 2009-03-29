package DPS::Utils;

use strict;
use warnings;
use DBI;
use Data::Dumper;

sub getConnection {
	my ($connDetails_rh) = @_;

	my $connString = "dbi:Pg:dbname=$connDetails_rh->{'dbname'};";
	$connString .= "host=$connDetails_rh->{'host'};";
	$connString .= "port=$connDetails_rh->{'port'};";

	my $username = $connDetails_rh->{'username'};
	my $password = $connDetails_rh->{'password'};

	my $conn = DBI->connect($connString, $username, $password,
                        {
                          RaiseError => 1,
                          AutoCommit => 0
                        }) || die "Database connection not made: $DBI::errstr";
	
	$conn->do("SET DateStyle = 'European'");
	return $conn;
}

sub makeFile {
        #my ($destConn, $parent, $name, $owner, $group, $entity, $type, $ur, $uw, $ux, $gr, $gw, $gx, $ar, $aw, $ax, $created) = @_;
        my $destConn = shift;
        my @args = @_;
        my $insertFileSQL = "INSERT INTO file ";
        $insertFileSQL .= "(parent, name, owner_id, group_id, entity_id, entity_type, user_r, user_w, user_x, ";
        $insertFileSQL .= "group_r, group_w, group_x, all_r, all_w, all_x, created, last_modified) VALUES ";
        $insertFileSQL .= "(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
        $insertFileSQL = $destConn->prepare($insertFileSQL);
        $insertFileSQL->execute(@args, time());
        my $id = $destConn->last_insert_id(undef, undef, 'file', 'file_id') or die "Unable to retrieve last inserted id";
        return $id;
}

return 1;
