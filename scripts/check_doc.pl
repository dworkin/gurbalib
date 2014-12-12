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

	if ($Debug) {
		print "$subname: $file, $line\n";
	}

	my $tmp = `grep $line \"$file\"`;

	chomp $tmp;

	if ($tmp && (length($tmp) > 1)) {
		return 1;
	}
	return 0;
}

sub get_dir_info {
	my ($fullfilename) = @_;
	my (@values, $i, $t, $dir);
	my $subname = "get_dir_info";

	@values = split('/', $fullfilename);
	$i = $#values;

	$t = length($fullfilename) - length($values[$i]);

	$dir = substr($fullfilename, 0, $t);
	if ($Debug) {
		print "$subname: fullfilename = $fullfilename\n";
		print "$subname: i = $i t = $t dir = $dir\n";
		print "$subname: values[i] = $values[$i]\n";
	}

	return ($dir ,$values[$i -1], $values[$i]);
}

sub get_see_also {
	my ($filename) = @_;
	my ($fh, $seeit);
	my (@values, @tmp);
	my $subname = "get_see_also";

	@tmp = ();
	open($fh,"<", $filename) or die "Unable to open $filename\n";
	$seeit = 0;
	while(<$fh>) {
		my $line = $_;

		if ($seeit) {
			$line =~ s/\s+//g; # Filter out whitespace
			@tmp = split(",", $line);
			push(@values, @tmp);
			
		} else {
			if ($line =~ /(.*)SEE ALSO(.*)/) {
				$seeit = 1;
			}
		}
	}

	return @values;
}

sub check_seealso {
	my ($fullfile) = @_;
	my ($dir, $subdir, $file) = get_dir_info($fullfile);
	my $subname = "check_seealso";

	my @values = get_see_also($fullfile);

	if ($Debug) { 
	   print "$subname: $dir, $subdir, $file\n";
           print "Calling get_see_also($fullfile), got:\n";
		foreach my $i (@values) {
			print "\t$i\n";
		}
	}
	foreach my $i (@values) {
		my ($sd, $fn) = split('/', $i);

		if ($sd eq $subdir) {
			if (!-f "$dir/$fn") {
				print "$file, SEE ALSO: no such file $i\n";
			} else {
				if (!file_contains("$dir/$fn",
					"$subdir/$file")) {
					print "SEE ALSO: $i does not " .
						"reference $subdir/$file\n";
				}
			}
		}
	}
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
	check_seealso($file);
}

sub check_source_doc_match {
	my ($source, $docdir) = @_;
	my (@files, $fh, $tmp); 
	my $subname = "check_source_doc_match";

	opendir($fh, $source) or die "Unable to open $source\n";;
	@files = readdir($fh);
	close $fh;

	foreach my $i (@files) {
		my $tmp;

		if ($i eq ".." || $i eq ".") {
		} elsif (-f "$source/$i") {
			if ($i =~ /(.*)\.c/) {
				$tmp = $1;
			} else {
				$tmp = $i;
			}

			if (! -f "$docdir/$tmp") {
				print "Missing $docdir/$tmp\n";
			}
		} else {
			print "You should look at $source/$i\n";
		}
	}
}

sub check_dir {
	my ($dir) = @_;
	my (@files, $fh, $tmp); 
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

	my $dir = "./lib/doc/afun";
	my $source = "./lib/kernel/lib/afun";
	if (-d $dir) {
		check_source_doc_match($source, $dir);
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
