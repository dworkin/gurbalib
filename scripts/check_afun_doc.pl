#!/usr/bin/perl

my (@files, $fh, $x, $tmp, $test); 
my $DIR = "./lib/kernel/lib/afun";

opendir($fh, $DIR) or die "Unable to open $DIR\n";;
@files = readdir($fh);
close $fh;

foreach my $i (@files) {
	if ($i =~ /^.*\.c$/) {
	   $x = length($i);
           $tmp = substr($i,0,$x-2);
	   $test = "./lib/doc/afun/$tmp";
	   if (-f "./lib/doc/afun/$tmp") {
	   } else {
		print "Warning no doc: $test\n";
           }
        }
}
