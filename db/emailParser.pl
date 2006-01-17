#!/usr/bin/perl

use Mail::Internet;
use DBI;
use DBD::Pg;

my $email = Mail::Internet->new( [ <STDIN> ] );
my $subject = $email->head->get("Subject");
my $from = $email->head->get("From");
my $body_arr = $email->body();
my $rec = time();

open (CONFIG, '</etc/digiplay.conf');
while ($line = <CONFIG>) {
#	print $line;
	if ($line =~ m/^DB_HOST=(.*)$/) {
		$dbhost=$1;
#		print "Woohoo\n";
	}
        if ($line =~ m/^DB_NAME=(.*)$/) {
                $dbname=$1;
#                print "Woohoo\n";
        }

        if ($line =~ m/^DB_USER=(.*)$/) {
	        $dbuser=$1;
#	        print "Woohoo\n";
	}
        if ($line =~ m/^DB_PASS=(.*)$/) {
                $dbpass=$1;
#                print "Woohoo\n";
        }
}
close (CONFIG);

#print "$dbhost\n";
#print "$dbname\n";
#print "$dbuser\n";
#print "$dbpass\n";

$count = @$body_arr;

for ($i = 0; $i<$count; $i++)  {
	$body = $body . $$body_arr[$i]
}

#print "Lines: $count\nBody: $body\n";
#print @body
$body =~ s/\'/\\\'/g;
$dbh = DBI->connect("dbi:Pg:dbname=$dbname;host=$dbhost;port=5432;", "$dbuser", "$dbpass", {AutoCommit => 1 });

#$SQL="INSERT INTO email (sender,subject,body,new_flag,datetime) VALUES ('$from','$subject','$body', 't', '$rec')";

$sth = $dbh->prepare("INSERT INTO email (sender,subject,body,new_flag,datetime) VALUES ('$from','$subject','$body', 't', '$rec');");
#print $SQL;

$sth->execute();
#$dbh->commit;
