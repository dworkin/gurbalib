void usage() {
  write("Usage: info [-h] OBJ\n");

  write("Get info about the object OBJ.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  object ob;

  if (!str || str == "") {
     usage();
     return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  write( "Object_name: " + this_player()->query_environment()->file_name() + 
    "\n" );
}
