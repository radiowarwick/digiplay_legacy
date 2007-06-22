#!/usr/bin/perl -T

use Digest::MD5;
use DBI;
use DBD::Pg;

my $webdir = "/var/www/DPS/uploads";
my $inbox = "/mnt/test-archive/audio/inbox";
my $config_file = "/etc/digiplay.conf";
$ENV{'PATH'}='/bin:/usr/bin:/usr/local/bin';

if (!defined($ARGV[0])) {
	print "noname_failed";
	exit;
}
$ARGV[0] =~ m/^(.*)$/;
my $webfile = $1;

my $result = validate_pcm("$webdir/$webfile");
if( $result ne "pcm") {
    print $result;
    exit;
}

# Read in digiplay configuration file and parse for database spec
open (CONFIG, "<$config_file");
while ($line = <CONFIG>) {
    if ($line =~ m/^DB_HOST=(.*)$/) { $dbhost = $1; }
    if ($line =~ m/^DB_PORT=(.*)$/) { $dbport = $1; }
    if ($line =~ m/^DB_NAME=(.*)$/) { $dbname = $1; }
    if ($line =~ m/^DB_USER=(.*)$/) { $dbuser = $1; }
    if ($line =~ m/^DB_PASS=(.*)$/) { $dbpass = $1; }
}
close (CONFIG);
my $db_connect = "dbi:Pg:dbname=$dbname;host=$dbhost;port=$dbport;";

# Get the time imported and title for hashing
my $importtime = time();
open (INFO, "<$webdir/$webfile.info");
while ($line = <INFO>) {
	if ($line =~ m/^title: (.*)$/) { $title = trim($1);	}
}
close (INFO);
my $hash_string = "$title,$webfile,web,$importtime";
$ctx = Digest::MD5->new;
$ctx->add($hash_string);
$md5 = $ctx->hexdigest;

my $length = `wc -c $webdir/$webfile` - 44;
# Untaint length
if ($length =~ m/(.*)/) {
    $length2 = $1;
}

system "tail -c $length2 $webdir/$webfile > $inbox/$md5";
system "rm $webdir/$webfile";

#system "mv -i $webdir/$webfile $inbox/$md5";
system "mv -i $webdir/$webfile.info $inbox/$md5.info";

system "dpsimport -m $md5 1>/dev/null";

my $dbh = DBI->connect($db_connect,"$dbuser","$dbpass") 
        || die "Cannot connect to database";
my $SQL = "SELECT id FROM audio WHERE md5=\'$md5\';";
my $sth = $dbh->prepare($SQL);
my $res = $sth->execute();
if (!$res) {
	print "query_failed";
	exit;
}
if ($sth->rows != 1) {
	print "rowcount_failed";
	exit;
}
@row = $sth->fetchrow();
print "@row";
exit;



# Validate the file is suitable PCM data
sub validate_pcm ($) {
	my $file = shift;
	my $container = `head -c 4 $file | cat -v`;
	my $format = ascii_to_hex(`head -c 22 $file | tail -c 2`);
	my $channels = ascii_to_hex(`head -c 23 $file | tail -c 1`);
	my $samplerate = ascii_to_hex(`head -c 28 $file | tail -c 4`);
	my $bits = ascii_to_hex(`head -c 35 $file | tail -c 1`);
	my $datalength = ascii_to_hex(`head -c 44 $file | tail -c 4`);
	my $filelength = sprintf("%x",`cat $file | wc -c` - 44);
	# First check we've actually got a RIFF Wav container
	if ($container ne "RIFF") {
		return "notwave_failed";
		exit;
	}
	# Now check that the contents is PCM audio
	if ($format ne "01") {
		return "notpcm_failed";
		exit;
	}
	# Check the parameters of the PCM audio are compatible
	# Must have 16bit, 44100, Stereo
	if ($channels ne "02") {
		return "badchannels_failed";
		exit;
	}
	if ($bits ne "10") {
		return "badbit_failed";
		exit;
	}
	if ($samplerate ne "ac44") {
		return "badsample_failed";
		exit;
	}
	# Finally check the file isn't corrupted by analysing the data block size
	if ($datalength ne $filelength) {
		return "badsize_failed";
		exit;
	}
	return "pcm";
}

# trim whitespace from ends of string function
sub trim($) {
    my $string = shift;
    $string =~ s/^\s+//;
    $string =~ s/\s+$//;
    return $string;
}

## Convert each ASCII character to a two-digit hex number and reverse to
## be compatible with perl hex function. Removes leading 00's
sub ascii_to_hex ($) {
   	(my $str = shift) =~ s/(.|\n)/sprintf("%02lx", ord $1)/eg;
	my $hex_val;
	my $next_symbol;
	for ($i = 0; $i < length($str); $i=$i+2) {
		$next_symbol = substr($str,length($str)-$i-2,2);
		if ($next_symbol eq "00" && $hex_val eq "") {
			next;
		}
		$hex_val = $hex_val . $next_symbol;
	}
   	return $hex_val;
}
