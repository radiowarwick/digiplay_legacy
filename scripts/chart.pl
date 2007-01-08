#!/usr/bin/perl
use strict;
use Date::Calc qw(Add_Delta_Days Today);
use Mail::Sender;
use DBI;
use DBD::Pg;

# Allow the configuration of where the chart is e-mailed.
my $recipient = 'head.of.music.true@raw.sunion.warwick.ac.uk';

# Allow configuration of the sender's details.
my $senderAddr = 'it@radio.warwick.ac.uk';
my $smtpServer = '127.0.0.1';

# Define the period for which the chart will be generated (in days).
my $period = 7;

my $config_file = "/etc/digiplay.conf";

# Read in digiplay configuration file and parse for database spec
open (CONFIG, "<$config_file");

my $dbhost;
my $dbport = 5432;
my $dbname;
my $dbuser;
my $dbpass;
my $line;

while ($line = <CONFIG>) {
	if ($line =~ m/^DB_HOST=(.*)$/) { $dbhost = $1; }
	if ($line =~ m/^DB_NAME=(.*)$/) { $dbname = $1; }
	if ($line =~ m/^DB_USER=(.*)$/) { $dbuser = $1; }
	if ($line =~ m/^DB_PASS=(.*)$/) { $dbpass = $1; }
}
close (CONFIG);
my $dbh = DBI->connect("dbi:Pg:dbname=$dbname;host=$dbhost;port=$dbport;",
	"$dbuser","$dbpass", {AutoCommit => 1})
	or die("Unable to connect to the database:" . DBI->errstr);



# Get the start and finish dates for this period
my $start = sprintf("%.4d%.2d%.2d", Add_Delta_Days(Today(), -$period));
my $end = sprintf("%.4d%.2d%.2d", Today());

my $dbEnd = time();
my $dbStart = $dbEnd - $period*24*60*60;

my $query = $dbh->prepare("SELECT track_title,track_artist FROM log WHERE datetime > ? AND datetime < ?")
	or die("Unable to prepare SQL statement: $dbh->errstr");

$query->execute($dbStart,$dbEnd);

# Mail stuff.
my $sender = new Mail::Sender {
	smtp => $smtpServer,
	from => $senderAddr,
	on_errors => 'die',
};

ref $sender->Open({to => $recipient,
		subject => "Chart Log Week $start to $end"})
	or die "Error: $Mail::Sender::Error\n";

my $FH = $sender->GetHandle();

if ($query->rows == 0) {
    # Nothing logged in this period.
    print $FH "Nothing logged in the period from $start to $end\n";
	close $FH;
    exit 0;
}



print $FH "Chart Log from $start to $end\n";

my(%plays, %play_names, @row);
while(@row = $query->fetchrow_array()) {
	my $title = $row[0];
	my $artist =  $row[1];

	my $trackName = $artist . ' - '  . $title;

	$_ = $trackName;
    #Let's munge lots of stuff out to try and match similares
    s/\s+//g;
    s/the//gi;
    s/\(?LP\)?//gi;
    s/[^\w\d]//gi;
    $_ = uc($_);
    $plays{$_}++;
	$play_names{$_}{$trackName} = 1;
}

my @list = map {[$plays{$_},[keys(%{$play_names{$_}})]]} keys(%plays);
my @other_list = sort{$a->[0] <=> $b->[0]} @list;
print $FH join("\n", map {$_->[0] . "\t=>\t" . "[". join(", ",@{$_->[1]}). ']'} @other_list),"\n";
close $FH;
