void usage() {
  write("Usage: date [-h]\n");
  write("Show the date.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  write( ctime( time() ) + "\n" );
}
