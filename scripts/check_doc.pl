#!/usr/bin/perl

use strict;
use warnings;
use Getopt::Long;

my (%Options, $Debug);

sub usage {
	print "Usage: $0 [DIR | FILE]\n";
	print "Check the specified FILE or files in a DIR to see if they\n";
	print "are a decent man page.  If no DIR is specified run through\n";
	print "our default manpage directorys.\n";

	return 1;
}

sub file_contains {
	my ($file, $line) = @_;
	my $subname = "file_contains";

	my $tmp = `grep $line \"$file\"`;
	chomp $tmp;
	if ($tmp && (length($tmp) > 1)) {
		return 1;
	}
	return 0;
}

sub check_file {
	my ($file) = @_;
	my $subname = "check_file";

	foreach my $i ("NAME", "SYNOPSIS", "DESCRIPTION", "RETURN", 
		"EXAMPLES", "SEE") {
		if (!file_contains($file,$i)) {
			if ($i eq "SEE") {
				print("$file is missing SEE ALSO\n");
			} elsif ($i eq "RETURN") {
				print("$file is missing RETURN VALUE\n");
			} else {
				print("$file is missing $i\n");
			}
		}
	}
}

sub check_dir {
	my ($dir) = @_;
	my (@files, $fh, $x, $tmp, $test); 
	my $subname = "check_dir";

	opendir($fh, $dir) or die "Unable to open $dir\n";;
	@files = readdir($fh);
	close $fh;

	foreach my $i (@files) {
		if ($i eq "." || $i eq "..") {
		} elsif (-d "$dir/$i") {
			check_dir("$dir/$i");
		} else {
			check_file("$dir/$i");
		}
	}
}

&GetOptions(\%Options, "help", "debug");

my ($fname) = @ARGV;
if ($Options{"debug"}) {
	$Debug = 1;
}

if ($Options{"help"}) {
	usage();
} elsif (!$fname || $fname eq "") {
	# Run through our default checks here..
	# XXX Was previously looking to make sure each afun had a doc
	# Need to add that back in.

	my $dir = "lib/doc/afun";
	if (-d $dir) {
		check_dir($dir);
	} else {
		print "Unable to find $dir\n";
	}
	
} elsif (-d $fname) {
	check_dir($fname);
} elsif (-f $fname) {
	check_file($fname);
} else {
	usage();
}
