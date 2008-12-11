#!/usr/bin/perl -T

# Note: this script should be run SUID so it has proper access to the filesystem.
# chmod 4755 this script.

use Digest::MD5;
use DBI;
use DBD::Pg;

my $webdir = "/usr/share/dps/www/DPS/uploads";
my $config_file = "/etc/digiplay.conf";
$ENV{'PATH'}='/bin:/usr/bin:/usr/local/bin';

# Check an uploaded file was specified
if (!defined($ARGV[0])) {
	print "noname_failed";
	exit;
}

# Untaint the uploaded filename
$ARGV[0] =~ m/^(.*)$/;
my $md5 = $1;

# Validate the file is a valid pcm file
# if it's not print the error string
my $result = validate_pcm("$webdir/$md5.wav");
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

# Connect to Database
my $db_connect = "dbi:Pg:dbname=$dbname;host=$dbhost;port=$dbport;";
my $dbh = DBI->connect($db_connect,"$dbuser","$dbpass") 
        || die "Cannot connect to database";

# Get name of the current audio archive
my $SQL = "SELECT val FROM configuration WHERE parameter=\'playin_archive\' AND location=-1;";
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
my $destarchive = $sth->fetchrow();

# Get location of audio inbox
my $SQL = "SELECT localpath FROM archives WHERE name=\'$destarchive\';";
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
my $inbox = $sth->fetchrow() . "inbox";

# Get the time imported and title for hashing
#my $importtime = time();
#open (INFO, "<$webdir/$webfile.info");
#while ($line = <INFO>) {
#	if ($line =~ m/^title: (.*)$/) { $title = trim($1);	}
#}
#close (INFO);
#my $hash_string = "$title,$webfile,web,$importtime";
#$ctx = Digest::MD5->new;
#$ctx->add($hash_string);
#$md5 = $ctx->hexdigest;

# Compute length of PCM data and untaint
my $length = `wc -c $webdir/$md5.wav` - 44;
if ($length =~ m/(.*)/) {
    $length2 = $1;
}

# Extract RAW PCM data to archive inbox
system "tail -c $length2 $webdir/$md5.wav > $inbox/$md5";

# Remove old wave file
system "rm $webdir/$md5.wav";

# Move info file to inbox
system "mv -i $webdir/$md5.info $inbox/$md5.info";
#print "done";
#exit;
# Upgrade info file to XML and import
system "dpsadmin --archive --upgrade $destarchive";
system "dpsadmin --music --import-md5 $md5 1>/dev/null";

# Get row index of new entry from database
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
#	my $datalength = ascii_to_hex(`head -c 44 $file | tail -c 4`);
#	my $filelength = sprintf("%x",`cat $file | wc -c` - 44);
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
#	if ($datalength ne $filelength) {
#		return "badsize_failed";
#		exit;
#	}
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
