#!/usr/bin/perl

use Mail::Internet;
use MIME::Parser;
use DBI;
use DBD::Pg;

# === Configuration Options ===
# This script drops any email marked as spam (i.e. "X-Spam-Flag: YES" in the
# header. The following list of Subject lines will be automatically accepted
# regardless of spam status. Useful for web-based request forms or mobile
# text numbers which you want to ALWAYS accept.
my @allowed_subjects = ("Web-Based Request",
						"MOBILE REQUEST to 07789 100 666");
my $config_file = "/etc/digiplay.conf";

# =============================

# Read in digiplay configuration file and parse for database spec
open (CONFIG, "<$config_file");
while ($line = <CONFIG>) {
	if ($line =~ m/^DB_HOST=(.*)$/) { $dbhost = $1; }
	if ($line =~ m/^DB_PORT=(.*)$/) { $dbport = $1;	}
	if ($line =~ m/^DB_NAME=(.*)$/) { $dbname = $1; }
	if ($line =~ m/^DB_USER=(.*)$/) { $dbuser = $1; }
	if ($line =~ m/^DB_PASS=(.*)$/) { $dbpass = $1; }
}
close (CONFIG);
my $db_connect = "dbi:Pg:dbname=$dbname;host=$dbhost;port=$dbport;";

# Create a Mail object by reading stdin
my $email = Mail::Internet->new( [ <STDIN> ] );
my $time_received = time();

# get header fields and trim them to remove leading and trailing spaces
my $h_subject = trim($email->head->get("Subject"));
my $h_from    = trim($email->head->get("From"));
my $h_spam    = trim($email->head->get("X-Spam-Flag-RaW"));

# use a MIME parser to parse the email
my $parser = MIME::Parser->new;
$parser->output_to_core(1);
$parser->output_to_core('ALL');
@lines = (@{$email->header}, "\n", @{$email->body});
$top = $parser->parse_data(\@lines);

# Determine MIME type
my $html = 0;
foreach $entity ($top->parts_DFS) {
	# test if it is a valid entity for processing  
	if ($entity->bodyhandle) {
		if ( ($entity->effective_type eq "text/plain" && !$html) 
				|| $entity->effective_type eq "text/html") {
			$body = $entity->bodyhandle->as_string;
		}
		if ( $effectivetype eq "text/html") { $html = 1; }
	}
}

# Filter spam but allow messages with specific subjects through
my $accept_flag = 1;
if ($h_spam ne "NO") { $accept_flag = 0; }
foreach $accept_subject (@allowed_subjects) {
	if ($h_subject eq $accept_subject) { $accept_flag = 1; last; }
}

# If it's good, put it in the database
if ( $accept_flag ) {
    $h_subject =~ s/\\//;
    $body =~ s/\\//;
	$dbh = DBI->connect($db_connect, $dbuser, $dbpass, {AutoCommit => 1 }) 
				|| die "Cannot connect to database";
	$SQL="INSERT INTO email (sender,subject,body,new_flag,datetime) VALUES (" 
		. $dbh->quote($h_from) . "," . $dbh->quote($h_subject) . "," 
		. $dbh->quote($body) . ", 't', " . $dbh->quote($time_received) . ");";

	$sth = $dbh->prepare($SQL);
	$sth->execute();
}

# trim whitespace from ends of string function
sub trim($) {
	my $string = shift;
	$string =~ s/^\s+//;
	$string =~ s/\s+$//;
	return $string;
}
