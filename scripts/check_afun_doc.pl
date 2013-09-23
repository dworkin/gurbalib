#!/usr/bin/perl

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

         if (-f "./lib/doc/afun/$tmp") {
         } else {
            print "Warning no doc: $test\n";
         }
      }
   }
}

check_dir("./lib/kernel/lib/afun");
check_dir("./lib/kernel/lib/afun-game");
