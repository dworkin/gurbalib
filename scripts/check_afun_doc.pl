#!/usr/bin/perl

sub file_contains {
	my ($file, $line) = @_;

	my $tmp = `grep $line \"$file\"`;
	chomp $tmp;
	if ($tmp && (length($tmp) > 1)) {
		return 1;
	}
	return 0;
}

sub check_file {
	my ($file) = @_;
	foreach my $i ("NAME", "SYNOPSIS", "DESCRIPTION", "RETURN", 
		"EXAMPLES", "SEE") {
		if (!file_contains($file,$i)) {
			if ($i eq "SEE") {
				print("$file is missing SEE ALSO\n");
			} elsif ($i eq "RETURN") {
				print("$file is missing RETURN VALUES\n");
			} else {
				print("$file is missing $i\n");
			}
		}
	}
}

sub check_dir {
   my ($dir) = @_;
   my (@files, $fh, $x, $tmp, $test); 

   opendir($fh, $dir) or die "Unable to open $dir\n";;
   @files = readdir($fh);
   close $fh;

   foreach my $i (@files) {
      if ($i =~ /^.*\.c$/) {
         $x = length($i);
         $tmp = substr($i,0,$x-2);
         $test = "./lib/doc/afun/$tmp";

         if (-f $test) {
		check_file($test);
         } else {
            print "Warning no doc: $test\n";
         }
      }
   }
}

check_dir("./lib/kernel/lib/afun");
check_dir("./lib/kernel/lib/afun-game");
