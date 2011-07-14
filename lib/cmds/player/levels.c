void usage() {
  write("Usage: levels [-h]\n");
  write("Displays a list of the various levels and requirements.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

// XXX add titles to the levels...
// and also add it to the exp increase level function...

void main( string str ) {
   string bar;
   int i,exp,maxi;
   mixed width;

   if (str && str != "") {
      usage();
      return;
   }

   write("LEVELS:");

   width = this_player()->query_env("width");
   maxi = intp(width);
   if (maxi < 2) maxi = DEFAULT_WIDTH;

   bar = "";
   for(i=0;i<maxi;i++) {
      bar += "-";
   }
   write(bar + "\n");

   for(i=1;i<=20;i++) {
      exp = i * i * 2000;
      write(i + "\tExp: " +  exp + "\n");
   }
}

