void usage() {
  write("Usage: here [-h]\n");
  write("Show the room's short descrition and filename.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string arg ) {

  if (str && str != "") {
     usage();
     return;
  }

  write( this_environment()->query_brief() + ": [" + 
    this_environment()->file_name() + "]\n" );
}

