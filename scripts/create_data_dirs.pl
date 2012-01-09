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
makedir("lib/sys/daemons/data/users/a");
makedir("lib/sys/daemons/data/users/b");
makedir("lib/sys/daemons/data/users/c");
makedir("lib/sys/daemons/data/users/d");
makedir("lib/sys/daemons/data/users/e");
makedir("lib/sys/daemons/data/users/f");
makedir("lib/sys/daemons/data/users/g");
makedir("lib/sys/daemons/data/users/h");
makedir("lib/sys/daemons/data/users/i");
makedir("lib/sys/daemons/data/users/j");
makedir("lib/sys/daemons/data/users/k");
makedir("lib/sys/daemons/data/users/l");
makedir("lib/sys/daemons/data/users/m");
makedir("lib/sys/daemons/data/users/n");
makedir("lib/sys/daemons/data/users/o");
makedir("lib/sys/daemons/data/users/p");
makedir("lib/sys/daemons/data/users/q");
makedir("lib/sys/daemons/data/users/r");
makedir("lib/sys/daemons/data/users/s");
makedir("lib/sys/daemons/data/users/t");
makedir("lib/sys/daemons/data/users/u");
makedir("lib/sys/daemons/data/users/v");
makedir("lib/sys/daemons/data/users/w");
makedir("lib/sys/daemons/data/users/x");
makedir("lib/sys/daemons/data/users/y");
makedir("lib/sys/daemons/data/users/z");
makedir("lib/sys/data");
makedir("lib/tmp");
makedir("lib/logs");
makedir("lib/logs/errors");
makedir("lib/wiz");

