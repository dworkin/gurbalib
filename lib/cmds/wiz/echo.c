void usage() {
  write("Usage: echo [-h] [mesg]\n");
  write("Echo a message to the room.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str){
  if (!str || (str == "")) {
     usage();
     return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  this_player()->query_environment()->tell_room( this_player(), "\n" + str +
    "\n" );
  write( "You echo to the room: '" + str + "'.\n");
}
