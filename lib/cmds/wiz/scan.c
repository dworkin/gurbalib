void usage() {
  write("scan [-h]\n");
  write("Print a list of objects in the current room.\n");
// XXX make it so it supports [OBJ]
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  object *objs;
  int i;

  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  write( "Scanning \"" + object_name( this_environment() ) + "\":" );
  objs = this_environment()->query_inventory();
  for( i = 0; i < sizeof( objs ); i ++ ) {
    write( "\"" + object_name(objs[i]) + "\"" );
  }
}
