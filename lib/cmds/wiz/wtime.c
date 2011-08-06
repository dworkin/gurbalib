void usage() {
  write("Usage: wtime [-h]\n");
  write("Show the game time.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also:date, time, status\n");
}

void main( string str ) {
  if (str && str != "") {
     usage();
     return;
  }

  write( TIME_D->query_time() );
}
