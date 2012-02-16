#!/usr/bin/perl -w

sub makedir {
   my ($infile) = @_;

   if (!-d $infile) {
      mkdir($infile);
   }
   # Use this to test things and make sure .gitignores are used properly
   # system("touch $infile/blah");
}

if (!-f "scripts/create_data_dirs.pl") {
   print "Error I'm not in the right location.  You need to run this script\n";
   print "in the base directory gurablib.\n";
   print "\tcd to your gurbalib then type: scripts/create_data_dirs.pl\n";
   exit 1;
}

makedir("bin");
makedir("tmp");
makedir("contrib/DGD/bin");
makedir("contrib/DGD/tmp");
# Everything after here is in the actual mudlib
makedir("lib/data/banished");
makedir("lib/data/banned");
makedir("lib/data/banned/a");
makedir("lib/data/banned/b");
makedir("lib/data/banned/c");
makedir("lib/data/players");
makedir("lib/domains/gurba/data");
makedir("lib/domains/gurba/data/boards");
makedir("lib/kernel/daemons/data");
makedir("lib/kernel/lib/net");
makedir("lib/sys/daemons/data");
makedir("lib/sys/daemons/data/users");
makedir("lib/sys/data");
makedir("lib/tmp");
makedir("lib/logs");
makedir("lib/logs/errors");
makedir("lib/wiz");

