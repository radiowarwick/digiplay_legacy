#!/usr/bin/perlme = "";
#
#here is what you need to look up a barcode from the ldap directory:
# $ perl ./search-barcode.pl 0110284
# David Flynn
# $ echo >/dev/null <<EOF

use Net::LDAP;
use strict;
my $uname = $ARGV[0];
my $recordcount = 0;
my $name = "";
		
my $ldap = Net::LDAP->new("fs0", port => 389) or die "$@";

  my $mesg3 = $ldap->bind(version => 3);
  my $user1 = $_;
  my $result = $ldap->search (base => "ou=people,dc=radio,dc=warwick,dc=ac,dc=uk", scope => "sub",filter=>"uid=$uname",attrs => ['uid']);

  if ($result->count == 0) {
  	print "No results!\n";
  }
  else {
	  #die $mesg3->error if ($mesg3->code);
	  my $user = $_;
	  print $result->entry(0)->get_value("uid"),"\n";
  }
  
#if(!$mesg3->is_error()){
#    print "true";
#  } else {
#    print "false";
#    print $mesg3->error(),"\n";
#  }

$ldap->unbind();
