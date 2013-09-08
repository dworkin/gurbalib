#!/usr/bin/perl -w
my ($word);

sub makedir {
   my ($infile) = @_;

   if (!-d $infile) {
      mkdir($infile);
   }
   # Use this to test things and make sure .gitignores are used properly
   # system("touch $infile/blah");
}

if (!(-f "scripts/create_data_dirs.pl")) {
   print "Error I'm not in the right location.  You need to run this script\n";
   print "in the base directory gurablib.\n";
   print "\tcd to your gurbalib then type: scripts/create_data_dirs.pl\n";
   exit 1;
}

makedir("bin");
makedir("src");
makedir("backups");
makedir("tmp");
# Everything after here is in the actual mudlib
makedir("lib/daemons/data");
makedir("lib/data");
makedir("lib/data/messages");
makedir("lib/data/banished");
makedir("lib/data/banned");
makedir("lib/data/banned/a");
makedir("lib/data/banned/b");
makedir("lib/data/banned/c");
makedir("lib/data/players");
makedir("lib/data/mail");
if (-d "lib/domains/gurba") {
   makedir("lib/domains/gurba/data");
   makedir("lib/domains/gurba/data/boards");
   makedir("lib/domains/gurba/data/lockers");
}
if (-d "lib/domains/required") {
   makedir("lib/domains/required/data");
   makedir("lib/domains/required/data/boards");
}
makedir("lib/kernel/daemons/data");
makedir("lib/sys/daemons/data");
makedir("lib/sys/daemons/data/users");
makedir("lib/tmp");
makedir("lib/logs");
makedir("lib/logs/errors");
makedir("lib/logs/nobody");
makedir("lib/wiz");

if (!(-f "lib/daemons/data/emote_d.o")) {
   print "lib/daemons/data/emote_d.o does not exist, do you want to use " .
      "contrib/emote_d.o?  It has quite a few emotes.  If you say no here " .
      "you will get the default which only contains one emote.\n(Y/N) ?";
   chomp($word = <STDIN>);

   if ($word eq "y" || $word eq "Y") {
	system("cp contrib/emote_d.o lib/daemons/data/emote_d.o");
   }
}

if (!(-f "lib/data/messages/login")) {
   print "lib/data/messages/login does not exist, do you want to use " .
      "contrib/login?\nIf you say no here " .
      "you will need to create that file later.\n(Y/N) ?";
   chomp($word = <STDIN>);

   if ($word eq "y" || $word eq "Y") {
	system("cp contrib/login lib/data/messages/login");
   }
}

if (!(-f "lib/data/messages/motd")) {
   print "lib/data/messages/motd does not exist, do you want to use " .
      "contrib/motd?\nIf you say no here " .
      "you will need to create that file later.\n(Y/N) ?";
   chomp($word = <STDIN>);

   if ($word eq "y" || $word eq "Y") {
	system("cp contrib/motd lib/data/messages/motd");
   }
}
