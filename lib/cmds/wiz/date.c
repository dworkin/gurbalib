void usage() {
  write("Usage: date [-h]\n");
  write("Show the realworld date.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  if (str && str != "") {
     usage();
     return;
  }
  write( ctime( time() ) + "\n" );
}
