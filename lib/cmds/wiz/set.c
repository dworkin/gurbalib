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
  } else {
    if( sscanf( str, "%s %s", name, value ) != 2 ) {
      write( "Usage: set <variable> <value>\n" );
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
}
