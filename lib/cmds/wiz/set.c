void usage() {
  write("Usage: set [-h] [VAR VALUE]\n");
  write("Set an environment varilable VAR to VALUE.\n");
  write("If no VAR VALUE pair is given print your current environment.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: unset\n");
}

void main( string str ) {
  string *names;
  string name;
  string value;
  int i;

  if( !str || str == "" ) {
    /* Print out the list */
    names = this_player()->query_env_indices();
    for( i = 0; i < sizeof( names ); i++ ) {
      out_unmod( names[i] + "=" + this_player()->query_env( names[i] ) + "\n" ); 
    }
  } else if (sscanf(str, "-%s",str)) {
     usage();
     return;
  } else if( sscanf( str, "%s %s", name, value ) != 2 ) {
      usage();
      return;
  } else {
      if( str2val( value ) != -1 ) {
	/* We've got a value */
	this_player()->set_env( name, str2val(value) );
      } else {
	this_player()->set_env( name, value );
      }
  }
}
