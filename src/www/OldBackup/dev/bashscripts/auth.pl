#!/usr/bin/perlme = "";
# Script to authenticate users logging onto the website.
# Takes their username and password and also checks their rawMemberStatus.
# 21/02/2006

use Net::LDAP;
use strict;
my $uname = $ARGV[0];
my $pword = $ARGV[1];
my $recordcount = 0;
my $name = "";
my $server = 1;

my $basedn = "dc=radio,dc=warwick,dc=ac,dc=uk";

my $host1 = "192.168.1.81";
my $host2 = "192.168.1.3";
		
my $ldap = Net::LDAP->new($host1, port => 389);
# Check if the connection succeeded
if (!defined($ldap)) {
	#It didn't. Try doorlock.
	$ldap = Net::LDAP->new($host2, port => 389);
	if (defined($ldap)) {
		# Connected to doorlock's failsafe LDAP.
		$server = 2;
	} else {
		# Oh dear. That's not good.
		$server = -1;
	}
}

if (defined($ldap)) {

	# Bind to LDAP as the user attempting to authenticate using their credentials.
	my $mesg = $ldap->bind(
		dn       => "uid=$uname,ou=people,$basedn",
        	password => $pword
	);

	my $user = $_;
	
	if (!$mesg->is_error()) {
		# The bind succeeded, check the username and rawMemberStatus.
		my $filter = "(&(uid=$uname)(!(rawMemberStatus=Ex-Member)))";
		my $searchMesg = $ldap->search(base => $basedn, filter => $filter);
	
		if ($searchMesg->count == 1) {
			# Authenticated successfully.
			print "true";
		} else {
			# The user probably isn't a current member. Display a suitable message.
			print "false";
			print "You must be a current member in order to access this part of the site."
		}
	} else {
		# There was some error with the bind, probably invalid password.
		print "false";
		print $mesg->error();
	}
	$ldap->unbind();
} else {
	# Oh dear. That's not good. Best give up and not allow the user to log in then.
	print "false";
	print "The authentication server could not be contacted.";
}
