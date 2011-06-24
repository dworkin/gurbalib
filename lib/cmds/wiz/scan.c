void usage() {
  write("scan [-h] [object]\n");
  write("scan allows a wizard to show the inventory of an object/room.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string arg ) {
  object *objs;
  int i;

  write( "Scanning \"" + object_name( this_environment() ) + "\":" );
  objs = this_environment()->query_inventory();
  for( i = 0; i < sizeof( objs ); i ++ ) {
    write( "\"" + object_name(objs[i]) + "\"" );
  }
}
