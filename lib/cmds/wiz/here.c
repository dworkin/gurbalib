void usage() {
  write("Usage: here [-h]\n");
  write("Show the room's short description and filename.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {

  if (str && str != "") {
     usage();
     return;
  }

  write( this_environment()->query_brief() + ": [" + 
    this_environment()->file_name() + "]\n" );
}

