void usage() {
  write("Usage: hp [-h]\n");
  write("A short way to display your current hit points.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  if (str && str != "") {
     usage();
     return;
  }

  write( "HP[" + this_player()->query_hp() + "/" 
	 + this_player()->query_max_hp() + "]" );
}
