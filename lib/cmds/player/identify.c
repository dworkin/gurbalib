void usage() {
  write("Usage: identify [-h] OBJ\n");
  write("Closely inspect an object OBJ to see if there is any addition " +
    "information.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  object obj;
  object *wielded;

   if ( !str || str == "" ) {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  obj = this_player()->present( lowercase( str ) );
  if( !obj ) {
    write( "Maybe you should get one first?" );
    return;
  }
	
	if( obj->query_detailed_desc() ) {
		write( obj->query_detailed_desc() );
	} else {
		write( "You discover nothing special" );
	}
}
